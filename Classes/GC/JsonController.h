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
	int getInt(string tag);
	string getString(string tag);
	string getString(const rapidjson::Value& object, string tag = "");
	int getInt(const rapidjson::Value& object, string tag = "");
	string getString(string object, string tag = "");
	int getInt(string object, string tag = "");
	const rapidjson::Value& getObject(string tag = "");

	bool isNull(const rapidjson::Value& object, string tag = "");
	bool isNull(string object, string tag = "");

};

#endif // __JSON_CONTROLLER_H__
