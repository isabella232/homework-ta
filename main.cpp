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
	const string src = "hheckout";
	const string dst = "checvour";
	unsigned int distance = d->Levenshtein(src, dst);
	printf("Difference between %s and %s is: %u\n", src.c_str(), dst.c_str(), distance);
	d->highLight(src, dst);
	printf("\n");
	delete d;
	
	return EXIT_SUCCESS;
}
