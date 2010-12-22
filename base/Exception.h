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
	protected:
		std::string message;
		int code;
		
		char** stack;
		std::size_t size;
		static int max;
	public:
		Exception(const std::string message = "", const int code = 0) throw();
		Exception(const Exception& orig);
		virtual ~Exception() throw();
		
		std::string getMessage();
		int getCode();
};

#endif /* _EXCEPTION_H */
