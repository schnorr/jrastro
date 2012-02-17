/*
    This file is part of jrastro.

    jrastro is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    jrastro is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
    for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with jrastro; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02111 USA.
*/
#include "jrst_private.h"

//list of buffers
static rst_buffer_t **buffers = NULL;
static int size = 0;
static int used = 0;

//the loader and monitor buffer
static rst_buffer_t *ptr_loader = NULL;
static rst_buffer_t *ptr_monitor = NULL;

//this should be called only during agent depth (UnLoad)
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

void trace_thread_start (jvmtiEnv * jvmti, jthread thread, char *name)
{
  static unsigned long long counter = 0;
  MONITOR_ENTER(jrst->monitor_thread);

  //allocate the buffer to keep this thread's events
  rst_buffer_t *ptr = (rst_buffer_t *) malloc(sizeof(rst_buffer_t));

  //set the buffer to the local storage of this thread
  SET_BUFFER(ptr);

  //rastro init, and first event
  rst_init_ptr(ptr,
               (u_int64_t) jrst_jvmid,
               (u_int64_t) counter);
  rst_event_s_ptr(ptr, JRST_THREAD_START, name);

  //book-keeping of all buffers to flush them at the end
  if (buffers == NULL){
    size = 2;
    buffers = (rst_buffer_t**) malloc (size * sizeof(rst_buffer_t*));
  }
  if (used+1 > size){
    size = size * 2;
    buffers = (rst_buffer_t**) realloc (buffers,
                                        size * sizeof(rst_buffer_t*));
  }

  //place this thread's buffer in the index position of buffers
  buffers[counter] = ptr;

  //buffers population has increased
  used++;

  //increment the thread counter for the next one
  counter++;

  MONITOR_EXIT(jrst->monitor_thread);
}

void trace_thread_end (jvmtiEnv * jvmti, jthread thread, char *name)
{
  MONITOR_ENTER(jrst->monitor_thread);
  rst_buffer_t *ptr = NULL;
  GET_BUFFER(ptr);
  buffers[ptr->id2] = NULL;
  if (ptr != NULL){
    rst_event_ptr(ptr, JRST_THREAD_END);
    rst_finalize_ptr(ptr);
  }
  SET_BUFFER(NULL);



  MONITOR_EXIT(jrst->monitor_thread);
}

void trace_event_object_free(jlong tag)
{
  MONITOR_ENTER(jrst->monitor_buffer);
  if (ptr_monitor == NULL) {
    ptr_monitor = (rst_buffer_t *) malloc(sizeof(rst_buffer_t));
    rst_init_ptr(ptr_monitor,
                 (u_int64_t) jrst_jvmid,
                 (u_int64_t) THE_MONITOR_THREAD);
  }
  rst_event_i_ptr(ptr_monitor, JVMTI_EVENT_OBJECT_FREE, (int) tag);
  MONITOR_EXIT(jrst->monitor_buffer);
}

void trace_event_gc_start()
{
  MONITOR_ENTER(jrst->monitor_buffer);
  if (ptr_monitor == NULL) {
    ptr_monitor = (rst_buffer_t *) malloc(sizeof(rst_buffer_t));
    rst_init_ptr(ptr_monitor,
                 (u_int64_t) jrst_jvmid,
                 (u_int64_t) THE_MONITOR_THREAD);
  }
  rst_event_ptr(ptr_monitor, JRST_GC_START);
  MONITOR_EXIT(jrst->monitor_buffer);
}

void trace_event_gc_finish()
{
  MONITOR_ENTER(jrst->monitor_buffer);
  rst_event_ptr(ptr_monitor, JRST_GC_FINISH);
  MONITOR_EXIT(jrst->monitor_buffer);
}

