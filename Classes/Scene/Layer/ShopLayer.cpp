#include "ShopLayer.h"
using namespace cocos2d;
using namespace std;

#define TAG_TAB_1 1
#define TAG_TAB_2 2

bool ShopLayer::init() {
	if (!GameLayer::init()) {
		return false;
	}
	Size ws = Director::getInstance()->getWinSize();
	float offset = 20;
	enableBackButton(true);

	m_lblInfor = Label::createWithTTF("Lvl1. Wonka Thi", "fonts/arial.ttf", 40);
	addChild(m_lblInfor);
	m_lblInfor->setAnchorPoint(Point(0.5, 1));
	m_lblInfor->setPosition(ws.width / 2.0f, m_btnBack->getPositionY() - m_btnBack->getContentSize().height);

	m_sprAvarta = Sprite::createWithSpriteFrameName("avarta_3.png");
	addChild(m_sprAvarta);
	m_sprAvarta->setAnchorPoint(Point(0.5, 1));
	m_sprAvarta->setPosition(Point(ws.width / 2.0f, m_lblInfor->getPositionY() - m_lblInfor->getContentSize().height - offset));

	for (int i = 0; i < 10; i++) {
		m_listItem1.pushBack(new ShopItemModel(ShopItemType::HAT, "1", StringUtils::format("Hat %d", i), 200 + i));
		m_listItem1.back()->release();
	}

	for (int i = 0; i < 8; i++) {
		m_listItem2.pushBack(new ShopItemModel(ShopItemType::PAN, "1", StringUtils::format("Pan %d", i), 300 + i));
		m_listItem2.back()->release();
	}

	m_tabItem1 = GC::gI()->btn()->create("ui_tab_red.png");
	Size tableSize = Size(0.9*ws.width, 0.9*(m_sprAvarta->getPositionY() - m_sprAvarta->getContentSize().height - m_tabItem1->getContentSize().height));
	m_cellSize = Size(0.3*tableSize.width, tableSize.height);
	m_currentCatagory = ShopItemType::HAT;

	ui::Scale9Sprite *tbwBg = ui::Scale9Sprite::createWithSpriteFrameName("ui_panel.png");
	addChild(tbwBg);
	tbwBg->setPosition(Point(0.05*ws.width, 0.05*ws.width));
	tbwBg->setAnchorPoint(Point::ZERO);
	tbwBg->setContentSize(tableSize + Size(0, m_tabItem1->getContentSize().height));
	tableSize = 0.9*tbwBg->getContentSize();

	m_tbw = TableView::create(this, tableSize);
	addChild(m_tbw);
	m_tbw->setDelegate(this);
	m_tbw->setAnchorPoint(Point::ZERO);
	m_tbw->setPosition(tbwBg->getPosition() + Point(0.05*tbwBg->getContentSize()));
	m_tbw->setDirection(extension::ScrollView::Direction::HORIZONTAL);
	m_tbw->setBounceable(true);
	m_tbw->reloadData();

	addChild(m_tabItem1);
	m_tabItem1->setAnchorPoint(Point(0.5, 1));
	m_tabItem1->setPosition(Point(tbwBg->getPosition() + Point(m_tabItem1->getContentSize().width / 2.0f + 5, tbwBg->getContentSize().height + 5)));
	m_tabItem1->setTag(TAG_TAB_1);
	m_tabItem1->addTouchEventListener(CC_CALLBACK_2(ShopLayer::callBackTab, this));

	m_tabItem2 = GC::gI()->btn()->create("ui_tab_grey.png");
	addChild(m_tabItem2);
	m_tabItem2->setAnchorPoint(Point(0.5, 1));
	m_tabItem2->setPosition(m_tabItem1->getPosition() + Point(m_tabItem1->getContentSize().width, 0));
	m_tabItem2->setTag(TAG_TAB_2);
	m_tabItem2->addTouchEventListener(CC_CALLBACK_2(ShopLayer::callBackTab, this));

	hide();

	return true;
}


void ShopLayer::callBackTab(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED: {
		Button *btn = (Button *)sender;
		switch (btn->getTag())
		{
		case TAG_TAB_1:{
			m_currentCatagory = ShopItemType::HAT;
			m_tabItem2->loadTextureNormal("ui_tab_grey.png", Widget::TextureResType::PLIST);
			m_tabItem1->loadTextureNormal("ui_tab_red.png", Widget::TextureResType::PLIST);
			break;
		}
		default:
			m_currentCatagory = ShopItemType::PAN;
			m_tabItem1->loadTextureNormal("ui_tab_grey.png", Widget::TextureResType::PLIST);
			m_tabItem2->loadTextureNormal("ui_tab_red.png", Widget::TextureResType::PLIST);
			break; 
		}
		m_tbw->reloadData();
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void ShopLayer::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell) {

}

cocos2d::extension::TableViewCell* ShopLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx) {
	ShopItemCell *cell = (ShopItemCell *)table->dequeueCell();
	if (!cell) {
		cell = ShopItemCell::create();
	}
	switch (m_currentCatagory)
	{
	case ShopItemType::HAT: {
		cell->setModel(m_listItem1.at(idx));
		break;
	}
	case ShopItemType::PAN: {
		cell->setModel(m_listItem2.at(idx));
		break;
	}
	default: {
		break;
	}
	}
	cell->layout(m_cellSize);
	return cell;
}

ssize_t ShopLayer::numberOfCellsInTableView(cocos2d::extension::TableView *table) {
	switch (m_currentCatagory)
	{
	case ShopItemType::HAT: {
		return m_listItem1.size();
	}
	case ShopItemType::PAN: {
		return m_listItem2.size();
	}
	default: {
		return m_listItem1.size();
	}
	}
}

cocos2d::Size ShopLayer::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx) {
	return m_cellSize;
}