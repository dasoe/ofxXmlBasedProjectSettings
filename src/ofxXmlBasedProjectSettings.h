#pragma once

#include "ofMain.h"

template <typename T>
struct genericStructProperties {
    T value;
    T defaultValue;
    bool noDefault = false;
};


class ofxXmlBasedProjectSettings {
public:

	void init(string path);
	void init(string path, bool loggingInit);
	void readValuesFromXml(bool loggingInit);
	void setLogSettings();

	void addBoolean(string name, bool defautlValue);
	void addBoolean(string name);

	void addInt(string name, int defautlValue);
	void addInt(string name);

	void addFloat(string name, float defautlValue);
	void addFloat(string name);

	void addString(string name, string defautlValue);
	void addString(string name);

	void addColor(string name, ofColor defautlValue);
	void addColor(string name);

	void addVec2f(string name, ofVec2f defautlValue);
	void addVec2f(string name);

	void addVec3f(string name, ofVec3f defautlValue);
	void addVec3f(string name);

	void addVec4f(string name, ofVec4f defautlValue);
	void addVec4f(string name);


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

	void valueMissingError(string name);
	void logValueFound(string name, string valueString);
	void logNoValueFound(string name, string valueString);
	void logValueChanged(string name, string valueString);
	void logNodeMissing(string xml, string name);
	void logSubNodeMissing(string xml, string subType, string name);

	bool logging;
	bool verbose;
	bool logToFile;

private:
	map < string, genericStructProperties<bool> > xmlBooleanValue;
	map < string, genericStructProperties<int> > xmlIntValue;
	map < string, genericStructProperties<float> > xmlFloatValue;
	map < string, genericStructProperties<std::string> > xmlStringValue;
	map < string, genericStructProperties<ofVec2f> > xmlVec2fValue;
	map < string, genericStructProperties<ofVec3f> > xmlVec3fValue;
	map < string, genericStructProperties<ofVec4f> > xmlVec4fValue;
	map < string, genericStructProperties<ofColor> > xmlColorValue;

	string pathToXML;
	ofXml XML;
	bool xmlChanged;
	string lineBreak, startMessages;
	unsigned long actualTime, xmlChangeSaveTimer;

};
