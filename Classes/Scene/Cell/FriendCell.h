//
//  FriendListLayer.h
//  RPS
//
//  Created by Tung Huynh Thanh on 11/6/15.
//
//

#ifndef __RPS__FriendCell__
#define __RPS__FriendCell__

#include "MyCustomCell.h"

class FriendCell : public MyCustomCell {
	Label *m_lblInfo;
	Sprite *m_sprAvatar;
public:
	static FriendCell *create(cocos2d::Size cellSize = cocos2d::Size::ZERO);
	virtual bool init(cocos2d::Size cellSize = cocos2d::Size::ZERO);
	virtual cocos2d::Size getCellSize() { return m_cellSize; }
	void setModel(UserModel *model);
	CREATE_FUNC(FriendCell);
};

#endif /* defined(__RPS__FriendListLayer__) */
