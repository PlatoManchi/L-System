#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	LString lString;
	
	// new method
	//string str = lString.GetLString(2, 3, string("F+F+F+F"), string("F=F+f-FF+F+FF+Ff+FF-f+FF-F-FF-Ff-FFF"), string("f=ffffff"));
	//string str = lString.GetLString(3, 2, string("F-F-F-F"), string("F=FF-F+F-F-FF"));
	//string str = lString.GetLString(7, 3, string("X"), string("X=F[+X][-X]FX"), string("F=FF"));
	//string str = lString.GetLString(1, 5, string("A"), string("A=B-F+CFC+F-D&F^D-F+&&CFC+F+B//"), string("B=A&F^CFB^F^D^^-F-D^|F^B|FC^F^A//"), string("C=|D^|F^B-F+C^F^A&&FA&F^C+F+B^F^D//"), string("D=|CFB-F+B|FA&F^A&&FB-F+B|FC//"));
	//string str = lString.GetLString(7, 5, string("A"), string("A=[&FL!A]/////'[&FL!A]///////'[&FL!A]"), string("F=S/////F"), string("S=FL"), string("D=L=['''^^{-f+f+f-|-f+f+f}]"));
	string str = lString.GetLString(5, 8, 
		string("plant "), 
		string("plant = internode + [ plant + fower ]--//[--leaf ] internode [++ leaf ]-[ plant flower ]++ plant flower "), 
		string("internode = F seg [//&& leaf ][//^^ leaf ]F seg "), 
		string("seg = seg F seg "), 
		string("leaf = ['{+f-ff-f+|+f-ff-f}]"),
		string("flower = [&&& pedicel '/ wedge //// wedge //// wedge //// wedge //// wedge ]"),
		string("pedicel = FF"),
		string("wedge = [^F][{&&&&-f+f|-f+f}]"));
	//string str = lString.GetLString(1, 2, string("A"), string("A=f[+F][-F][&F][^F][\\F][/F]"));
	//string str = lString.GetLString(1, 1, string("+F&F-F\\F^F/F"));

	//ofLog() << str;
	n1 = lString.GenerateQuad( str, 18.0f );
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0, 0, 0);
	cam.begin();
	ofRotateZ(180);

	ofPoint point;
	//point.x = ofGetScreenWidth() / 2.0f;
	//point.y = ofGetScreenHeight() / 2.0f;
	point.x = 500.0f;
	point.y = 700.0f;
	point.z = -2500.0f;

	ofTranslate(point);     // move the coordinate system to position of point and make that zero.


	/*ofColor green(0, 255, 0);
	ofSetColor(green);
	for (int i = 0; i < initiator.LineCount(); i++){
		LLine tmpLine = initiator.GetLine(i);

		ofLine(tmpLine.start.x, tmpLine.start.y, tmpLine.end.x, tmpLine.end.y);
	}*/

	ofColor white(255, 255, 255);
	ofSetColor(white);

	for (int i = 0; i < n1.LineCount(); i++){
		LLine tmpLine = n1.GetLine( i );

		ofLine(tmpLine.start.x, tmpLine.start.y, tmpLine.start.z, tmpLine.end.x, tmpLine.end.y, tmpLine.end.z);
	}
	cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
