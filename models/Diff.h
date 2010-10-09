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

class Diff {
	public:
		Diff();
		Diff(const Diff& orig);
		~Diff();
		
		typedef std::map<std::string, std::string> LevenshteinVerboseReturn;
		std::string beforeMatch;
		std::string afterMatch;
		
		unsigned int Levenshtein(const std::string& src, const std::string& dst);
		Diff::LevenshteinVerboseReturn LevenshteinVerbose(const std::string& src, const std::string& dst);
		std::string highLight(const std::string& src, const std::string& dst);
};

#endif /* _DIFF_H */
