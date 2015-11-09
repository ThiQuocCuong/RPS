#include "JsonController.h"

JsonController::JsonController() {
	//m_document.SetObject();
}
void JsonController::read(string json) {
	m_document.Parse(json.c_str());
}

int JsonController::getInt(string tag) {
	if (m_document[tag.c_str()].IsInt()) {
		return m_document[tag.c_str()].GetInt();
	}
	else {
		return 0;
	}
}

string JsonController::getString(string tag) {
	if (m_document[tag.c_str()].IsString()) {
		return m_document[tag.c_str()].GetString();
	}
	else {
		return "";
	}
}

const rapidjson::Value& JsonController::getObject(string tag) {
	return m_document[tag.c_str()];
}

string JsonController::getString(const rapidjson::Value& object, string tag) {
	if (!isNull(object, tag)) {
		return object[tag.c_str()].GetString();
	}
	else {
		return "";
	}
}

int JsonController::getInt(const rapidjson::Value& object, string tag) {
	if (!isNull(object, tag)) {
		return object[tag.c_str()].GetInt();
	}
	else {
		return 0;
	}
}

string JsonController::getString(string object, string tag) {
	if (isNull(object, tag)) {
		return "";
	}
	rapidjson::Value& _obj = m_document[object.c_str()];
	if (_obj.IsNull()) {
		return "";
	}
	else {
		if (_obj[tag.c_str()].IsNull()) {
			return "";
		}
		else {
			return _obj[tag.c_str()].GetString();
		}
	}
}

int JsonController::getInt(string object, string tag) {
	const rapidjson::Value& _obj = m_document[object.c_str()];
	if (_obj.IsNull()) {
		return 0;
	}
	else {
		if (_obj[tag.c_str()].IsNull()) {
			return 0;
		}
		else {
			return _obj[tag.c_str()].GetInt();
		}
	}
}


bool JsonController::isNull(const rapidjson::Value& object, string tag) {
	if (!m_document.IsObject()){
		return false;
	}
	if (tag.compare("")!=0) {
		return object.IsNull();
	}
	return object[tag.c_str()].IsNull();
}

bool JsonController::isNull(string object, string tag) {
	if (!m_document.IsObject()){
		return false;
	}
	rapidjson::Value& _obj = m_document[object.c_str()];
	if (tag.compare("") != 0) {
		return _obj.IsNull();
	}
	return _obj[tag.c_str()].IsNull();
}
