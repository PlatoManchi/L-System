#ifndef _LLINE_STACK_H_
#define _LLINE_STACK_H_

#include "LLine.h";

class LLineStack{
public:
	LLine line;
	ofVec3f direction;

	LLineStack(LLine pLine, ofVec3f pDirection) : line(pLine), direction (pDirection){

	}
};

#endif