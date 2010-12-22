/**
 * @author Azat Khuzhin
 *
 * Heat equation analyzer
 */

#include "Analyzer.h"

Analyzer::Analyzer(char* subject) {
	this->subject = subject;
	this->length = strlen(subject);
	this->currentPosition = 0;
}

Analyzer::Analyzer(const Analyzer& orig) {}
Analyzer::~Analyzer() {}

/**
 * Check by expression
 */
bool Analyzer::checkByExpression(const char* expression) {
	std::string stack = "";
	size_t expLength = strlen(expression);
	bool beginWrite = true;
	
	while (expLength--) {
		if (beginWrite && (*expression != '|')) {
			stack += (char)*expression;
		} else if (beginWrite && (*expression == '|')) {
			checkByStaticString(stack.c_str());
			stack = "";
		}
		expression++;
	}
	
	return true;
}

/**
 * Check by static string
 */
bool Analyzer::checkByStaticString(const char* string, const bool noTrows) {
	if (currentPosition >= length) throw new Exception("End of string", currentPosition);
	
	size_t stringLength = strlen(string);
	while (stringLength--) {
		if (*subject != *string) {
			if (noTrows) {
				subject++;
				currentPosition++;
				return false;
			} else {
				char buffer[12];
				
				char symbol[2];
				symbol[1] = 0;
				symbol[0] = *string;
				
				sprintf(buffer, "Must be '%s'", symbol);
				throw new Exception(buffer, currentPosition);
			}
		}
		
		string++;
		subject++;
		currentPosition++;
	}
	
	return true;
}

/**
 * Check for first term/part
 */
void Analyzer::checkForFirstTerm() {
	if (checkByStaticString("(", true)) {
		checkByStaticString("d^2/d");
		checkByExpression("x|y|z|r");
		checkByStaticString("^2)T");
	} else {
		checkByStaticString("d^2T/d");
		checkByExpression("x|y|z|r");
		checkByStaticString("^2");
	}
}

/**
 * Check for second term/part
 */
void Analyzer::checkForSecondTerm() {
}

/**
 * Check for var x|y|x|r
 */
void Analyzer::checkForVar() {
}

/**
 * Check for real numbers
 */
void Analyzer::checkForReal() {
}

/**
 * Check for -|+
 */
void Analyzer::checkForSign() {
}

/**
 * Check for "=0"
 */
void Analyzer::checkForEqually() {
}

/**
 * Main
 */
void Analyzer::check() {
	checkForFirstTerm();
}
