#include "jrst_private.h"

//list of buffers
static rst_buffer_t **buffers = NULL;
static int size = 0;
static int used = 0;

//the loader and monitor buffer
static rst_buffer_t *ptr_loader = NULL;
static rst_buffer_t *ptr_monitor = NULL;

//this should be called only in VMDeath, because of the free below
void trace_finalize_buffers (void)
{
  if (ptr_monitor != NULL){
    rst_finalize_ptr (ptr_monitor);
  }

  if (ptr_loader != NULL){
    rst_finalize_ptr (ptr_loader);
  }

  int i;
  for (i = 0; i < used; i++){
    if (buffers[i] != NULL){
      rst_event_ptr(buffers[i], JRST_THREAD_END);
      rst_finalize_ptr(buffers[i]);
    }
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

  rst_event_isiii_ptr(ptr, JRST_INITIALIZE, (int) threadId, name,
                      (int) infoThread.priority,
                      (int) infoThread.is_daemon,
                      (int) infoThread.thread_group);

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


#define THREAD_MONITOR 4321
void trace_event_object_free(jlong tag)
{
  jrst_enter_critical_section(GET_JVMTI(), jrst->monitor_buffer);
  if (ptr_monitor == NULL) {
    ptr_monitor = (rst_buffer_t *) malloc(sizeof(rst_buffer_t));
    rst_init_ptr(ptr_monitor,
                 (u_int64_t) jrst_jvmid,
                 (u_int64_t) THREAD_MONITOR);
  }
  rst_event_i_ptr(ptr_monitor, JVMTI_EVENT_OBJECT_FREE, (int) tag);
  jrst_exit_critical_section(GET_JVMTI(), jrst->monitor_buffer);
}

void trace_event_gc_start()
{
  jrst_enter_critical_section(GET_JVMTI(), jrst->monitor_buffer);
  if (ptr_monitor == NULL) {
    ptr_monitor = (rst_buffer_t *) malloc(sizeof(rst_buffer_t));
    rst_init_ptr(ptr_monitor,
                 (u_int64_t) jrst_jvmid,
                 (u_int64_t) THREAD_MONITOR);
  }
  rst_event_ptr(ptr_monitor, JVMTI_EVENT_GARBAGE_COLLECTION_START);
  jrst_exit_critical_section(GET_JVMTI(), jrst->monitor_buffer);
}

void trace_event_gc_finish()
{
  jrst_enter_critical_section(GET_JVMTI(), jrst->monitor_buffer);
  rst_event_ptr(ptr_monitor, JVMTI_EVENT_GARBAGE_COLLECTION_FINISH);
  jrst_exit_critical_section(GET_JVMTI(), jrst->monitor_buffer);
}
#undef THREAD_MONITOR

void trace_event_monitor_contended_enter(jvmtiEnv * jvmtiLocate,
                                         jthread thread,
                                         int object)
{
  rst_buffer_t *ptr;
  jvmtiError error;

  jrst_enter_critical_section(GET_JVMTI(), jrst->monitor_thread);

  error =
    (*GET_JVMTI())->GetThreadLocalStorage(GET_JVMTI(), thread,
                                          (void **) &ptr);
  if (ptr == NULL) {
    jrst_exit_critical_section(GET_JVMTI(), jrst->monitor_thread);
    return;
  }

  rst_event_i_ptr(ptr, JRST_MONITOR_ENTER, object);

  jrst_exit_critical_section(GET_JVMTI(), jrst->monitor_thread);
}

void trace_event_monitor_contended_entered(jvmtiEnv * jvmtiLocate,
                                           jthread thread,
                                           int object)
{
  rst_buffer_t *ptr;
  jvmtiError error;

  jrst_enter_critical_section(GET_JVMTI(), jrst->monitor_thread);

  error =
    (*GET_JVMTI())->GetThreadLocalStorage(GET_JVMTI(), thread,
                                          (void **) &ptr);
  if (ptr == NULL) {
    jrst_exit_critical_section(GET_JVMTI(), jrst->monitor_thread);
    return;
  }

  rst_event_i_ptr(ptr, JRST_MONITOR_ENTERED, object);

  jrst_exit_critical_section(GET_JVMTI(), jrst->monitor_thread);
}

void trace_event_monitor_wait(jvmtiEnv * jvmtiLocate, jthread thread,
                              int object)
{
  rst_buffer_t *ptr;
  jvmtiError error;

  jrst_enter_critical_section(GET_JVMTI(), jrst->monitor_thread);

  error =
    (*GET_JVMTI())->GetThreadLocalStorage(GET_JVMTI(),
                                          thread,
                                          (void **) &ptr);
  if (ptr == NULL) {
    jrst_exit_critical_section(GET_JVMTI(), jrst->monitor_thread);
    return;
  }

  rst_event_i_ptr(ptr, JRST_MONITOR_WAIT, object);

  jrst_exit_critical_section(GET_JVMTI(), jrst->monitor_thread);
}

void trace_event_monitor_waited(jvmtiEnv * jvmtiLocate, jthread thread,
                                int object)
{
  rst_buffer_t *ptr;
  jvmtiError error;

  jrst_enter_critical_section(GET_JVMTI(), jrst->monitor_thread);

  error =
    (*GET_JVMTI())->GetThreadLocalStorage(GET_JVMTI(),
                                          thread,
                                          (void **) &ptr);
  if (ptr == NULL) {
    jrst_exit_critical_section(GET_JVMTI(), jrst->monitor_thread);
    return;
  }

  rst_event_i_ptr(ptr, JRST_MONITOR_WAITED, object);

  jrst_exit_critical_section(GET_JVMTI(), jrst->monitor_thread);
}
