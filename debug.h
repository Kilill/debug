#ifndef __DEBUG_H__
#define __DEBUG_H__
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
#include "dbgLevels.h"

/**
 * Debug macros for level controlled printout
 * Macro definitions anre enabled depending on bit values in the the
 * define DEBUG_LEVEL if the bit is set the macro is defined as a call to dbg()
 * otherwise its defined as empty
 * 
 * IF DEBUG_LEVEL is not set prior to including debug.h
 * it is set bellow to DBG_DEF_L
 * 
 * dbgLevels.h needs be included before setting DEBUG_LEVEL to gett access to the level definitions
 *
 * example:
 * #include "dbgLevels.h" 
 * #define DEBUG_LEVEL (DBG_DEF_L|DBG_INFO_L|DBG_1FV_L|DBG_2FV_L)
 * #include "debug.h"
 *
 * by using the SET_XYS(onOff) macros, debugging printout can be dynamically enabled/disabled
 * the printout macros comes in 2 flavours, one that prints the level as a prefix (DBG_XYZ()) and a silent variant
 * that does not (DBG_XYZ_S()).
 * Each leval (123) also has 2 variants , and "F" and a "V" variant (Even though the print macros drops the "F" for
 * conviniece) the "F" variant is meant for be used for function type printouts while the "V" variants are meant for 
 * variables.
 * All the variants have a "NewLine" variant that only prints a newline at the specified level
 * 
 * there are also 4 dedicated macros for "FAIL","ERROR","WARNING" and INFO
 * 
 * see the README for further explanations
 */

// default debug level if not already set

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL DBG_DEF_L
#endif

// logical bit tests
#define IS_FAIL		(DEBUG_LEVEL & DBG_FAIL_L)
#define IS_ERROR	(DEBUG_LEVEL & DBG_ERR_L)
#define IS_WARN		(DEBUG_LEVEL & DBG_WARN_L)
#define IS_INFO		(DEBUG_LEVEL & DBG_INFO_L)

#define IS_1F		(DEBUG_LEVEL & DBG_1F_L)
#define IS_2F		(DEBUG_LEVEL & DBG_2F_L)
#define IS_3F		(DEBUG_LEVEL & DBG_3F_L)

#define IS_1V		(DEBUG_LEVEL & DBG_1V_L)
#define IS_2V		(DEBUG_LEVEL & DBG_2V_L)
#define IS_3V		(DEBUG_LEVEL & DBG_3V_L)

#define IS_VERB_L	(DEBUG_LEVEL & DBG_VERBOSE_L)
#define IS_ALL_L   	(DEBUG_LEVEL & DBG_ALL_L)

// Both functions and variables
#define IS_1FV_L	(DEBUG_LEVEL & (DBG_1F_L | DBG_1V_L))
#define IS_2FV_L	(DEBUG_LEVEL & (DBG_2F_L | DBG_2V_L))
#define IS_FV3_L	(DEBUG_LEVEL & (DBG_3F_L | DBG_3V_L))

// Functions and variabels for multiple levels
#define IS_12FV_L	(DEBUG_LEVEL & (DBG_1F_L | DBG_1V_L| DBG_2F_L | DBG_2V_L))
#define IS_13FV_L	(DEBUG_LEVEL & (DBG_1F_L | DBG_1V_L| DBG_3F_L | DBG_3V_L))
#define IS_23FV_L	(DEBUG_LEVEL & (DBG_2F_L | DBG_2V_L| DBG_3F_L | DBG_3V_L))
#define IS_3FV_L	(DEBUG_LEVEL & (DBG_1F_L | DBG_1V_L| DBG_2F_L | DBG_2V_L| F3_L | V3_L))

#define IS_ANNY     (DEBUG_LEVEL & DBG_ALL_L)

#define ON true
#define OFF false
#define CLR true
#define NOCLR false

// if anny debuging level is set 
#if IS_ANNY
#define SET_DBGNONE	setDbgLvl(DBG_ALL_L,OFF,CLR)
#define SET_DBGALL	setDbgLvl(DBG_ALL_L,ON,false)
#define SET_DBGDEF	setDbgLvl((DBG_FAIL_L|DBG_ERROR_L|DBG_WARN_L),ON,true)
#define SET_DBG(dbgMap,onOff,clear)	setDbgLvl(dbgMap,onOff,clear)
#define DBGANY(format,...) dbg(ALL_L,false,format,##__VA_ARGS__)
#else
#define DBGANY
#define SET_ANNY
#endif

