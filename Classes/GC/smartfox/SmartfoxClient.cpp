#include "SmartFoxClient.h"
#include "LoginRequest.h"
#include "LogoutRequest.h"
#include "PublicMessageRequest.h"
#include "JoinRoomRequest.h"
#include "SFSBuddyEvent.h"
#include "AddBuddyRequest.h"
#include "AdminMessageRequest.h"
#include "BanUserRequest.h"
#include "BlockBuddyRequest.h"
#include "BuddyMessageRequest.h"
#include "ChangeRoomCapacityRequest.h"
#include "ChangeRoomNameRequest.h"
#include "ChangeRoomPasswordStateRequest.h"
#include "CreateRoomRequest.h"
#include "SFSRoomVariable.h"
#include "CreateSFSGameRequest.h"
#include "ExtensionRequest.h"
#include "FindRoomsRequest.h"
#include "FindUsersRequest.h"
#include "GoOnlineRequest.h"
#include "InitBuddyListRequest.h"
#include "InvitationReplyRequest.h"
#include "InviteUsersRequest.h"
#include "ObjectMessageRequest.h"
#include "KickUserRequest.h"
#include "LeaveRoomRequest.h"
#include "ModeratorMessageRequest.h"
#include "PlayerToSpectatorRequest.h"
#include "SpectatorToPlayerRequest.h"
#include "QuickJoinGameRequest.h"
#include "RemoveBuddyRequest.h"
#include "SetBuddyVariablesRequest.h"
#include "SetRoomVariablesRequest.h"
#include "SetUserVariablesRequest.h"
#include "SubscribeRoomGroupRequest.h"
#include "UnsubscribeRoomGroupRequest.h"
#include "SFSRoom.h"
#include "SFSUser.h"
#include "SFSBuddy.h"

using namespace Buddylist;

//#pragma region Init methods
string SmartFoxClient::m_userName = "";
string SmartFoxClient::m_password = "";
string SmartFoxClient::m_zoneName = "";
string SmartFoxClient::m_roomName = "";
string SmartFoxClient::m_serverIp = "";
int SmartFoxClient::m_serverPort = 0;
bool SmartFoxClient::m_isAutoLogin = false;
bool SmartFoxClient::m_isLogining = false;
bool SmartFoxClient::m_isLoginSucess = false;

boost::shared_ptr<Sfs2X::SmartFox> SmartFoxClient::m_sm = nullptr;
SmartFoxClient *SmartFoxClient::m_instance = nullptr;
SFDelegate *SmartFoxClient::m_delegate = nullptr;
SmartFoxClient* SmartFoxClient::getInstance() {
	if (m_instance == nullptr) {
		m_instance = new SmartFoxClient();
	}
	return m_instance;
}

void SmartFoxClient::init(string serverIp, int serverPort, string userName, string password, string zoneName, string roomName, bool isAutoLogin)
{
	m_isAutoLogin = isAutoLogin;
	m_userName = userName;
	m_password = password;
	m_zoneName = zoneName;
	m_roomName = roomName;
	m_serverIp = serverIp;
	m_serverPort = serverPort;
	if (m_sm != nullptr)
	{
		if (m_sm->IsConnected())
		{
			login();
			return;
		}
		m_sm->RemoveAllEventListeners();
	}

	m_sm = boost::shared_ptr<Sfs2X::SmartFox>(new Sfs2X::SmartFox(true));
	m_sm->ThreadSafeMode(true);

	m_sm->AddEventListener(SFSEvent::CONNECTION, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onConnection, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::CONNECTION_LOST, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onConnectionLost, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::LOGIN, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onLogin, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::LOGIN_ERROR, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onLoginError, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::LOGOUT, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onLogout, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::ROOM_JOIN, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onJoinRoom, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::ROOM_JOIN_ERROR, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onJoinRoomError, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::USER_EXIT_ROOM, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onExitRoom, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::USER_ENTER_ROOM, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onEnterRoom, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::EXTENSION_RESPONSE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onExtensionResponse, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::PUBLIC_MESSAGE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onPublicChat, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::PRIVATE_MESSAGE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onPrivateChat, (unsigned long long)this)));
	m_sm->AddEventListener(SFSBuddyEvent::BUDDY_ADD, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onAddBuddySuccess, (unsigned long long)this)));
	m_sm->AddEventListener(SFSBuddyEvent::BUDDY_ERROR, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onBuddyError, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::ADMIN_MESSAGE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onAdminMessage, (unsigned long long)this)));
	m_sm->AddEventListener(SFSBuddyEvent::BUDDY_BLOCK, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onBlockBuddy, (unsigned long long)this)));
	m_sm->AddEventListener(SFSBuddyEvent::BUDDY_MESSAGE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onBuddyMessage, (unsigned long long)this)));
	m_sm->AddEventListener(SFSBuddyEvent::BUDDY_ONLINE_STATE_UPDATE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onUpdateBuddyOnlineStatus, (unsigned long long)this)));
	m_sm->AddEventListener(SFSBuddyEvent::BUDDY_LIST_INIT, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onInitBuddyList, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::ROOM_CAPACITY_CHANGE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onChangeRoomCapacity, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::ROOM_CAPACITY_CHANGE_ERROR, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onChangeRoomCapacityError, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::ROOM_PASSWORD_STATE_CHANGE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onChangeRoomPasswordState, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::ROOM_PASSWORD_STATE_CHANGE_ERROR, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onChangeRoomPasswordStateError, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::ROOM_NAME_CHANGE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onChangeRoomName, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::ROOM_NAME_CHANGE_ERROR, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onChangeRoomNameError, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::ROOM_ADD, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onCreateRoom, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::ROOM_CREATION_ERROR, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onCreateRoomError, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::ROOM_FIND_RESULT, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onFindRoomsResult, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::USER_FIND_RESULT, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onFindUsersResult , (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::INVITATION, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onInvitationReceived, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::INVITATION_REPLY_ERROR, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onReplyInvitationError, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::INVITATION_REPLY, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onReplyInvitation, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::MODERATOR_MESSAGE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onModeratorMessage, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::OBJECT_MESSAGE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onObjectMessage, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::PLAYER_TO_SPECTATOR, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onPlayerToSpectator, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::PLAYER_TO_SPECTATOR_ERROR, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onPlayerToSpectatorError, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::SPECTATOR_TO_PLAYER, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onSpectatorToPlayer, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::SPECTATOR_TO_PLAYER_ERROR, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onSpectatorToPlayerError, (unsigned long long)this)));
	m_sm->AddEventListener(SFSBuddyEvent::BUDDY_REMOVE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onRemoveBuddy, (unsigned long long)this)));
	m_sm->AddEventListener(SFSBuddyEvent::BUDDY_VARIABLES_UPDATE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onUpdateBuddyVariables, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::ROOM_VARIABLES_UPDATE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onUpdateRoomVariables, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::USER_VARIABLES_UPDATE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onUpdateUserVariables, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::ROOM_GROUP_SUBSCRIBE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onSubscribeRoomGroup, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::ROOM_GROUP_SUBSCRIBE_ERROR, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onSubscribeRoomGroupError, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::ROOM_GROUP_UNSUBSCRIBE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onUnsubscribeRoomGroup, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::ROOM_GROUP_UNSUBSCRIBE_ERROR, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onUnsubscribeRoomGroupError, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::HANDSHAKE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onHandShake, (unsigned long long)this)));
	m_sm->AddEventListener(SFSEvent::DEBUG_MESSAGE, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onDebugMessage, (unsigned long long)this)));
	
	/// <summary>
	/// log debug
	/// </summary>
	/// <param name="Name of the parameter">Description</param>
	/// <returns>Description of return value</returns>
	m_sm->AddLogListener(LogLevel::LOGLEVEL_DEBUG, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onDebugMessage, (unsigned long long)this)));
	m_sm->AddLogListener(LogLevel::LOGLEVEL_ERROR, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onDebugMessage, (unsigned long long)this)));
	m_sm->AddLogListener(LogLevel::LOGLEVEL_INFO, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onDebugMessage, (unsigned long long)this)));
	m_sm->AddLogListener(LogLevel::LOGLEVEL_WARN, boost::shared_ptr<EventListenerDelegate>(new EventListenerDelegate(SmartFoxClient::onDebugMessage, (unsigned long long)this)));

	//Connect
	if (isAutoLogin) {
		autoConnect();
	}
}
//#pragma endregion

