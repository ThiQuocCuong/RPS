#include "WaitingRoomLayer.h"
#include "../GameScene.h"

// on "init" you need to initialize your instance
bool WaitingRoomLayer::init()
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

	ui::Scale9Sprite *panel1 = ui::Scale9Sprite::createWithSpriteFrameName("ui_panel.png");
	addChild(panel1);
	panel1->setContentSize(Size(0.425*ws.width, 0.5*ws.height));
	panel1->setPosition(0.275*ws.width, 0.4*ws.height);

	ui::Scale9Sprite *panel2 = ui::Scale9Sprite::createWithSpriteFrameName("ui_panel.png");
	addChild(panel2);
	panel2->setContentSize(panel1->getContentSize());
	panel2->setPosition(0.725*ws.width, 0.4*ws.height);

	m_sprUser1Avarta = Sprite::createWithSpriteFrameName("avarta_1.png");
	addChild(m_sprUser1Avarta);
	m_sprUser1Avarta->setPosition(panel1->getPosition());

	m_sprUser2Avarta = Sprite::createWithSpriteFrameName("avarta_2.png");
	addChild(m_sprUser2Avarta);
	m_sprUser2Avarta->setPosition(panel2->getPosition());
	m_sprUser2Avarta->setVisible(false);
	
	m_lblUser1Infor = Label::createWithTTF("Lvl.1 Wonka Thi", "fonts/arial.ttf", 25);
	addChild(m_lblUser1Infor);
	m_lblUser1Infor->setAnchorPoint(Point(0.5, 0));
	m_lblUser1Infor->setPosition(panel1->getPosition() + Point(0, panel1->getContentSize().height / 2.0f + offset));

	m_lblUser2Infor = Label::createWithTTF("Lvl.1 Luffy", "fonts/arial.ttf", 25);
	addChild(m_lblUser2Infor);
	m_lblUser2Infor->setAnchorPoint(Point(0.5, 0));
	m_lblUser2Infor->setPosition(panel2->getPosition() + Point(0, panel2->getContentSize().height / 2.0f + offset));
	m_lblUser2Infor->setVisible(false);

	m_lblRoomName = Label::createWithTTF("Room Name", "fonts/arial.ttf", 40);
	addChild(m_lblRoomName);
	m_lblRoomName->setPosition(ws.width / 2.0f, m_lblUser1Infor->getPositionY() + (m_btnBack->getPositionY() - m_lblUser1Infor->getPositionY()) / 2.0f);

	m_lblStatus = Label::createWithTTF("Waiting", "fonts/arial.ttf", 30);
	addChild(m_lblStatus);
	m_lblStatus->setPosition(panel2->getPosition());

	m_btnBack->addTouchEventListener(CC_CALLBACK_2(WaitingRoomLayer::callBackBtn, this));

	hide();
    return true;
}

void WaitingRoomLayer::show() {
	GameLayer::show();
	stopAllActions();

	runAction(Sequence::create(DelayTime::create(3),
		CallFunc::create(CC_CALLBACK_0(WaitingRoomLayer::joinGame, this)),
		DelayTime::create(2),
		CallFunc::create([] {
		Director::getInstance()->replaceScene(GameScene::createScene());
	}),
		nullptr));
}
 
void WaitingRoomLayer::callBackBtn(Ref *sender, Widget::TouchEventType type) {
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
			break;
		}
		case MyButtonEvent::BACK: {
			stopAllActions();
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

void WaitingRoomLayer::joinGame() {
	m_sprUser2Avarta->setVisible(true);
	m_lblUser2Infor->setVisible(true);
	m_lblStatus->setVisible(false);
}
