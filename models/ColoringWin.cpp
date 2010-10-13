/**
 * @author Azat Khuzhin
 *
 * Coloring
 */

#include "ColoringWin.h"

/**
 * Init
 */
Coloring::Coloring() {
	hstdin  = GetStdHandle(STD_INPUT_HANDLE);
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
}

Coloring::Coloring(const Coloring& orig) {}
Coloring::~Coloring() {}

/**
 * Like printf function but use colors
 * 
 * @todo remember and restore previous color
 */
int Coloring::printf(int const color, const bool bold, const char* formatedString, ...) {
	va_list args;
	va_start(args, formatedString);
	
	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	// change color
	SetConsoleTextAttribute(hstdout, (bold ? color | FOREGROUND_INTENSITY : color));
	int status = vprintf(formatedString, args);
	FlushConsoleInputBuffer(hstdin);
	// Keep users happy
	SetConsoleTextAttribute(hstdout, csbi.wAttributes);
	
	va_end(args);
	
	return status;
}