//#pragma region Private auto methods
void SmartFoxClient::autoLogin(boost::shared_ptr<ISFSObject> data) {
	if (!m_isAutoLogin || m_isLogining || m_isLoginSucess) {
		return;
	}
	boost::shared_ptr<ISFSObject> loginData;
	if (!data) {
		loginData = boost::shared_ptr<ISFSObject>(new SFSObject());
		loginData->PutUtfString("language", "vi");
		loginData->PutUtfString("version", "0.0.1");
		loginData->PutUtfString("token", m_password);
	}
	else {
		loginData = data;
	}
	m_isLogining = true;
	m_sm->Send(boost::shared_ptr<LoginRequest>(new LoginRequest(m_userName, m_password, m_zoneName, loginData)));
}

void SmartFoxClient::autoConnect() {
	if (!m_sm->IsConnected())
	{
		m_sm->Connect(m_serverIp, (long int)m_serverPort);
	}
	else {
		autoLogin();
	}
}

void SmartFoxClient::autoDisconnect() {
	if (!m_isAutoLogin) {
		return;
	}
	if (m_sm == nullptr) { return; }
	m_sm->RemoveAllEventListeners();
	if (m_sm->IsConnected()) { m_sm->Disconnect(); }
}

void SmartFoxClient::autoJoinRoom() {
	boost::shared_ptr<string> ptrStdRoomName(new string(m_roomName));
	boost::shared_ptr<IRequest> request(new JoinRoomRequest(*ptrStdRoomName));
	m_sm->Send(request);
}

//#pragma endregion
//
//#pragma region Callback methods

/// <summary>
/// Log all message callback
/// </summary>
void SmartFoxClient::onDebugMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
	boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueMessage);
	//log(ptrNotifiedMessage->c_str());
}

void SmartFoxClient::onHandShake(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
					//boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
					//boost::shared_ptr<void> ptrEventParamValueSuccess = (*ptrEventParams)["success"];
	
					//if ((*((boost::static_pointer_cast<bool>)(ptrEventParamValueSuccess))) == true)
					//{
	 			//	   // Init OK: Execute an extension call via UDP
					//	
					//}
					//else
					//{
					//	// Sorry, UDP is not available. Initialization failed
					//}
}

void SmartFoxClient::onJoinRoomError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	autoDisconnect();
	if (m_delegate) {
		m_delegate->onUserJoinRoomError();
	}
}

void SmartFoxClient::onLogout(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	if (m_delegate) {
		m_delegate->onUserLogout();
	}
}

void SmartFoxClient::onLoginError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
	boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueErrorMessage);

	m_isLogining = false;
	m_isLoginSucess = false;
	autoDisconnect();
	if (m_delegate) {
		m_delegate->onUserLogin(false);
	}
}

void SmartFoxClient::onConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	autoDisconnect();
	if (m_delegate) {
		m_delegate->onUserConnection(false);
	}
}

void SmartFoxClient::onConnection(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	autoLogin();

	if (m_delegate) {
		m_delegate->onUserConnection(true);
	}
}

void SmartFoxClient::onLogin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	m_isLogining = false;
	m_isLoginSucess = true;
	m_isAutoLogin = true;
	if (m_roomName != "")
	{
		autoJoinRoom();
	}
	if (m_delegate) {
		m_delegate->onUserLogin(true);
	}
}

void SmartFoxClient::onJoinRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
	boost::shared_ptr<Room> ptrRoom = ((boost::static_pointer_cast<Room>))(ptrEventParamValueRoom);

	boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	//boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);

	string roomName = ptrRoom->Name()->c_str();
	//string userName = ptrNotifiedUser->Name()->c_str();
	string userName = "";
	if (m_delegate) {
		m_delegate->onUserJoinRoom(roomName);
	}
}

void SmartFoxClient::onEnterRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);

	boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
	boost::shared_ptr<Room> ptrRoom = ((boost::static_pointer_cast<Room>))(ptrEventParamValueRoom);

	string userName = ptrNotifiedUser->Name()->c_str();
	string roomName = ptrRoom->Name()->c_str();

	if (m_delegate) {
		m_delegate->onUserEnterRoom(userName, roomName);
	}
}

void SmartFoxClient::onExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);

	boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
	boost::shared_ptr<Room> ptrRoom = ((boost::static_pointer_cast<Room>))(ptrEventParamValueRoom);

	string userName = ptrNotifiedUser->Name()->c_str();
	string roomName = ptrRoom->Name()->c_str();
	if (m_delegate) {
		m_delegate->onUserExitRoom(userName, roomName);
	}
}

