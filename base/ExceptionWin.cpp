/**
 * @author Azat Khuzhin
 *
 * Exception
 * Fucking Win
 */

#include "ExceptionWin.h"

/**
  * Throw an instance of Exception
  * 
  * @link http://www.gnu.org/s/libc/manual/html_node/Backtraces.html
  */
Exception::Exception(const std::string message, const int code) throw() {
	this->message = message;
	this->code = code;
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
