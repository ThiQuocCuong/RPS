#include "SelectRoomLayer.h"

// on "init" you need to initialize your instance
bool SelectRoomLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !GameLayer::init() )
    {
        return false;
    }
	Size ws = Director::getInstance()->getWinSize();

	float offset = 20;
	enableBackButton(true);

	Button *btnCreateRoom = GC::gI()->btn()->create("btn_green.png");
	addChild(btnCreateRoom);
	btnCreateRoom->setContentSize(Size(ws.width / 2.0f, 0.75*m_btnBack->getContentSize().height));
	btnCreateRoom->setScale9Enabled(true);
	btnCreateRoom->setPosition(Point(ws.width/2.0f, btnCreateRoom->getContentSize().height));
	btnCreateRoom->setTitleText("Create Room");
	btnCreateRoom->setTitleFontSize(30);
	btnCreateRoom->setTag((int)MyButtonEvent::CREATE_ROOM);
	btnCreateRoom->addTouchEventListener(CC_CALLBACK_2(SelectRoomLayer::callBackBtn, this));

	Button *btnJoinRoom = GC::gI()->btn()->create("btn_green.png");
	addChild(btnJoinRoom);
	btnJoinRoom->setContentSize(btnCreateRoom->getContentSize());
	btnJoinRoom->setScale9Enabled(true);
	btnJoinRoom->setPosition(btnCreateRoom->getPosition() + Point(0, btnCreateRoom->getContentSize().height + offset));
	btnJoinRoom->setTitleText("Join Room");
	btnJoinRoom->setTitleFontSize(30);
	btnJoinRoom->setTag((int)MyButtonEvent::JOIN_ROOM);
	btnJoinRoom->addTouchEventListener(CC_CALLBACK_2(SelectRoomLayer::callBackBtn, this));

	Size tableSize = Size(0.9*ws.width, (m_btnBack->getPositionY() - btnJoinRoom->getPositionY() - 2 * m_btnBack->getContentSize().height));
	m_cellSize = Size(tableSize.width / 2.0f, tableSize.height);

	for (int i = 0; i < 10; i++) {
		m_models.pushBack(new RoomModel());
		m_models.back()->release();
	}

	TableView *tbw = TableView::create(this, tableSize);
	addChild(tbw);
	tbw->setDelegate(this);
	tbw->setAnchorPoint(Point::ZERO);
	tbw->setPosition(Point(0.05*ws.width, btnJoinRoom->getPositionY() + 1.5*btnJoinRoom->getContentSize().height));
	tbw->setDirection(extension::ScrollView::Direction::HORIZONTAL);
	tbw->setBounceable(true);
	tbw->reloadData();

	m_currentSelectedId = 0;

	setVisible(false);
    return true;
}
 
void SelectRoomLayer::callBackBtn(Ref *sender, Widget::TouchEventType type) {
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED: {
		Button *btn = (Button *)sender;
		MyButtonEvent tag = (MyButtonEvent)btn->getTag();
		switch (tag)
		{
		case MyButtonEvent::JOIN_ROOM: {
			RoomModel *model = m_models.at(m_currentSelectedId);
			if (m_delegate) {
				m_delegate->onEnterRoom(model);
			}
			break;
		}
		case MyButtonEvent::BACK: {
			hide();
			break;
		}
		case MyButtonEvent::CREATE_ROOM: {
			break;
		}
		default:
			break;
		}
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void SelectRoomLayer::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell) {
	m_currentSelectedId = cell->getIdx();
	for (int i = 0; i < m_models.size(); i++) {
		MyCustomCell * c = (MyCustomCell*)table->cellAtIndex(i);
		if (c) {
			if (i != m_currentSelectedId) {
				c->highlight(false);
			}
			else {
				c->highlight(true);
			}
		}
	}
}
cocos2d::extension::TableViewCell* SelectRoomLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx) {
	RoomCell *cell = (RoomCell *)table->dequeueCell();
	if (!cell) {
		cell = RoomCell::create();
		cell->layout(m_cellSize);
	}
	cell->highlight(false);
	return cell;
}
ssize_t SelectRoomLayer::numberOfCellsInTableView(cocos2d::extension::TableView *table) {
	return m_models.size();
}
cocos2d::Size SelectRoomLayer::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx) {
	return m_cellSize;
}