void SmartFoxClient::onPublicChat(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueSender = (*ptrEventParams)["sender"];
	boost::shared_ptr<User> ptrNotifiedUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueSender);

	boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
	boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueMessage);

	boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
	boost::shared_ptr<Room> ptrRoom = ((boost::static_pointer_cast<Room>))(ptrEventParamValueRoom);

	// Show message
	string userName = ptrNotifiedUser->Name()->c_str();
	string message = ptrNotifiedMessage->c_str();
	string roomName = ptrRoom->Name()->c_str();

	if (m_delegate) {
		m_delegate->onUserPublicChat(userName, roomName, message);
	}
}

void SmartFoxClient::onPrivateChat(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	//auto user = evt.Params["user"] as User;
}

void SmartFoxClient::onAddBuddySuccess(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	// Buddy was added
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueBuddy = (*ptrEventParams)["buddy"];
	boost::shared_ptr<Buddy> ptrNotifiedBuddy = ((boost::static_pointer_cast<Buddy>)(ptrEventParamValueBuddy));
	if (m_delegate) {
		Buddy *buddy = (Buddy*)ptrNotifiedBuddy.get();
		m_delegate->onAddBuddySuccess(buddy);
	}
}

void SmartFoxClient::onBuddyError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	// Room password change failed
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
	boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueErrorMessage));
	if (m_delegate) {
		m_delegate->onBuddyError(ptrErrorMessage->c_str());
	}
}

void SmartFoxClient::onAdminMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent){
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueSender = (*ptrEventParams)["sender"];
	boost::shared_ptr<User> ptrNotifiedSender = ((boost::static_pointer_cast<User>)(ptrEventParamValueSender));
	boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
	boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueMessage));
	if (m_delegate) {
		User *sender = (User*)ptrNotifiedSender.get();
		m_delegate->onAdminMessage(sender, ptrNotifiedMessage->c_str());
	}
}

void SmartFoxClient::onBlockBuddy(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	//SmartFoxClient* ptrMyClass = (SmartFoxClient*)ptrContext;
	// Buddy block status was changed
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueBuddy = (*ptrEventParams)["buddy"];
	boost::shared_ptr<Buddy> ptrNotifiedBuddy = ((boost::static_pointer_cast<Buddy>)(ptrEventParamValueBuddy));
	if (m_delegate) {
		Buddy *buddy = (Buddy*)ptrNotifiedBuddy.get();
		m_delegate->onBlockBuddySuccess(buddy);
	}
}
void SmartFoxClient::onBuddyMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueBuddy = (*ptrEventParams)["buddy"];
	boost::shared_ptr<Buddy> ptrNotifiedBuddy = ((boost::static_pointer_cast<Buddy>)(ptrEventParamValueBuddy));
	boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
	boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueMessage));
	boost::shared_ptr<void> ptrEventParamValueIsItMe = (*ptrEventParams)["isItMe"];
	boost::shared_ptr<bool> ptrNotifiedIsItMe = ((boost::static_pointer_cast<bool>)(ptrEventParamValueIsItMe));
	bool isMe = false;
	if ((*ptrNotifiedIsItMe) == true)
	{
		isMe = true;
	}

	if (m_delegate) {
		m_delegate->onBuddyMessage(ptrNotifiedMessage->c_str(), isMe);
	}
}

void SmartFoxClient::onChangeRoomCapacity(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
	boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>)(ptrEventParamValueRoom));
	if (m_delegate) {
		Room *room = (Room *)ptrNotifiedRoom.get();
		m_delegate->onChangeRoomCapacity(room);
	}
}

void SmartFoxClient::onChangeRoomCapacityError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
	boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueErrorMessage));
	if (m_delegate) {
		m_delegate->onChangeRoomStateError(ptrErrorMessage->c_str());
	}
}

void SmartFoxClient::onChangeRoomName(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
	boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>)(ptrEventParamValueRoom));
	boost::shared_ptr<void> ptrEventParamValueOldName = (*ptrEventParams)["oldName"];
	boost::shared_ptr<string> ptrOldName = ((boost::static_pointer_cast<string>)(ptrEventParamValueOldName));
	if (m_delegate) {
		Room *room = (Room *)ptrNotifiedRoom.get();
		m_delegate->onChangeRoomName(room, ptrOldName->c_str());
	}
}

void SmartFoxClient::onChangeRoomNameError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
	boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueErrorMessage));
	if (m_delegate) {
		m_delegate->onChangeRoomStateError(ptrErrorMessage->c_str());
	}
}

void SmartFoxClient::onChangeRoomPasswordState(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
	boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>)(ptrEventParamValueRoom));
	if (m_delegate) {
		Room *room = (Room *)ptrNotifiedRoom.get();
		m_delegate->onChangeRoomPassword(room);
	}
}

void SmartFoxClient::onChangeRoomPasswordStateError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
	boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueErrorMessage));
	if (m_delegate) {
		m_delegate->onChangeRoomStateError(ptrErrorMessage->c_str());
	}
}

void SmartFoxClient::onCreateRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
	boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>)(ptrEventParamValueRoom));
	if (m_delegate) {
		Room *room = (Room *)ptrNotifiedRoom.get();
		m_delegate->onCreateRoom(room);
	}
}

void SmartFoxClient::onCreateRoomError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
	boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueErrorMessage));
	if (m_delegate) {
		m_delegate->onChangeRoomStateError(ptrErrorMessage->c_str());
	}
}

void SmartFoxClient::onExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueCmd = (*ptrEventParams)["cmd"];
	boost::shared_ptr<string> ptrNotifiedCmd = ((boost::static_pointer_cast<string>)(ptrEventParamValueCmd));
	//if (*ptrNotifiedCmd == "add")
	//{
	//	// Similarly the server sends us an object with custom data.
	//	boost::shared_ptr<void> ptrEventParamValueParams = (*ptrEventParams)["params"];
	//	boost::shared_ptr<ISFSObject> ptrNotifiedISFSObject = ((boost::static_pointer_cast<ISFSObject>)(ptrEventParamValueParams));
	//	// We expect an int called sum
	//}
}

void SmartFoxClient::onFindRoomsResult(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueRooms = (*ptrEventParams)["rooms"];
	boost::shared_ptr<vector<boost::shared_ptr<Room>>> ptrNotifiedRooms = (boost::static_pointer_cast<vector<boost::shared_ptr<Room>>>)(ptrEventParamValueRooms);
	if (m_delegate) {
		vector<Room *> listRoom;
		for (int i = 0; i < ptrNotifiedRooms->size(); i++) {
			boost::shared_ptr<Room> r = ptrNotifiedRooms->at(i);
			Room *room = (Room *)r.get();
			listRoom.push_back(room);
		}
		m_delegate->onFindRooms(listRoom);
	}
}

