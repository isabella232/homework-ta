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
#include <cstring>

using namespace std;

// cross platform exceptions
#ifdef _WIN32
#include "base/ExceptionWin.h"
#else
#include "base/Exception.h"
#endif

// cross platform coloring output
#ifdef _WIN32
#include "models/ColoringWin.h"
#else
#include "models/Coloring.h"
#endif

// standart my models
#include "models/Diff.h"
#include "models/Analyzer.h"

#endif	/* _MAIN_H */
