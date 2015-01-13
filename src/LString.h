#ifndef _LSTRING_
#define _LSTRING_

#include <iostream>
#include <string>
#include <list>
#include <stdarg.h>

#include "ofMain.h"
#include "LLineStack.h";
#include "Quad.h";

// rules 
// F : move forward and draw line forward
// f : move forward without drawing line forward
// + : rotate counter clock wise (add angle)
// - : rotate clock wise (substract angle)
class LString{

public:
	LString();

	string GetLString(int pIteration, int pArgCount, ...);
	Quad GenerateQuad( string pLString, float pAngle );
private:
	std::list<LLineStack> LStringStack;
	
	string replace(string pSource, string pDelimiter, string pReplaceString);
	ofVec3f RotateVector( ofMatrix3x3 pRotationMatrix, ofVec3f pVector );
};
#endif