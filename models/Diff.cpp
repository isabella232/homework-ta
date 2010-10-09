/**
 * @author Azat Khuzhin
 *
 * Diff
 */

#include "Diff.h"

Diff::Diff(const Diff& orig) {}
Diff::~Diff() {}

/**
 * Set default options
 */
Diff::Diff() {
	this->beforeMatch = "|";
	this->afterMatch = "|";
}

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
	std::string routeRev;
	for (i = route.size(); i >= 0; --i) {
		routeRev += route[i];
	}

	Diff::LevenshteinVerboseReturn result;
	result["distance"] = D[srcLength][dstLength];
	result["route"] = routeRev;
	
	return result;
}


/**
 * Highlight difference between two phrases
 */
std::string Diff::highLight(const std::string& src, const std::string& dst) {
	Diff::LevenshteinVerboseReturn levenshtein = this->LevenshteinVerbose(src, dst);
	std::string dstHighLighted = dst;
	std::string levenshteinRoute = levenshtein["route"];
	unsigned int levenshteinRouteLen = levenshteinRoute.size();

	unsigned int begin = -1; // default: negative
	bool last = false;
	unsigned int l, offset = 0, beginOffset = 0;
	char c;
	for (unsigned int i = 0; i < levenshteinRouteLen; i++) {
		c = levenshteinRoute[i];

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
						this->beforeMatch + dstHighLighted.substr(begin + offset, i - begin + (last ? 1 : 0)) + this->afterMatch +
						dstHighLighted.substr(i + offset + (last ? 1 : 0), l);

			offset += this->beforeMatch.size() +this->afterMatch.size();
			begin = -1;
		}
	}
	return dstHighLighted;
}