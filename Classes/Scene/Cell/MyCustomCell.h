//
//  FriendListLayer.h
//  RPS
//
//  Created by Tung Huynh Thanh on 11/6/15.
//
//

#ifndef __RPS__MyCustomCell__
#define __RPS__MyCustomCell__

#include "../../GC/GC.h"
#include "../GameDelegate.h"
#include "GameModel.h"

class MyCustomCell : public cocos2d::extension::TableViewCell {
protected:
	GameDelegate *m_delegate;
	cocos2d::Size m_cellSize;
	ui::Scale9Sprite *m_bg;
public:
	void setDelegate(GameDelegate *del);
    virtual bool init();
	virtual void layout(Size size) {};
	CREATE_FUNC(MyCustomCell);
};

#endif /* defined(__RPS__FriendListLayer__) */
