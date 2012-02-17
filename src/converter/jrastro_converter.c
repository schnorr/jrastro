#include "jrastro_private.h"

static char doc[] = "Converts jrastro trace files to the Paje file format";
static char args_doc[] = "{rastro-0-0.rst rastro-1-0.rst ...}";

static struct argp_option options[] = {
  /* {"ignore-errors", 'i', 0, OPTION_ARG_OPTIONAL, "Ignore aky errors"}, */
  /* {"no-links", 'l', 0, OPTION_ARG_OPTIONAL, "Don't convert links"}, */
  /* {"no-states", 's', 0, OPTION_ARG_OPTIONAL, "Don't convert states"}, */
  {"basic", 'b', 0, OPTION_ARG_OPTIONAL, "Avoid extended events (impoverished trace file)"},
  {"sync", 'z', "SYNC_FILE", 0, "Synchronization file (from rastro_timesync)"},
  {"comment", 'm', "COMMENT", 0, "Comment is echoed to output"},
  {"commentfile", 'n', "FILE", 0, "Comments (from file) echoed to output"},
  { 0 }
};

struct arguments {
  char *input[JRST_INPUT_SIZE];
  int input_size;
  int basic;
  char *synchronization_file;
  char *comment;
  char *comment_file;
};

static int parse_options (int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;
  switch (key){
  case 'b': arguments->basic = 1; break;
  case 'z': arguments->synchronization_file = arg; break;
  case 'm': arguments->comment = arg; break;
  case 'n': arguments->comment_file = arg; break;
  case ARGP_KEY_ARG:
    if (arguments->input_size == JRST_INPUT_SIZE) {
      /* Too many arguments. */
      argp_usage (state);
    }
    arguments->input[state->arg_num] = arg;
    arguments->input_size++;
    break;
  case ARGP_KEY_END:
    if (state->arg_num < 1)
      /* Not enough arguments. */
      argp_usage (state);
    break;
  default: return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = { options, parse_options, args_doc, doc };

static int dump_commented_file (char *filename)
{
  FILE *file = fopen (filename, "r");
  if (file == NULL){
    fprintf(stderr,
            "[jrastro_converter] at %s,\n"
            "comment file %s could not be opened for reading\n",
            __FUNCTION__, filename);
    return 1;
  }
  while (!feof(file)){
    char c;
    c = fgetc(file);
    if (feof(file)) break;
    printf ("# ");
    while (c != '\n'){
      printf ("%c", c);
      c = fgetc(file);
      if (feof(file)) break;
    }
    printf ("\n");
  }
  fclose(file);
  return 0;
}


int main (int argc, char **argv)
{
  struct arguments arguments;
  bzero (&arguments, sizeof(struct arguments));
  if (argp_parse (&argp, argc, argv, 0, 0, &arguments) == ARGP_KEY_ERROR){
    fprintf(stderr,
            "[jrastro_converter] at %s, "
            "error during the parsing of parameters\n",
            __FUNCTION__);
    return 1;
  }


  rst_rastro_t rastro;
  bzero (&rastro, sizeof(rst_rastro_t));
  rst_event_t event;
  int i;
  int fail = 0;

  for (i = 0; i < arguments.input_size; i++){
    int ret = rst_open_file(&rastro, 100000,
                            arguments.input[i],
                            arguments.synchronization_file);
    if (ret == -1) {
      fprintf(stderr,
              "[jrastro_converter] at %s, "
              "trace file %s could not be opened\n",
              __FUNCTION__, arguments.input[i]);
      return 1;
    }
  }

  if (arguments.comment){
    printf ("# %s\n", arguments.comment);
  }
  if (arguments.comment_file){
    if (dump_commented_file (arguments.comment_file) == 1){
      return 1;
    }
  }

  /* output build version, date and conversion for aky in the trace */
  printf ("#JRST_GIT_VERSION %s\n", GITVERSION);
  printf ("#JRST_GIT_DATE (date of the cmake configuration) %s\n", GITDATE);
  {
    printf ("#JRST_CONVERSION: ");
    int i;
    for (i = 0; i < argc; i++){
      printf ("%s ", argv[i]);
    }
    printf ("\n");
  }
  /* output contents of synchronization file if used */
  if (arguments.synchronization_file){
    if (dump_commented_file (arguments.synchronization_file) == 1){
      return 1;
    }
  }

  /* start trace generation */
  paje_header(arguments.basic);
  paje_hierarchy();

  while (rst_decode_event(&rastro, &event) && !fail) {
    char container[100];
    snprintf(container, 100, "t%ld", event.id2);
    double timestamp = event.timestamp;
    switch (event.type) {
    case JRST_THREAD_START:
      pajeCreateContainer(timestamp, container, "THREAD", "root", container);
      break;
    case JRST_THREAD_END:
      pajeDestroyContainer(timestamp, "THREAD", container);
      break;
    case JRST_MONITOR_ENTER:
    case JRST_MONITOR_ENTERED:
    case JRST_MONITOR_WAIT:
    case JRST_MONITOR_WAITED:
      break;
    case JRST_METHOD_ENTRY:
      {
        char *method_name = event.v_string[0];
        pajePushState(timestamp, container, "STATE", method_name);
      }
      break;
    case JRST_METHOD_EXIT:
      {
        pajePopState(timestamp, container, "STATE");
      }
      break;
    case JRST_METHOD_EXCEPTION:
    case JRST_METHOD_EXIT_EXCEPTION:
    case JRST_METHOD_LOAD:
    case JRST_CLASS_LOAD:
    default:
      break;
    }
  }
}
