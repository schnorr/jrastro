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

void JNICALL jrst_EventBreakpoint
    (jvmtiEnv *jvmti_env,
     JNIEnv* jni_env,
     jthread thread,
     jmethodID method,
     jlocation location)
{
}

void JNICALL jrst_EventClassFileLoadHook (jvmtiEnv *jvmti_env,
                                          JNIEnv* jni_env,
                                          jclass class_being_redefined,
                                          jobject loader,
                                          const char* name,
                                          jobject protection_domain,
                                          jint class_data_len,
                                          const unsigned char* class_data,
                                          jint* new_class_data_len,
                                          unsigned char** new_class_data)
{
  MONITOR_ENTER(jrst->monitor);

  /* if (initialized == false) { */

  /*   if (jrst_trace_class((char *) name) == false) { */
  /*     class_number++; */
  /*     jrst_exit_critical_section(jvmtiLocate, gagent->monitor); */
  /*     return; */
  /*   } */

  /*   jvmtiClassDefinition definition; */
  /*   definition.class_byte_count = class_data_len; */
  /*   definition.class_bytes = class_data; */

  /*   /\* hash_insert(&h_class, (hash_key_t) name, (hash_data_t) & definition); *\/ */

  /*   jrst_exit_critical_section(jvmtiLocate, gagent->monitor); */
  /*   return; */
  /* } */

  /* jvmtiError err; */
  /* int system_class = 0; */
  /* unsigned char *new_file_image = NULL; */
  /* long new_file_len = 0; */


  /* if (class_being_redefined == NULL) { */
  /*   if (jrst_trace_class((char *) name) == false */
  /*       || strcmp(name, "org/lsc/JRastro/Instru") == 0) { */
  /*     class_number++; */
  /*     jrst_exit_critical_section(jvmtiLocate, gagent->monitor); */
  /*     return; */
  /*   } */
  /* } else { */
  /*   system_class = 1; */
  /* } */

  /* //Registro do identificador e nome da classe */
  /* trace_event_class_load(class_number, (char *) name); */

  /* java_crw_demo(class_number, */
  /*               name, */
  /*               class_data, */
  /*               class_data_len, */
  /*               system_class, */
  /*               &new_file_image, &new_file_len, &jrst_trace_methods); */

  /* if (new_file_len > 0) { */
  /*   unsigned char *jvmti_space; */
  /*   err = */
  /*       (*jvmtiLocate)->Allocate(jvmtiLocate, (jlong) new_file_len, */
  /*                                &jvmti_space); */
  /*   jrst_check_error(jvmtiLocate, err, "Cannot Allocate memory"); */

  /*   (void) memcpy((void *) jvmti_space, (void *) new_file_image, */
  /*                 (int) new_file_len); */
  /*   *new_class_data_len = (jint) new_file_len; */
  /*   *new_class_data = jvmti_space; */

  /* } */
  /* class_number++; */

  MONITOR_EXIT(jrst->monitor);
}

void JNICALL jrst_EventClassLoad (jvmtiEnv *jvmti_env,
                                  JNIEnv* jni_env,
                                  jthread thread,
                                  jclass klass)
{
}

void JNICALL jrst_EventClassPrepare (jvmtiEnv *jvmti_env,
                                     JNIEnv* jni_env,
                                     jthread thread,
                                     jclass klass)
{
}

void JNICALL jrst_EventCompiledMethodLoad (jvmtiEnv *jvmti_env,
                                           jmethodID method,
                                           jint code_size,
                                           const void* code_addr,
                                           jint map_length,
                                           const jvmtiAddrLocationMap* map,
                                           const void* compile_info)
{
}

void JNICALL jrst_EventCompiledMethodUnload (jvmtiEnv *jvmti_env,
                                             jmethodID method,
                                             const void* code_addr)
{
}

void JNICALL jrst_EventDataDumpRequest (jvmtiEnv *jvmti_env)
{
}

void JNICALL jrst_EventDynamicCodeGenerated (jvmtiEnv *jvmti_env,
                                             const char* name,
                                             const void* address,
                                             jint length)
{
}

void JNICALL jrst_EventException (jvmtiEnv *jvmti_env,
                                  JNIEnv* jni_env,
                                  jthread thread,
                                  jmethodID method,
                                  jlocation location,
                                  jobject exception,
                                  jmethodID catch_method,
                                  jlocation catch_location)
{
}

