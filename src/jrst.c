/*
    Copyright (c) 1998--2006 Benhur Stein
    
    This file is part of Pajé.

    Pajé is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    Pajé is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
    for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Pajé; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02111 USA.
*/


//////////////////////////////////////////////////
/*      Author: Geovani Ricardo Wiedenhoft      */
/*      Email: grw@inf.ufsm.br                  */
//////////////////////////////////////////////////

#include "jrst_private.h"

jrst_agent *jrst = NULL;
/*Identifica as capacidades da JVM*/
/*Seta as funcoes para retorno dos eventos*/

/*Identificador da thread main == Identificador da JVM*/
unsigned long long jrst_jvmid;

/*Nome do arquivo com as opcoes dos eventos a serem selecionados*/
//char eventsOptionName[MAX_NAME_OPTIONS];
/*Nome do arquivo com as opcoes das classes e metodos a serem selecionados*/
//char methodsOptionName[MAX_NAME_OPTIONS];

/*Variavel para indicar se sera rastreados os eventos monitorados*/
int traces = 1;
/*Variavel para setar se todos as classes e metodos serao rastreados*/
int tracesAll = 0;
/*Variavel para indicar se os metodos serao rastreados*/
int methodsTrace = 0;
/*Variavel para indicar se a alocacao e liberacao de memoria sera rastreado*/
int memoryTrace = 0;

/*Indica se ja ocorreu a inicializacao da JVM*/
int initialized = 0;

/*Hash com as classes a serem redefinidas*/
/* hash_t h_class; */
/*Hash com as opcoes, classes e metodos*/
/* hash_t h_options; */

/*Buffers*/
/* rst_buffer_t *ptr_loader = NULL; */
/* rst_buffer_t *ptr_monitor = NULL; */
/* rst_buffer_t *ptr_new_array = NULL; */


JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM *jvm,
                                    char *options,
                                    void *reserved)
{
  jint ret;

  //allocate global agent
  if (jrst != NULL){
    printf ("[jrastro] at %s, global agent is already allocated\n",
            __FUNCTION__);
    return JNI_ERR;
  }else{
    jrst = (jrst_agent*) malloc (sizeof(jrst_agent));
  }

  //get the jvmti reference, save it in the global agent
  ret = (*jvm)->GetEnv(jvm, (void*)(&jrst->jvmti), JVMTI_VERSION_1_0);
  if (ret != JNI_OK || jrst->jvmti == NULL) {
    printf("ERROR: Unable to access JVMTI Version 1 (0x%x),"
           " is your J2SE a 1.5 or newer version?"
           " JNIEnv's GetEnv() returned %d\n", JVMTI_VERSION_1, ret);
    return JNI_ERR;
  }

  //check jvmti capabilities
  jvmtiCapabilities capabilities;
  bzero (&capabilities, sizeof(jvmtiCapabilities));
  (*GET_JVMTI())->GetPotentialCapabilities(GET_JVMTI(), &capabilities);
  if (capabilities.can_signal_thread != 1 ||
      capabilities.can_get_owned_monitor_info != 1 ||
      capabilities.can_generate_exception_events != 1 ||
      capabilities.can_generate_frame_pop_events != 1 ||
      capabilities.can_generate_method_entry_events != 1 ||
      capabilities.can_generate_method_exit_events != 1 ||
      capabilities.can_generate_vm_object_alloc_events != 1 ||
      capabilities.can_generate_object_free_events != 1 ||
      capabilities.can_get_current_thread_cpu_time != 1 ||
      capabilities.can_get_thread_cpu_time != 1 ||
      capabilities.can_access_local_variables != 1 ||
      capabilities.can_generate_compiled_method_load_events != 1 ||
      capabilities.can_maintain_original_method_order != 1 ||
      capabilities.can_generate_monitor_events != 1 ||
      capabilities.can_generate_garbage_collection_events != 1 ||
      capabilities.can_generate_all_class_hook_events != 1) {
    printf("[jrastro] at %s, JVMTI capabilities don't check\n",
           __FUNCTION__);
    return JNI_ERR;
  }
  (*GET_JVMTI())->AddCapabilities(GET_JVMTI(), &capabilities);

  //set callback functions
  jvmtiEventCallbacks cb;
  bzero (&cb, sizeof(jvmtiEventCallbacks));
  cb.VMInit = &jrst_EventVMInit;
  cb.VMDeath = &jrst_EventVMDeath;
  cb.ThreadStart = &jrst_EventThreadStart;
  cb.ThreadEnd = &jrst_EventThreadEnd;
  cb.ClassFileLoadHook = &jrst_EventClassFileLoadHook;
  cb.ClassLoad = &jrst_EventClassLoad;
  cb.ClassPrepare = &jrst_EventClassPrepare;
  cb.VMStart = &jrst_EventVMStart;
  cb.Exception = &jrst_EventException;
  cb.ExceptionCatch = &jrst_EventExceptionCatch;
  cb.SingleStep = &jrst_EventSingleStep;
  cb.FramePop = &jrst_EventFramePop;
  cb.Breakpoint = &jrst_EventBreakpoint;
  cb.FieldAccess = &jrst_EventFieldAccess;
  cb.FieldModification = &jrst_EventFieldModification;
  cb.MethodEntry = &jrst_EventMethodEntry;
  cb.MethodExit = &jrst_EventMethodExit;
  cb.NativeMethodBind = &jrst_EventNativeMethodBind;
  cb.CompiledMethodLoad = &jrst_EventCompiledMethodLoad;
  cb.CompiledMethodUnload = &jrst_EventCompiledMethodUnload;
  cb.DynamicCodeGenerated = &jrst_EventDynamicCodeGenerated;
  cb.DataDumpRequest = &jrst_EventDataDumpRequest;
  cb.MonitorWait = &jrst_EventMonitorWait;
  cb.MonitorWaited = &jrst_EventMonitorWaited;
  cb.MonitorContendedEnter = &jrst_EventMonitorContendedEnter;
  cb.MonitorContendedEntered = &jrst_EventMonitorContendedEntered;
  cb.ResourceExhausted = &jrst_EventResourceExhausted;
  cb.GarbageCollectionStart = &jrst_EventGarbageCollectionStart;
  cb.GarbageCollectionFinish = &jrst_EventGarbageCollectionFinish;
  cb.ObjectFree = &jrst_EventObjectFree;
  cb.VMObjectAlloc = &jrst_EventVMObjectAlloc;
  (*GET_JVMTI())->SetEventCallbacks(GET_JVMTI(),
                                    &cb,
                                    sizeof(jvmtiEventCallbacks));

  //set notifications jrastro uses to control the tracing
  (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(),
                                           JVMTI_ENABLE,
                                           JVMTI_EVENT_CLASS_FILE_LOAD_HOOK,
                                           (jthread) NULL);
  (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(),
                                           JVMTI_ENABLE,
                                           JVMTI_EVENT_VM_INIT,
                                           (jthread) NULL);
  (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(),
                                           JVMTI_ENABLE,
                                           JVMTI_EVENT_VM_DEATH,
                                           (jthread) NULL);
  (*GET_JVMTI())->SetEventNotificationMode(GET_JVMTI(),
                                           JVMTI_ENABLE,
                                           JVMTI_EVENT_VM_START,
                                           (jthread) NULL);

  //create monitors to protect some parts of tracing
  (*GET_JVMTI())->CreateRawMonitor(GET_JVMTI(),
                                   "agent",
                                   &(jrst->monitor));
  (*GET_JVMTI())->CreateRawMonitor(GET_JVMTI(),
                                   "thread",
                                   &(jrst->monitor_thread));
  (*GET_JVMTI())->CreateRawMonitor(GET_JVMTI(),
                                   "buffer",
                                   &(jrst->monitor_buffer));
  (*GET_JVMTI())->CreateRawMonitor(GET_JVMTI(),
                                   "newArray",
                                   &(jrst->monitor_new_array));
  (*GET_JVMTI())->CreateRawMonitor(GET_JVMTI(),
                                   "tag",
                                   &(jrst->monitor_tag));

  /* hash_initialize(&h_options, hash_value_string, hash_copy_string, */
  /*                 hash_key_cmp_string, hash_destroy_string_list); */
  /* hash_initialize(&h_class, hash_value_string, hash_copy_string_data, */
  /*                 hash_key_cmp_string, hash_destroy_string_data); */


  /* /\*Le nomes dos arquivos "opcoes" *\/ */
  /* jrst_read_names_options(options); */

  /* /\*Funcao que abilita os methodos a serem rastreados *\/ */
  /* jrst_read_class_methods_enable(); */

  return JNI_OK;

}

