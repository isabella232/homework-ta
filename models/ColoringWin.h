/**
 * @author Azat Khuzhin
 *
 * Coloring
 */

#ifndef _COLORING_WIN_H
#	define _COLORING_WIN_H

#include <stdarg.h>
#include <stdio.h>
#include <windows.h>

class Coloring {
	public:
		Coloring();
		Coloring(const Coloring& orig);
		virtual ~Coloring();
		
		static const int colorRed 	= FOREGROUND_RED;
		static const int colorGreen 	= FOREGROUND_GREEN;
		static const int colorYellow 	= FOREGROUND_GREEN | FOREGROUND_RED;
		static const int colorBlue 	= FOREGROUND_BLUE;
		static const int colorPink 	= FOREGROUND_RED | FOREGROUND_BLUE;
		static const int colorTeal 	= FOREGROUND_GREEN | FOREGROUND_BLUE;
		static const int colorWhite 	= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		
		int printf(int const color, const bool bold, const char* formatedString, ...);
		
	private:
		HANDLE hstdin;
		HANDLE hstdout;
};

#endif /* _COLORING_WIN_H */