void JNICALL jrst_EventExceptionCatch (jvmtiEnv *jvmti_env,
                                       JNIEnv* jni_env,
                                       jthread thread,
                                       jmethodID method,
                                       jlocation location,
                                       jobject exception)
{
}

void JNICALL jrst_EventFieldAccess (jvmtiEnv *jvmti_env,
                                    JNIEnv* jni_env,
                                    jthread thread,
                                    jmethodID method,
                                    jlocation location,
                                    jclass field_klass,
                                    jobject object,
                                    jfieldID field)
{
}

void JNICALL jrst_EventFieldModification (jvmtiEnv *jvmti_env,
                                          JNIEnv* jni_env,
                                          jthread thread,
                                          jmethodID method,
                                          jlocation location,
                                          jclass field_klass,
                                          jobject object,
                                          jfieldID field,
                                          char signature_type,
                                          jvalue new_value)
{
}

void JNICALL jrst_EventFramePop (jvmtiEnv *jvmti_env,
                                 JNIEnv* jni_env,
                                 jthread thread,
                                 jmethodID method,
                                 jboolean was_popped_by_exception)
{
}

void JNICALL jrst_EventGarbageCollectionFinish (jvmtiEnv *jvmti_env)
{
  trace_event_gc_finish();
}

void JNICALL jrst_EventGarbageCollectionStart (jvmtiEnv *jvmti_env)
{
  trace_event_gc_start();
}

void JNICALL jrst_EventMethodEntry (jvmtiEnv *jvmti_env,
                                    JNIEnv* jni_env,
                                    jthread thread,
                                    jmethodID method)
{
  char *name, *signature, *generic;
  (*GET_JVMTI())->GetMethodName(GET_JVMTI(),
                                method,
                                &name,
                                &signature,
                                &generic);
  jclass class;
  (*GET_JVMTI())->GetMethodDeclaringClass(GET_JVMTI(),
                                          method,
                                          &class);
  char *class_signature, *class_generic;
  (*GET_JVMTI())->GetClassSignature(GET_JVMTI(),
                                    class,
                                    &class_signature,
                                    &class_generic);
  char *class_clean = class_signature+1;
  int i;
  for (i = 0; class_clean[i] != '\0'; i++){
    if (class_clean[i] == ';'){
      class_clean[i] = '\0';
      break;
    }
  }
  if (jrst_filtered(class_clean, name) == 0){
    trace_event_method_entry (thread, name);
  }
  (*GET_JVMTI())->Deallocate (GET_JVMTI(), (unsigned char*)name);
  (*GET_JVMTI())->Deallocate (GET_JVMTI(), (unsigned char*)signature);
  (*GET_JVMTI())->Deallocate (GET_JVMTI(), (unsigned char*)generic);
  (*GET_JVMTI())->Deallocate (GET_JVMTI(), (unsigned char*)class_signature);
  (*GET_JVMTI())->Deallocate (GET_JVMTI(), (unsigned char*)class_generic);
}

void JNICALL jrst_EventMethodExit (jvmtiEnv *jvmti_env,
                                   JNIEnv* jni_env,
                                   jthread thread,
                                   jmethodID method,
                                   jboolean was_popped_by_exception,
                                   jvalue return_value)
{
  char *name, *signature, *generic;
  jvmtiError error = (*GET_JVMTI())->GetMethodName(GET_JVMTI(),
                                                   method,
                                                   &name,
                                                   &signature,
                                                   &generic);
  jclass class;
  (*GET_JVMTI())->GetMethodDeclaringClass(GET_JVMTI(),
                                          method,
                                          &class);
  char *class_signature, *class_generic;
  (*GET_JVMTI())->GetClassSignature(GET_JVMTI(),
                                    class,
                                    &class_signature,
                                    &class_generic);
  char *class_clean = class_signature+1;
  int i;
  for (i = 0; class_clean[i] != '\0'; i++){
    if (class_clean[i] == ';'){
      class_clean[i] = '\0';
      break;
    }
  }
  if (jrst_filtered(class_clean, name) == 0){
    trace_event_method_exit (thread, name);
  }
  (*GET_JVMTI())->Deallocate (GET_JVMTI(), (unsigned char*)name);
  (*GET_JVMTI())->Deallocate (GET_JVMTI(), (unsigned char*)signature);
  (*GET_JVMTI())->Deallocate (GET_JVMTI(), (unsigned char*)generic);
}

