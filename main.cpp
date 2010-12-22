/**
 * @author Azat Khuzhin
 *
 * Main start
 */

#include "main.h"

/**
 * Main
 */
int main(int argc, char** argv) {
	Coloring* c = new Coloring();
	
	// check for empty string
	if (argc == 1 || strlen(argv[1]) == 0) {
		c->printf(Coloring::colorRed, false, "String is empty or not set\n");
	}
	// check for too long string
	else if (strlen(argv[1]) > Analyzer::SUBJECT_LIMIT) {
		c->printf(Coloring::colorRed, false, "Length of input sting can`t be more then %u symbols\n", Analyzer::SUBJECT_LIMIT);
	}
	// analyze input string
	else {
		Analyzer* a = new Analyzer(argv[1]);
		c->printf(Coloring::colorGreen, false, "String to check ");
		c->printf(Coloring::colorGreen, true, argv[1]);
		printf("\n");
		try {
			a->check();
			c->printf(Coloring::colorGreen, false, "All ok!\n");
		} catch (Exception* exc) {
			const char* error = (*exc).getMessage().c_str();
			const int code = (*exc).getCode();
			c->printf(Coloring::colorRed, false, "Error occured: %s: at symbol %u\n", error, code+1);
			c->printf(Coloring::colorRed, false, "Human view of error: ");
			a->printHighLightedError(code);
			printf("\n");
		}
		delete a;
	}
	delete c;
	
	return EXIT_SUCCESS;
}
