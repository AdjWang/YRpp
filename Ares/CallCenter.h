#ifndef CALLCENTER_H
#define CALLCENTER_H

#include <YRPP.h>
#include <YRCallbacks.h>

#include "Ares.h"
#include "Foundations.h"
#include "Countries.h"

/*
	Since only one function can be assigned to the YRPP callbacks,
	I'll introduce a "call center" to allow multiple functions.
*/

class CallCenter
{
public:
	static void Init();

};

#endif
