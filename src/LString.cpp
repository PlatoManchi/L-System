#include "LString.h"
#include <math.h>

LString::LString( ){
	
}

string LString::GetLString(int pIteration, int pArgCount, ...){
	const int s = pArgCount;
	std::vector<string> rules;

	//ofLog() << "Args count : " << pArgCount;

	va_list ap;
	va_start(ap, pArgCount);
	string axiom = va_arg(ap, string);

	//ofLog() << "Axiom : '" << axiom << "'";

	for (int i = 0; i < pArgCount - 1; i++) {
		string rule = va_arg(ap, string);
		//ofLog() << i + 1 << " rule : '" << rule << "'";
		rules.push_back(rule);
		//rules[i] = rule;
	}
	va_end(ap);

	string result = axiom;
	
	for (int itr = 0; itr < pIteration; itr++){
		for (int ruleCount = 0; ruleCount < pArgCount - 1; ruleCount++){
			
			string rule = rules[ruleCount];
			string variable = "";
			string equation = "";
			bool isFindingVariable = true;

			// seperating the variable and equation from
			// the rule
			for (int i = 0; i < rule.size(); i++){
				if (rule[i] != '='){
					if (isFindingVariable){
						variable += rule[i];
					}
					else{
						equation += rule[i];
					}
				}
				else{
					isFindingVariable = false;
				}
			}

			// now replacing the variable with equation
			//ofLog() << "replacing '" << variable << "' with " << equation;
			result = replace(result, variable, equation);
			//ofLog() << result;
		}
	}

	return result;
}

string LString::replace(string pSource, string pDelimiter, string pReplaceString){
	string result="";
	for (int i = 0; i < pSource.size(); i++){
		string tmp = pSource.substr( i, pDelimiter.size() );
		if (tmp.compare(pDelimiter) == 0){
			result += pReplaceString;
			i = i + pDelimiter.size() - 1;
			//ofLog() << tmp << "==" << pDelimiter << " : " << result << "(" << i << ")";
		}
		else{
			result += pSource.substr(i, 1);
			//ofLog() << tmp << "!=" << pDelimiter << " : " << result << "(" << i << ")";
		}
	}

	return result;
}

