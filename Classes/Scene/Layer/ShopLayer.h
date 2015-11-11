#ifndef __SHOP_LAYER_H__
#define __SHOP_LAYER_H__

#include "GameLayer.h"
#include "../Cell/ShopItemCell.h"

class ShopLayer : public GameLayer, cocos2d::extension::TableViewDataSource, cocos2d::extension::TableViewDelegate {
	cocos2d::ui::Button *m_tabItem1;
	cocos2d::ui::Button *m_tabItem2;
	ShopItemType m_currentCatagory;
	cocos2d::Vector<ShopItemModel *> m_listItem1;
	cocos2d::Vector<ShopItemModel* > m_listItem2;
	cocos2d::Sprite *m_sprAvarta;
	cocos2d::Label *m_lblInfor;
	cocos2d::extension::TableView *m_tbw;

	cocos2d::Size m_cellSize;
	//TableView
	void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
	cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);


	void callBackTab(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
public:
	virtual bool init();
	CREATE_FUNC(ShopLayer);
};

#endif // __SHOP_LAYER_H__
