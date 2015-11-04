#include "LoginScene.h"
#include "GameScene.h"

#define TAG_BTN_LOGIN 1
#define TAG_BTN_LOGIN_2 2
#define TAG_BTN_REGISTER 3

Scene* LoginScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = LoginScene::create();
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoginScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	Size ws = Director::getInstance()->getWinSize();
	LayerColor *lc = LayerColor::create(Color4B::ORANGE);
	addChild(lc);

	m_btnLogin = GC::gI()->btn()->create("btn_blue.png");
	addChild(m_btnLogin);
	m_btnLogin->setContentSize(Size(300, 80));
	m_btnLogin->setScale9Enabled(true);
	m_btnLogin->setPosition(ws / 2.0f);
	m_btnLogin->setTitleText("Login");
	m_btnLogin->setTitleFontSize(40);
	m_btnLogin->setTag(TAG_BTN_LOGIN);
	m_btnLogin->addTouchEventListener(CC_CALLBACK_2(LoginScene::callBackBtn, this));

	m_loginNode = Node::create();
	addChild(m_loginNode);
	m_loginNode->setVisible(false);

	float offset = 20;

	Label *lblUserName = Label::createWithTTF("User name: ", FNT_TTF, 30);
	m_loginNode->addChild(lblUserName);
	lblUserName->setAnchorPoint(Point(0, 0.5));

	Label *lblPassword = Label::createWithTTF("Password: ", FNT_TTF, 30);
	m_loginNode->addChild(lblPassword);
	lblPassword->setAnchorPoint(Point(0, 0.5));

	lblPassword->setPosition(Point(ws.width / 2.0f - lblPassword->getContentSize().width - offset, ws.height / 2.0f + offset + lblPassword->getContentSize().height / 2.0f));
	lblUserName->setPosition(lblPassword->getPosition() + Point(0, lblUserName->getContentSize().height + offset));

	EditBox *boxUserName = EditBox::create(Size(ws.width / 3.0f, 50), "ui_panel_2.png", Widget::TextureResType::PLIST);
	m_loginNode->addChild(boxUserName);
	boxUserName->setAnchorPoint(Point(0, 0.5));
	boxUserName->setPosition(Point(ws.width / 2.0f, lblUserName->getPositionY()));

	EditBox *boxPassword = EditBox::create(Size(ws.width / 3.0f, 50), "ui_panel_2.png", Widget::TextureResType::PLIST);
	m_loginNode->addChild(boxPassword);
	boxPassword->setAnchorPoint(Point(0, 0.5));
	boxPassword->setPosition(Point(ws.width / 2.0f, lblPassword->getPositionY()));

	Button *btnLogin = GC::gI()->btn()->create("btn_yellow.png");
	m_loginNode->addChild(btnLogin);
	btnLogin->setPosition(Point(ws.width / 2.0f - offset, ws.height / 2.0f - btnLogin->getContentSize().height / 2.0f - offset));
	btnLogin->setScale9Enabled(true);
	btnLogin->setContentSize(Size(ws.width / 4.0f, 50));
	btnLogin->setAnchorPoint(Point(1, 0.5));
	btnLogin->setTag(TAG_BTN_LOGIN_2);
	btnLogin->addTouchEventListener(CC_CALLBACK_2(LoginScene::callBackBtn, this));

	Button *btnRegister = GC::gI()->btn()->create("btn_yellow.png");
	m_loginNode->addChild(btnRegister);
	btnRegister->setPosition(Point(ws.width / 2.0f + offset, btnLogin->getPositionY()));
	btnRegister->setScale9Enabled(true);
	btnRegister->setContentSize(Size(ws.width / 4.0f, 50));
	btnRegister->setAnchorPoint(Point(0, 0.5));
	btnRegister->setTag(TAG_BTN_REGISTER);
	btnRegister->addTouchEventListener(CC_CALLBACK_2(LoginScene::callBackBtn, this));

    return true;
}

void LoginScene::callBackBtn(Ref *sender, Widget::TouchEventType type) {
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
		case TAG_BTN_LOGIN: {
			m_loginNode->setVisible(true);
			m_btnLogin->setVisible(false);
			break;
		}
		case TAG_BTN_LOGIN_2:{
			Director::getInstance()->replaceScene(GameScene::createScene());
			break;
		}
		case TAG_BTN_REGISTER:{
			GC::gI()->fb()->login();
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