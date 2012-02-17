#ifndef __JRASTRO_PRIVATE_H__
#define __JRASTRO_PRIVATE_H__
#include <jrastro.h>
#include <strings.h>
#include <argp.h>

void pajeDefineContainerType(const char *alias,
                             const char *containerType, const char *name);
void pajeDefineStateType(const char *alias,
                         const char *containerType, const char *name);
void pajeDefineLinkType(const char *alias,
                        const char *containerType,
                        const char *sourceContainerType,
                        const char *destContainerType, const char *name);
void pajeCreateContainer(double timestamp,
                         const char *alias,
                         const char *type,
                         const char *container, const char *name);
void pajeDestroyContainer(double timestamp,
                          const char *type, const char *container);
void pajeSetState(double timestamp,
                  const char *container,
                  const char *type, const char *value);
void pajePushState(double timestamp,
                   const char *container,
                   const char *type, const char *value);
void pajePushStateWithMark(double timestamp,
                   const char *container,
                   const char *type, const char *value, const int mark);
void pajePopState(double timestamp,
                  const char *container, const char *type);
void pajeStartLink(double timestamp,
                   const char *container,
                   const char *type,
                   const char *sourceContainer,
                   const char *value, const char *key);
void pajeStartLinkWithMessageSize(double timestamp,
                   const char *container,
                   const char *type,
                   const char *sourceContainer,
                   const char *value, const char *key,
                   const int messageSize);
void pajeStartLinkWithMessageSizeAndMark(double timestamp,
                   const char *container,
                   const char *type,
                   const char *sourceContainer,
                   const char *value, const char *key,
                   const int messageSize, const int mark);
void pajeEndLink(double timestamp,
                 const char *container,
                 const char *type,
                 const char *endContainer,
                 const char *value, const char *key);
void paje_header(int basic);
void paje_hierarchy(void);

typedef enum {
  PAJE_DefineContainerType,
  PAJE_DefineVariableType,
  PAJE_DefineStateType,
  PAJE_DefineEventType,
  PAJE_DefineLinkType,
  PAJE_DefineEntityValue,
  PAJE_CreateContainer,
  PAJE_DestroyContainer,
  PAJE_SetVariable,
  PAJE_AddVariable,
  PAJE_SubVariable,
  PAJE_SetState,
  PAJE_PushState,
  PAJE_PushStateWithMark,
  PAJE_PopState,
  PAJE_StartLink,
  PAJE_StartLinkWithMessageSize,
  PAJE_StartLinkWithMessageSizeAndMark,
  PAJE_EndLink,
  PAJE_NewEvent,
} e_event_type;


#endif // __JRASTRO_PRIVATE_H__
