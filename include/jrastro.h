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
