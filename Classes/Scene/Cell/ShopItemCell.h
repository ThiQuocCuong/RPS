//
//  FriendListLayer.h
//  RPS
//
//  Created by Tung Huynh Thanh on 11/6/15.
//
//

#ifndef __RPS__ShopItemCell__
#define __RPS__ShopItemCell__

#include "MyCustomCell.h"

class ShopItemCell : public MyCustomCell {
	cocos2d::ui::Button *m_btnBuy;
	cocos2d::Label *m_lblName;
	cocos2d::Label *m_lblCost;
	cocos2d::Sprite *m_sprUnit;
	cocos2d::Sprite *m_avarta;
public:
    virtual bool init();
	virtual void layout(cocos2d::Size cellSize);
	void setModel(ShopItemModel *model);
	CREATE_FUNC(ShopItemCell);
};

#endif /* defined(__RPS__ShopItemCell__) */
