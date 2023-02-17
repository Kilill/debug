# debug library 
see dbgLevel.h for the diffierent levels and debug.h for macros and functions

a set of macros and print routines to print debug information
rellies heavly on printf functionality 

Debug printout can be controlled runtime using setDebg

levels are bitmapped so that they can be enabled/disable turned on/of individually

Debug macros are null defined unless corresponding level enabled in DEBUG_LEVEL
meaning that no code will be created, so that all debuggin can be stripped out


# usage:

```
#include "dbgLevels.h"

// which macros are going to be included
// if not set the default is (DBG_FAIL_L|DBG_ERROR_L|DBG_WARN_L|DBG_INFO_L)
#define DEBUG_LEVEL (DBG_DEF_L|DBGFV1_L)

#include "debug.h"

void someFunc() {
	int someVar;
	DBGF1("In some func\n)
	DBGV1("someVar = %d",someVar);
	
	DBG3("this can not be printed since DEBUG_LEVEL does not have DBG_3F_L set");
}


void someOtherFunc(int var1, int var2) {
	INFO("in function someOtherFunc\n");
	if(var1 == var2) {
		DBG1F("we have twins!");
		DBG1V_S("Var 1,2: %d , %d",var1,var2);
		DBG1NL;
	}
}

main() {

	INFO("program starting\n");
	someFunc();

	//after this no nothing will be printed not even Fail,Error or Warnings
	setDbgLvl(NONE_DBGL,OFF,CLR);	// dynamically turn of all text
	// for conviniance this is the same:
	SET_DBG_NONE;
	// someOtherFunc's debug will not show
	someOtherFunc();
}

```

