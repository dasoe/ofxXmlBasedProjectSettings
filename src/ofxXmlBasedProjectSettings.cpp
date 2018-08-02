#include "ofxXmlBasedProjectSettings.h"

// -------------------------------
void ofxXmlBasedProjectSettings::init(string path) {
	init(path, false);
}
// -------------------------------
void ofxXmlBasedProjectSettings::init(string path, bool debugInit) {
	pathToXML = path;
	readValuesFromXml(debugInit);
}

// -------------------------------
void ofxXmlBasedProjectSettings::readValuesFromXml(bool debugInit) {
	if (debugInit) {
		lineBreak = "\n  ";
		startMessages = "";
		// ---------------------- settings on file ------------------------------

		// first messages are recorded until we know if to write them in file or on screen
		startMessages += "versuche " + ofToString(pathToXML) + " zu laden..." + lineBreak;

		//we load our settings file
		if (XML.load(pathToXML)) {
			startMessages += ofToString(pathToXML) +" geladen." + lineBreak;
		}
		else {
			startMessages += "unable to load " + ofToString(pathToXML) + " check data/ folder" + lineBreak;
			ofLogNotice(startMessages);
			ofLogError("--- FEHLER ---: " + ofToString(pathToXML) + " nicht gefunden / " + ofToString(pathToXML) + " komplett leer / fehlerhaft. Abbruch.");
			ofSleepMillis(4000);
			ofExit();
		}

		if (XML.exists("debug")) {
			debug = XML.getValue<bool>("debug");
			startMessages += "XML value found. debug set to " + ofToString(debug) + lineBreak;
		}
		else {
			debug = true;
			startMessages += "no XML value found. debug set to true" + lineBreak;
		}

		// ------- set Log settings depending on first XML Value (debug) ---------
		setLogSettings();
	}
	else {
		if (XML.load(pathToXML)) {
			ofLogNotice(ofToString(pathToXML) + " geladen.");
		}
		else {
			ofLogError("--- FEHLER ---: " + ofToString(pathToXML) + " nicht gefunden / " + ofToString(pathToXML) + " komplett leer / fehlerhaft. Abbruch.");
			ofSleepMillis(4000);
			ofExit();
		}
	}

	for (const auto& iterator : xmlStringValue) {
		//ofLogNotice(iterator.second.defaultValue);
		//ofLogNotice(ofToString(iterator.second.saveAutomatically));
		if (XML.exists(iterator.first)) {
			xmlStringValue[iterator.first].value = XML.getValue<string>(iterator.first);
			ofLog(OF_LOG_NOTICE, "XML value found. " + iterator.first + " set to " + ofToString(iterator.second.value));
		}
		else {
			if (iterator.second.defaultValue.empty()) {
				ofLogError("benötigen XML Wert nicht gefunden: " + iterator.first + " scheint zu fehlen. Abbruch.");
				ofSleepMillis(4000);
				ofExit();
			}
			else {
				xmlStringValue[iterator.first].value = iterator.second.defaultValue;
				ofLog(OF_LOG_NOTICE, "no XML value found. " + iterator.first + " set to " + ofToString(iterator.second.value));
			}
		}
	}

	for (const auto& iterator : xmlIntValue) {
		if (XML.exists(iterator.first)) {
			xmlIntValue[iterator.first].value = XML.getValue<int>(iterator.first);
			ofLog(OF_LOG_NOTICE, "XML value found. " + iterator.first + " set to " + ofToString(iterator.second.value));
		}
		else {
			if (iterator.second.defaultValue == NULL) {
				ofLogError("benötigen XML Wert nicht gefunden: " + iterator.first + " scheint zu fehlen. Abbruch.");
				ofSleepMillis(4000);
				ofExit();
			}
			else {
				xmlIntValue[iterator.first].value = iterator.second.defaultValue;
				ofLog(OF_LOG_NOTICE, "no XML value found. " + iterator.first + " set to " + ofToString(iterator.second.value));
			}
		}
	}

	for (const auto& iterator : xmlBooleanValue) {
		if (XML.exists(iterator.first)) {
			xmlBooleanValue[iterator.first].value = XML.getValue<bool>(iterator.first);
			ofLog(OF_LOG_NOTICE, "XML value found. " + iterator.first + " set to " + ofToString(iterator.second.value));
		}
		else {
			if (iterator.second.defaultValue == NULL) {
				ofLogError("benötigen XML Wert nicht gefunden: " + iterator.first + " scheint zu fehlen. Abbruch.");
				ofSleepMillis(4000);
				ofExit();
			}
			else {

				xmlBooleanValue[iterator.first].value = iterator.second.defaultValue;
				ofLog(OF_LOG_NOTICE, "no XML value found. " + iterator.first + " set to " + ofToString(iterator.second.value));
			}
		}
	}

	for (const auto& iterator : xmlFloatValue) {
		if (XML.exists(iterator.first)) {

			xmlFloatValue[iterator.first].value = XML.getValue<float>(iterator.first);
			ofLog(OF_LOG_NOTICE, "XML value found. " + iterator.first + " set to " + ofToString(iterator.second.value));
		}
		else {
			if (iterator.second.defaultValue == NULL) {
				ofLogError("benötigen XML Wert nicht gefunden: " + iterator.first + " scheint zu fehlen. Abbruch.");
				ofSleepMillis(4000);
				ofExit();
			}
			else {

				xmlFloatValue[iterator.first].value = iterator.second.defaultValue;
				ofLog(OF_LOG_NOTICE, "no XML value found. " + iterator.first + " set to " + ofToString(iterator.second.value));
			}
		}
	}

	for (const auto& iterator : xmlVec2fValue) {
		if (XML.exists(iterator.first)) {
			XML.setTo(iterator.first);

			xmlVec2fValue[iterator.first].value = ofVec2f(XML.getValue<float>("x"), XML.getValue<float>("y"));
			ofLog(OF_LOG_NOTICE, "XML value found. " + iterator.first + " set to " + ofToString(iterator.second.value));
			XML.setToParent();
		}
		else {
				xmlVec2fValue[iterator.first].value = iterator.second.defaultValue;
				ofLog(OF_LOG_NOTICE, "no XML value found. " + iterator.first + " set to " + ofToString(iterator.second.value));
		}
	}

	for (const auto& iterator : xmlVec3fValue) {
		if (XML.exists(iterator.first)) {
			XML.setTo(iterator.first);

			xmlVec3fValue[iterator.first].value = ofVec3f(XML.getValue<float>("x"), XML.getValue<float>("y"), XML.getValue<float>("z"));
			ofLog(OF_LOG_NOTICE, "XML value found. " + iterator.first + " set to " + ofToString(iterator.second.value));
			XML.setToParent();
		}
		else {

				xmlVec3fValue[iterator.first].value = iterator.second.defaultValue;
				ofLog(OF_LOG_NOTICE, "no XML value found. " + iterator.first + " set to " + ofToString(iterator.second.value));
		}
	}

	for (const auto& iterator : xmlVec4fValue) {
		if (XML.exists(iterator.first)) {
			XML.setTo(iterator.first);

			xmlVec4fValue[iterator.first].value = ofVec4f(XML.getValue<float>("x"), XML.getValue<float>("y"), XML.getValue<float>("z"), XML.getValue<float>("w"));
			ofLog(OF_LOG_NOTICE, "XML value found. " + iterator.first + " set to " + ofToString(iterator.second.value));
			XML.setToParent();
		}
		else {

				xmlVec4fValue[iterator.first].value = iterator.second.defaultValue;
				ofLog(OF_LOG_NOTICE, "no XML value found. " + iterator.first + " set to " + ofToString(iterator.second.value));
		}
	}

	for (const auto& iterator : xmlColorValue) {
		if (XML.exists(iterator.first)) {
			XML.setTo(iterator.first);

			xmlColorValue[iterator.first].value = ofColor(XML.getValue<float>("r"), XML.getValue<float>("g"), XML.getValue<float>("b"), XML.getValue<float>("a"));
			ofLog(OF_LOG_NOTICE, "XML value found. " + iterator.first + " set to " + ofToString(iterator.second.value));
			XML.setToParent();
		}
		else {
			if (iterator.second.defaultValue == NULL) {
				ofLogError("benötigen XML Wert nicht gefunden: " + iterator.first + " scheint zu fehlen. Abbruch.");
				ofSleepMillis(4000);
				ofExit();
			}
			else {

				xmlColorValue[iterator.first].value = iterator.second.defaultValue;
				ofLog(OF_LOG_NOTICE, "no XML value found. " + iterator.first + " set to " + ofToString(iterator.second.value));
			}
		}
	}

}


