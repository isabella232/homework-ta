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
 * Seek string
 */
void Analyzer::seek() {
	subject++;
	currentPosition++;
}

/**
 * Check by expression
 */
bool Analyzer::checkByExpression(const char* expression, const bool noTrows) {
	std::string stack = "";
	size_t exprLength = strlen(expression);
	bool beginWrite = true;
	
	while (exprLength--) {
		if (beginWrite && (*expression != '|')) {
			stack += *expression;
		}
		if (beginWrite && (*expression == '|' || exprLength == 0)) {
			if (checkByStaticString(stack.c_str(), noTrows)) {
				return true;
			}
			stack = "";
		}
		expression++;
	}
	
	return false;
}

/**
 * Check by static string
 */
bool Analyzer::checkByStaticString(const char* string, const bool noTrows) {
	// and of string
	if (currentPosition >= length) {
		char buffer[12];
		
		char symbol[2];
		symbol[1] = 0;
		symbol[0] = *string;
		
		sprintf(buffer, "Must be '%s'", symbol);
		throw new Exception(buffer, currentPosition);
	}
	
	size_t stringLength = strlen(string);
	while (stringLength--) {
		if (*subject != *string) {
			if (noTrows) {
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
		seek();
	}
	
	return true;
}

/**
 * Check for first term/part
 */
void Analyzer::checkForFirstTerm() {
	if (checkByStaticString("(", true)) {
		checkByStaticString("d^2/d");
		checkForVar();
		checkByStaticString("^2)T");
	} else {
		checkByStaticString("d^2T/d");
		checkForVar();
		checkByStaticString("^2");
	}
	
	if (checkByExpression("-|+", true)) {
		checkForReal();
	}
}

/**
 * Check for second term/part
 */
void Analyzer::checkForSecondTerm() {
	if (checkByStaticString("(", true)) {
		checkByStaticString("dT/dt)");
	} else {
		checkByStaticString("dT/dt");
	}
}

/**
 * Check for var x|y|x|r
 */
void Analyzer::checkForVar() {
	checkByExpression("x|y|z|r");
}

/**
 * Check for real numbers
 */
void Analyzer::checkForReal() {
	bool hasOne = false;
	unsigned int level = 0;
	while (checkByExpression("0|1|2|3|4|5|6|7|8|9", true)) {
		if (!hasOne) hasOne = true;
		if (++level > Analyzer::MAX_NESTED_LEVEL) throw new Exception("Max nested level is reached", currentPosition);
	}
	if (hasOne) {
		if (checkByStaticString(".", true)) {
			level = 0;
			unsigned int subLevel = 0;
			while (checkByExpression("0", true)) {
				subLevel = 0;
				while (checkByExpression("1|2|3|4|5|6|7|8|9", true)) {
					if (++subLevel > Analyzer::MAX_NESTED_LEVEL) throw new Exception("Max nested level, after point, after '0', is reached", currentPosition);
				}
				if (++level > Analyzer::MAX_NESTED_LEVEL) throw new Exception("Max nested level, after point, is reached", currentPosition);
			}
			if (level == 0) {
				while (checkByExpression("1|2|3|4|5|6|7|8|9", true)) {
					if (++level > Analyzer::MAX_NESTED_LEVEL) throw new Exception("Max nested level, after point, exclude '0', is reached", currentPosition);
				}
			}
			if (level == 0) {
				checkByExpression("1|2|3|4|5|6|7|8|9");
			}
		}
		checkByStaticString("*");
		checkForSecondTerm();
	} else {
		checkForSecondTerm();
	}
}

/**
 * Check for "=0"
 */
void Analyzer::checkForEqually() {
	checkByStaticString("=0");
}

/**
 * Print sibject with highlighted error
 */
void Analyzer::printHighLightedError(unsigned int offset) {
	// seekers & convert from char* => string
	subject -= currentPosition;
	std::string subjectAsString = subject;
	subject += currentPosition;
	
	Coloring* c = new Coloring();
	c->printf(Coloring::colorGreen, true, "%s", subjectAsString.substr(0, currentPosition).c_str());
	// replace white space => "_"
	if (subjectAsString.substr(currentPosition, 1) != " ") {
		c->printf(Coloring::colorRed, true, "%s", subjectAsString.substr(currentPosition, 1).c_str());
	} else {
		c->printf(Coloring::colorRed, true, "_");
	}
	c->printf(Coloring::colorGreen, true, "%s", subjectAsString.substr(currentPosition+1, subjectAsString.length()).c_str());
	delete c;
}

/**
 * Main
 */
void Analyzer::check() {
	checkForFirstTerm();
	checkForEqually();
}
