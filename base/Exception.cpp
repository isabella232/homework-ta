/**
 * @author Azat Khuzhin
 *
 * Exception
 */

#include "Exception.h"

/**
  * define max stack size
  * 
  * @see execinfo.h
  */
#ifdef DEBUG
int Exception::max = 10;
#else
int Exception::max = 1;
#endif

/**
  * Throw an instance of Exception
  * 
  * @link http://www.gnu.org/s/libc/manual/html_node/Backtraces.html
  */
Exception::Exception(const std::string message, const int code) throw() {
	this->message = message;
	this->code = code;
	
	void* array[max];
	size = backtrace(array, max);
	stack = backtrace_symbols(array, size);
	// free(array);
}

Exception::Exception(const Exception& orig) {}
Exception::~Exception() throw() {}

/**
 * Get message
 */
std::string Exception::getMessage() {
	return message;
}

/**
 * Get code
 */
int Exception::getCode() {
	return code;
}
