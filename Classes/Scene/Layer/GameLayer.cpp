#include "GameLayer.h"

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }
	m_delegate = nullptr;
	LayerColor *lc = LayerColor::create(Color4B(0, 0, 0, 200));
	addChild(lc);

	Button *btnLockTouch = Button::create();
	addChild(btnLockTouch);
	btnLockTouch->setScale9Enabled(true);
	btnLockTouch->setAnchorPoint(Point::ZERO);
	btnLockTouch->setContentSize(Director::getInstance()->getWinSize());
	btnLockTouch->setTouchEnabled(true);
	btnLockTouch->setEnabled(true);

	Size ws = Director::getInstance()->getWinSize();
	m_btnBack = GC::gI()->btn()->create("btn_back.png");
	addChild(m_btnBack);
	m_btnBack->setPosition(Point(m_btnBack->getContentSize().width, ws.height - 0.75*m_btnBack->getContentSize().height));
	m_btnBack->setTag((int)MyButtonEvent::BACK);
	m_btnBack->setVisible(false);
	m_btnBack->addTouchEventListener([=](Ref *sender, Widget::TouchEventType type) {
		this->hide();
	});
    return true;
}

void GameLayer::enableBackButton(bool value) {
	m_btnBack->setVisible(value);
}

void GameLayer::show() {
	setVisible(true);
}
void GameLayer::hide() {
	setVisible(false);
}