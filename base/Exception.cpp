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
Exception::Exception(std::string message) throw() {
	this->message = message;
	
	void* array[max];
	size = backtrace(array, max);
	stack = backtrace_symbols(array, size);
	// free(array);
}

Exception::Exception(const Exception& orig) {}
Exception::~Exception() throw() {}
