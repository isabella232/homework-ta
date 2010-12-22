/**
 * @author Azat Khuzhin
 *
 * Exception
 * Fucking Win
 */

#ifndef _EXCEPTION_WIN_H
#define	_EXCEPTION_WIN_H

#include <string>
#include <exception>

class Exception : public std::exception {
	protected:
		std::string message;
		int code;
	public:
		Exception(const std::string message = "", const int code = 0) throw();
		Exception(const Exception& orig);
		virtual ~Exception() throw();
		
		std::string getMessage();
		int getCode();
};

#endif /* _EXCEPTION_WIN_H */
