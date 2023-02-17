/*
  Copyright (c) 2022 Kim Lilliestierna. All rights reserved.

  This code is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library in the LICENSE file. If not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  or via https://www.gnu.org/licenses/gpl-3.0.en.html

*/

#ifndef __DBGLEVELS_H__
#define __DBGLEVELS_H__

/*! \file debgLevels.h
 * @brief debug level defines
 *
 * must be included before debug.h
 * then set debug level
 * this since stuff will be excluded from debug.h depending ong setting og debug level...
 * if you change these you need to fix debug.h ans debug.cpp as well
 */


#define DBG_NONE_L		0
#define	DBG_FAIL_L		1<<0
#define	DBG_ERROR_L		1<<1
#define	DBG_WARN_L		1<<2
#define	DBG_INFO_L		1<<3

#define	DBG_1F_L		1<<4
#define	DBG_2F_L		1<<5
#define	DBG_3F_L		1<<6

#define	DBG_1V_L		1<<7
#define	DBG_2V_L		1<<8
#define	DBG_3V_L		1<<9

#define DBG_2FV_L		(DBG_2F_L|DBG_2V_L)
#define DBG_1FV_L		(DBG_1F_L|DBG_1V_L)
#define DBG_3FV_L		(DBG_3F_L|DBG_3F_L)

#define	DBG_VERB_L		1<<10
#define	DBG_ALL_L		0xffff

#define DBG_DEF_L		(DBG_FAIL_L|DBG_ERROR_L|DBG_WARN_L)

#endif