// rules 
// F : move forward and draw line forward
// f : move forward without drawing line forward
// + : rotate counter clock wise (add angle)
// - : rotate clock wise (substract angle)
Quad LString::GenerateQuad(string pLString, float pAngle){

	Quad quad;

	// this unit vector is only for direction
	ofVec3f unitDirectionVector(0.0f, -1.0f, 0.0f);
	LLine prevLine(ofVec3f(0.0f, -1.0f, 0.0f), ofVec3f(0.0f, 0.0f, 0.0f));

	float m_CurrentLineLength = 10.0f;
	float rotationAngle = pAngle * (M_TWO_PI / 360.0f);

	LStringStack.clear();

	for (int i = 0; i < pLString.size(); i++){
		char operation = pLString[i];

		if (operation == 'F'){
			// this is for batching the 'F'. if there are four 'F'
			// instead of drawing 4 small lines drawing one big line is
			// better for performance
			/*int numOfF = 0;
			for (int j = i; j < pLString.size(); j++){
				if (pLString[j] == 'F')	numOfF++;
				else break;
			}
			i = i + numOfF - 1;*/

			ofVec3f start = prevLine.end;
			ofVec3f end = start + m_CurrentLineLength  * unitDirectionVector;

			LLine tmpLine(start, end);

			prevLine = tmpLine;

			quad.AddLine(tmpLine);
		}
		else if (operation == 'f'){
			ofVec3f start = prevLine.end;
			ofVec3f end = start + m_CurrentLineLength * unitDirectionVector;

			LLine tmpLine(start, end);
			prevLine = tmpLine;
		}
		else if (operation == '+'){
			//  cos(angle)  sin(angle)      0
			// -sin(angle)  cos(angle)      0
			//     0            0           1
			ofMatrix3x3 rotationMatrix;
			rotationMatrix.a = cosf( -rotationAngle );
			rotationMatrix.b = sinf( -rotationAngle );
			rotationMatrix.c = 0;

			rotationMatrix.d = -sinf( -rotationAngle );
			rotationMatrix.e = cosf( -rotationAngle );
			rotationMatrix.f = 0;

			rotationMatrix.g = 0;
			rotationMatrix.h = 0;
			rotationMatrix.i = 1;

			unitDirectionVector = unitDirectionVector.rotateRad(-rotationAngle, ofVec3f(0.0f, 0.0f, 1.0f));
			//unitDirectionVector = RotateVector(rotationMatrix, unitDirectionVector);
			//ofLog() << unitDirectionVector.x << ", " << unitDirectionVector.y << ", " << unitDirectionVector.z;
		}
		else if (operation == '-'){
			//  cos(angle)  sin(angle)      0
			// -sin(angle)  cos(angle)      0
			//     0            0           1
			ofMatrix3x3 rotationMatrix;
			rotationMatrix.a = cosf(rotationAngle);
			rotationMatrix.b = sinf(rotationAngle);
			rotationMatrix.c = 0;

			rotationMatrix.d = -sinf(rotationAngle);
			rotationMatrix.e = cosf(rotationAngle);
			rotationMatrix.f = 0;

			rotationMatrix.g = 0;
			rotationMatrix.h = 0;
			rotationMatrix.i = 1;

			//unitDirectionVector = RotateVector(rotationMatrix, unitDirectionVector);
			unitDirectionVector = unitDirectionVector.rotateRad(rotationAngle, ofVec3f(0.0f, 0.0f, 1.0f));
			//ofLog() << unitDirectionVector.x << ", " << unitDirectionVector.y << ", " << unitDirectionVector.z;
		}
		else if (operation == '&'){
			//  cos(angle)      0      sin(angle)
			//      0           1           0
			//  sin(angle)      0      cos(angle)
			ofMatrix3x3 rotationMatrix;
			rotationMatrix.a = cosf(rotationAngle);
			rotationMatrix.b = 0;
			rotationMatrix.c = sinf(rotationAngle);

			rotationMatrix.d = 0;
			rotationMatrix.e = 1;
			rotationMatrix.f = 0;

			rotationMatrix.g = sinf(rotationAngle);
			rotationMatrix.h = 0;
			rotationMatrix.i = cosf(rotationAngle);

			unitDirectionVector = RotateVector(rotationMatrix, unitDirectionVector);
			//unitDirectionVector = unitDirectionVector.rotateRad(PI-rotationAngle, ofVec3f(0.0f, 1.0f, 0.0f));
			//ofLog() << unitDirectionVector.x << ", " << unitDirectionVector.y << ", " << unitDirectionVector.z;
		}
		else if (operation == '^'){
			//  cos(angle)      0      sin(angle)
			//      0           1           0
			//  sin(angle)      0      cos(angle)
			ofMatrix3x3 rotationMatrix;
			rotationMatrix.a = cosf(-rotationAngle);
			rotationMatrix.b = 0;
			rotationMatrix.c = sinf(-rotationAngle);

			rotationMatrix.d = 0;
			rotationMatrix.e = 1;
			rotationMatrix.f = 0;

			rotationMatrix.g = sinf(-rotationAngle);
			rotationMatrix.h = 0;
			rotationMatrix.i = cosf(-rotationAngle);

			unitDirectionVector = RotateVector(rotationMatrix, unitDirectionVector);
			//unitDirectionVector = unitDirectionVector.rotateRad(rotationAngle, ofVec3f(0.0f, 1.0f, 0.0f));
			//ofLog() << unitDirectionVector.x << ", " << unitDirectionVector.y << ", " << unitDirectionVector.z;
		}
		else if (operation == '\\'){
			//      1           0           0
			//      0      cos(angle)   -sin(angle)
			//      0      sin(angle)    cos(angle)
			ofMatrix3x3 rotationMatrix;
			rotationMatrix.a = 1;
			rotationMatrix.b = 0;
			rotationMatrix.c = 0;

			rotationMatrix.d = 0;
			rotationMatrix.e = cosf(rotationAngle);
			rotationMatrix.f = -sinf(rotationAngle);

			rotationMatrix.g = 0;
			rotationMatrix.h = sinf(rotationAngle);
			rotationMatrix.i = cosf(rotationAngle);

			unitDirectionVector = RotateVector(rotationMatrix, unitDirectionVector);
			//ofLog() << unitDirectionVector.x << ", " << unitDirectionVector.y << ", " << unitDirectionVector.z;
		}
		else if (operation == '/'){
			//      1           0           0
			//      0      cos(angle)   -sin(angle)
			//      0      sin(angle)    cos(angle)
			ofMatrix3x3 rotationMatrix;
			rotationMatrix.a = 1;
			rotationMatrix.b = 0;
			rotationMatrix.c = 0;

			rotationMatrix.d = 0;
			rotationMatrix.e = cosf(-rotationAngle);
			rotationMatrix.f = -sinf(-rotationAngle);

			rotationMatrix.g = 0;
			rotationMatrix.h = sinf(-rotationAngle);
			rotationMatrix.i = cosf(-rotationAngle);

			unitDirectionVector = RotateVector(rotationMatrix, unitDirectionVector);
			//ofLog() << unitDirectionVector.x << ", " << unitDirectionVector.y << ", " << unitDirectionVector.z;
		}
		else if (operation == '|'){
			//  cos(angle)  sin(angle)      0
			// -sin(angle)  cos(angle)      0
			//     0            0           1
			ofMatrix3x3 rotationMatrix;
			rotationMatrix.a = cosf(-PI);
			rotationMatrix.b = sinf(-PI);
			rotationMatrix.c = 0;

			rotationMatrix.d = -sinf(-PI);
			rotationMatrix.e = cosf(-PI);
			rotationMatrix.f = 0;

			rotationMatrix.g = 0;
			rotationMatrix.h = 0;
			rotationMatrix.i = 1;

			unitDirectionVector = RotateVector(rotationMatrix, unitDirectionVector);

			//unitDirectionVector = RotateVector(rotationMatrix, unitDirectionVector);
			//ofLog() << unitDirectionVector.x << ", " << unitDirectionVector.y << ", " << unitDirectionVector.z;
		}
		else if (operation == '['){
			LStringStack.push_back( LLineStack(prevLine, unitDirectionVector) );
		}
		else if (operation == ']'){
			LLineStack tmpLine = LStringStack.back();
			LStringStack.pop_back();
			prevLine = tmpLine.line;

			unitDirectionVector = tmpLine.direction;
		}
		//else if ( operation == '' )
	}

	return quad;
}

ofVec3f LString::RotateVector(ofMatrix3x3 pRotationMatrix, ofVec3f pVector){
	ofVec3f result;
	result.x = pRotationMatrix.a * pVector.x + pRotationMatrix.b * pVector.y + pRotationMatrix.c *  pVector.z;
	result.y = pRotationMatrix.d * pVector.x + pRotationMatrix.e * pVector.y + pRotationMatrix.f *  pVector.z;
	result.z = pRotationMatrix.g * pVector.x + pRotationMatrix.h * pVector.y + pRotationMatrix.i *  pVector.z;

	return result;
}