//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::setLogSettings() {

	// --------- LOG SETTINGS ---------
	// log something at all?
	if (!debug) {
		ofSetLogLevel(OF_LOG_FATAL_ERROR);
	}
	else {
		ofSetLogLevel(OF_LOG_NOTICE);
		// check how much to log
		if (XML.exists("verbose")) {
			verbose = XML.getValue<bool>("verbose");
			startMessages += "XML value found. verbose set to " + ofToString(verbose) + lineBreak;;
		}
		else {
			verbose = true;
			startMessages += "no XML value found. verbose set to true" + lineBreak;;
		}
		if (verbose) {
			ofSetLogLevel(OF_LOG_VERBOSE);
		}

		// check where to log (screen or file)
		if (XML.exists("logToFile")) {
			logToFile = XML.getValue<bool>("logToFile");
			startMessages += "XML value found. logToFile set to " + ofToString(logToFile) + lineBreak;;
			ofLog(OF_LOG_NOTICE, "XML value found. logToFile set to " + ofToString(logToFile));
		}
		else {
			logToFile = false;
			startMessages += "no XML value found. logToFile set to false" + lineBreak;;
			ofLog(OF_LOG_NOTICE, "no XML value found. logToFile set to false");
		}
		if (logToFile) {
			ofLogToFile("log.txt", false);
		}
	}
	ofLog(OF_LOG_NOTICE, startMessages);

	// log first messages (from above)
	// from now on (as it is decided where to write),no need to use "startMessages" any more
	// we can go on using ofLog directly

}


