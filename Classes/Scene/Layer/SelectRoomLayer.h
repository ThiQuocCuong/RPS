#ifndef __SELECT_ROOM_LAYER_H__
#define __SELECT_ROOM_LAYER_H__

#include "GameLayer.h"
#include "../Cell/RoomCell.h"

class SelectRoomLayer : public GameLayer, cocos2d::extension::TableViewDataSource, cocos2d::extension::TableViewDelegate
{

	int m_currentSelectedId;
	Vector<RoomModel *> m_models;
	Size m_cellSize;
	//TableView
	void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
	cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);

	void callBackBtn(Ref *sender, Widget::TouchEventType type);
public:
	virtual bool init();
	CREATE_FUNC(SelectRoomLayer);
};

#endif // __SELECT_ROOM_LAYER_H__
