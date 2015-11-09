#ifndef __JSON_CONTROLLER_H__
#define __JSON_CONTROLLER_H__

#include "json/document.h"
using namespace std;

class JsonController
{
	rapidjson::Document m_document;
public:
	JsonController();
	void read(string json);
	string getString(rapidjson::Value& object, string tag = "", int index = -1);
    string getString(rapidjson::Value& object, int index);
    string getString(string object, string tag = "", int index = -1);
    int getInt(rapidjson::Value& object, string tag = "", int i = -1);
    int getInt(rapidjson::Value& object, int index);
	int getInt(string object, string tag = "", int index = -1);
    bool getBool(rapidjson::Value& object, string tag = "", int i = -1);
    bool getBool(rapidjson::Value& object, int index);
    bool getBool(string object, string tag = "", int index = -1);
    
    //remember to check null before call these getObject method
    rapidjson::Value & getObject(rapidjson::Value &object, string tag = "", int index = -1);
    rapidjson::Value & getObject(string object, string tag = "", int index = -1);
    rapidjson::Value & getObject(rapidjson::Value &object, int index);
    

	bool isNull(rapidjson::Value& object, string tag = "", int index = -1);
	bool isNull(string object, string tag = "", int index = -1);
    bool isNull(rapidjson::Value& object, int index);

};

#endif // __JSON_CONTROLLER_H__
