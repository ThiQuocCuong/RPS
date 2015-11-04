#include "GameScene.h"

#define TAG_BTN_ROCK 1
#define TAG_BTN_PAPER 2
#define TAG_BTN_SCISSORS 3
#define TAG_BTN_PAUSE 4
#define TAG_BTN_MENU 5
#define MAX_COUNT_DOWN 5

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = GameScene::create();
	auto result = ResultLayer::create();
	result->setDelegate(layer);
    // add layer as a child to scene
    scene->addChild(layer);
	scene->addChild(result);
	layer->m_resultLayer = result;

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	Size ws = Director::getInstance()->getWinSize();

	LayerColor *lc = LayerColor::create(Color4B(47, 121, 197, 255));
	addChild(lc);

	float offset = 20;

	Scale9Sprite *borderTop = Scale9Sprite::createWithSpriteFrameName("ui_border_top_1.png");
	addChild(borderTop);
	borderTop->setContentSize(Size(ws.width, borderTop->getContentSize().height));
	borderTop->setAnchorPoint(Point(0.5, 1));
	borderTop->setPosition(ws.width / 2.0f, ws.height);

	Scale9Sprite *borderBot = Scale9Sprite::createWithSpriteFrameName("ui_border_bot_2.png");
	addChild(borderBot);
	borderBot->setContentSize(Size(ws.width, borderBot->getContentSize().height));
	borderBot->setAnchorPoint(Point(0.5, 0));
	borderBot->setPosition(ws.width / 2.0f, 0);

	Sprite *borderMid = Sprite::createWithSpriteFrameName("ui_border_mid.png");
	addChild(borderMid);
	borderMid->setAnchorPoint(Point(0.5, 1));
	borderMid->setPosition(borderTop->getPosition());

	m_lblCountDown = Label::createWithTTF(StringUtils::format("%d", MAX_COUNT_DOWN), "fonts/arial.ttf", 50);
	addChild(m_lblCountDown);
	m_lblCountDown->setPosition(borderMid->getPosition() + Point(0, -borderMid->getContentSize().height / 2.0f));

	Scale9Sprite *panel1 = Scale9Sprite::createWithSpriteFrameName("ui_panel.png");
	addChild(panel1);
	panel1->setContentSize(Size(0.4*ws.width, 0.7*(ws.height - borderTop->getContentSize().height - borderBot->getContentSize().height)));
	panel1->setPosition(0.25*ws.width, 0.5*ws.height);

	Scale9Sprite *panel2 = Scale9Sprite::createWithSpriteFrameName("ui_panel.png");
	addChild(panel2);
	panel2->setContentSize(panel1->getContentSize());
	panel2->setPosition(0.75*ws.width, 0.5*ws.height);

	Sprite *avarta1 = Sprite::createWithSpriteFrameName("avarta_1.png");
	addChild(avarta1);
	avarta1->setScale(0.5);
	avarta1->setPosition(panel1->getPosition() + Point(panel1->getContentSize().width / 2.0f - avarta1->getContentSize().width / 4.0f, -panel1->getContentSize().height / 2.0f));

	Sprite *avarta2 = Sprite::createWithSpriteFrameName("avarta_2.png");
	addChild(avarta2);
	avarta2->setScale(0.5);
	avarta2->setPosition(panel2->getPosition() + Point(panel2->getContentSize().width/2.0f - avarta2->getContentSize().width/4.0f, -panel2->getContentSize().height / 2.0f));

	m_sprUser1 = Sprite::createWithSpriteFrameName("paper.png");
	addChild(m_sprUser1);
	m_sprUser1->setPosition(panel1->getPosition());
	m_sprUser1->setColor(Color3B::RED);
	m_sprUser1->setTag(TAG_BTN_PAPER);

	m_sprUser2 = Sprite::createWithSpriteFrameName("paper.png");
	addChild(m_sprUser2);
	m_sprUser2->setPosition(panel2->getPosition());
	m_sprUser2->setColor(Color3B::GREEN);
	m_sprUser2->runAction(getDisorderAction());
	m_sprUser2->setFlippedX(true);

	m_lblUser1Name = Label::createWithTTF("Mr. A", "fonts/arial.ttf", 40);
	m_lblUser1Name->setAnchorPoint(Point(0.5, 0));
	addChild(m_lblUser1Name);
	m_lblUser1Name->setPosition(panel1->getPosition() + Point(0, panel1->getContentSize().height / 2.0f + offset));

	m_lblUser2Name = Label::createWithTTF("Miss B", "fonts/arial.ttf", 40);
	m_lblUser2Name->setAnchorPoint(Point(0.5, 0));
	addChild(m_lblUser2Name);
	m_lblUser2Name->setPosition(panel2->getPosition() + Point(0, panel2->getContentSize().height / 2.0f + offset));

	Button *btnPause = GC::gI()->btn()->create("btn_pause.png");
	addChild(btnPause);
	btnPause->setPosition(Point(ws) - Point(btnPause->getContentSize().width, 0.75*btnPause->getContentSize().height));
	btnPause->setTag(TAG_BTN_PAUSE);
	btnPause->addTouchEventListener(CC_CALLBACK_2(GameScene::callBackRPS, this));

	Button *btnMenu = GC::gI()->btn()->create("btn_menu.png");
	addChild(btnMenu);
	btnMenu->setPosition(Point(btnPause->getContentSize().width, ws.height - 0.75*btnPause->getContentSize().height));
	btnMenu->setTag(TAG_BTN_MENU);
	btnMenu->addTouchEventListener(CC_CALLBACK_2(GameScene::callBackRPS, this));

	Button *btnPaper = GC::gI()->btn()->create("paper.png");
	addChild(btnPaper);
	btnPaper->setPosition(Point(ws.width / 2.0f, btnPaper->getContentSize().height));
	btnPaper->setTag(TAG_BTN_PAPER);
	btnPaper->addTouchEventListener(CC_CALLBACK_2(GameScene::callBackRPS, this));

	Button *btnRock = GC::gI()->btn()->create("rock.png");
	addChild(btnRock);
	btnRock->setPosition(btnPaper->getPosition() + Point(-btnRock->getContentSize().width / 2.0f - btnPaper->getContentSize().width / 2.0f - offset, 0));
	btnRock->setTag(TAG_BTN_ROCK);
	btnRock->addTouchEventListener(CC_CALLBACK_2(GameScene::callBackRPS, this));

	Button *btnScissors = GC::gI()->btn()->create("scissors.png");
	addChild(btnScissors);
	btnScissors->setPosition(btnPaper->getPosition() + Point(btnRock->getContentSize().width / 2.0f + btnPaper->getContentSize().width / 2.0f + offset, 0));
	btnScissors->setTag(TAG_BTN_SCISSORS);
	btnScissors->addTouchEventListener(CC_CALLBACK_2(GameScene::callBackRPS, this));

	m_countDown = MAX_COUNT_DOWN;
	scheduleUpdate();
	startNewRound();

	//test Source Tree
    return true;
}

