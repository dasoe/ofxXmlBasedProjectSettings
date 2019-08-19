#pragma once

#include "ofMain.h"

struct booleanStructProperties {
	bool value;
	bool defaultValue;
};

struct intStructProperties {
	int value;
	int defaultValue;
};

struct floatStructProperties {
	float value;
	float defaultValue;
};

struct stringStructProperties {
	string value;
	string defaultValue;
};

struct vec2fStructProperties {
	ofVec2f value;
	ofVec2f defaultValue;
};

struct vec3fStructProperties {
	ofVec3f value;
	ofVec3f defaultValue;
};

struct vec4fStructProperties {
	ofVec4f value;
	ofVec4f defaultValue;
};

struct colorStructProperties {
	ofColor value;
	ofColor defaultValue;
};


class ofxXmlBasedProjectSettings {
public:

	void init(string path);
	void init(string path, bool loggingInit);
	void readValuesFromXml(bool loggingInit);
	void setLogSettings();

	void addBoolean(string name, bool defautlValue);
	void addInt(string name, int defautlValue);
	void addFloat(string name, float defautlValue);
	void addString(string name, string defautlValue);
	void addColor(string name, ofColor defautlValue);
	void addVec2f(string name, ofVec2f defautlValue);
	void addVec3f(string name, ofVec3f defautlValue);
	void addVec4f(string name, ofVec4f defautlValue);


	void update();
	bool getBooleanValue(string name);
	int getIntValue(string name);
	float getFloatValue(string name);
	string getStringValue(string name);
	ofVec2f getVec2fValue(string name);
	ofVec3f getVec3fValue(string name);
	ofVec4f getVec4fValue(string name);
	ofColor getColorValue(string name);

	void setBooleanValue(string name, bool newValue);
	void setBooleanValue(string name, bool newValue, bool autoSave);

	void setIntValue(string name, int newValue);
	void setIntValue(string name, int newValue, bool autoSave);

	void setFloatValue(string name, float newValue);
	void setFloatValue(string name, float newValue, bool autoSave);

	void setStringValue(string name, string newValue);
	void setStringValue(string name, string newValue, bool autoSave);

	void setColorValue(string name, ofColor newValue);
	void setColorValue(string name, ofColor newValue, bool autoSave);

	void setVec2fValue(string name, ofVec2f newValue);
	void setVec2fValue(string name, ofVec2f newValue, bool autoSave);

	void setVec3fValue(string name, ofVec3f newValue);
	void setVec3fValue(string name, ofVec3f newValue, bool autoSave);

	void setVec4fValue(string name, ofVec4f newValue);
	void setVec4fValue(string name, ofVec4f newValue, bool autoSave);


	void changeXMLPrepareSave(string name, string newValue);
	void changeXMLPrepareSave(string name, ofVec2f newValue);
	void changeXMLPrepareSave(string name, ofVec3f newValue);
	void changeXMLPrepareSave(string name, ofVec4f newValue);
	void changeXMLPrepareSave(string name, ofColor newValue);


	bool logging;
	bool verbose;
	bool logToFile;

private:
	map < string, booleanStructProperties > xmlBooleanValue;
	map < string, intStructProperties > xmlIntValue;
	map < string, floatStructProperties > xmlFloatValue;
	map < string, stringStructProperties > xmlStringValue;
	map < string, vec2fStructProperties > xmlVec2fValue;
	map < string, vec3fStructProperties > xmlVec3fValue;
	map < string, vec4fStructProperties > xmlVec4fValue;
	map < string, colorStructProperties > xmlColorValue;

	string pathToXML;
	ofXml XML;
	bool xmlChanged;
	string lineBreak, startMessages;
	unsigned long actualTime, xmlChangeSaveTimer;

};
