/**
 * @author Azat Khuzhin
 *
 * Diff
 */

#include "Diff.h"

/**
 * Set default options
 */
Diff::Diff() {
	beforeMatch = '|';
	afterMatch = '|';
	defaultColor = Coloring::colorRed;
	isBold = true;
}

Diff::Diff(const Diff& orig) {}
Diff::~Diff() {}

/**
 * Count Levenshtein length/distance
 *
 * @link http://ru.wikipedia.org/wiki/%D0%94%D0%B8%D1%81%D1%82%D0%B0%D0%BD%D1%86%D0%B8%D1%8F_%D0%9B%D0%B5%D0%B2%D0%B5%D0%BD%D1%88%D1%82%D0%B5%D0%B9%D0%BD%D0%B0
 */
unsigned int Diff::Levenshtein(const std::string& src, const std::string& dst) {
	const unsigned int srcLength = src.size();
	const unsigned int dstLength = dst.size();

	if (srcLength == 0) return dstLength;
	if (dstLength == 0) return srcLength;

	// basic options
	std::vector< std::vector<unsigned int> > matrix(srcLength + 1);
	for (unsigned int  i = 0; i <= srcLength; ++i) {
		matrix[i].resize(dstLength + 1);
		matrix[i][0] = i;
	}
	for (unsigned int i = 0; i <= dstLength; ++i) {
		matrix[0][i] = i;
	}

	unsigned int aboveCell, leftCell, diagonalCell, cost;
	for (unsigned int  i = 1; i <= srcLength; ++i) {
		for (unsigned int  j = 1; j <= dstLength; ++j) {
			cost = src[i-1] == dst[j-1] ? 0 : 1;
			aboveCell = matrix[i-1][j];
			leftCell = matrix[i][j-1];
			diagonalCell = matrix[i-1][j-1];
			matrix[i][j] = std::min(std::min(aboveCell + 1, leftCell + 1), diagonalCell + cost);
		}
	}

	return matrix[srcLength][dstLength];
}

/**
 * Count Levenshtein length/distance & route
 *
 * @link http://ru.wikipedia.org/wiki/%D0%94%D0%B8%D1%81%D1%82%D0%B0%D0%BD%D1%86%D0%B8%D1%8F_%D0%9B%D0%B5%D0%B2%D0%B5%D0%BD%D1%88%D1%82%D0%B5%D0%B9%D0%BD%D0%B0
 */
Diff::LevenshteinVerboseReturn Diff::LevenshteinVerbose(const std::string& src, const std::string& dst) {
	unsigned int srcLength = src.size();
	unsigned int dstLength = dst.size();
	std::vector< std::vector<unsigned int> > P(srcLength+1), D(srcLength+1);
	
	// basic options
	for (unsigned int i = 0; i <= srcLength; i++) {
		P[i].resize(dstLength+1);
		D[i].resize(dstLength+1);
		
		D[i][0] = i;
		P[i][0] = 'D';
	}
	for (unsigned int i = 0; i <= dstLength; i++) {
		D[0][i] = i;
		P[0][i] = 'I';
	}

	unsigned int cost = 0;
	for (unsigned int i = 1; i <= srcLength; i++) {
		for (unsigned int j = 1; j <= dstLength; j++) {
			cost = (src[i - 1] != dst[j - 1]) ? 1 : 0;
			// insert
			if (D[i][j - 1] < D[i - 1][j] && D[i][j - 1] < D[i - 1][j - 1] + cost) {
				D[i][j] = D[i][j - 1] + 1;
				P[i][j] = 'I';
			}
			// delete
			else if (D[i - 1][j] < D[i - 1][j - 1] + cost) {
				D[i][j] = D[i - 1][j] + 1;
				P[i][j] = 'D';
			}
			// replace or nothing
			else {
				D[i][j] = D[i - 1][j - 1] + cost;
				P[i][j] = (cost == 1) ? 'R' : 'M';
			}
		}
	}

	// restore prescription
	std::string route;
	unsigned int i = srcLength;
	unsigned int j = dstLength;
	unsigned int c;
	do {
		c = P[i][j];
		route += c;
		if (c == 'R' || c == 'M') {
			i--;
			j--;
		} else if (c == 'D') {
			i--;
		} else {
			j--;
		}
	} while ((i != 0) && (j != 0));
	
	// revert string
	std::string routeRev = "";
	std::string::reverse_iterator iter = route.rbegin();
	while (iter != route.rend()) {
		routeRev += *iter++;
	}
	
	Diff::LevenshteinVerboseReturn result;
	result["distance"] = D[srcLength][dstLength];
	result["route"] = routeRev;
	
	return result;
}


/**
 * Difference between two phrases
 */
std::string Diff::get(const std::string& src, const std::string& dst) {
	Diff::LevenshteinVerboseReturn levenshtein = LevenshteinVerbose(src, dst);
	std::string dstHighLighted = dst;
	std::string levenshteinRoute = levenshtein["route"];
	unsigned int levenshteinRouteLen = levenshteinRoute.size();

	bool last = false;
	char c;
	int begin = -1;
	unsigned int l = 0, offset = 0, beginOffset = 0, i = 0;
	std::string::iterator iter = levenshteinRoute.begin();
	while (iter != levenshteinRoute.end()) {
		c = *iter++;
		
		if (c == 'D') {
			beginOffset--;
			continue;
		}
		if ((c == 'I' || c == 'R') && begin < 0) {
			begin = i + beginOffset;
		}
		if ((c == 'M' || (i+1) == levenshteinRouteLen) && begin >= 0) {
			l = dstHighLighted.size();
			if ((i+1) == levenshteinRouteLen && c != 'M') last = true;

			dstHighLighted = 	dstHighLighted.substr(0, begin + offset) +
						beforeMatch + dstHighLighted.substr(begin + offset, i - begin + (last ? 1 : 0)) + afterMatch +
						dstHighLighted.substr(i + offset + (last ? 1 : 0), l);

			offset += 2;
			begin = -1;
		}
		
		i++;
	}
	return dstHighLighted;
}

/**
 * Print highligh
 * 
 * @TODO
 */
void Diff::highLight(const std::string& src, const std::string& dst) {
	std::string newDst = get(src, dst);
	int begin = -1, i = 0;
	unsigned int offset = 0;
	std::string::iterator iter = newDst.begin();
	char c;
	
	while (iter != newDst.end()) {
		c = *iter++;
		
		if (c == beforeMatch && begin < 0) {
			begin = i;
		} else if (c == afterMatch && begin >= 0) {
			::printf(newDst.substr(offset, begin - offset).c_str());
			printf(defaultColor, isBold, newDst.substr(begin + 1, i - begin - 1).c_str()); // colored part
			offset = i + 1;
			begin = -1;
		}
		
		i++;
	}
	// afterMatch - not at the end
	offset -= 1;
	if (offset != i) {
		::printf(newDst.substr(offset + 1, newDst.size() - 1).c_str());
	}
}
