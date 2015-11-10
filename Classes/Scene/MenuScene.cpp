#include "MenuScene.h"
#include "GameScene.h"
#include "LoginScene.h"

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MenuScene::create();
	auto friendList = FriendListLayer::create();
	auto selectRoom = SelectRoomLayer::create();

    // add layer as a child to scene
	scene->addChild(layer);
	scene->addChild(friendList);
	scene->addChild(selectRoom);

	layer->m_frendListLayer = friendList;
	layer->m_selectRoomLayer = selectRoom;

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	Size ws = Director::getInstance()->getWinSize();
	LayerColor *lc = LayerColor::create(Color4B(47, 121, 197, 255));
	addChild(lc);

	ui::Scale9Sprite *borderTop = ui::Scale9Sprite::createWithSpriteFrameName("ui_border_top_1.png");
	addChild(borderTop);
	borderTop->setContentSize(Size(ws.width, borderTop->getContentSize().height));
	borderTop->setAnchorPoint(Point(0.5, 1));
	borderTop->setPosition(ws.width / 2.0f, ws.height);

	ui::Scale9Sprite *borderBot = ui::Scale9Sprite::createWithSpriteFrameName("ui_border_bot_1.png");
	addChild(borderBot);
	borderBot->setContentSize(Size(ws.width, borderBot->getContentSize().height));
	borderBot->setAnchorPoint(Point(0.5, 0));
	borderBot->setPosition(ws.width / 2.0f, 0);

	float offset = 20;
	Button *btnFriend = GC::gI()->btn()->create("btn_friends.png");
	addChild(btnFriend);

	float offsetBtnX = (ws.width - 4 * btnFriend->getContentSize().width) / 5.0f;

	btnFriend->setPosition(Point(ws.width / 2.0f + btnFriend->getContentSize().width / 2.0f + offsetBtnX/2.0f, btnFriend->getContentSize().height / 2.0f + offset));
	btnFriend->setTag((int)MyButtonEvent::FRIEND);
	btnFriend->addTouchEventListener(CC_CALLBACK_2(MenuScene::callBackBtn, this));

	Button *btnLeaderBoard = GC::gI()->btn()->create("btn_leader_board.png");
	addChild(btnLeaderBoard);
	btnLeaderBoard->setPosition(Point(ws.width / 2.0f - btnLeaderBoard->getContentSize().width / 2.0f - offsetBtnX/2.0f, btnFriend->getPositionY()));
	btnLeaderBoard->setTag((int)MyButtonEvent::LEADER_BOARD);
	btnLeaderBoard->addTouchEventListener(CC_CALLBACK_2(MenuScene::callBackBtn, this));

	Button *btnSetting = GC::gI()->btn()->create("btn_setting.png");
	addChild(btnSetting);
	btnSetting->setPosition(btnFriend->getPosition() + Point(btnFriend->getContentSize().width / 2.0f + offsetBtnX + btnSetting->getContentSize().width / 2.0f, 0));
	btnSetting->setTag((int)MyButtonEvent::SETTING);
	btnSetting->addTouchEventListener(CC_CALLBACK_2(MenuScene::callBackBtn, this));

	Button *btnShop = GC::gI()->btn()->create("btn_shop.png");
	addChild(btnShop);
	btnShop->setPosition(btnLeaderBoard->getPosition() + Point(-btnLeaderBoard->getContentSize().width / 2.0f - btnShop->getContentSize().width / 2.0f - offsetBtnX, 0));
	btnShop->setTag((int)MyButtonEvent::SHOP);
	btnShop->addTouchEventListener(CC_CALLBACK_2(MenuScene::callBackBtn, this));

	Button *btnWithFriend = GC::gI()->btn()->create("btn_green.png");
	addChild(btnWithFriend);
	btnWithFriend->setContentSize(Size(ws.width / 2.0f, 0.75*btnShop->getContentSize().height));
	btnWithFriend->setScale9Enabled(true);
	btnWithFriend->setPosition(Point(ws.width / 2.0f, btnFriend->getPositionY() + btnFriend->getContentSize().height / 2.0f + offset + btnWithFriend->getContentSize().height / 2.0f));
	btnWithFriend->setTitleText("With Friend");
	btnWithFriend->setTitleFontSize(30);
	btnWithFriend->setTag((int)MyButtonEvent::WITH_FRIEND);
	btnWithFriend->addTouchEventListener(CC_CALLBACK_2(MenuScene::callBackBtn, this));

	Button *btnJoinRoom = GC::gI()->btn()->create("btn_green.png");
	addChild(btnJoinRoom);
	btnJoinRoom->setContentSize(btnWithFriend->getContentSize());
	btnJoinRoom->setScale9Enabled(true);
	btnJoinRoom->setPosition(btnWithFriend->getPosition() + Point(0, btnWithFriend->getContentSize().height + offset));
	btnJoinRoom->setTitleText("Join Room");
	btnJoinRoom->setTitleFontSize(30);
	btnJoinRoom->setTag((int)MyButtonEvent::JOIN_ROOM);
	btnJoinRoom->addTouchEventListener(CC_CALLBACK_2(MenuScene::callBackBtn, this));

	Button *btnCreateRoom = GC::gI()->btn()->create("btn_green.png");
	addChild(btnCreateRoom);
	btnCreateRoom->setContentSize(btnJoinRoom->getContentSize());
	btnCreateRoom->setScale9Enabled(true);
	btnCreateRoom->setPosition(btnJoinRoom->getPosition() + Point(0, btnJoinRoom->getContentSize().height + offset));
	btnCreateRoom->setTitleText("Create Room");
	btnCreateRoom->setTitleFontSize(30);
	btnCreateRoom->setTag((int)MyButtonEvent::CREATE_ROOM);
	btnCreateRoom->addTouchEventListener(CC_CALLBACK_2(MenuScene::callBackBtn, this));

	m_avarta = Sprite::createWithSpriteFrameName("avarta_3.png");
	addChild(m_avarta);
	m_avarta->setAnchorPoint(Point(0.5, 0));
	m_avarta->setPosition(btnCreateRoom->getPosition() + Point(0, btnCreateRoom->getContentSize().height/2.0f + offset));

	m_lblUserInfo = Label::createWithTTF("Lvl15. Wonka Thi", FNT_TTF, 40);
	addChild(m_lblUserInfo);
	m_lblUserInfo->setAnchorPoint(Point(0.5, 0));
	m_lblUserInfo->setPosition(m_avarta->getPosition() + Point(0, m_avarta->getContentSize().height + offset));

	Button *btnMoney = GC::gI()->btn()->create("btn_yellow.png");
	addChild(btnMoney);
	btnMoney->setScale9Enabled(true);
	btnMoney->setContentSize(Size(150, 50));
	btnMoney->setPosition(Point(btnSetting->getPositionX() + btnSetting->getContentSize().width / 2.0f - btnMoney->getContentSize().width / 2.0f,
		ws.height - btnMoney->getContentSize().height/2.0f - offset/2.0f));
	btnMoney->setTag((int)MyButtonEvent::MONEY);
	btnMoney->addTouchEventListener(CC_CALLBACK_2(MenuScene::callBackBtn, this));

	Sprite *sprCash = Sprite::createWithSpriteFrameName("icon_cash.png");
	addChild(sprCash);
	sprCash->setPosition(btnMoney->getPosition() + Point(-btnMoney->getContentSize().width / 2.0f + sprCash->getContentSize().width, 0));

	m_lblCash = Label::createWithTTF("00000000", FNT_TTF, 20);
	addChild(m_lblCash);
	m_lblCash->setAnchorPoint(Point(0, 0.5));
	m_lblCash->setPosition(sprCash->getPosition() + Point(sprCash->getContentSize().width/2.0f + 5, 0));

	Button *btnHeart = GC::gI()->btn()->create("btn_yellow.png");
	addChild(btnHeart);
	btnHeart->setScale9Enabled(true);
	btnHeart->setContentSize(Size(150, 50));
	btnHeart->setPosition(btnMoney->getPosition() + Point(-btnMoney->getContentSize().width - offset/2.0f, 0));
	btnHeart->setTag((int)MyButtonEvent::HEART);
	btnHeart->addTouchEventListener(CC_CALLBACK_2(MenuScene::callBackBtn, this));

	Sprite *sprHeart = Sprite::createWithSpriteFrameName("icon_heart.png");
	addChild(sprHeart);
	sprHeart->setPosition(btnHeart->getPosition() + Point(-btnHeart->getContentSize().width / 2.0f + sprHeart->getContentSize().width, 0));

	m_lblHeart = Label::createWithTTF("00000000", FNT_TTF, 20);
	addChild(m_lblHeart);
	m_lblHeart->setAnchorPoint(Point(0, 0.5));
	m_lblHeart->setPosition(sprHeart->getPosition() + Point(sprHeart->getContentSize().width / 2.0f + 5, 0));

	Button *btnMail = GC::gI()->btn()->create("btn_gift.png");
	addChild(btnMail);
	btnMail->setPosition(Point(offset + btnMail->getContentSize().width, ws.height - btnMail->getContentSize().height/2.0f - btnHeart->getContentSize().height/2.0f));
	btnMail->setTag((int)MyButtonEvent::MAIL);
	btnMail->addTouchEventListener(CC_CALLBACK_2(MenuScene::callBackBtn, this));

    GC::gI()->fb()->setDelegate(this);
	return true;
}

void MenuScene::callBackBtn(Ref *sender, Widget::TouchEventType type) {
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED: {
		Button *btn = (Button*)sender;
		MyButtonEvent tag = (MyButtonEvent)btn->getTag();
		switch (tag)
		{
		case MyButtonEvent::SHOP:
			break;
            case MyButtonEvent::FRIEND: {
                m_frendListLayer->show();
			break;
            }
		case MyButtonEvent::SETTING:
			break;
		case MyButtonEvent::LEADER_BOARD:
			break;
        case MyButtonEvent::WITH_FRIEND:{
                
			break;
            }
		case MyButtonEvent::CREATE_ROOM:
			break;
		case MyButtonEvent::JOIN_ROOM: {
			m_selectRoomLayer->show();
			break;
		}
		case MyButtonEvent::MAIL:
			break;
		case MyButtonEvent::MONEY:
			break;
		case MyButtonEvent::HEART:
			break;
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

//facebook delegate
void MenuScene::onAPI(const std::string& tag, const std::string& jsonData) {
    if(tag.compare(TAG_API_INVITE_FRIEND) == 0) {
        m_frendListLayer->onReceivedInvitableFriends(jsonData);
    }
}