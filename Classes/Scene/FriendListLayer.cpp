//
//  FriendListLayer.cpp
//  RPS
//
//  Created by Tung Huynh Thanh on 11/6/15.
//
//

#include "FriendListLayer.h"
using namespace cocos2d;
using namespace extension;

bool FriendListLayer::init() {
    if(!Node::init()) {
        return false;
    }
 /*   std::map<std::string, std::string> params;
    params.insert(std::pair<std::string, std::string>("limit", "50"));
    GC::gI()->fb()->requestInvitableFriends(params);*/
	Size ws = Director::getInstance()->getWinSize();
	LayerColor *lc = LayerColor::create(Color4B(0, 0, 0, 100));
	addChild(lc);

	Scale9Sprite *bg = Scale9Sprite::createWithSpriteFrameName("ui_panel.png");
	addChild(bg);
	bg->setContentSize(Size(0.8*ws));
	bg->setAnchorPoint(Point::ZERO);
	bg->setPosition(0.1*ws);

	FriendCell *cell = FriendCell::create(ws);
	m_cellSize = cell->getCellSize();
	m_cellSize.width = 0.9*bg->getContentSize().width;

	for (int i = 0; i < 10; i++) {
		m_friendModels.pushBack(new UserModel());
		m_friendModels.back()->release();
	}

	TableView *tbw = TableView::create(this, Size(0.9*bg->getContentSize()));
	addChild(tbw);
	tbw->setDelegate(this);
	tbw->setAnchorPoint(Point::ZERO);
	tbw->setPosition(bg->getPosition() + Point(0.05*bg->getContentSize()));
	tbw->setBounceable(true);
	tbw->reloadData();

    return true;
}

void FriendListLayer::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell) {

}
TableViewCell* FriendListLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx) {
	FriendCell *cell = (FriendCell *)table->dequeueCell();
	if (!cell) {
		cell = FriendCell::create(m_cellSize);
	}
	return cell;
}
ssize_t FriendListLayer::numberOfCellsInTableView(cocos2d::extension::TableView *table) {
	return m_friendModels.size();
}
Size FriendListLayer::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx) {
	return m_cellSize;
}
