/**
 * @author Azat Khuzhin
 *
 * Diff
 */

#ifndef _DIFF_H
#	define _DIFF_H

#include "../main.h"

class Diff {
	public:
		Diff();
		Diff(const Diff& orig);
		virtual ~Diff();
};

#endif /* _DIFF_H */