void JNICALL jrst_EventMonitorContendedEnter (jvmtiEnv *jvmti_env,
                                              JNIEnv* jni_env,
                                              jthread thread,
                                              jobject object)
{
  jlong tag;
  (*GET_JVMTI())->GetTag(GET_JVMTI(), object, &tag);
  trace_event_monitor_contended_enter(jvmti_env, thread, (int) tag);
}

void JNICALL jrst_EventMonitorContendedEntered (jvmtiEnv *jvmti_env,
                                                JNIEnv* jni_env,
                                                jthread thread,
                                                jobject object)
{
  jlong tag;
  (*GET_JVMTI())->GetTag(GET_JVMTI(), object, &tag);
  trace_event_monitor_contended_entered(jvmti_env, thread, (int) tag);
}

void JNICALL jrst_EventMonitorWait (jvmtiEnv *jvmti_env,
                                    JNIEnv* jni_env,
                                    jthread thread,
                                    jobject object,
                                    jlong timeout)
{
  jlong tag;
  (*GET_JVMTI())->GetTag(GET_JVMTI(), object, &tag);
  trace_event_monitor_wait(jvmti_env, thread, (int) tag);
}

void JNICALL jrst_EventMonitorWaited (jvmtiEnv *jvmti_env,
                                      JNIEnv* jni_env,
                                      jthread thread,
                                      jobject object,
                                      jboolean timed_out)
{
  jlong tag;
  (*GET_JVMTI())->GetTag(GET_JVMTI(), object, &tag);
  trace_event_monitor_waited(jvmti_env, thread, (int) tag);
}

void JNICALL jrst_EventNativeMethodBind (jvmtiEnv *jvmti_env,
                                         JNIEnv* jni_env,
                                         jthread thread,
                                         jmethodID method,
                                         void* address,
                                         void** new_address_ptr)
{
}

void JNICALL jrst_EventObjectFree (jvmtiEnv *jvmti_env,
                                   jlong tag)
{
  trace_event_object_free(tag);
}

void JNICALL jrst_EventResourceExhausted (jvmtiEnv *jvmti_env,
                                          JNIEnv* jni_env,
                                          jint flags,
                                          const void* reserved,
                                          const char* description)
{
}

void JNICALL jrst_EventSingleStep (jvmtiEnv *jvmti_env,
                                   JNIEnv* jni_env,
                                   jthread thread,
                                   jmethodID method,
                                   jlocation location)
{
}

void JNICALL jrst_EventThreadStart (jvmtiEnv *jvmti_env,
                                    JNIEnv* jni_env,
                                    jthread thread)
{
  jvmtiThreadInfo info;
  bzero (&info, sizeof(jvmtiThreadInfo));
  (*GET_JVMTI())->GetThreadInfo(GET_JVMTI(), thread, &info);
  trace_thread_start (GET_JVMTI(), thread, info.name);
}

void JNICALL jrst_EventThreadEnd (jvmtiEnv *jvmti_env,
                                  JNIEnv* jni_env,
                                  jthread thread)
{
  jvmtiThreadInfo info;
  bzero (&info, sizeof(jvmtiThreadInfo));
  (*GET_JVMTI())->GetThreadInfo(GET_JVMTI(), thread, &info);
  trace_thread_end (GET_JVMTI(), thread, info.name);
}

void JNICALL jrst_EventVMDeath (jvmtiEnv *jvmti_env,
                                JNIEnv* jni_env)
{
}

