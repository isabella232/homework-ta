/**
 * @author Azat Khuzhin
 *
 * Heat equation analyzer
 */

#ifndef _ANALYZER_H
#define	_ANALYZER_H

#include <stdio.h>
#include <cstring>
#include <string>

// cross platform exceptions
#ifdef _WIN32
#include "../base/ExceptionWin.h"
#else
#include "../base/Exception.h"
#endif

// cross platform coloring output
#ifdef _WIN32
#include "ColoringWin.h"
#else
#include "Coloring.h"
#endif

class Analyzer {
	protected:
		void checkForFirstTerm();
		void checkForSecondTerm();
		void checkForReal();
		void checkForEqually();
		void checkForVar();
		bool checkByExpression(const char* expression, const bool noTrows = false);
		bool checkByStaticString(const char* string = NULL, const bool noTrows = false);
		void seek();
		
		/**
		 * Subject to check
		 */
		char* subject;
		/**
		 * Length of string
		 */
		size_t length;
		/**
		 * Current pos in subject
		 */
		int currentPosition;
		/**
		 * Max nested level for while() {}
		 * 
		 * Basicly for checkByReal()
		 */
		static unsigned int const MAX_NESTED_LEVEL = 100;
	public:
		Analyzer(char* subject);
		Analyzer(const Analyzer& orig);
		virtual ~Analyzer();
		
		void check();
		void printHighLightedError(unsigned int offset);
		
		/**
		 * Max subject length
		 */
		static unsigned int const SUBJECT_LIMIT = 1000;
};

#endif /* _ANALYZER_H */
