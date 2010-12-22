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

// cross platform
#ifdef _WIN32
#include "../base/ExceptionWin.h"
#else
#include "../base/Exception.h"
#endif

class Analyzer {
	protected:
		void checkForFirstTerm();
		void checkForSecondTerm();
		void checkForReal();
		void checkForSign();
		void checkForEqually();
		void checkForVar();
		bool checkByExpression(const char* expression);
		bool checkByStaticString(const char* string, const bool noTrows = false);
		
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
	public:
		Analyzer(char* subject);
		Analyzer(const Analyzer& orig);
		virtual ~Analyzer();
		
		void check();
};

#endif /* _ANALYZER_H */