void SmartFoxClient::onFindUsersResult(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueUsers = (*ptrEventParams)["users"];
	boost::shared_ptr<vector<boost::shared_ptr<User>>> ptrNotifiedUsers = ((boost::static_pointer_cast<vector<boost::shared_ptr<User>>>)(ptrEventParamValueUsers));
	if (m_delegate) {
		vector<User *> listUser;
		for (int i = 0; i < ptrNotifiedUsers->size(); i++) {
			boost::shared_ptr<User> r = ptrNotifiedUsers->at(i);
			User *user = (User *)r.get();
			listUser.push_back(user);
		}
		m_delegate->onFindUsers(listUser);
	}
}

void SmartFoxClient::onUpdateBuddyOnlineStatus(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueBuddy = (*ptrEventParams)["buddy"];
	boost::shared_ptr<Buddy> ptrNotifiedBuddy = ((boost::static_pointer_cast<Buddy>)(ptrEventParamValueBuddy));
	if (m_delegate) {
		m_delegate->onUpdateBuddyOnlineStatus(ptrNotifiedBuddy->IsOnline());
	}
}

void SmartFoxClient::onInitBuddyList(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	
}

void SmartFoxClient::onInvitationReceived(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueInvitation = (*ptrEventParams)["invitation"];
	boost::shared_ptr<Entities::Invitation::Invitation> ptrNotifiedInvitation = ((boost::static_pointer_cast<Entities::Invitation::Invitation>))(ptrEventParamValueInvitation);
	if (m_delegate) {
		Entities::Invitation::Invitation *inv = (Entities::Invitation::Invitation*)ptrNotifiedInvitation.get();
		m_delegate->onInvitationReceived(inv);
	}
}

void SmartFoxClient::onReplyInvitationError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent)
{
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
	boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueErrorMessage));
	if (m_delegate) {
		m_delegate->onReplyInvitationError(ptrErrorMessage->c_str());
	}
}

void SmartFoxClient::onReplyInvitation(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueReply = (*ptrEventParams)["reply"];
	boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
	boost::shared_ptr<Room> ptrNotifiedRoom = ((boost::static_pointer_cast<Room>)(ptrEventParamValueRoom));
	boost::shared_ptr<string> ptrNotifiedReply = ((boost::static_pointer_cast<string>))(ptrEventParamValueReply);
	if (ptrNotifiedReply->c_str() == "INVITATIONREPLY_ACCEPT")
	{
		// Send a game move to all players
		boost::shared_ptr<ISFSObject> dataObj(new SFSObject());
		dataObj->PutInt("roomId", ptrNotifiedRoom->Id());
		boost::shared_ptr<IRequest> request(new ObjectMessageRequest(dataObj));
		m_sm->Send(request);
	}
	else
	{
		// User has refused the invitation
		boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["invitee"];
		boost::shared_ptr<User> ptrNotifiedReply = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
	}
}

void SmartFoxClient::onModeratorMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueSender = (*ptrEventParams)["sender"];
	boost::shared_ptr<User> ptrNotifiedSender = ((boost::static_pointer_cast<User>)(ptrEventParamValueSender));
	boost::shared_ptr<void> ptrEventParamValueMessage = (*ptrEventParams)["message"];
	boost::shared_ptr<string> ptrNotifiedMessage = ((boost::static_pointer_cast<string>)(ptrEventParamValueMessage));
	if (m_delegate) {
		User *sender = (User*)ptrNotifiedSender.get();
		m_delegate->onModeratorMessage(sender, ptrNotifiedMessage->c_str());
	}
}

void SmartFoxClient::onObjectMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueSender = (*ptrEventParams)["sender"];
	boost::shared_ptr<User> ptrNotifiedSender = ((boost::static_pointer_cast<User>)(ptrEventParamValueSender));
	boost::shared_ptr<void> ptrEventParamValueObject = (*ptrEventParams)["message"];
	boost::shared_ptr<ISFSObject> ptrNotifiedObject = ((boost::static_pointer_cast<ISFSObject>)(ptrEventParamValueObject));
	if (m_delegate) {
		User *user = (User*)ptrNotifiedSender.get();
		SFSObject *message = (SFSObject*)ptrNotifiedObject.get();
		m_delegate->onObjectMessage(user, message);
	}
}

void SmartFoxClient::onPlayerToSpectator(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	// Success! I am now a spectator in this Game!
	if (m_delegate) {
		m_delegate->onPlayerToSpectator(true);
	}
}

void SmartFoxClient::onPlayerToSpectatorError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	// I was not able to become spectator in the Game
	if (m_delegate) {
		m_delegate->onPlayerToSpectator(false);
	}
}

void SmartFoxClient::onSpectatorToPlayer(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	// Success! I am now a player in this Game!
	if (m_delegate) {
		m_delegate->onSpectatorToPlayer(true);
	}
}

void SmartFoxClient::onSpectatorToPlayerError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueBuddy = (*ptrEventParams)["buddy"];
	boost::shared_ptr<Buddy> ptrNotifiedBuddy = ((boost::static_pointer_cast<Buddy>)(ptrEventParamValueBuddy));
	if (m_delegate) {
		m_delegate->onSpectatorToPlayer(false);
	}
}

void SmartFoxClient::onRemoveBuddy(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueBuddy = (*ptrEventParams)["buddy"];
	boost::shared_ptr<Buddy> ptrNotifiedBuddy = ((boost::static_pointer_cast<Buddy>)(ptrEventParamValueBuddy));
	if (m_delegate) {
		Buddy *buddy = (Buddy*)ptrNotifiedBuddy.get();
		m_delegate->onRemovedBuddy(buddy);
	}
}

void SmartFoxClient::onUpdateBuddyVariables(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueBuddy = (*ptrEventParams)["buddy"];
	boost::shared_ptr<void> ptrEventParamValueVars = (*ptrEventParams)["changedVars"];
	boost::shared_ptr<vector<boost::shared_ptr<string>>> changedVars = ((boost::static_pointer_cast<vector<boost::shared_ptr<string>>>)(ptrEventParamValueVars));
	boost::shared_ptr<Buddy> ptrNotifiedBuddy = ((boost::static_pointer_cast<Buddy>)(ptrEventParamValueBuddy));
	if (m_delegate) {
		Buddy *buddy = (Buddy*)ptrNotifiedBuddy.get();
		vector<string> _changedVars;
		for (int i = 0; i < changedVars->size(); i++) {
			boost::shared_ptr<string> str = changedVars->at(i);
			_changedVars.push_back(str->c_str());
		}
		m_delegate->onUpdateBuddyVariables(buddy, _changedVars);
	}
}

