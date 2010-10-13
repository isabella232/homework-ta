/**
 * @author Azat Khuzhin
 *
 * Diff
 */

#ifndef _DIFF_H
#	define _DIFF_H

#include <string>
#include <vector>
#include <map>
#include <stdio.h>

#include "Coloring.h"

class Diff : public Coloring {
	public:
		Diff();
		Diff(const Diff& orig);
		~Diff();
		
		typedef std::map<std::string, std::string> LevenshteinVerboseReturn;
		char beforeMatch;
		char afterMatch;
		int defaultColor;
		bool isBold;
		
		unsigned int Levenshtein(const std::string& src, const std::string& dst);
		Diff::LevenshteinVerboseReturn LevenshteinVerbose(const std::string& src, const std::string& dst);
		std::string get(const std::string& src, const std::string& dst);
		void highLight(const std::string& src, const std::string& dst);
};

#endif /* _DIFF_H */
