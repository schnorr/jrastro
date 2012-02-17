#include "jrst_private.h"

#define _GNU_SOURCE
#define __USE_GNU
#include <search.h>

static struct hsearch_data classes;
static struct hsearch_data methods;

typedef enum {
  ParseStart,
  ParseClass,
  ParseMethod,
}ParseState;

void jrst_filter_init (void)
{
  char *filename = getenv ("JRST_FILTER");
  if (!filename) {
    return;
  }

  FILE *file = fopen (filename, "r");
  if (!file){
    return;
  }

  hcreate_r (1000, &classes);
  hcreate_r (1000, &methods);

  char p1[JRST_MAX_STRING];
  ParseState state = ParseStart;
  while (!feof(file)){
    fscanf (file, "%s", p1);
    switch (state){
    case ParseStart:
      switch (p1[0]){
      case 'C': state = ParseClass; break;
      case 'M': state = ParseMethod; break;
      }
      break;
    case ParseClass:
      {
        ENTRY e, *ep = NULL;
        e.key = p1;
        e.data = NULL;
        hsearch_r (e, FIND, &ep, &classes);
        if (ep == NULL){
          e.key = strdup (p1);
          e.data = NULL;
          hsearch_r (e, ENTER, &ep, &classes);
        }
      }
      state = ParseStart;
      break;
    case ParseMethod:
      {
        ENTRY e, *ep = NULL;
        e.key = p1;
        e.data = NULL;
        hsearch_r (e, FIND, &ep, &methods);
        if (ep == NULL){
          e.key = strdup (p1);
          e.data = NULL;
          hsearch_r (e, ENTER, &ep, &methods);
        }
      }
      state = ParseStart;
      break;
    }     
  }
  fclose(file);
}

void jrst_filter_finalize (void)
{
  hdestroy_r (&classes);
  hdestroy_r (&methods);
}

int jrst_filtered (char *classname, char *methodname)
{
  int ret = 1;

  ENTRY e, *ep = NULL;
  e.key = classname;
  e.data = NULL;
  hsearch_r (e, FIND, &ep, &classes);
  if (ep != NULL){
    ret = 0;
  }

  e.key = methodname;
  e.data = NULL;
  hsearch_r (e, FIND, &ep, &methods);
  if (ep != NULL){
    ret = 0;
  }

  return ret;
}
