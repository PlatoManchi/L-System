#ifndef _QUAD_H_
#define _QUAD_H_

#include <list>

#include "LLine.h"


class Quad{

	std::vector<LLine> lineList;
public:
	void AddLine( LLine pLine );
	LLine GetLine(unsigned pIndex);
	int LineCount();
};


#endif