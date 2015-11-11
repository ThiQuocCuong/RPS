#ifndef __CLIENT_MODEL_H__
#define __CLIENT_MODEL_H__
#include "cocos2d.h"
#include "Entities/Data/Vec3D.h"
using namespace std;
using namespace cocos2d;

enum class RecipientMode {
	TO_USER = 0, //the message will be sent to the User(passed as the target parameter)
	TO_ROOM, // the message will be sent to all Users in the Room(passed as the target parameter)
	TO_GROUP, // the message will be sent to all Users in the Room Group(passed as a String in the target parameter)
	TO_ZONE // the message will be sent to all Users in the Zone(target is ignored)
};

class LoginData : public Ref {
public:
	LoginData();
	LoginData(string language, string version, string token) {
		m_language = language;
		m_version = version;
		m_token = token;
	}
	string m_language;
	string m_version;
	string m_token;
};

class ModelRoom : public Ref {
public:
	ModelRoom() {
		m_id = 0;
		m_name = "";
		m_groupId = "";
		m_isJoined = false;
		m_isGame = false;
		m_isHidden = false;
		m_isPasswordProtected = false;
		m_isManaged = false;
		m_userCount = false;
		m_maxUsers = 0;
		m_spectatorCount = false;
		m_maxSpectators = 0;
		m_capacity = 0;
	}
	long int m_id;
	string m_name;
	string m_groupId;
	bool m_isJoined;
	bool m_isGame;
	bool m_isHidden;
	bool m_isPasswordProtected;
	bool m_isManaged;
	long int m_userCount;
	long int m_maxUsers;
	long int m_spectatorCount;
	long int m_maxSpectators;
	long int m_capacity;
};

class ModelUser : public Ref {
public:
	ModelUser() {
		m_id = 0;
		m_name = "";
		m_groupId = false;
		m_isPlayer = false;
		m_isSpectator = false;
		m_privilegeId = 0;
		m_isGuest = false;
		m_standardUser = false;
		m_isModerator = false;
		m_isAdmin = false;
		m_isItMe = false;
	}
	long int m_id;
	string m_name;
	long int m_groupId;
	bool m_isPlayer;
	bool m_isSpectator;
	long int m_privilegeId;
	bool m_isGuest;
	bool m_standardUser;
	bool m_isModerator;
	bool m_isAdmin;
	bool m_isItMe;
	//Vec3D *m_AOIEntryPoint;
};

class ModelInvitation : public Ref {
public:
	long int m_id;
	ModelUser *m_inviter;
	ModelUser *m_invitee;
	short int m_secondForAnswer;
};

class ModelMessageRecipientMode : public Ref {

};

class ModelRoomPermission : public Ref {
public:
	bool m_allowNameChange;
	bool m_allowPasswordStateChange;
	bool m_allowPublicMessage;
	bool m_allowResizig;
};

class ModelRoomEvent : public Ref {
public:
	bool m_allowUserEnter;
	bool m_allowUserExit;
	bool m_allowUserCountChange;
	bool m_allowVariableUpdate;
};

class ModelRoomExtention {
public:
	string m_id;
	string m_className;
	string m_propertesFile;
};

class ModelRoomSettings : public Ref {
public:
	string m_name;
	string m_password;
	bool m_isGame;
	short int m_maxUsers;
	short int m_maxVariables;
	short int m_maxSpectators;
	ModelRoomPermission *m_permission;
	ModelRoomEvent *m_events;
	ModelRoomExtention *m_ext;
	string m_groupID;
};

class ModelSFSGameSettings : public Ref {

};
class ModelBuddy : public Ref {


};
#endif