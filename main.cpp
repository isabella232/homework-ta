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
	// Words difference
	Diff* d = new Diff();
	const string src = "checkout";
	const string dst = "checvout";
	unsigned int distance = d->Levenshtein(src, dst);
	delete d;
	printf("Difference between %s and %s is: %u\n", src.c_str(), dst.c_str(), distance);
	
	// Coloring
	Coloring* c = new Coloring();
	c->printf(FOREGROUND_RED, 		false, "It some more this franch buns\n");
	c->printf(FOREGROUND_BLUE, 		false, "It some more this franch buns\n");
	c->printf(FOREGROUND_GREEN, 		false, "It some more this franch buns\n");
	delete c;
	
	return EXIT_SUCCESS;
}
