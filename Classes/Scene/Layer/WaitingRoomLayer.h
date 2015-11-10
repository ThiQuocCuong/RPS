#ifndef __WAITING_ROOM_LAYER_H__
#define __WAITING_ROOM_LAYER_H__

#include "GameLayer.h"
#include "../Cell/RoomCell.h"

class WaitingRoomLayer: public GameLayer {
	Label *m_lblRoomName;
	Label *m_lblUser1Infor;
	Label *m_lblUser2Infor;
	Sprite *m_sprUser1Avarta;
	Sprite *m_sprUser2Avarta;
	Label *m_lblStatus;
	void callBackBtn(Ref *sender, Widget::TouchEventType type);

	void joinGame();
public:
	virtual bool init();
	virtual void show();
	CREATE_FUNC(WaitingRoomLayer);
};

#endif // __SELECT_ROOM_LAYER_H__