// -------------------------------
void ofxXmlBasedProjectSettings::addBoolean(string name, bool defautlValue) {
	xmlBooleanValue[name].defaultValue = defautlValue;
}

// -------------------------------
void ofxXmlBasedProjectSettings::addInt(string name, int defautlValue) {
	xmlIntValue[name].defaultValue = defautlValue;
}

// -------------------------------
void ofxXmlBasedProjectSettings::addFloat(string name, float defautlValue) {
	xmlFloatValue[name].defaultValue = defautlValue;
}

// -------------------------------
void ofxXmlBasedProjectSettings::addString(string name, string defautlValue) {
	xmlStringValue[name].defaultValue = defautlValue;
}


// -------------------------------
void ofxXmlBasedProjectSettings::addVec2f(string name, ofVec2f defautlValue) {
	xmlVec2fValue[name].defaultValue = defautlValue;
}

// -------------------------------
void ofxXmlBasedProjectSettings::addVec3f(string name, ofVec3f defautlValue) {
	xmlVec3fValue[name].defaultValue = defautlValue;
}

// -------------------------------
void ofxXmlBasedProjectSettings::addVec4f(string name, ofVec4f defautlValue) {
	xmlVec4fValue[name].defaultValue = defautlValue;
}

// -------------------------------
void ofxXmlBasedProjectSettings::addColor(string name, ofColor defautlValue) {
	xmlColorValue[name].defaultValue = defautlValue;
}


// -------------------------------
void ofxXmlBasedProjectSettings::update() {

	actualTime = ofGetElapsedTimeMillis();
	if (
		xmlChanged &&
		actualTime - xmlChangeSaveTimer > 500
		) {
		XML.save(pathToXML);
		ofLogNotice("XML " + ofToString(pathToXML) + " saved");
		xmlChanged = false;
	}
}


// #################### getter #####################

// -------------------------------
bool ofxXmlBasedProjectSettings::getBooleanValue(string name) {
	return xmlBooleanValue[name].value;
}

// -------------------------------
int ofxXmlBasedProjectSettings::getIntValue(string name) {
	return xmlIntValue[name].value;
}

// -------------------------------
float ofxXmlBasedProjectSettings::getFloatValue(string name) {
	return xmlFloatValue[name].value;
}

// -------------------------------
string ofxXmlBasedProjectSettings::getStringValue(string name) {
	return xmlStringValue[name].value;
}

// -------------------------------
ofVec2f ofxXmlBasedProjectSettings::getVec2fValue(string name) {
	return xmlVec2fValue[name].value;
}

// -------------------------------
ofVec3f ofxXmlBasedProjectSettings::getVec3fValue(string name) {
	return xmlVec3fValue[name].value;
}

// -------------------------------
ofVec4f ofxXmlBasedProjectSettings::getVec4fValue(string name) {
	return xmlVec4fValue[name].value;
}

