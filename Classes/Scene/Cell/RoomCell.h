//
//  FriendListLayer.h
//  RPS
//
//  Created by Tung Huynh Thanh on 11/6/15.
//
//

#ifndef __RPS__RoomCell__
#define __RPS__RoomCell__

#include "MyCustomCell.h"

class RoomCell : public MyCustomCell {
	Label *m_lblName;
	Label *m_lblStatus;
	Sprite *m_avarta;
	Sprite *m_sprIcon;
public:
    virtual bool init();
	virtual void layout(Size cellSize);
	void setModel(RoomModel *model);
	CREATE_FUNC(RoomCell);
};

#endif /* defined(__RPS__RoomCell__) */
