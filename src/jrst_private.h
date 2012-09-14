/*
    This file is part of JRastro.

    JRastro is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    JRastro is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with JRastro.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __JRASTRO_PRIVATE_
#define __JRASTRO_PRIVATE_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jvmti.h>
#include <jni.h>
#include <jvmti.h>
#include <rastro.h>
#include <jrastro.h>
#include "jrst_functions.h"

typedef struct {
  jvmtiEnv *jvmti;
  jrawMonitorID monitor;
  jrawMonitorID monitor_thread;
  jrawMonitorID monitor_buffer;
  jrawMonitorID monitor_new_array;
  jrawMonitorID monitor_tag;

  //tracing configuration
  int thread_tracing;
  int method_tracing;
  int monitor_tracing;
  int gc_tracing;
} jrst_agent;

extern jrst_agent *jrst;
extern unsigned long long jrst_jvmid;

#define GET_JVMTI() (jrst->jvmti)
#define MONITOR_ENTER(monitor) (*GET_JVMTI())->RawMonitorEnter(GET_JVMTI(), monitor)
#define MONITOR_EXIT(monitor) (*GET_JVMTI())->RawMonitorExit(GET_JVMTI(), monitor)
#define GET_BUFFER(ptr) (*GET_JVMTI())->GetThreadLocalStorage(GET_JVMTI(), thread, (void **) &ptr)
#define SET_BUFFER(ptr) (*GET_JVMTI())->SetThreadLocalStorage(GET_JVMTI(), thread, ptr)

#define JRST_MAX_STRING 1000
#define JRST_MAX_THREAD_NAME JRST_MAX_STRING
#define THE_MONITOR_THREAD 5000
#define THE_LOADER_THREAD  5001

//callbacks prototypes
void JNICALL jrst_EventBreakpoint
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread,
     jmethodID method,
     jlocation location);

void JNICALL jrst_EventClassFileLoadHook
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jclass class_being_redefined,
     jobject loader,
     const char* name,
     jobject protection_domain,
     jint class_data_len,
     const unsigned char* class_data,
     jint* new_class_data_len,
     unsigned char** new_class_data);

void JNICALL jrst_EventClassLoad
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread,
     jclass klass);

void JNICALL jrst_EventClassPrepare
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread,
     jclass klass);

void JNICALL jrst_EventCompiledMethodLoad
    (jvmtiEnv *jvmti_env,
     jmethodID method,
     jint code_size,
     const void* code_addr,
     jint map_length,
     const jvmtiAddrLocationMap* map,
     const void* compile_info);

void JNICALL jrst_EventCompiledMethodUnload
    (jvmtiEnv *jvmti_env,
     jmethodID method,
     const void* code_addr);

void JNICALL jrst_EventDataDumpRequest
    (jvmtiEnv *jvmti_env);

void JNICALL jrst_EventDynamicCodeGenerated
    (jvmtiEnv *jvmti_env,
     const char* name,
     const void* address,
     jint length);

void JNICALL jrst_EventException
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread,
     jmethodID method,
     jlocation location,
     jobject exception,
     jmethodID catch_method,
     jlocation catch_location);

void JNICALL jrst_EventExceptionCatch
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread,
     jmethodID method,
     jlocation location,
     jobject exception);

void JNICALL jrst_EventFieldAccess
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread,
     jmethodID method,
     jlocation location,
     jclass field_klass,
     jobject object,
     jfieldID field);

void JNICALL jrst_EventFieldModification
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread,
     jmethodID method,
     jlocation location,
     jclass field_klass,
     jobject object,
     jfieldID field,
     char signature_type,
     jvalue new_value);

void JNICALL jrst_EventFramePop
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread,
     jmethodID method,
     jboolean was_popped_by_exception);

void JNICALL jrst_EventGarbageCollectionFinish
    (jvmtiEnv *jvmti_env);

void JNICALL jrst_EventGarbageCollectionStart
    (jvmtiEnv *jvmti_env);

void JNICALL jrst_EventMethodEntry
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread,
     jmethodID method);

void JNICALL jrst_EventMethodExit
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread,
     jmethodID method,
     jboolean was_popped_by_exception,
     jvalue return_value);

void JNICALL jrst_EventMonitorContendedEnter
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread,
     jobject object);

void JNICALL jrst_EventMonitorContendedEntered
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread,
     jobject object);

void JNICALL jrst_EventMonitorWait
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread,
     jobject object,
     jlong timeout);

void JNICALL jrst_EventMonitorWaited
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread,
     jobject object,
     jboolean timed_out);

void JNICALL jrst_EventNativeMethodBind
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread,
     jmethodID method,
     void* address,
     void** new_address_ptr);

void JNICALL jrst_EventObjectFree
    (jvmtiEnv *jvmti_env,
     jlong tag);

void JNICALL jrst_EventResourceExhausted
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jint flags,
     const void* reserved,
     const char* description);

void JNICALL jrst_EventSingleStep
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread,
     jmethodID method,
     jlocation location);

void JNICALL jrst_EventThreadEnd
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread);

void JNICALL jrst_EventThreadStart
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread);

void JNICALL jrst_EventVMDeath
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env);

void JNICALL jrst_EventVMInit
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread);

void JNICALL jrst_EventVMObjectAlloc
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread,
     jobject object,
     jclass object_klass,
     jlong size);

void JNICALL jrst_EventVMStart
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env);

//from jrst_trace.c
void trace_finalize_buffers (void);
void trace_thread_start(jvmtiEnv * jvmti, jthread thread, char *name);
void trace_thread_end(jvmtiEnv * jvmti, jthread thread, char *name);
void trace_event_object_free(jlong tag);
void trace_event_gc_start(void);
void trace_event_gc_finish(void);
void trace_event_monitor_contended_enter(jvmtiEnv * jvmti,
                                         jthread thread,
                                         int object);
void trace_event_monitor_contended_entered(jvmtiEnv * jvmti,
                                           jthread thread,
                                           int object);
void trace_event_monitor_wait(jvmtiEnv * jvmti,
                              jthread thread,
                              int object);
void trace_event_monitor_waited(jvmtiEnv * jvmti,
                                jthread thread,
                                int object);
void trace_event_method_entry(jthread thread, char *method_name);
void trace_event_method_exit(jthread thread, char *method_name);
void trace_event_exception(jthread thread, int exception);
void trace_event_method_exit_exception(jthread thread);
void trace_event_method_load(int method, char *name, unsigned access_flags,
                             int klass);
void trace_event_class_load(int klass, char *name);

//from jrst_filter.c
void jrst_filter_init (void);
void jrst_filter_finalize (void);
int jrst_filtered (char *classname, char *methodname);

#endif