void JNICALL jrst_EventVMInit (jvmtiEnv *jvmti_env,
                               JNIEnv* jni_env,
                               jthread thread)
{
  MONITOR_ENTER(jrst->monitor);

  /* Thread tracing */
  if (jrst->thread_tracing){
    (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(),
                                             JVMTI_ENABLE,
                                             JVMTI_EVENT_THREAD_START,
                                             NULL);
    (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(),
                                             JVMTI_ENABLE,
                                             JVMTI_EVENT_THREAD_END,
                                             NULL);
  }

  /* Method tracing */
  if (jrst->thread_tracing && jrst->method_tracing){
    (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(),
                                             JVMTI_ENABLE,
                                             JVMTI_EVENT_METHOD_ENTRY,
                                             NULL);
    (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(),
                                             JVMTI_ENABLE,
                                             JVMTI_EVENT_METHOD_EXIT,
                                             NULL);
  }

  /* Monitor tracing */
  if (jrst->monitor_tracing){
    (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(),
                                             JVMTI_ENABLE,
                                             JVMTI_EVENT_MONITOR_WAIT,
                                             NULL);
    (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(),
                                             JVMTI_ENABLE,
                                             JVMTI_EVENT_MONITOR_WAITED,
                                             NULL);
    (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(),
                                             JVMTI_ENABLE,
                                             JVMTI_EVENT_MONITOR_CONTENDED_ENTER,
                                             NULL);
    (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(),
                                             JVMTI_ENABLE,
                                             JVMTI_EVENT_MONITOR_CONTENDED_ENTERED,
                                             NULL);
  }

  /* Memory allocation tracing */
  if (jrst->gc_tracing){
    (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(),
                                             JVMTI_ENABLE,
                                             JVMTI_EVENT_GARBAGE_COLLECTION_START,
                                             NULL);
    (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(),
                                             JVMTI_ENABLE,
                                             JVMTI_EVENT_GARBAGE_COLLECTION_FINISH,
                                             NULL);
    (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(),
                                             JVMTI_ENABLE,
                                             JVMTI_EVENT_OBJECT_FREE,
                                             NULL);
    (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(),
                                             JVMTI_ENABLE,
                                             JVMTI_EVENT_VM_OBJECT_ALLOC,
                                             NULL);
  }

  /* Other notifications */
  /* (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(), */
  /*                                          JVMTI_ENABLE, */
  /*                                          JVMTI_EVENT_CLASS_LOAD, */
  /*                                          NULL); */
  /* (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(), */
  /*                                          JVMTI_ENABLE, */
  /*                                          JVMTI_EVENT_CLASS_PREPARE, */
  /*                                          NULL); */
  /* (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(), */
  /*                                          JVMTI_ENABLE, */
  /*                                          JVMTI_EVENT_VM_START, */
  /*                                          NULL); */
  /* (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(), */
  /*                                          JVMTI_ENABLE, */
  /*                                          JVMTI_EVENT_EXCEPTION, */
  /*                                          NULL); */
  /* (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(), */
  /*                                          JVMTI_ENABLE, */
  /*                                          JVMTI_EVENT_EXCEPTION_CATCH, */
  /*                                          NULL); */
  /* (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(), */
  /*                                          JVMTI_ENABLE, */
  /*                                          JVMTI_EVENT_SINGLE_STEP, */
  /*                                          NULL); */
  /* (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(), */
  /*                                          JVMTI_ENABLE, */
  /*                                          JVMTI_EVENT_FRAME_POP, */
  /*                                          NULL); */
  /* (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(), */
  /*                                          JVMTI_ENABLE, */
  /*                                          JVMTI_EVENT_BREAKPOINT, */
  /*                                          NULL); */
  /* (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(), */
  /*                                          JVMTI_ENABLE, */
  /*                                          JVMTI_EVENT_FIELD_ACCESS, */
  /*                                          NULL); */
  /* (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(), */
  /*                                          JVMTI_ENABLE, */
  /*                                          JVMTI_EVENT_FIELD_MODIFICATION, */
  /*                                          NULL); */
  /* (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(), */
  /*                                          JVMTI_ENABLE, */
  /*                                          JVMTI_EVENT_NATIVE_METHOD_BIND, */
  /*                                          NULL); */
  /* (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(), */
  /*                                          JVMTI_ENABLE, */
  /*                                          JVMTI_EVENT_COMPILED_METHOD_LOAD, */
  /*                                          NULL); */
  /* (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(), */
  /*                                          JVMTI_ENABLE, */
  /*                                          JVMTI_EVENT_COMPILED_METHOD_UNLOAD, */
  /*                                          NULL); */
  /* (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(), */
  /*                                          JVMTI_ENABLE, */
  /*                                          JVMTI_EVENT_DYNAMIC_CODE_GENERATED, */
  /*                                          NULL); */
  /* (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(), */
  /*                                          JVMTI_ENABLE, */
  /*                                          JVMTI_EVENT_DATA_DUMP_REQUEST, */
  /*                                          NULL); */
  /* (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(), */
  /*                                          JVMTI_ENABLE, */
  /*                                          JVMTI_EVENT_RESOURCE_EXHAUSTED, */
  /*                                          NULL); */

  MONITOR_EXIT(jrst->monitor);
}

void JNICALL jrst_EventVMObjectAlloc (jvmtiEnv *jvmti_env,
                                      JNIEnv* jni_env,
                                      jthread thread,
                                      jobject object,
                                      jclass object_klass,
                                      jlong size)
{
}

void JNICALL jrst_EventVMStart (jvmtiEnv *jvmti_env,
                                JNIEnv* jni_env)
{
}
