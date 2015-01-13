#ifndef _LINE_H_
#define _LINE_H_

#include "ofMain.h"

class LLine{
public:
	ofVec3f start, end;

	LLine(ofVec3f pStart, ofVec3f pEnd);
};

#endif