void trace_event_monitor_contended_enter(jvmtiEnv * jvmti,
                                         jthread thread,
                                         int object)
{
  MONITOR_ENTER(jrst->monitor_thread);
  rst_buffer_t *ptr = NULL;
  GET_BUFFER(ptr);
  if (ptr != NULL){
    rst_event_i_ptr(ptr, JRST_MONITOR_ENTER, object);
  }
  MONITOR_EXIT(jrst->monitor_thread);
}

void trace_event_monitor_contended_entered(jvmtiEnv * jvmti,
                                           jthread thread,
                                           int object)
{
  MONITOR_ENTER(jrst->monitor_thread);
  rst_buffer_t *ptr = NULL;
  GET_BUFFER(ptr);
  if (ptr != NULL){
    rst_event_i_ptr(ptr, JRST_MONITOR_ENTERED, object);
  }
  MONITOR_EXIT(jrst->monitor_thread);
}

void trace_event_monitor_wait(jvmtiEnv * jvmti, jthread thread,
                              int object)
{
  MONITOR_ENTER(jrst->monitor_thread);
  rst_buffer_t *ptr = NULL;
  GET_BUFFER(ptr);
  if (ptr != NULL){
    rst_event_i_ptr(ptr, JRST_MONITOR_WAIT, object);
  }
  MONITOR_EXIT(jrst->monitor_thread);
}

void trace_event_monitor_waited(jvmtiEnv * jvmti, jthread thread,
                                int object)
{
  MONITOR_ENTER(jrst->monitor_thread);
  rst_buffer_t *ptr = NULL;
  GET_BUFFER(ptr);
  if (ptr != NULL){
    rst_event_i_ptr(ptr, JRST_MONITOR_WAITED, object);
  }
  MONITOR_EXIT(jrst->monitor_thread);
}


void trace_event_method_entry(jthread thread, char *method_name)
{
  MONITOR_ENTER(jrst->monitor_thread);
  rst_buffer_t *ptr = NULL;
  GET_BUFFER(ptr);
  if (ptr != NULL){
    rst_event_s_ptr(ptr, JRST_METHOD_ENTRY, method_name);
  }
  MONITOR_EXIT(jrst->monitor_thread);
}

;
void trace_event_method_exit(jthread thread, char *method_name)
{
  MONITOR_ENTER(jrst->monitor_thread);
  rst_buffer_t *ptr = NULL;
  GET_BUFFER(ptr);
  if (ptr != NULL){
    rst_event_s_ptr(ptr, JRST_METHOD_EXIT, method_name);
  }
  MONITOR_EXIT(jrst->monitor_thread);
}

void trace_event_exception(jthread thread, int exception)
{
  MONITOR_ENTER(jrst->monitor_thread);
  rst_buffer_t *ptr = NULL;
  GET_BUFFER(ptr);
  if (ptr != NULL){
    rst_event_i_ptr(ptr, JRST_METHOD_EXCEPTION, exception);
  }
  MONITOR_EXIT(jrst->monitor_thread);
}

void trace_event_method_exit_exception(jthread thread)
{
  MONITOR_ENTER(jrst->monitor_thread);
  rst_buffer_t *ptr = NULL;
  GET_BUFFER(ptr);
  if (ptr != NULL){
    rst_event_ptr(ptr, JRST_METHOD_EXIT_EXCEPTION);
  }
  MONITOR_EXIT(jrst->monitor_thread);
}

void trace_event_method_load(int method, char *name, unsigned access_flags,
                             int klass)
{
  rst_event_isii_ptr(ptr_loader, JRST_METHOD_LOAD, method, name, klass,
                     access_flags);
}

void trace_event_class_load(int klass, char *name)
{
  if (ptr_loader == NULL) {
    ptr_loader = (rst_buffer_t *) malloc(sizeof(rst_buffer_t));
    rst_init_ptr(ptr_loader,
                 (u_int64_t) jrst_jvmid,
                 (u_int64_t) THE_LOADER_THREAD);
  }
  rst_event_is_ptr(ptr_loader, JRST_CLASS_LOAD, klass, name);
}