void SmartFoxClient::onUpdateRoomVariables(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueVars = (*ptrEventParams)["changedVars"];
	boost::shared_ptr<vector<boost::shared_ptr<string>>> changedVars = ((boost::static_pointer_cast<vector<boost::shared_ptr<string>>>)(ptrEventParamValueVars));
	boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["room"];
	boost::shared_ptr<Room> room = ((boost::static_pointer_cast<Room>)(ptrEventParamValueRoom));
	if (m_delegate) {
		Room *_room = (Room*)room.get();
		vector<string> _changedVars;
		for (int i = 0; i < changedVars->size(); i++) {
			boost::shared_ptr<string> str = changedVars->at(i);
			_changedVars.push_back(str->c_str());
		}
		m_delegate->onUpdateRoomVariables(_room, _changedVars);
	}
}

void SmartFoxClient::onUpdateUserVariables(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueVars = (*ptrEventParams)["changedVars"];
	boost::shared_ptr<vector<boost::shared_ptr<string>>> changedVars = ((boost::static_pointer_cast<vector<boost::shared_ptr<string>>>)(ptrEventParamValueVars));
	boost::shared_ptr<void> ptrEventParamValueRoom = (*ptrEventParams)["user"];
	boost::shared_ptr<User> room = ((boost::static_pointer_cast<User>)(ptrEventParamValueRoom));
	if (m_delegate) {
		User *_user = (User*)room.get();
		vector<string> _changedVars;
		for (int i = 0; i < changedVars->size(); i++) {
			boost::shared_ptr<string> str = changedVars->at(i);
			_changedVars.push_back(str->c_str());
		}
		m_delegate->onUpdateUserVariables(_user, _changedVars);
	}
}

void SmartFoxClient::onSubscribeRoomGroup(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueRooms = (*ptrEventParams)["newRooms"];
	boost::shared_ptr<vector<boost::shared_ptr<Room>>> ptrRooms = ((boost::static_pointer_cast<vector<boost::shared_ptr<Room>>>)(ptrEventParamValueRooms));
	if (m_delegate) {
		int size = ptrRooms->size();
		vector<Room *> rooms;
		for (int i = 0; i < size; i++) {
			boost::shared_ptr<Room> r = ptrRooms->at(i);
			Room *room = (Room *)r.get();
			rooms.push_back(room);
		}
		m_delegate->onSubscribeRoomGroup(rooms);
	}
}

void SmartFoxClient::onSubscribeRoomGroupError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
	boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueErrorMessage);
	if (m_delegate) {
		m_delegate->onSubcribeRoomGroupError(ptrErrorMessage->c_str());
	}
}

void SmartFoxClient::onUnsubscribeRoomGroup(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueGroupId = (*ptrEventParams)["groupId"];
	boost::shared_ptr<string> ptrGroupId = ((boost::static_pointer_cast<string>)(ptrEventParamValueGroupId));
	if (m_delegate) {
		m_delegate->onUnsubscribeRoomGroup(ptrGroupId->c_str());
	}
}

void SmartFoxClient::onUnsubscribeRoomGroupError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) {
	boost::shared_ptr<map<string, boost::shared_ptr<void>>> ptrEventParams = ptrEvent->Params();
	boost::shared_ptr<void> ptrEventParamValueErrorMessage = (*ptrEventParams)["errorMessage"];
	boost::shared_ptr<string> ptrErrorMessage = ((boost::static_pointer_cast<string>))(ptrEventParamValueErrorMessage);
	if (m_delegate) {
		m_delegate->onUnsubscribeRoomGroupError(ptrErrorMessage->c_str());
	}
}

//#pragma endregion
//
//#pragma region Core public methods
void SmartFoxClient::setDelegate(SFDelegate *del) {
	m_delegate = del;
}

void SmartFoxClient::updateEvents() {
	m_sm->ProcessEvents();
}

void SmartFoxClient::connect(string serverIp, int serverPort) {
	if (serverIp.compare("") != 0
		&& serverPort != -1) {
		m_serverIp = serverIp;
		m_serverPort = serverPort;
		autoConnect();
	}
}

void SmartFoxClient::login(string userName, string password, string zoneName, LoginData *loginData) {
	if (zoneName.compare("") != 0 ||
		m_zoneName.compare("") != 0) {
		m_userName = userName;
		m_password = password;
		if (zoneName.compare("") != 0) {
			m_zoneName = zoneName;
		}
		m_isAutoLogin = true;
		if (loginData) {
			boost::shared_ptr<ISFSObject> lData = boost::shared_ptr<ISFSObject>(new SFSObject());
			lData->PutUtfString("language", loginData->m_language);
			lData->PutUtfString("version", loginData->m_version);
			lData->PutUtfString("token", loginData->m_token);
			autoLogin(lData);
		}
		else  if(m_zoneName.compare("") !=0){
			autoLogin();
		}
	}
}

void SmartFoxClient::disconnect() {
	autoDisconnect();
}

void SmartFoxClient::joinRoom(string roomName) {
	if (roomName.compare("") != 0) {
		m_roomName = roomName;
		autoJoinRoom();
	}
}

void SmartFoxClient::logout() {
	boost::shared_ptr<IRequest> request(new LogoutRequest());
	m_sm->Send(request);
}

void SmartFoxClient::sendChatMessage(string userName, string message) {
	// Send chat message
	if (message == "") {
		return;
	}
	boost::shared_ptr<IRequest> request(new PublicMessageRequest(message));
	m_sm->Send(request);
	//m_sm->Send(boost::shared_ptr<PublicMessageRequest>(new PublicMessageRequest(m_userName, m_password, m_zoneName, loginData)));
}

void SmartFoxClient::addBuddy(string buddyName) {
	boost::shared_ptr<IRequest> request(new Buddylist::AddBuddyRequest(buddyName));
	m_sm->Send(request);
}

