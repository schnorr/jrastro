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
#include "jrst_private.h"

#define _GNU_SOURCE
#define __USE_GNU
#include <search.h>

static struct hsearch_data classes;
static struct hsearch_data methods;
static int hash_initialized = 0;

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
  hash_initialized = 1;

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
  if (!hash_initialized) return 0;

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
