#include "JsonController.h"

JsonController::JsonController() {
	//m_document.SetObject();
}
void JsonController::read(string json) {
	m_document.Parse(json.c_str());
}

string JsonController::getString( rapidjson::Value& object, string tag, int index) {
	if (isNull(object, tag, index)) {
		return "";
	}
	else {
        if(index == -1) {
            return object[tag.c_str()].GetString();
        }
        return object[tag.c_str()][index].GetString();
	}
}

int JsonController::getInt( rapidjson::Value& object, string tag, int index) {
    if (isNull(object, tag, index)) {
        return 0;
    }
    else {
        if(index == -1) {
            return object[tag.c_str()].GetInt();
        }
        return object[tag.c_str()][index].GetInt();
    }
}

string JsonController::getString(string object, string tag, int index) {
    if (isNull(object, tag, index)) {
        return "";
    }
    else {
        rapidjson::Value &_obj = m_document[object.c_str()];
        if(index == -1) {
            if(tag == "") {
                return _obj.GetString();
            }
            return _obj[tag.c_str()].GetString();
        }
        return _obj[tag.c_str()][index].GetString();
    }
//	if (isNull(object, tag)) {
//		return "";
//	}
//    
//    if(tag == "") {
//        return m_document[object.c_str()].GetString();
//    }
//    
//	rapidjson::Value& _obj = m_document[object.c_str()];
//	if (_obj.IsNull()) {
//		return "";
//	}
//	else {
//		return _obj[tag.c_str()].GetString();
//	}
}

int JsonController::getInt(string object, string tag, int index) {
    if (isNull(object, tag, index)) {
        return 0;
    }
    else {
        rapidjson::Value &_obj = m_document[object.c_str()];
        if(index == -1) {
            if(tag == "") {
                return _obj.GetInt();
            }
            return _obj[tag.c_str()].GetInt();
        }
        return _obj[tag.c_str()][index].GetInt();
    }
//    if(isNull(object, tag)) {
//        return 0;
//    }
//    if(tag == "") {
//        return m_document[object.c_str()].GetInt();
//    }
//	 rapidjson::Value& _obj = m_document[object.c_str()];
//	if (_obj.IsNull()) {
//		return 0;
//	}
//	else {
//        return _obj[tag.c_str()].GetInt();
//	}
}

bool JsonController::getBool(rapidjson::Value& object, string tag, int index) {
    if (isNull(object, tag, index)) {
        return false;
    }
    else {
        if(index == -1) {
            return object[tag.c_str()].GetBool();
        }
        return object[tag.c_str()][index].GetBool();
    }
}
bool JsonController::getBool(rapidjson::Value& object, int index) {
    return object[index].GetBool();
}
bool JsonController::getBool(string object, string tag, int index) {
    if (isNull(object, tag, index)) {
        return false;
    }
    else {
        rapidjson::Value &_obj = m_document[object.c_str()];
        if(index == -1) {
            if(tag == "") {
                return _obj.GetBool();
            }
            return _obj[tag.c_str()].GetBool();
        }
        return _obj[tag.c_str()][index].GetBool();
    }
}

rapidjson::Value& JsonController::getObject(rapidjson::Value &object, string tag, int index) {
    if(index == -1) {
         return object[tag.c_str()];
    }
    return object[tag.c_str()][index];
}

rapidjson::Value & JsonController::getObject(string object, string tag, int index) {
    rapidjson::Value &_obj = m_document[object.c_str()];
    if(index == -1) {
        if(tag == "") {
            return _obj;
        }
        return _obj[tag.c_str()];
    }
    return _obj[tag.c_str()][index];
//    if(tag == "") {
//        return m_document[object.c_str()];
//    }
//    rapidjson::Value &_obj = m_document[object.c_str()];
//    return _obj[tag.c_str()];
}

rapidjson::Value &JsonController::getObject(rapidjson::Value &object, int index) {
    return object[index];
}

int JsonController::getInt(rapidjson::Value &object, int index) {
    return object[index].GetInt();
}

string JsonController::getString(rapidjson::Value &object, int index) {
    return object[index].GetString();
}

bool JsonController::isNull(string object, string tag, int index) {
	if (!m_document.IsObject()){
		return false;
	}
    if(index == -1) {
        if(tag == "") {
            return m_document[object.c_str()].IsNull();
        }
        rapidjson::Value& _obj = m_document[object.c_str()];
        if(_obj.IsNull()) {
            return true;
        }
        return _obj[tag.c_str()].IsNull();
    }
    
    rapidjson::Value& _obj = m_document[object.c_str()];
    if(_obj.IsNull()) {
        return false;
    }
    rapidjson::Value& _obj2 = _obj[tag.c_str()];
    if(_obj2.IsNull()) {
        return true;
    }
    return _obj2[index].IsNull();

}


bool JsonController::isNull(rapidjson::Value& object, string tag, int index) {
    if (!m_document.IsObject()){
        return false;
    }
    if(index == -1) {
        if(tag == "") {
            return object.IsNull();
        }
        return object[tag.c_str()].IsNull();
    }
    
    if(object[tag.c_str()].IsNull()) {
        return true;
    }
    return object[tag.c_str()][index].IsNull();
}

bool JsonController::isNull(rapidjson::Value& object, int index) {
    return object[index].IsNull();
}
