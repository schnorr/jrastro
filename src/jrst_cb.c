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
  jvmtiError error = (*GET_JVMTI())->GetMethodName(GET_JVMTI(),
                                                   method,
                                                   &name,
                                                   &signature,
                                                   &generic);
  trace_event_method_entry (thread, name);
  (*GET_JVMTI())->Deallocate (GET_JVMTI(), (unsigned char*)name);
  (*GET_JVMTI())->Deallocate (GET_JVMTI(), (unsigned char*)signature);
  (*GET_JVMTI())->Deallocate (GET_JVMTI(), (unsigned char*)generic);
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
  trace_event_method_exit (thread, name);
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

  /* /\*Funcao que abilita as opcoes dos eventos *\/ */
  /* jrst_read_events_enable(jvmtiLocate); */

  /* jvmtiError error; */
  /* jint class_count_ptr; */
  /* jclass *classes_ptr; */
  /* jvmtiClassDefinition definitions[300]; */
  /* hash_data_t *class = NULL; */
  /* int count = 0; */
  /* int i; */

  /* error = */
  /*     (*jvmtiLocate)->GetLoadedClasses(jvmtiLocate, &class_count_ptr, */
  /*                                      &classes_ptr); */
  /* jrst_check_error(jvmtiLocate, error, "Cannot Get Loaded Classes"); */

  /* for (i = 0; i < class_count_ptr; i++) { */

  /*   char *signature_ptr; */
  /*   char *generic_ptr; */
  /*   int size = 0; */
  /*   char *tmp; */

  /*   error = */
  /*       (*jvmtiLocate)->GetClassSignature(jvmtiLocate, classes_ptr[i], */
  /*                                         &signature_ptr, &generic_ptr); */
  /*   jrst_check_error(jvmtiLocate, error, "Cannot Get Class Signature"); */

  /*   /\*Tirar da signature o caracter 'L' *\/ */
  /*   tmp = (char *) signature_ptr + 1; */
  /*   /\* -1 Pois comeca em 0 o vetor *\/ */
  /*   size = strlen(tmp) - 1; */
  /*   /\*Tira da signature o caracter ';' *\/ */
  /*   tmp[size] = '\0'; */

  /*   class = hash_locate(&h_class, (hash_key_t) tmp); */

  /*   if (class != NULL) { */
  /*     definitions[count] = **(jvmtiClassDefinition **) class; */
  /*     definitions[count].klass = classes_ptr[i]; */
  /*     count++; */

  /*   } */

  /*   error = */
  /*       (*jvmtiLocate)->Deallocate(jvmtiLocate, */
  /*                                  (unsigned char *) signature_ptr); */
  /*   jrst_check_error(jvmtiLocate, error, "Cannot deallocate memory"); */
  /*   error = */
  /*       (*jvmtiLocate)->Deallocate(jvmtiLocate, */
  /*                                  (unsigned char *) generic_ptr); */
  /*   jrst_check_error(jvmtiLocate, error, "Cannot deallocate memory"); */
  /* } */

  /* initialized = true; */

  /* error = (*jvmtiLocate)->RedefineClasses(jvmtiLocate, count, definitions); */
  /* jrst_check_error(jvmtiLocate, error, "Redefine Classes"); */

  /* error = */
  /*     (*jvmtiLocate)->Deallocate(jvmtiLocate, */
  /*                                (unsigned char *) classes_ptr); */
  /* jrst_check_error(jvmtiLocate, error, "Cannot deallocate memory"); */


  /* if (traces) { */
  /*   jrst_threads(jvmtiLocate); */
  /* } */


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
