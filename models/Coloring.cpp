/**
 * @author Azat Khuzhin
 *
 * Coloring
 */

#include "Coloring.h"

Coloring::Coloring() {}
Coloring::Coloring(const Coloring& orig) {}
Coloring::~Coloring() {}

/**
 * Like printf function but use colors
 * 
 * @todo remember and restore previous color
 */
int Coloring::printf(const int color, const bool bold, const char* formatedString, ...) {
	va_list args;
	va_start(args, formatedString);
	
	::printf("\033[%u;%um", bold, color);
	int status = vprintf(formatedString, args);
	::printf("\033[0m");
	
	va_end(args);
	
	return status;
}
