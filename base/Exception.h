/**
 * @author Azat Khuzhin
 *
 * Exception
 */

#ifndef _EXCEPTION_H
#define	_EXCEPTION_H

#include "../main.h"

#include <exception>
#include <execinfo.h>

class Exception : public exception {
	public:
		string message;
		char** stack;
		size_t size;
		static int max;
		
		Exception(string message = "") throw();
		Exception(const Exception& orig);
		virtual ~Exception() throw();
};

#endif /* _EXCEPTION_H */
