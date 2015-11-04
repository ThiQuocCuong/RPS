#include "ResultLayer.h"

// on "init" you need to initialize your instance
bool ResultLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	m_delegate = nullptr;
	Size ws = Director::getInstance()->getWinSize();
	LayerColor *lc = LayerColor::create(Color4B(0, 0, 0, 180));
	addChild(lc);

	Scale9Sprite *panel = Scale9Sprite::createWithSpriteFrameName("ui_panel.png");
	addChild(panel);
	panel->setPosition(ws / 2.0f);

	Sprite*panelBG = Sprite::createWithSpriteFrameName("ui_panel_background.png");
	addChild(panelBG);
	panelBG->setPosition(Point(ws/2.0f));
	panel->setContentSize(Size(1.1*panelBG->getContentSize().width, 1.2*panelBG->getContentSize().height));

	Button *btnMenu = Button::create("btn_menu.png", "", "", Widget::TextureResType::PLIST);
	addChild(btnMenu);
	btnMenu->setPosition(panel->getPosition() + Point(-panel->getContentSize().width / 4.0f, 0));
	btnMenu->addTouchEventListener([&](Ref *sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED && m_delegate) {
			m_delegate->onReplay();
		}
	});

	Button *btnReplay = Button::create("btn_replay.png", "", "", Widget::TextureResType::PLIST);
	addChild(btnReplay);
	btnReplay->setPosition(panel->getPosition() + Point(panel->getContentSize().width / 4.0f, 0));
	btnReplay->addTouchEventListener([&](Ref *sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED && m_delegate) {
			m_delegate->onReplay();
		}
	});

	m_lblNotify = Label::createWithTTF("Win","fonts/arial.ttf", 40);
	addChild(m_lblNotify);
	m_lblNotify->setPosition(panel->getPosition() + Point(0, panel->getContentSize().height / 2.0f - m_lblNotify->getContentSize().height));

	setVisible(false);
    return true;
}

void ResultLayer::show(BattleResult result) {
	runAction(Sequence::create(DelayTime::create(1), Show::create(), nullptr));
	switch (result)
	{
	case BattleResult::WIN: {
		m_lblNotify->setString("Win");
		break;
	}
	case BattleResult::LOSE: {
		m_lblNotify->setString("Lose");
		break;
	}
	case BattleResult::EQUAL: {
		m_lblNotify->setString("Equal");
		break;
	}
	default:
		break;
	}
}