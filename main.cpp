/**
 * @author Azat Khuzhin
 *
 * Main start
 */

#include "main.h"

// my models
#include "models/Coloring.h"
#include "models/Diff.h"
#include "models/Analyzer.h"

/**
 * Main
 */
int main(int argc, char** argv) {
	Diff* d = new Diff();
	const string src = "checkout";
	const string dst = "checvout";
	unsigned int distance = d->Levenshtein(src, dst);
	delete d;
	printf("Difference between %s and %s is: %u\n", src.c_str(), dst.c_str(), distance);
	
	return EXIT_SUCCESS;
}
