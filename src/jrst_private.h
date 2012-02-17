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
} jrst_agent;

extern jrst_agent *jrst;
extern unsigned long long jrst_jvmid;

#define GET_JVMTI() (jrst->jvmti)
#define JRST_MAX_THREAD_NAME 1000

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

//from jrst.c
void jrst_describe_error(jvmtiEnv * jvmtiLocate, jvmtiError error);
void jrst_check_error(jvmtiEnv * jvmtiLocate,
                      jvmtiError error,
                      const char *message);
void jrst_enter_critical_section(jvmtiEnv * jvmtiLocate,
                                 jrawMonitorID monitor);
void jrst_exit_critical_section(jvmtiEnv * jvmtiLocate,
                                jrawMonitorID monitor);
void jrst_get_thread_name(jvmtiEnv * jvmtiLocate,
                          jthread thread,
                          char *name,
                          int numMax);

//from jrst_trace.c
void trace_finalize_buffers (void);
void trace_initialize(jvmtiEnv * jvmtiLocate, jthread thread, char *name);
void trace_finalize(jvmtiEnv * jvmtiLocate, jthread thread);
void trace_event_object_free(jlong tag);
void trace_event_gc_start(void);
void trace_event_gc_finish(void);
void trace_event_monitor_contended_enter(jvmtiEnv * jvmtiLocate,
                                         jthread thread,
                                         int object);
void trace_event_monitor_contended_entered(jvmtiEnv * jvmtiLocate,
                                           jthread thread,
                                           int object);
void trace_event_monitor_wait(jvmtiEnv * jvmtiLocate,
                              jthread thread,
                              int object);
void trace_event_monitor_waited(jvmtiEnv * jvmtiLocate,
                                jthread thread,
                                int object);

#endif
