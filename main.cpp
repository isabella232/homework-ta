/**
 * @author Azat Khuzhin
 *
 * Main start
 */

#include "main.h"

// my models
// cross platform
#ifdef _WIN32
#include "models/ColoringWin.h"
#else
#include "models/Coloring.h"
#endif
// standart
#include "models/Diff.h"
#include "models/Analyzer.h"

/**
 * Main
 */
int main(int argc, char** argv) {
	Coloring* c = new Coloring();
	if (argc == 1 || strlen(argv[1]) == 0) {
		c->printf(Coloring::colorRed, false, "String is empty or not set\n");
	} else {
		Analyzer* a = new Analyzer(argv[1]);
		c->printf(Coloring::colorGreen, false, "String to check ");
		c->printf(Coloring::colorGreen, true, argv[1]);
		printf("\n");
		try {
			a->check();
			c->printf(Coloring::colorGreen, false, "All ok!\n");
		} catch (Exception* exp) {
			const char* error = (*exp).getMessage().c_str();
			c->printf(Coloring::colorRed, false, "Error occured: %s: at symbol %u\n", error, (*exp).getCode());
		}
		delete a;
	}
	delete c;
	
	return EXIT_SUCCESS;
}
