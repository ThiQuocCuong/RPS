//
//  FriendListLayer.h
//  RPS
//
//  Created by Tung Huynh Thanh on 11/6/15.
//
//

#ifndef __RPS__FriendListLayer__
#define __RPS__FriendListLayer__

#include "GameLayer.h"
#include "../Cell/FriendCell.h"
class FriendListLayer : public GameLayer, cocos2d::extension::TableViewDataSource, cocos2d::extension::TableViewDelegate {

	Vector<UserModel *> m_friendModels;
	Size m_cellSize;

	//TableView
	void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
	cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
	ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
	cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
public:
    virtual bool init();
    CREATE_FUNC(FriendListLayer);
};

#endif /* defined(__RPS__FriendListLayer__) */