// -------------------------------
ofColor ofxXmlBasedProjectSettings::getColorValue(string name) {
	return xmlColorValue[name].value;
}


// #################### setter #####################
//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::setBooleanValue(string name, bool newValue) {
	setBooleanValue(name, newValue, false);
}
//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::setBooleanValue(string name, bool newValue, bool autoSave) {
	xmlBooleanValue[name].value = newValue;
	if (autoSave) {
		ofLogNotice("xml variable | " + name + " | set to " + ofToString(newValue) + " - will be saved in an instant.");
		changeXMLPrepareSave(name, ofToString(newValue));
	}
}

//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::setIntValue(string name, int newValue) {
	setIntValue(name, newValue, false);
}
//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::setIntValue(string name, int newValue, bool autoSave) {
	xmlIntValue[name].value = newValue;
	if (autoSave) {
		ofLogNotice("xml variable | " + name + " | set to " + ofToString(newValue) + " - will be saved in an instant.");
		changeXMLPrepareSave(name, ofToString(newValue));
	}
}

//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::setFloatValue(string name, float newValue) {
	setFloatValue(name, newValue, false);
}
//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::setFloatValue(string name, float newValue, bool autoSave) {
	xmlFloatValue[name].value = newValue;
	if (autoSave) {
		ofLogNotice("xml variable | " + name + " | set to " + ofToString(newValue) + " - will be saved in an instant.");
		changeXMLPrepareSave(name, ofToString(newValue));
	}
}

//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::setStringValue(string name, string newValue) {
	setStringValue(name, newValue, false);
}
//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::setStringValue(string name, string newValue, bool autoSave) {
	xmlStringValue[name].value = newValue;
	if (autoSave) {
		ofLogNotice("xml variable | " + name + " | set to " + newValue + " - will be saved in an instant.");
		changeXMLPrepareSave(name, newValue);
	}
}

//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::setVec2fValue(string name, ofVec2f newValue) {
	setVec2fValue(name, newValue, false);
}
//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::setVec2fValue(string name, ofVec2f newValue, bool autoSave) {
	xmlVec2fValue[name].value = newValue;
	if (autoSave) {
		ofLogNotice("xml variable | " + name + " | set to " + ofToString(newValue) + " - will be saved in an instant.");
		changeXMLPrepareSave(name, newValue);
	}
}

//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::setVec3fValue(string name, ofVec3f newValue) {
	setVec3fValue(name, newValue, false);
}
//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::setVec3fValue(string name, ofVec3f newValue, bool autoSave) {
	xmlVec3fValue[name].value = newValue;
	if (autoSave) {
		ofLogNotice("xml variable | " + name + " | set to " + ofToString(newValue) + " - will be saved in an instant.");
		changeXMLPrepareSave(name, newValue);
	}
}

//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::setVec4fValue(string name, ofVec4f newValue) {
	setVec4fValue(name, newValue, false);
}
//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::setVec4fValue(string name, ofVec4f newValue, bool autoSave) {
	xmlVec4fValue[name].value = newValue;
	if (autoSave) {
		ofLogNotice("xml variable | " + name + " | set to " + ofToString(newValue) + " - will be saved in an instant.");
		changeXMLPrepareSave(name, newValue);
	}
}

//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::setColorValue(string name, ofColor newValue) {
	setColorValue(name, newValue, false);
}
//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::setColorValue(string name, ofColor newValue, bool autoSave) {
	xmlColorValue[name].value = newValue;
	if (autoSave) {
		ofLogNotice("xml variable | " + name + " | set to " + ofToString(newValue) + " - will be saved in an instant.");
		changeXMLPrepareSave(name, newValue);
	}
}


// #################### XML altering and save preparation stuff #####################
//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::changeXMLPrepareSave(string name, string newValue) {
	XML.setTo("//SETTINGS");
	if (XML.exists(name)) {
		XML.setValue(name, newValue);
	}
	else {
		ofLogWarning("Versuch einen in " + ofToString(pathToXML) + " nicht vorhandenen Knoten (" + ofToString(name) + ") zu speichern. Knoten bitte manuell anlegen.");
	}
	xmlChanged = true;
	xmlChangeSaveTimer = ofGetElapsedTimeMillis();

}

