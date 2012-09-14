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
#ifndef __JRASTRO_H_
#define __JRASTRO_H_
#include <rastro.h>
#include <jrastro_config.h>

#define JRST_INPUT_SIZE 100

#define JRST_THREAD_START 0
#define JRST_THREAD_END 1
#define JRST_MONITOR_ENTER 2
#define JRST_MONITOR_ENTERED 3
#define JRST_MONITOR_WAIT 4
#define JRST_MONITOR_WAITED 5
#define JRST_METHOD_ENTRY 6
#define JRST_METHOD_EXIT 7
#define JRST_METHOD_EXCEPTION 8
#define JRST_METHOD_EXIT_EXCEPTION 9
#define JRST_METHOD_LOAD 10
#define JRST_CLASS_LOAD 11
#define JRST_GC_START 12
#define JRST_GC_FINISH 13


#endif
