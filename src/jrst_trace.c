#include "jrst_private.h"

//list of buffers
static rst_buffer_t **buffers = NULL;
static int size = 0;
static int used = 0;

//this should be called only in VMDeath, because of the free below
void trace_flush_buffers (void)
{
  int i;
  for (i = 0; i < used; i++){
    rst_flush (buffers[i]);
    rst_finalize_ptr (buffers[i]);
  }
  free (buffers);
  size = used = 0;
}

void trace_initialize(jvmtiEnv * jvmtiLocate, jthread thread, char *name)
{
  static unsigned long long threadId = 0;
  rst_buffer_t *ptr;
  jvmtiThreadInfo infoThread;
  jvmtiError error;

  //allocate space for keep pointers to all buffers
  if (buffers == NULL){
    size = 2;
    buffers = (rst_buffer_t**) malloc (size * sizeof(rst_buffer_t*));
  }

  if (used+1 > size){
    size = size * 2;
    buffers = (rst_buffer_t**) realloc (buffers,
                                        size * sizeof(rst_buffer_t*));
  }

  //allocate one buffer
  ptr = (rst_buffer_t *) malloc(sizeof(rst_buffer_t));

  //put it in the list of buffers
  buffers[used++] = ptr;

  jrst_enter_critical_section(jvmtiLocate, jrst->monitor_thread);
  error = (*jvmtiLocate)->GetThreadInfo(jvmtiLocate, thread, &infoThread);
  jrst_check_error(jvmtiLocate, error, "Cannot get Thread Info");

  rst_init_ptr(ptr,
               (u_int64_t) jrst_jvmid,
               (u_int64_t) threadId++);

  /* rst_event_isiii_ptr(ptr, INITIALIZE, (int) threadId, name, */
  /*                     (int) infoThread.priority, */
  /*                     (int) infoThread.is_daemon, */
  /*                     (int) infoThread.thread_group); */

  error = (*jvmtiLocate)->SetThreadLocalStorage(jvmtiLocate, thread, (void *) ptr);
  jrst_check_error(jvmtiLocate, error, "Cannot Set Thread Local Storage");
  jrst_exit_critical_section(jvmtiLocate, jrst->monitor_thread);

  error = (*jvmtiLocate)->Deallocate(jvmtiLocate, (unsigned char *) infoThread.name);
  jrst_check_error(jvmtiLocate, error, "Cannot deallocate memory");
}

void trace_finalize(jvmtiEnv * jvmtiLocate, jthread thread)
{
  rst_buffer_t *ptr;
  jvmtiError error;

  jrst_enter_critical_section(jvmtiLocate, jrst->monitor_thread);

  error =
    (*jvmtiLocate)->GetThreadLocalStorage(jvmtiLocate, thread,
                                          (void **) &ptr);
  if (ptr == NULL) {
    printf ("=> error\n");
    jrst_check_error(jvmtiLocate, error, "Cannot deallocate memory");
    jrst_exit_critical_section(jvmtiLocate, jrst->monitor_thread);
    return;
  }

  rst_event_ptr(ptr, JRST_FINALIZE);
  rst_finalize_ptr(ptr);

  error =
    (*jvmtiLocate)->SetThreadLocalStorage(jvmtiLocate, thread, NULL);
  jrst_check_error(jvmtiLocate, error,
                   "Cannot Set Thread Local Storage");

  jrst_exit_critical_section(jvmtiLocate, jrst->monitor_thread);
}
