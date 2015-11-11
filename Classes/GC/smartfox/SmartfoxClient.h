#ifndef __SMARTFOX_CLIENT_H__
#define __SMARTFOX_CLIENT_H__

#include "SFXModel.h"
#include "SFDelegate.h"
#include "SmartFox.h"
#include "MessageRecipientMode.h"
#include "BanMode.h"
#include "RoomSettings.h"
#include "SFSGameSettings.h"
#include "MatchExpression.h"
#include "Invitation.h"
#include "InvitationReply.h"

using namespace Sfs2X;
using namespace Requests;
class SmartFoxClient{
	static bool m_isLoginSucess;
	static bool m_isLogining;
	static SFDelegate *m_delegate;
	static SmartFoxClient *m_instance;
	static bool m_isAutoLogin;
	static string m_userName;
	static string m_password;
	static string m_zoneName;
	static string m_roomName;
	static string m_serverIp;
	static int m_serverPort;

	static boost::shared_ptr<Sfs2X::SmartFox> m_sm;

	static void showLog(string mess);

	static void autoLogin(boost::shared_ptr<ISFSObject> data = nullptr);
	static void autoConnect();
	static void autoDisconnect();
	static void autoJoinRoom();

	static void onHandShake(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onJoinRoomError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onLogout(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onLoginError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onConnectionLost(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onConnection(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onLogin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onJoinRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onEnterRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onExitRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onExtensionResponse(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onPublicChat(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onPrivateChat(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onAddBuddySuccess(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onBuddyError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onAdminMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onModeratorMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onBanUser(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onBlockBuddy(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onBuddyMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onRemoveBuddy(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onUpdateBuddyVariables(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onChangeRoomCapacity(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onChangeRoomCapacityError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onChangeRoomName(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onChangeRoomNameError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onChangeRoomPasswordState(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onChangeRoomPasswordStateError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onCreateRoom(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onCreateRoomError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onFindRoomsResult(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onUpdateRoomVariables(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onUpdateUserVariables(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onFindUsersResult(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onUpdateBuddyOnlineStatus(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onInitBuddyList(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onInvitationReceived(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onReplyInvitationError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onReplyInvitation(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onObjectMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onPlayerToSpectator(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onPlayerToSpectatorError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onSpectatorToPlayer(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onSpectatorToPlayerError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onSubscribeRoomGroup(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onSubscribeRoomGroupError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onUnsubscribeRoomGroup(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onUnsubscribeRoomGroupError(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	static void onDebugMessage(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
public:
	static SmartFoxClient *getInstance();

	/// <summary>
	/// To receive and send message continuity
	/// </summary>
	void updateEvents();

	/// <summary>
	/// Init enviroment, add eventListener
	/// </summary>
	/// <param name="isAutoLogin">If u want to connect to server automatically/param>
	/// <param name="serverIp">server ip adress</param>
	/// <param name="serverPort">server port</param>
	/// <param name="userName">user Name</param>
	/// <param name="password">password login</param>
	/// <param name="zoneName">zone name</param>
	/// <param name="roomName">name of the room which user join in</param>
	/// <returns>Description of return value</returns>
	void init(string serverIp = "",
			  int serverPort = -1, 
			  string userName ="", 
			  string password ="", 
			  string zoneName ="", 
			  string roomName ="",
			  bool isAutoLogin = false);

	/// <summary>
	/// Connect to server
	/// </summary>
	void connect(string serverIp = "", int serverPort = -1);

	/// <summary>
	/// login to server. Can pass empty parameters if auto call (in connect)
	/// </summary>
	void login(string userName = "", string password = "", string zoneName = "", LoginData *loginData= nullptr);

	/// <summary>
	/// Disconnect from server
	/// </summary>
	void disconnect();

	/// <summary>
	/// Call to join room with roomName parameter
	/// </summary>
	/// <param name="Name of the parameter">Description</param>
	/// <returns>Description of return value</returns>
	void joinRoom(string roomName ="");

	/// <summary>
	/// logout from server
	/// </summary>

	void logout();

	/// <summary>
	/// Add a new Buddy to the current Buddy List
	/// </summary>
	/// <param name="buddyName">the name of the buddy to add</param>

	void addBuddy(string buddyName);

	void sendChatMessage(string userName, string message);

	/// <summary>
	/// Send a Admin Message to a specific User or groups of Users
	/// The sender must have the admin privileges to be able to send these kinds of messages.
	/// The recipient parameter can be used to specify if the message is sent to a User, a Room, the Room Group or the whole Zone.
	/// </summary>
	/// <param name="messager">The admin message</param>
	/// <param name="recipientMode">the recipient mode (message can be sent to single User, a Room, the whole Room Group or the Zone)</param>
	/// <param name="targetName">Name of the targetUser, targetRoom or groupID, empty when sent to zone</param>
	/// <returns>Description of return value</returns>
	void sendAdminMessage(string message, RecipientMode mode, string targetName = "");

	/// <summary>
	/// Banish a User from the system (for moderators and admins only)
	/// Allows to send a custom message and to set a delay in seconds.It also allows to choose banning by user name or user IP address
	/// </summary>
	/// <param name="userID">the id of the User to be banned</param>
	/// <param name="message">a custom ban message, if null the message configured on the server side will be used</param>
	/// <param name="banMode">choose between banning by Ip Address or User name, see BanMode class</param>
	/// <param name="delaySeconds">a delay in seconds between the message (immediate) and the kick (delayed). Default is 5 seconds</param>
	/// <param name="durationHours">The duration of the banishment, expressed in hours.</param>
	/// <returns>Description of return value</returns>
	void banUser(int userId,
		         string message,
		         BanMode banMode = BanMode::BANMODE_BY_NAME,
		         int delaySeconds = 5,
		         int durationHours = 0);


	/// <summary>
	/// Block/Unblock a Buddy in the User's BuddyList
    /// Blocked buddies won't be able to see the the User online status and send messages or events
	/// </summary>
	/// <param name="buddyName">the name of the buddy to add</param>
	/// <param name="blocked">the blocked status</param>
	/// <returns>Description of return value</returns>
	void blockBuddy(string buddyName, bool blocked);

	/// <summary>
	/// BuddyMessage(s) are similar to private chat messages but are specifically designed for the Buddy List system.
	/// They don't require any Room parameter, nor they require that Users are joined into any particular Room. Additionally the Buddy Message performs specific validation such as making sure that the recipient is in the User's BuddyList and verifies the Buddy block status.
	/// </summary>
	/// <param name="Name of the parameter">Description</param>
	/// <returns>Description of return value</returns>
	void sendBuddyMessage(string message, Buddy *buddy, SFSObject *parameters = nullptr);

	/// <summary>
	/// Initializes the BuddyList system.
    /// This involves loading any previously stored Buddy data from the server, such as the User's Buddy List, his previous state and his persistent Buddy Variables. The init request is the first operation required to initialize the BuddyList system. Once the Init is executed the User can have access to all his previous data and start to interact with his Buddies.
	/// </summary>
	void initBuddyList();

	/// <summary>
	/// Change the capacity of a Room (maxUsers and maxSpectators) at runtime.
	/// This request might fail if the Room was configured not be re - sizable or if the User sending the request is not the owner of the Room.Moderators and Administrator can override this last constraint.
    /// It is possible to "shrink" the Room capacity so that maxUsers < userCount.
	/// In this case nothing will happen to the "extra" users.
	/// As soon as clients will leave the Room the userCount will get down to the new maxUsers value.
	/// </summary>
	/// <param name="Name of the parameter">Description</param>
	/// <returns>Description of return value</returns>
	void changeRoomCapcity(Room *room, long int newMaxUsers, long int newMaxSpect);
	void changeRoomCapcity(string roomName, long int newMaxUsers, long int newMaxSpect);

	/// <summary>
	/// Change the name of a Room at runtime.
    /// This request might fail if the Room was configured not be renamed or if the User sending the request is not the owner of the Room.
	/// Moderators and Administrator can override this last constraint.
	/// </summary>
	/// <param name="room">the Room to rename - is can be replaced by a name</param>
	/// <param name="name">the new Room name (no duplicates are allowed)< / param>
	/// <returns>Description of return value</returns>
	void changeRoomName(Room *room, string name);
	void changeRoomName(string oldName, string newName);

	/// <summary>
	/// Changes the password of a Room at runtime.
    /// The request not only changes the password of a Room but also its "password state", which indicates if a Room is password protected or not.
	/// This request might fail if the Room was configured to deny password runtime changes or if the User sending the request is not the owner of the Room.
    /// Moderators and Administrator can override this last constraint.
	/// </summary>
	/// <param name="room">the room< / param>
	/// <param name="newPass">the new password (null or empty string means no password)< / param>
	/// <returns>Description of return value</returns>
	void changeRoomPasswordState(Room *room, string newPass);
	void changeRoomPasswordState(string roomName, string newPass);

	/// <summary>
	/// Creates a new Room in the current Zone
	/// </summary>
	/// <param name="settings">the new room settings, see RoomSettings for all the details</param>
	/// <param name="autoJoin">if true the Room will be joined as soon as it is created</param>
	/// <param name="roomToLeave">indicates which Room should be left once the join has succeeded< / param>
	/// <returns>Description of return value</returns>
	void createRoom(RoomSettings *settings, bool autoJoin = false, Room *roomToLeave = nullptr);

	/// <summary>
	/// Search Rooms in the system by matching their variables and properties against a MatchExpression
	/// </summary>
	/// <param name="expr">the match expression</param>
	/// <param name="groupId">the id of the Room Group where to perform the search, if null the search will be Zone-wide (default)</param>
	/// <param name="limit">the number of results wanted. Zero means no limit, we will get all results (default)</param>
	/// <returns>Description of return value</returns>
	void findRoom(MatchExpression *expr, string groupId, long int limit = 0);

	/// <summary>
	/// Search Users in the system by matching their variables and properties against a MatchExpression
	/// </summary>
	/// <param name="expr">the match expression</param>
	/// <param name="target">it can be a Room or String (the Group Id), if null the search will done in the whole Zone (default)</param>
	/// <param name="limit">the number of results wanted. Zero means no limit, we will get all results (default)</param>
	/// <returns>Description of return value</returns>
	void findUsers(MatchExpression *expr, string target, long int limit = 0);
	void findUsers(MatchExpression *expr, Room *target, long int limit = 0);

	/// <summary>
	/// The request launches a new public or private game, including game invitations, player matching and a lot more.
    /// The game is launched via the creation of an SFSGame, a specialized Room type that provides advanced features during the creation phase of a game.
    /// A more in - depth overview of the SFS2X Game API is provided in the general documentation
	/// </summary>
	void createSFSGame(Requests::Game::SFSGameSettings *settings);

	/// <summary>
	/// Sends a request to a Zone or Room Extension.
    /// Each request to an extension is characterized by two parameters :
	/// //// command name : any string that identifies an action that should be executed on the server side.We recommend to use the same command name for both the client request and the server response.
	/// ///	request data : you can send any simple or complex data structures to your extension(s) via the SFSObject class
	/// </summary>
	/// <param name="extCmd">the command name</param>
	/// <param name="parameters">the custom extension request data</param>
	/// <param name="room">when specified it will send the request to the Room Extension. The user must be joined in that Room</param>
	/// <param name="useUDP">(optional) uses UDP to send the request</param>
	/// <returns>Description of return value</returns>
	void sendExtensionRequest(string extCmd, SFSObject *parameters, Room *room, bool useUDP = false);

	/// <summary>
	/// Toggles the Buddy ONLINE status of the User.
    /// All clients who have the current User as their Buddy in the BuddyList, will see his status change accordingly.Going online / offline as Buddy doesn't affect the User connection,the currently joined Zone/Rooms etc...
    /// The ONLINE status is maintained by a reserved and persistent BuddyVariable.
	/// </summary>
	/// <param name="online">the Buddy Online status< / param>
	/// <returns>Description of return value</returns>
	void goOnline(bool online);

	/// <summary>
	/// Send a reply to an Invitation.
    /// The reply can be either an ACCEPT or REFUSE.If the reply doesn't get to the inviter within the expected amount of time the system will handle it as a REFUSE.
	/// </summary>
	/// <param name="invitation">a reference to the received invitation</param>
	/// <param name="reply">the reply code</param>
	/// <param name="parameters">custom reply parameters</param>
	/// <returns>Description of return value</returns>
	void replyInvitation(Entities::Invitation::Invitation *invitation, Entities::Invitation::InvitationReply *reply, SFSObject *parameters = nullptr);

	/// <summary>
	/// end one or more generic invitations to a list of Users.
	/// Invitations can be used for different purposes such as playing games, visiting a specific Room, Buddy requests etc...
	/// </summary>
	/// <param name="invitedUsers">a list of invited Users</param>
	/// <param name="secondsDelay">	the amount of seconds allowed to the invited User to reply (recommended range 15-40 seconds)</param>
	/// <param name="parameters">optional custom invitation parameters</param>
	/// <returns>Description of return value</returns>
	void inviteUser(vector<User*> invitedUsers, long int secondsDelay = 15, SFSObject *parameters = nullptr);

	/// <summary>
	/// Kicks a User out of the server (for moderators and admins only)
    /// Allows to send a custom message and to set a delay in seconds.
	/// </summary>
	/// <param name="userID">the id of the User to be kicked out of the server</param>
	/// <param name="message">a custom kick message, if null the message configured on the server side will be used</param>
	/// <param name="delaySeconds">a delay in seconds between the message (immediate) and the kick (delayed). Default is 5 seconds</param>
	/// <returns>Description of return value</returns>
	void kickUser(long int userID, string message = "", long int delaySeconds = 5);

	/// <summary>
	/// Leaves a currently joined Room
	/// </summary>
	/// <returns>Description of return value</returns>

	void leaveRoom(Room *room);

	/// <summary>
	/// Send a Moderator Message to a specific User or groups of Users
	/// The sender must have the moderator privileges to be able to send these kinds of messages.
	///	The recipient parameter can be used to specify if the message is sent to a User, a Room, the Room Group or the whole Zone.
	/// </summary>
	/// <param name="Name of the parameter">Description</param>
	/// <returns>Description of return value</returns>
	//void sendModeratorMessage(string message, MessageRecipientMode *recipientMode, SFSObject*parameters = nullptr);
	void sendModeratorMessage(string message, RecipientMode mode, string targetName = "");

	/// <summary>
	/// Send a custom data Object to all users in a Room or a sub-selection of them
	/// (If you are familiar with SmartFoxServer 1.x this request the equivalent of sendObject)
	/// The request allow to send a custom data object to all users in the same Room.A typical use of this request is for sending game moves to other players
	/// </summary>
	/// <param name="obj">the custom object</param>
	/// <param name="targetRoom">an optional target room. This room must be joined and by default it is the last joined Room</param>
	/// <param name="recipients">an optional selection of Users in the target Room (by default the message is sent to all Users)< / param>
	/// <returns>Description of return value</returns>

	void sendObjectMessage(SFSObject *obj, Room *targetRoom, vector<User*> recipients);
	void sendObjectMessage(SFSObject *obj, Room *targetRoom = nullptr);

	/// <summary>
	/// Attempt to turn the current User from Player to a Spectator (in a Game Room)
	/// This could fail if no Spectator slots are available in the Room at the time of the request
	/// </summary>
	/// <param name="targetRoom">the Room where the change has to be performed, a null value indicates the last joined Room (default)</param>
	/// <returns>Description of return value</returns>
	void turnPlayerToSpectator(Room *targetRoom = nullptr);

	/// <summary>
	/// Attempt to turn the current User from Spectator into a Player (in a Game Room)
    /// This could fail if no Player slots are available in the Room at the time of the request
	/// </summary>
	/// <param name="targetRoom">the Room where the change has to be performed, a null value indicates the last joined Room (default)</param>
	/// <returns>Description of return value</returns>
	void turnSpectatorToPlayer(Room *targetRoom = nullptr);

	/// <summary>
	/// Quick join a User in a public game.
	/// By providing a MatchExpression and a list of Rooms or Groups the system can search for matching Rooms and immediately teleport the player in the game action.
	/// </summary>
	/// <param name="Name of the parameter">Description</param>
	/// <returns>Description of return value</returns>
	void quickJoinGame(MatchExpression *exp, vector<string> whereToSearch, Room *roomToLeave = nullptr);

	/// <summary>
	/// Remove a new Buddy fron the current Buddy List
	/// </summary>
	/// <param name="Name of the parameter">Description</param>
	/// <returns>Description of return value</returns>
	void removeBuddy(string buddyName);

	/// <summary>
	/// Sets one or more BuddyVariables for the current User. This will update all Users in the Zona who have this User as Buddy in their Buddy Lists.
	/// </summary>
	/// <param name="Name of the parameter">Description</param>
	/// <returns>Description of return value</returns>

	void setBuddyVariables(vector<BuddyVariable*> variables);

	/// <summary>
	/// Set custom Room Variables in a Room
	/// </summary>
	/// <param name="roomVariables">a vector of RoomVariables</param>
	/// <param name="targetRoom">the target Room</param>
	/// <returns>Description of return value</returns>
	void setRoomVariables(vector<RoomVariable*> variables, Room *targetRoom = nullptr);

	/// <summary>
	/// Set custom User Variables for the current User
	/// </summary>
	/// <param name="Name of the parameter">Description</param>
	/// <returns>Description of return value</returns>
	void setUserVariables(vector<UserVariable*> variables);

	/// <summary>
	/// Subscribe to the events of a Room Group
	/// </summary>
	/// <param name="Name of the parameter">Description</param>
	/// <returns>Description of return value</returns>

	void subscribeRoomGroup(string groupName);

	/// <summary>
	/// Stop listening to events of a specific Room Group
	/// </summary>
	/// <param name="Name of the parameter">Description</param>
	/// <returns>Description of return value</returns>
	void UnsubscribeRoomGroup(string groupName);

	/// <summary>
	/// Get - set methods
	/// </summary>
	/// <param name="Name of the parameter">Description</param>
	/// <returns>Description of return value</returns>
	Room *getRoom(string roomName);

	static void setDelegate(SFDelegate *del);

};
#endif // __HELLOWORLD_SCENE_H__