//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::changeXMLPrepareSave(string name, ofColor newValue) {
	XML.setTo("//SETTINGS");
	if (XML.exists(name)) {
		XML.setTo(name);
		if (
			XML.exists("r") &&
			XML.exists("g") &&
			XML.exists("b") &&
			XML.exists("a") 
			) {
			// directly (ofToString(newValue.r)) it will not work, do not know why, so first to int
			int rot = newValue.r;
			int gruen = newValue.g;
			int blau = newValue.b;
			int alpha = newValue.a;
			XML.setValue("r", ofToString(rot));
			XML.setValue("g", ofToString(gruen));
			XML.setValue("b", ofToString(blau));
			XML.setValue("a", ofToString(alpha));
		}
		else {
			ofLogWarning("Versuch in " + ofToString(pathToXML) + " in einen nicht vorhandenen Sub-Knoten (r/g/b/a) von " + ofToString(name) + " zu speichern. Sub-Knoten bitte manuell anlegen.");
		}
		XML.setToParent();
	}
	else {
		ofLogWarning("Versuch einen in " + ofToString(pathToXML) + " nicht vorhandenen Knoten (" + ofToString(name) + ") zu speichern. Knoten bitte manuell anlegen.");
	}
	xmlChanged = true;
	xmlChangeSaveTimer = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::changeXMLPrepareSave(string name, ofVec2f newValue) {
	XML.setTo("//SETTINGS");
	if (XML.exists(name)) {
		XML.setTo(name);
		if (
			XML.exists("x") &&
			XML.exists("y") 
			) {

			XML.setValue("x", ofToString(newValue.x));
			XML.setValue("y", ofToString(newValue.y));
		}
		else {
			ofLogWarning("Versuch in " + ofToString(pathToXML) + " in einen nicht vorhandenen Sub-Knoten (x/y) von " + ofToString(name) + " zu speichern. Sub-Knoten bitte manuell anlegen.");
		}

		XML.setToParent();
	}
	else {
		ofLogWarning("Versuch einen in " + ofToString(pathToXML) + " nicht vorhandenen Knoten (" + ofToString(name) + ") zu speichern. Knoten bitte manuell anlegen.");
	}
	xmlChanged = true;
	xmlChangeSaveTimer = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::changeXMLPrepareSave(string name, ofVec3f newValue) {
	XML.setTo("//SETTINGS");
	if (XML.exists(name)) {
		XML.setTo(name);
		if (
			XML.exists("x") &&
			XML.exists("y") &&
			XML.exists("z")
			) {

			XML.setValue("x", ofToString(newValue.x));
			XML.setValue("y", ofToString(newValue.y));
			XML.setValue("z", ofToString(newValue.z));
		}
		else {
			ofLogWarning("Versuch in " + ofToString(pathToXML) + " in einen nicht vorhandenen Sub-Knoten (x/y/z) von " + ofToString(name) + " zu speichern. Sub-Knoten bitte manuell anlegen.");
		}

		XML.setToParent();
	}
	else {
		ofLogWarning("Versuch einen in " + ofToString(pathToXML) + " nicht vorhandenen Knoten (" + ofToString(name) + ") zu speichern. Knoten bitte manuell anlegen.");
	}
	xmlChanged = true;
	xmlChangeSaveTimer = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void ofxXmlBasedProjectSettings::changeXMLPrepareSave(string name, ofVec4f newValue) {
	XML.setTo("//SETTINGS");
	if (XML.exists(name)) {
		XML.setTo(name);
		if (
			XML.exists("x") &&
			XML.exists("y") &&
			XML.exists("z") &&
			XML.exists("w")
			) {

			XML.setValue("x", ofToString(newValue.x));
			XML.setValue("y", ofToString(newValue.y));
			XML.setValue("z", ofToString(newValue.z));
			XML.setValue("w", ofToString(newValue.w));
		}
		else {
			ofLogWarning("Versuch in " + ofToString(pathToXML) + " in einen nicht vorhandenen Sub-Knoten (x/y/z/w) von " + ofToString(name) + " zu speichern. Sub-Knoten bitte manuell anlegen.");
		}

		XML.setToParent();
	}
	else {
		ofLogWarning("Versuch einen in " + ofToString(pathToXML) + " nicht vorhandenen Knoten (" + ofToString(name) + ") zu speichern. Knoten bitte manuell anlegen.");
	}
	xmlChanged = true;
	xmlChangeSaveTimer = ofGetElapsedTimeMillis();
}
