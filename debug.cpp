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
/** \file debug.cpp */
#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "dbgLevels.h"
//#define DEBUG_LEVEL DBG_DBGL
#include "debug.h"

uint16_t DbgLevel=DBG_DEF_L;
const char * dbgLvlTxt[]={
	"FAIL", //0
	"ERROR", //1
	"WARN",	//2
	"INFO", //3
	"1F",	//4
	"2F",	//5
	"3F",	//6
	"1V",	//7
	"2v",	//8
	"3V",	//9
	"VERBOSE" // 10
	};

// print debug message

void dbg(uint16_t level,bool prefix,const char * format,...) {
va_list ap;
const char* tmp="";

    if((DbgLevel & level ) && (format!=nullptr)) {  // level not high enough or no format ? ignore...
		if(prefix) {
			switch (DbgLevel & level) {
				case DBG_FAIL_L:
					tmp="FAIL:";
					break;
				case DBG_ERROR_L:
					tmp="ERROR:";
					break;
				case DBG_WARN_L:
					tmp="WARN:";
					break;
				case DBG_INFO_L:
					tmp="INFO:";
					break;
				case DBG_1F_L:
				case DBG_1V_L:
					tmp="DBG1:";
					break;
				case DBG_2F_L:
				case DBG_2V_L:
					tmp="DBG2:";
					break;
				case DBG_3F_L:
				case DBG_3V_L:
					tmp="DBG3:";
					break;
				case DBG_VERB_L:
					tmp="VERB:";
					break;
				default:
					tmp="";
			}
			printf(tmp);			// print preample if anny
		}
		va_start(ap, format);
		vprintf(format,ap);
	}
}

void dbgHexDump(const uint8_t *bP,int len) {

	uint8_t s[40];
    int i,j,l;

	printf("hexdump %d (%2.2x) bytes\n",len,len);
    printf("    ");
    for(i=0; i<16 && i< len;i++)
        printf("%2.2x ",i);
    printf("\n");
    printf("    ");
    for(i=0; i<16 && i< len;i++)
        printf("---");
    printf("\n");

    for(i =0 ; i <len ; i++ ) {
        s[(i%16)] = *bP>=' ' && *bP<='z'?*bP:'.'; // build asci representation string

        if(!((i)%16) ) {
                printf("%2.2d: ", i/16);    // are vi on a new line ? print line number
        }
        printf("%2.2x ",*bP++);              // print hex value of current byte

        if (!((i+1)%16) && i>0) {           // have printed 16 bytes ?
            printf("\t");                   // yep , print ascii reprenstaiton

            for (j=0;j<16;j++) {
                printf("%c ",s[j]);
            }

            printf("\n");
        }
    }

    if((i+1)%16) {              // take care of eventual tail in ascii buffer
        for(j=0;j<((i+1)%16);j++)
            printf("%c ",s[j]);

    }
    printf("\n");
}

const uint8_t * const WtoBstr(uint16_t b,uint8_t * out) {
	static uint8_t str[20];
	uint8_t *bp = (bp == NULL)? str:out;
	int j,i;
	for (i=j=0;i<17;i++,j++) {
		str[16-j]= (b&(1<<i))? '1': '0';
		if(i == 7){
			str[8]=' ';
			j++;
		}
	}
	str[17]=0;
	return bp;
}

void printDbgLvl(uint16_t level) {
	printf("DbgLevel=(%s))=>: ",WtoBstr(DbgLevel));
	for(int i=0;i<11;i++) {
		if(DbgLevel &(1<<i))
			printf("%s ",dbgLvlTxt[i]);
	}
	printf("\n");
}

void setDbgLvl(uint16_t level,bool onOff,bool clear) {
	if(onOff)
		if (clear) DbgLevel = level;
		else DbgLevel |= level;
	else
		DbgLevel &= !level;
	printDbgLvl(DbgLevel);

}

void dbgNl(uint16_t level) {
	if(DbgLevel&level){
		 putchar('\n');
	}
}