void SmartFoxClient::sendAdminMessage(string message, RecipientMode mode, string targetName) {
	switch (mode)
	{
	case RecipientMode::TO_USER: {
		boost::shared_ptr<User> user = m_sm->UserManager()->GetUserByName(targetName);
		boost::shared_ptr< MessageRecipientMode > recipientMode(new MessageRecipientMode((long int)mode, user));
		boost::shared_ptr<IRequest> request(new AdminMessageRequest(message, recipientMode));
		m_sm->Send(request);
		break;
	}
	case RecipientMode::TO_ROOM:{
		boost::shared_ptr<Room> room = m_sm->RoomManager()->GetRoomByName(targetName);
		boost::shared_ptr< MessageRecipientMode > recipientMode(new MessageRecipientMode((long int)mode, room));
		boost::shared_ptr<IRequest> request(new AdminMessageRequest(message, recipientMode));
		m_sm->Send(request);
		break;
	}
	case RecipientMode::TO_GROUP:{
		boost::shared_ptr< MessageRecipientMode > recipientMode(new MessageRecipientMode((long int)mode, targetName));
		boost::shared_ptr<IRequest> request(new AdminMessageRequest(message, recipientMode));
		m_sm->Send(request);
		break;
	}
	case RecipientMode::TO_ZONE:{
		boost::shared_ptr< MessageRecipientMode > recipientMode(new MessageRecipientMode((long int)mode, m_sm->CurrentZone()->c_str()));
		boost::shared_ptr<IRequest> request(new AdminMessageRequest(message, recipientMode));
		m_sm->Send(request);
	}
		break;
	default:
		break;
	}
}

void SmartFoxClient::banUser(int userId, string message, BanMode banMode, int 	delaySeconds, int durationHours) {
	boost::shared_ptr<IRequest> request(new BanUserRequest(userId, message, banMode, delaySeconds, durationHours));
	m_sm->Send(request);
}

void SmartFoxClient::blockBuddy(string buddyName, bool blocked) {
	boost::shared_ptr<IRequest> request(new BlockBuddyRequest(buddyName, blocked));
	m_sm->Send(request);
}

void SmartFoxClient::sendBuddyMessage(string message, Buddy *buddy, SFSObject *parameters) {
	boost::shared_ptr<Buddy> kermitTheFrog = m_sm->BuddyManager()->GetBuddyByName(buddy->Name()->c_str());
	boost::shared_ptr<IRequest> request(new BuddyMessageRequest(message, kermitTheFrog));
	m_sm->Send(request);
}

void SmartFoxClient::changeRoomCapcity(Room *room, long int newMaxUsers, long int newMaxSpect) {
	boost::shared_ptr<Room> theRoom = m_sm->GetRoomByName(room->Name()->c_str());
	boost::shared_ptr<IRequest> request(new ChangeRoomCapacityRequest(theRoom, newMaxUsers, newMaxSpect));
	m_sm->Send(request);
}

void SmartFoxClient::changeRoomCapcity(string roomName, long int newMaxUsers, long int newMaxSpect) {
	boost::shared_ptr<Room> theRoom = m_sm->GetRoomByName(roomName);
	boost::shared_ptr<IRequest> request(new ChangeRoomCapacityRequest(theRoom, newMaxUsers, newMaxSpect));
	m_sm->Send(request);
}

void SmartFoxClient::changeRoomName(Room *room, string name) {
	boost::shared_ptr<Room> theRoom = m_sm->GetRoomByName(room->Name()->c_str());
	// Change room name
	boost::shared_ptr<IRequest> request(new ChangeRoomNameRequest(theRoom, name));
	m_sm->Send(request);
}

void SmartFoxClient::changeRoomName(string oldName, string newName) {
	boost::shared_ptr<Room> theRoom = m_sm->GetRoomByName(oldName);
	// Change room name
	boost::shared_ptr<IRequest> request(new ChangeRoomNameRequest(theRoom, newName));
	m_sm->Send(request);
}

void SmartFoxClient::changeRoomPasswordState(Room *room, string newPass) {
	boost::shared_ptr<Room> theRoom = m_sm->GetRoomByName(room->Name()->c_str());
	// Change room password
	boost::shared_ptr<IRequest> request(new ChangeRoomPasswordStateRequest(theRoom, newPass));
	m_sm->Send(request);
}

void SmartFoxClient::changeRoomPasswordState(string roomName, string newPass) {
	boost::shared_ptr<Room> theRoom = m_sm->GetRoomByName(roomName);
	// Change room password
	boost::shared_ptr<IRequest> request(new ChangeRoomPasswordStateRequest(theRoom, newPass));
	m_sm->Send(request);
}


void SmartFoxClient::createRoom(RoomSettings *settings, bool autoJoin, Room *roomToLeave) {
	boost::shared_ptr<Room> theRoom = m_sm->GetRoomByName(roomToLeave->Name()->c_str());
	boost::shared_ptr<RoomSettings> _settings(settings);
	boost::shared_ptr<IRequest> request(new CreateRoomRequest(_settings));
	m_sm->Send(request);
}

void SmartFoxClient::findRoom(MatchExpression *expr, string groupId, long int limit) {
	//boost::shared_ptr<MatchExpression> expr(new MatchExpression("country", NumberMatch::EQUALS, "Sweden"));
	boost::shared_ptr<MatchExpression> _expr(expr);
	// Send request
	boost::shared_ptr<IRequest> request(new FindRoomsRequest(_expr, groupId, limit));
	m_sm->Send(request);

}

void SmartFoxClient::createSFSGame(Requests::Game::SFSGameSettings *settings) {
	boost::shared_ptr<Requests::Game::SFSGameSettings> _settings(settings);
	boost::shared_ptr<IRequest> request(new Requests::Game::CreateSFSGameRequest(_settings));
	m_sm->Send(request);
}

void SmartFoxClient::sendExtensionRequest(string extCmd, SFSObject *parameters, Room *room, bool useUDP) {
	// Send two integers to the Zone extension and get their sum in return
	/*boost::shared_ptr<ISFSObject> parameters(new SFSObject());
	parameers->PutInt("n1", 26);
	parameters->PutInt("n2", 16);*/
	// Send request
	boost::shared_ptr<ISFSObject> para(parameters);
	boost::shared_ptr<Room> _room(room);
	boost::shared_ptr<IRequest> request(new ExtensionRequest(extCmd, para, _room, useUDP));
	m_sm->Send(request);
}

void SmartFoxClient::findUsers(MatchExpression *expr, string target, long int limit) {
	//boost::shared_ptr<MatchExpression> expr(new MatchExpression("age", NumberMatch::EQUALS, 29));
	// Send request
	boost::shared_ptr<MatchExpression> _expr(expr);
	boost::shared_ptr<IRequest> request( new FindUsersRequest(_expr, target, limit));
	m_sm->Send(request);
}

