**XML settings addon for standard settings - for of 0.10.x/0.11.x/..**  
Basic xml variable handling and standard features I need in nearly any project:
- getters and setters for most common variable types (no groups, though)
- Default variables in code that will be overwritten if variable is present in xml file
- optional auto-saving at setting of variable (note that variable has to be present in xml file for this function. It will not be auto-created!)
- verbose output of what's happening
- logging functionality included: log level and log type (terminal/file) can be defined through standard xml variables (variable "debug" has been renamed to "logging"! as it is much more appropriate)



## How to use (also see example project):
### **1) include and define in ofApp.h:**
    
    #include "ofxXmlBasedProjectSettings.h" on top  
    ofxXmlBasedProjectSettings settingsXml, otherXml; in class  

### **2) in setup():**

add XML variables: Give it a default/fallback value.  
On init() the XML is checked for these variables and if found default/fallback value is overridden.  
Standard procedure is to add all XML variables like below in setup() and later use the setter functions if those variables are altered.  
Please do not set a variable later in code without having added it first - it can be used and even be saved in XML (node has to be present - will not be auto-generated). But it might not be treated correctly in init().  
    
    settingsXml.addBoolean("flag1", true);  
    settingsXml.addInt("einint", 156);  
    settingsXml.addFloat("einefloat", 2.893);  
    settingsXml.addString("einstring", "gehMalArbeiten");  
    settingsXml.addColor("beige", ofColor(10, 23, 33, 4));  
    settingsXml.addVec2f("punkt1", ofVec2f(10, 23));  
    settingsXml.addVec3f("dreiDPunkt", ofVec3f(4, 10, 23));  
    settingsXml.addVec4f("vierdddd", ofVec4f(10, 23, 33, 4));  
  
 to add a variable that *require* a setting in XML (otherwise exit on program start!) just pass an empty default value (according to the variable type)  
	
    settingsXml.addBoolean("requiredFlag");  
	settingsXml.addFloat("requiredFloat");  
	settingsXml.addInt("requiredInt");  
	settingsXml.addString("hintergrundBild");  
	settingsXml.addColor("requiredBeige");  
    ...


### **3) in setup():**

init the xml. The added variables will be processed    
Second parameter switches on logging stuff: When true, the variables "logging", "verbose" and "logToFile" will be added, which control the logging output (everything that is sent through ofLog functions). Should be used in the main/first xml object/file  
    
    settingsXml.init("settings.xml",true);  


do the same for other objects/files, but logging stuff should not be used another time (as it used for App in general it would not make any sense to do it 2 times)  

	otherXml.addInt("otherInt", 156);  
	otherXml.addVec2f("punkt1", ofVec2f(10, 23));  

	otherXml.init("otherSettings.xml");  


Then all the variables can be set in XML and are ready for use.


### **getting Variables:**

    settingsXml.getVec2fValue("punkt1");  
    settingsXml.getStringValue("einstring");  

Please note, that there is a method for every available variable type.



### **setting Variables (assigning a new value):**

    settingsXml.setFloatValue("einefloat", 0.4, true);  
    settingsXml.setStringValue("einstring", "mehr über Torf", true);  
    settingsXml.setVec4fValue("vierdddd", ofVec4f(214,12,85,45), true);  

Second property is new value, third property switches auto save on: Value is saved (after a short time buffer). Please note, that there is a method for every available variable type.



### **basic notes:**

- Please add a node in your xml file manually for every included variable. It will not be auto-created!
- Do not start a variable name with a digit. XML will not handle this
- If you have a non-utf8 encoding involved somewhere, your XML file will get corrupted on saving when you use special characters.
- Visual Studio might have an unrecognizable non-utf8 - encoding on ofApp.cpp. Please open it in other editor (e.g. Geany) change the encoding to utf8 (even if it's showing utf8 already) and save it. Then re-open in Visual Basic and re-compile.
- ofDrawBitmapString will not properly show special characters, nore will the Command prompt - even if they are correct in our Addon.  That does not mean there is a problem - if you use a font addon like ofxFontStash all shall most likely to be good.


### **XML structure**

The xml structure (includign sub nodes) is analog to the use of the variable types in OF. boolean value is set by using 0/1.

logging part 

    <logging>1</logging>
    <verbose>0</verbose>
    <logToFile>0</logToFile>

boolean:

    <flag1>0</flag1>

int: 

    <someint>56.348</someint>

float: 

    <nocheinefloat>56.348</nocheinefloat>

string: 

    <message>All will be good</message>

color:

    <beige>
        <r>2</r>
        <g>3</g>
        <b>4</b>
        <a>5</a>
    </beige>

vec2f

    <zweiDPunkt>
        <x>45</x>
        <y>25</y>
    </zweiDPunkt>

vec3f

    <dreiDPunkt>
        <x>45</x>
        <y>25</y>
        <z>15</z>
    </dreiDPunkt>

vec4f

    <vierdddd>
        <x>214</x>
        <y>12</y>
        <z>85</z>
        <w>45</w>
    </vierdddd>


Please also see example