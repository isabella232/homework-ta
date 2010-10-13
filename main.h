/**
 * @author Azat Khuzhin
 * 
 * Base includes
 */

#ifndef _MAIN_H
#      define	_MAIN_H

// debug moments
#define DEBUG
#define VERBOSE

// standart libraries
#include <stdlib.h>
#include <stdio.h>

using namespace std;

// cross platform
#ifdef _WIN32
#include "base/ExceptionWin.h"
#else
#include "base/Exception.h"
#endif

#endif	/* _MAIN_H */