void SmartFoxClient::findUsers(MatchExpression *expr, Room *target, long int limit) {
	boost::shared_ptr<Room> _room(target);
	boost::shared_ptr<MatchExpression> _expr(expr);
	boost::shared_ptr<IRequest> request(new FindUsersRequest(_expr, _room, limit));
	m_sm->Send(request);
}

void SmartFoxClient::goOnline(bool online) {
	boost::shared_ptr<IRequest> request(new GoOnlineRequest(online));
	m_sm->Send(request);
}

void SmartFoxClient::initBuddyList() {
	boost::shared_ptr<IRequest> request(new InitBuddyListRequest());
	m_sm->Send(request);
}

void SmartFoxClient::replyInvitation(Entities::Invitation::Invitation *invitation, Entities::Invitation::InvitationReply *reply, SFSObject *parameters) {
	boost::shared_ptr<Entities::Invitation::Invitation> _inv(invitation);
	boost::shared_ptr<Entities::Invitation::InvitationReply> _invRep(reply);
	boost::shared_ptr<SFSObject> _para(parameters);
	boost::shared_ptr<IRequest> request(new Requests::Game::InvitationReplyRequest(_inv, _invRep, _para));
	m_sm->Send(request);
}

void SmartFoxClient::inviteUser(vector<User*> invitedUsers, long int secondsDelay, SFSObject *parameters) {
	// Prepare the invitation
	
	boost::shared_ptr<User> user1 = m_sm->UserManager()->GetUserByName("Piggy");
	boost::shared_ptr<User> user2 = m_sm->UserManager()->GetUserByName("Gonzo");
	boost::shared_ptr<list<boost::shared_ptr<User>>> _invitedUsers(new list<boost::shared_ptr<User>>());
	_invitedUsers->push_back(user1);
	_invitedUsers->push_back(user2);
	// Send invitation
	boost::shared_ptr<IRequest> request(new Requests::Game::InviteUsersRequest(_invitedUsers, 20, boost::shared_ptr<ISFSObject>()));
	m_sm->Send(request);
}

void SmartFoxClient::kickUser(long int userID, string message, long int delaySeconds) {
	// Send request
	boost::shared_ptr<IRequest> request(new KickUserRequest(userID, message, delaySeconds));
	m_sm->Send(request);
}

void SmartFoxClient::leaveRoom(Room *room) {
	boost::shared_ptr<IRequest> request(new LeaveRoomRequest());
	m_sm->Send(request);
}

//void SmartFoxClient::sendModeratorMessage(string message, MessageRecipientMode *recipientMode, SFSObject*parameters) {
//	boost::shared_ptr<SFSObject> _para(parameters);
//	boost::shared_ptr<MessageRecipientMode> _recipientMode(recipientMode);
//	boost::shared_ptr<IRequest> request(new ModeratorMessageRequest(message, _recipientMode, _para));
//	m_sm->Send(request);
//}
void SmartFoxClient::sendModeratorMessage(string message, RecipientMode mode, string targetName) {
	switch (mode)
	{
	case RecipientMode::TO_USER: {
		boost::shared_ptr<User> user = m_sm->UserManager()->GetUserByName(targetName);
		boost::shared_ptr< MessageRecipientMode > recipientMode(new MessageRecipientMode((long int)mode, user));
		boost::shared_ptr<IRequest> request(new ModeratorMessageRequest(message, recipientMode));
		m_sm->Send(request);
		break;
	}
	case RecipientMode::TO_ROOM:{
		boost::shared_ptr<Room> room = m_sm->RoomManager()->GetRoomByName(targetName);
		boost::shared_ptr< MessageRecipientMode > recipientMode(new MessageRecipientMode((long int)mode, room));
		boost::shared_ptr<IRequest> request(new ModeratorMessageRequest(message, recipientMode));
		m_sm->Send(request);
		break;
	}
	case RecipientMode::TO_GROUP:{
		boost::shared_ptr< MessageRecipientMode > recipientMode(new MessageRecipientMode((long int)mode, targetName));
		boost::shared_ptr<IRequest> request(new ModeratorMessageRequest(message, recipientMode));
		m_sm->Send(request);
		break;
	}
	case RecipientMode::TO_ZONE:{
		boost::shared_ptr< MessageRecipientMode > recipientMode(new MessageRecipientMode((long int)mode, m_sm->CurrentZone()->c_str()));
		boost::shared_ptr<IRequest> request(new ModeratorMessageRequest(message, recipientMode));
		m_sm->Send(request);
	}
								break;
	default:
		break;
	}
}

void SmartFoxClient::sendObjectMessage(SFSObject *obj, Room *targetRoom) {
	// Send a game move to all players
	//boost::shared_ptr<ISFSObject> dataObj(new SFSObject());
	//dataObj->PutInt("x", myCharacter.x);
	//dataObj->PutInt("y", myCharacter.y);
	boost::shared_ptr<SFSObject> dataObj(obj);
	boost::shared_ptr<Room> room(targetRoom);

	boost::shared_ptr<IRequest> request(new ObjectMessageRequest(dataObj, room));
	m_sm->Send(request);
}

void SmartFoxClient::sendObjectMessage(SFSObject *obj, Room *targetRoom, vector<User*> recipients) {
	// Send a game move to all players
	//boost::shared_ptr<ISFSObject> dataObj(new SFSObject());
	//dataObj->PutInt("x", myCharacter.x);
	//dataObj->PutInt("y", myCharacter.y);
	boost::shared_ptr<SFSObject> dataObj(obj);
	boost::shared_ptr<Room> room(targetRoom);
	boost::shared_ptr< vector< boost::shared_ptr< User >>> _recipients(new vector<boost::shared_ptr<User>>);
	for (auto r : recipients) {
		boost::shared_ptr<User> user(r);
		_recipients->push_back(user);
	}
	boost::shared_ptr<IRequest> request(new ObjectMessageRequest(dataObj, room, _recipients));
	m_sm->Send(request);
}

void SmartFoxClient::turnPlayerToSpectator(Room *targetRoom) {
	if (targetRoom) {
		boost::shared_ptr<Room> room(targetRoom);
		boost::shared_ptr<IRequest> request(new PlayerToSpectatorRequest(room));
		m_sm->Send(request);
	}
	else {
		boost::shared_ptr<IRequest> request(new PlayerToSpectatorRequest());
		m_sm->Send(request);
	}
}

