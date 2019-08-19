#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// basic notes: 
	// - do not start a variable name with a digit. XML will not handle this
	// - If you have a non-utf8 encoding involved somewhere, your XML file will get corrupted on saving when you use special characters. 
	//   Visual basic might have a unrecognizable non-utf8 - encoding on ofApp.cpp. Please open it in other editor (e.g. Geany) change the encoding 
	//	 to utf8 (try even if it's showing utf8 already) and save it. Then re-open in Visual Basic and re-compile. 
	// - ofDrawBitmapString will not properly show special characters, nore will the Command prompt - even if they are correct in our Addon. 
	//	 That does not mean there is a problem - if you use a font addon like ofxFontStash all shall most likely to be good.


	// Step 1: 
	// add XML variables: Give it a default/fallback value.
	// On init() the XML is checked for these variables and if found default/fallback value is overridden.
	// Standard procedure is to add all XML variables like below in setup() and later use the setter functions if those variables are altered.
	// Please do not set a variable without having added it - it can be used and even be saved in XML (node has to be present - will notbe auto-genrated). 
	// But it might not be treated correctly in init().
	settingsXml.addBoolean("flag1", true);
	settingsXml.addInt("einint", 156);
	settingsXml.addFloat("einefloat", 2.893);
	settingsXml.addString("einstring", "gehMalArbeiten");
	settingsXml.addColor("beige", ofColor(10, 23, 33, 4));
	settingsXml.addVec2f("punkt1", ofVec2f(10, 23));
	settingsXml.addVec3f("dreiDPunkt", ofVec3f(4, 10, 23));
	settingsXml.addVec4f("vierdddd", ofVec4f(10, 23, 33, 4));

	// Step 2: 
	// init the xml. The added variables will be processed
	//
	// Second parameter switches on logging stuff: When true, the variables "logging", "verbose" and "logToFile" will be added, which control the logging output
	// (everything that is sent through ofLog functions). Should be used in the main/first xml object/file
	settingsXml.init("settings.xml",true);


	// do the same for other objects/files
	otherXml.addInt("otherInt", 156);
	otherXml.addVec2f("punkt1", ofVec2f(10, 23));

	otherXml.init("otherSettings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
	settingsXml.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDrawBitmapString(ofToString(settingsXml.getVec2fValue("punkt1")), 20, 20);
	ofDrawBitmapString(ofToString(settingsXml.getStringValue("einstring")), 20, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'w':
		settingsXml.setFloatValue("einefloat", 0.4, true);
		settingsXml.setStringValue("einstring", "mehr über Torf", true);
		settingsXml.setVec4fValue("vierdddd", ofVec4f(214,12,85,45), true);

		break;

	}
}