void GameScene::update(float dt)  {

}

void GameScene::updateCountDown(float dt) {
	if (m_countDown > 0) {
		m_countDown--;
		m_lblCountDown->setString(StringUtils::format("%d", m_countDown));
	}
	else {
		int randomUser2Result = rand() % 3;
		m_sprUser2->setTag(randomUser2Result);
		m_sprUser2->stopAllActions();
		switch (randomUser2Result)
		{
		case TAG_BTN_PAPER: {
			m_sprUser2->setSpriteFrame("paper.png");
			break;
		}
		case TAG_BTN_ROCK: {
			m_sprUser2->setSpriteFrame("rock.png");
			break;
		}
		case TAG_BTN_SCISSORS:{
			m_sprUser2->setSpriteFrame("scissors.png");
			break;
		}
		default:
			break;
		}

		BattleResult result = getResult(m_sprUser1->getTag(), m_sprUser2->getTag());
		m_resultLayer->show(result);
		unschedule(CC_SCHEDULE_SELECTOR(GameScene::updateCountDown));
	}
}

void GameScene::startNewRound() {
	m_countDown = MAX_COUNT_DOWN;
	m_sprUser2->runAction(getDisorderAction());
	schedule(CC_SCHEDULE_SELECTOR(GameScene::updateCountDown), 1);
}

void GameScene::callBackRPS(Ref *sender, Widget::TouchEventType type) {
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED: {
		Button *btn = (Button *)sender;
		m_sprUser1->setTag(btn->getTag());
		switch (btn->getTag())
		{
		case TAG_BTN_PAPER: {
			m_sprUser1->setSpriteFrame("paper.png");
			break;
		}
		case TAG_BTN_ROCK: {
			m_sprUser1->setSpriteFrame("rock.png");
			break;
		}
		case TAG_BTN_SCISSORS:{
			m_sprUser1->setSpriteFrame("scissors.png");
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

Action *GameScene::getDisorderAction() {
	float delayTime = 0.15;
	Vector<SpriteFrame*> frames;
	frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("paper.png"));
	frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("rock.png"));
	frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("scissors.png"));
	Animation *animation = Animation::createWithSpriteFrames(frames, delayTime);
	Animate *anim = Animate::create(animation);
	return RepeatForever::create(anim);
}

BattleResult GameScene::getResult(int user1Result, int user2Result) {
	if (user1Result == user2Result) {
		return BattleResult::EQUAL;
	}
	if ((user1Result == TAG_BTN_PAPER && user2Result == TAG_BTN_ROCK) ||
		(user1Result == TAG_BTN_ROCK && user2Result == TAG_BTN_SCISSORS) ||
		(user1Result == TAG_BTN_SCISSORS && user2Result == TAG_BTN_PAPER)) {
		return BattleResult::WIN;
	}
	return BattleResult::LOSE;
}

void GameScene::onReplay() {
	m_resultLayer->setVisible(false);
	startNewRound();
}
