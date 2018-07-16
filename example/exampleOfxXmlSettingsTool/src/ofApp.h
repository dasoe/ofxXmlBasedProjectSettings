#pragma once

#include "ofMain.h"
#include "ofxXmlBasedProjectSettings.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);

		ofxXmlBasedProjectSettings settingsXml,  otherXml;

};