void SmartFoxClient::turnSpectatorToPlayer(Room *targetRoom) {
	if (targetRoom) {
		boost::shared_ptr<Room> room(targetRoom);
		boost::shared_ptr<IRequest> request(new SpectatorToPlayerRequest(room));
		m_sm->Send(request);
	}
	else {
		boost::shared_ptr<IRequest> request(new SpectatorToPlayerRequest());
		m_sm->Send(request);
	}
}

void SmartFoxClient::quickJoinGame(MatchExpression *exp, vector<string> whereToSearch, Room *roomToLeave) {
	//boost::shared_ptr<string> value(new string("Darts"));
	//boost::shared_ptr<long int> value1(new long int());
	//*value1 = 400;
	//boost::shared_ptr<MatchExpression> exp(new MatchExpression("type", StringMatch::EQUALS, value, MatchExpression::MatchExpressionValueType::MatchExpression_ValueString))->And(new MatchExpression("bestScore", NumberMatch::LESS_THAN, value1, MatchExpression::MatchExpressionValueType::MatchExpression_ValueOther));
	//// Search the "games" Group for a free public game of Darts with a bestScore variable < 400 
	//boost::shared_ptr<vector<boost::shared_ptr<string>>> whereToSearch(new vector<boost::shared_ptr<string>>);
	//whereToSearch->push_back("[""games""]");
	boost::shared_ptr<MatchExpression> _exp(exp);
	boost::shared_ptr<Room> room(roomToLeave);
	boost::shared_ptr<vector<string>> where(new vector<string>);
	for (auto s : whereToSearch) {
		where->push_back(s);
	}
	boost::shared_ptr<IRequest> request(new Requests::Game::QuickJoinGameRequest(_exp, where, room));
	m_sm->Send(request);
}

void SmartFoxClient::removeBuddy(string buddyName) {
	boost::shared_ptr<IRequest> request(new RemoveBuddyRequest(buddyName));
	m_sm->Send(request);
}

void SmartFoxClient::setBuddyVariables(vector<BuddyVariable*> variables) {
	/*boost::shared_ptr<list<boost::shared_ptr<BuddyVariable>>> myVars(new list<boost::shared_ptr<BuddyVariable>>());
	boost::shared_ptr<SFSBuddyVariable> currentTrack(new SFSBuddyVariable("track", "Beethoven's 8th Symphony", VARIABLETYPE_STRING));
	myVars->push_back(currentTrack);*/
	boost::shared_ptr<list<boost::shared_ptr<BuddyVariable>>> myVars(new list<boost::shared_ptr<BuddyVariable>>);
	for (auto v : variables){
		boost::shared_ptr<BuddyVariable> bv(v);
		myVars->push_back(bv);
	}
	boost::shared_ptr<IRequest> request(new SetBuddyVariablesRequest(myVars));
	m_sm->Send(request);
}

void SmartFoxClient::setRoomVariables(vector<RoomVariable*> variables, Room *targetRoom) {
	/*boost::shared_ptr<vector<boost::shared_ptr<RoomVariable>>> collectionRoomVariables(new vector<boost::shared_ptrvRoomVariable >> ());
	boost::shared_ptr<RoomVariable> variable(new RoomVariable("gameStarted", false, VARIABLETYPE_BOOL));
	collectionRoomVariables->push_back(variable);
	boost::shared_ptr<RoomVariable> variable1(new RoomVariable("gameType", "Snooker", VARIABLETYPE_STRING));
	collectionRoomVariables->push_back(variable1);
	boost::shared_ptr<RoomVariable> variable2(new RoomVariable("minRank", 10, VARIABLETYPE_INT));
	collectionRoomVariables->push_back(variable2);
	collectionUserVariable->push_back(variable3);
	boost::shared_ptr<IRequest> request(new SetRoomVariablesRequest(collectionRoomVariables, ptrSmartFox->MySelf()->LastJoinedRoom()));
	ptrSmartFox->Send(request);*/
	boost::shared_ptr<vector<boost::shared_ptr<RoomVariable>>> myVars(new vector<boost::shared_ptr<RoomVariable>>);
	for (auto v : variables){
		boost::shared_ptr<RoomVariable> bv(v);
		myVars->push_back(bv);
	}
	boost::shared_ptr<Room> room(targetRoom);
	boost::shared_ptr<IRequest> request(new SetRoomVariablesRequest(myVars, room));
	m_sm->Send(request);
}

void SmartFoxClient::setUserVariables(vector<UserVariable*> variables) {	
	/*boost::shared_ptr<vector<boost::shared_ptr<UserVariable>>> collectionUserVariable(new vector<boost::shared_ptr<UserVariable>>());
	boost::shared_ptr<UserVariable> variable(new UserVariable("avatarType", "SwedishCook", VARIABLETYPE_STRING));
	collectionUserVariable->push_back(variable);
	boost::shared_ptr<UserVariable> variable1(new UserVariable("country", "Sweden", VARIABLETYPE_STRING));
	collectionUserVariable->push_back(variable1);
	boost::shared_ptr<UserVariable> variable2(new UserVariable("x", 10, VARIABLETYPE_INT));
	collectionUserVariable->push_back(variable2);
	boost::shared_ptr<UserVariable> variable3(new UserVariable("y", 10, VARIABLETYPE_INT));
	collectionUserVariable->push_back(variable3);
	boost::shared_ptr<IRequest> request(new SetUserVariablesRequest(collectionUserVariable));
	ptrSmartFox->Send(request);*/
	boost::shared_ptr<vector<boost::shared_ptr<UserVariable>>> myVars(new vector<boost::shared_ptr<UserVariable>>);
	for (auto v : variables){
		boost::shared_ptr<UserVariable> bv(v);
		myVars->push_back(bv);
	}
	boost::shared_ptr<IRequest> request(new SetUserVariablesRequest(myVars));
	m_sm->Send(request);
}

void SmartFoxClient::subscribeRoomGroup(string groupName) {
	boost::shared_ptr<IRequest> request(new SubscribeRoomGroupRequest(groupName));
	m_sm->Send(request);
}

void SmartFoxClient::UnsubscribeRoomGroup(string groupName) {
	boost::shared_ptr<IRequest> request(new UnsubscribeRoomGroupRequest(groupName));
	m_sm->Send(request);
}

//#pragma endregion

//#pragma region Get-set method
Room *SmartFoxClient::getRoom(string roomName) {
	boost::shared_ptr<Room> room = m_sm->GetRoomByName(roomName);
	return (Room*)room.get();
}
//#pragma endregion