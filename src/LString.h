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
// + : turn left by angle, using rotation matrix Ru(-angle)
// - : turn right by angle, using rotation matrix Ru(angle)
// & : pitch down by angle, using rotation matrix Rl(-angle)
// ^ : pitch up by angle, using rotation matrix Rl(angle)
// \ : roll left by angle, using rotation matrix Rh(-angle)
// / : roll right by angle, using rotation matrx rh(angle)
// | : turn around using rotation matrix Ru(-180)
// [ : Push the current state of the turtle onto a pushdown
//     operations stack.The information saved on the stack contains the
//     turtle's position and orientation, and possibly other attributes
//     such as the color and width of lines being drawn.
// ] : Pop a state from the stack and make it the current state
//     of the turtle.No line is drawn, although in general the
//     position of the turtle changes.
// Ru(angle) : 
//             cos(angle)  sin(angle)      0
//            -sin(angle)  cos(angle)      0
//                0            0           1
// Rl(angle):
//            cos(angle)      0      -sin(angle)
//                0           1           0
//            sin(angle)      0      cos(angle)
// Rh(angle)
//                1           0           0
//                0      cos(angle)   -sin(angle)
//                0      sin(angle)    cos(angle)
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