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
    return true;
}

void GameLayer::show() {
	setVisible(true);
}
void GameLayer::hide() {
	setVisible(false);
}