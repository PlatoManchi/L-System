#include "Quad.h"

void Quad::AddLine(LLine pLine){
	lineList.push_back( pLine );
}

LLine Quad::GetLine(unsigned pIndex){
	return lineList[pIndex];
}

int Quad::LineCount(){
	return lineList.size();
}