/**
 * @author Azat Khuzhin
 *
 * Coloring
 */

#ifndef _COLORING_H
#	define _COLORING_H

#include <stdarg.h>
#include <stdio.h>

class Coloring {
	public:
		Coloring();
		Coloring(const Coloring& orig);
		virtual ~Coloring();
		
		static const int colorRed 	= 31;
		static const int colorGreen 	= 32;
		static const int colorYellow 	= 33;
		static const int colorBlue 	= 34;
		static const int colorPink 	= 35;
		static const int colorTeal 	= 36;
		static const int colorWhite 	= 37;
		
		int printf(const int color, const bool bold, const char* formatedString, ...);
};

#endif /* _COLORING_H */