JNIEXPORT void JNICALL Agent_OnUnload(JavaVM * vm)
{
  /* hash_finalize(&h_options); */
  /* hash_finalize(&h_class); */

  //flush all TODO
}

void jrst_describe_error(jvmtiEnv * jvmtiLocate, jvmtiError error)
{
  char *describe;
  jvmtiError err;

  describe = NULL;
  err = (*jvmtiLocate)->GetErrorName(jvmtiLocate, error, &describe);
  if (err != JVMTI_ERROR_NONE) {
    printf("\n[JRastro ERROR]: Cannot Get Error:(%d) Name\n", error);
    return;
  }

  printf("\n[JRastro ERROR](%d): <%s>\n", error,
         (describe == NULL ? "Unknown" : describe));
  err =
      (*jvmtiLocate)->Deallocate(jvmtiLocate, (unsigned char *) describe);
  if (err != JVMTI_ERROR_NONE) {
    printf("\n[JRastro ERROR]: Cannot Deallocate\n");
    return;
  }
}

void jrst_check_error(jvmtiEnv * jvmtiLocate,
                      jvmtiError error,
                      const char *message)
{
  if (error != JVMTI_ERROR_NONE) {
    jrst_describe_error(jvmtiLocate, error);
    if (message){
      printf("[jrastro] %s\n", message);
    }
    exit(1);
  }
}

void jrst_enter_critical_section(jvmtiEnv * jvmtiLocate,
                                 jrawMonitorID monitor)
{
  jvmtiError error;
  error = (*jvmtiLocate)->RawMonitorEnter(jvmtiLocate, monitor);
  jrst_check_error(jvmtiLocate, error, "Cannot enter with raw monitor");
}

void jrst_exit_critical_section(jvmtiEnv * jvmtiLocate,
                                jrawMonitorID monitor)
{
  jvmtiError error;
  error = (*jvmtiLocate)->RawMonitorExit(jvmtiLocate, monitor);
  jrst_check_error(jvmtiLocate, error, "Cannot exit with raw monitor");
}

void jrst_get_thread_name(jvmtiEnv * jvmtiLocate,
                          jthread thread,
                          char *name,
                          int numMax)
{
  jvmtiThreadInfo infoThread;
  jvmtiError error;

  (void) memset(&infoThread, 0, sizeof(infoThread));
  error = (*jvmtiLocate)->GetThreadInfo(jvmtiLocate, thread, &infoThread);
  jrst_check_error(jvmtiLocate, error, "Cannot get Thread Info");
  if (infoThread.name != NULL) {
    int len;
    len = (int) strlen(infoThread.name);
    if (len < numMax) {
      (void) strcpy(name, infoThread.name);
    } else {
      (void) strcpy(name, "Unknown");

    }
    error =
        (*jvmtiLocate)->Deallocate(jvmtiLocate,
                                   (unsigned char *) infoThread.name);
    jrst_check_error(jvmtiLocate, error, "Cannot deallocate memory");
    return;
  }
  (void) strcpy(name, "Unknown");
}