// verbose
#if  VERB_L
#define VERB(format,...)	dbg(DBG_VERB_L,true,format,##__VA_ARGS__)
#define VERB_S(format,...)	dbg(DBG_VERB_L,false,format,##__VA_ARGS__)
#define SET_VERB(onOff)		setDbgLvl(DBG_FAIL_L,onOff,false)
#else
#define VERB
#define VERB_S
#define SET_VERB
#endif

#if IS_FAIL
#define FAIL(format,...)	dbg(DBG_FAIL_L,true,format,##__VA_ARGS__)
#define FAIL_S(format,...)	dbg(DBG_FAIL_L,false,format,##__VA_ARGS__)
#define SET_FAIL(onOff)		setDbgLvl(DBG_FAIL_L,onOff,false)
#else
#define FAIL
#define FAIL_S
#define SET_FAIL
#endif

#if  IS_ERROR
#define ERROR(format,...)	dbg(DBG_ERROR_L,true,format,##__VA_ARGS__)
#define ERROR_S(format,...)	dbg(DBG_ERROR_L,false,format,##__VA_ARGS__) 
#define SET_ERROR(onOff)	setDbgLvl(DBG_ERROR_L,onOff,false)
#else
#define ERROR
#define ERROR_S
#define SET_ERROR
#endif

#if  IS_WARN
#define WARN(format,...)	dbg(DBG_WARN_L,true,format,##__VA_ARGS__)
#define WARN_S(format,...)	dbg(DBG_WARN_L,false,format,##__VA_ARGS__)
#define SET_WARN(onOff)		setDbgLvl(DBG_WARN_L,onOff,false)
#else
#define WARN
#define WARN_S
#define SET_WARN
#endif

#if  IS_INFO
#define INFO(format,...)	dbg(DBG_INFO_L,true,format,##__VA_ARGS__)
#define INFO_S(format,...)	dbg(DBG_INFO_L,false,format,##__VA_ARGS__)
#define SET_INFO(onOff)		setDbgLvl(DBG_INFO_L,onOff,false)
#else
#define INFO
#define INFO_S
#define SET_INFO
#endif

#if  IS_1F
#define DBG1(format,...)	dbg(DBG_1F_L,true,format,##__VA_ARGS__)
#define DBG1_S(format,...)	dbg(DBG_1F_L,false,format,##__VA_ARGS__)
#define DBG1NL				dbgNl(DBG_1F_L)
#define SET_DBG1(onOff)		setDbgLvl(DBG_1F_L,onOff,false)
#else
#define DBG1
#define DBG1_S
#define DBG1NL
#define SET_DBG1
#endif

#if IS_1V
#define DBG1V(format,...)	dbg(DBG_1V_L,true,format,##__VA_ARGS__)
#define DBG1V_S(format,...) dbg(DBG_1V_L,false,format,##__VA_ARGS__)
#define DBG1VNL				dbgNl(DBG_1V_L)
#define SET_DBG1V(onOff)	setDbgLvl(DBG_1V_L,onOff,false)
#else
#define DBG1V
#define DBG1V_S
#define DBG1VNL
#define SET_DBG1V
#endif

#if  IS_2F
#define DBG2(format,...)	dbg(DBG_2F_L,true,format,##__VA_ARGS__)
#define DBG2_S(format,...)	dbg(DBG_2F_L,false,format,##__VA_ARGS__)
#define DBG2NL				dbgNl(DBG_2F_L)
#define SET_DBG2(onOff)		setDbgLvl(DBG_2V_L,onOff,false)
#else
#define DBG2
#define DBG2_S
#define DBG2NL
#define SET_DBG2
#endif


#if  IS_2V
#define DBG2V(format,...)	dbg(DBG_2V_L,true,format,##__VA_ARGS__)
#define DBG2V_S(format,...)	dbg(DBG_2V_L,false,format,##__VA_ARGS__)
#define DBG2VNL 			dbgNl(DBG_FV2_L)
#define SET_DBG2V(onOff)	setDbgLvl(DBG_2V_L,onOff,false)
#else
#define DBG2V
#define DBG2V_S
#define DBG2VNL
#define SET_DBG2V
#endif


