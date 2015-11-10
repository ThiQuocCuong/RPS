#ifndef __GAME_DELEGATE_H__
#define __GAME_DELEGATE_H__
#include "Cell/GameModel.h"
class GameDelegate {
public:
	virtual void onReplay() = 0;
    virtual void onReturnToMenu() = 0;
	virtual void onEnterRoom(RoomModel *model) = 0;
};
#endif