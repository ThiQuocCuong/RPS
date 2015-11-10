//
//  LeaderBoardLayer.cpp
//  RPS
//
//  Created by Tung Huynh Thanh on 11/6/15.
//
//

#include "LeaderBoardLayer.h"

bool LeaderBoardLayer::init() {
    if(!GameLayer::init()) {
        return false;
    }
    Size ws = Director::getInstance()->getWinSize();

	enableBackButton(true);
    ui::Scale9Sprite *bg = ui::Scale9Sprite::createWithSpriteFrameName("ui_panel.png");
    addChild(bg);
    bg->setContentSize(Size(0.8*ws));
    bg->setAnchorPoint(Point::ZERO);
    bg->setPosition(0.1*ws);
    
    FriendCell *cell = FriendCell::create(ws);
    m_cellSize = cell->getCellSize();
    m_cellSize.width = 0.9*bg->getContentSize().width;
    
	for (int i = 0; i < 6; i++) {
		m_friendModels.pushBack(new UserModel("1", "Wonka Thi", 2));
		m_friendModels.back()->release();
	}
    
    m_tbw = TableView::create(this, Size(0.9*bg->getContentSize()));
    addChild(m_tbw);
    m_tbw->setDelegate(this);
    m_tbw->setAnchorPoint(Point::ZERO);
    m_tbw->setPosition(bg->getPosition() + Point(0.05*bg->getContentSize()));
    m_tbw->setBounceable(true);
    
    setVisible(false);
    return true;
}

void LeaderBoardLayer::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell) {
    
}
TableViewCell* LeaderBoardLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx) {
    FriendCell *cell = (FriendCell *)table->dequeueCell();
    if (!cell) {
        cell = FriendCell::create(m_cellSize);
    }
	UserModel *model = m_friendModels.at(idx);
    cell->setModel(model);
    return cell;
}
ssize_t LeaderBoardLayer::numberOfCellsInTableView(cocos2d::extension::TableView *table) {
    return m_friendModels.size();
}
Size LeaderBoardLayer::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx) {
    return m_cellSize;
}