#if  IS_3F
#define DBG3(format,...)	dbg(DBG_3F_L,true,format,##__VA_ARGS__)
#define DBG3_S(format,...)	dbg(DBG_3F_L,false,format,##__VA_ARGS__)
#define DBG3NL				dbgNl(DBG_F3_L)
#define SET_DBG3F(onOff)	setDbgLvl(DBG_3F_L,onOff,false)
#else
#define DBG3
#define DBG3_S
#define DBG3NL
#define SET_DBG3F
#endif

#if  IS_3V
#define DBG3V(format,...)	dbg(DBG_3V_L,true,format,##__VA_ARGS__)
#define DBG3V_S(format,...)	dbg(DBG_3V_L,false,format,##__VA_ARGS__)
#define DBG3NL				dbgNl(DBG_F3_L)
#define SET_DBG3V(onOff)	setDbgLvl(DBG_3V_L,onOff,false)
#else
#define DBG3V
#define DBG3V_S
#define DBG3VNL				dbgNl(DBG_F3_L)
#define SET_DBG3V
#endif

// define newline macros for combos of levels
#if IS_12FV
#define DBG12NL		dbgNl(DBG_FV1_L|DBG_FV2_L)
#else
#define DBG12NL
#endif

#if IS_13FV
#define DBG13NL		dbgNl(DBG_FV1_L|DBG_FV3_L)
#else 
#define DBG13NL 
#endif

#if IS_23FV
#define DBG23NL		dbgNl(DBG_FV2_L|DBG_FV3_L)
#else 
#define DBG23NL 
#endif

#if IS123FV_L
#define DBG123NL	dbgNl(DBG_FV1_L|DBG_FV2_L|DBG_FV3_L)
#else
#define DBG123NL 
#endif


/** dynamic debug level 
 *
 * global bitmap variable used to dynamically controll debugging, 
 * be aware tha some macros wont be included in the code
 * unless enabled in the DEBUGLEVEL define
 */
extern uint16_t  DbgLevel; 
						
/** print debug messages
 *
 * will only print if DbgLevel & level != 0
 * usually not used by itself but via the DBG macros
 * that are guarded by conditionals

 * @param level  debug level required to print message
 * @param prefix  Should prefix be printed or not
 * @param format  printf format string
 * @param ... varargs arguments to format string
 */
void dbg(uint16_t level,bool prefix,const char* format,...);

/** decode uint_16 to bit string
 * 
 * This is not thread safe unless the bP pointer is not null 
 * since it uses and internal static buffer
 * to which the poitner is returned
 *
 * @param w16 word to deccode
 * @param bP 	pointer to buffer where to store string,
 * 						make sure its at least 18 chars long
 * 						(16 '1' or '0' + 1 space + null char)
 * @return bP	Pointer to decoded string defaults to NULL
 */
const uint8_t * const WtoBstr(uint16_t w16, uint8_t * bP=NULL);

/** decode and  print debug level
 * 
 * prints list of debug levels enabled in "level"
 * @param level level to decode
 */
void printDbgLvl(uint16_t level);

/** print newline char if DbgLevel matches
 *
 * @param level  leval at witch to print
 */
void dbgNl(uint16_t level);


/** set/reset debug levels  in gloable DBgLevel
 * 
 * Sets the global DbgLevel bitmat to controll what messages are eneabled
 * the onOff paramete controls if the level bit(s) is set or cleared
 * the clear paramater controlls if DbgLevel is cleared of other bits on setting
 * has no efect on other bits if reseting bits
 * usually not used alone but via the SET_DBG... macros
 * 
 * @param level level(s) to enable / disable  see dbgLevel.h for levels
 * @param onOff set or unset
 * @param clear should all previous bits be cleared or not
 */
void setDbgLvl(uint16_t level,bool onOff,bool clear=false);


/** dump buffer in hex and ascii
 *
 * @param bP 	pointer to buffer to dump from
 * @param len	number of bytes to dump
 */
void dbgHexDump(const uint8_t *bP,int len);

#endif
