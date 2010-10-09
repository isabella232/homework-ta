/**
 * @author Azat Khuzhin
 *
 * Exception
 */

#ifndef _EXCEPTION_H
#define	_EXCEPTION_H

#include <string>
#include <exception>
#include <execinfo.h>

class Exception : public std::exception {
	public:
		std::string message;
		char** stack;
		std::size_t size;
		static int max;
		
		Exception(std::string message = "") throw();
		Exception(const Exception& orig);
		virtual ~Exception() throw();
};

#endif /* _EXCEPTION_H */
