#ifndef _GAME_PREFIX_H__
#define _GAME_PREFIX_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#define FNT_TTF "fonts/arial.ttf"

#define API_INVITABLE_FRIENDS "/me/invitable_friends"

#define TAG_API_INVITE_FRIEND "tag_api_invitable"

#define MAX_HEIGHT_AVARTA 55

#define SFX2X_DEFAULT_HOST "127.0.0.1"
#define SFX2X_DEFAULT_PORT 9933
//#define DEFAULT_HOST "210.211.122.251"
//#define DEFAULT_PORT 9955
#define SFX2X_DEFAULT_USERNAME ""
#define SFX2X_DEFAULT_PASS ""
#define SFX2X_DEFAULT_ROOM "ChatRoom"
#define SFX2X_DEFAULT_ZONE "ChatZone"

enum class MyButtonEvent {
	SHOP = 0,
	FRIEND,
	SETTING,
	LEADER_BOARD,
	WITH_FRIEND,
	CREATE_ROOM,
	JOIN_ROOM,
	MAIL,
	MONEY,
	HEART,
	PAUSE,
	BACK,
	NEXT,
	RETURN_TO_MENU,
	GAME_PAPER,
	GAME_ROCK,
	GAME_SCISSORS
};

enum class BattleResult {
	WIN = 0,
	LOSE,
	EQUAL
};

enum class RoomStatus {
	PLAYING = 0,
	WAITING
};


#endif