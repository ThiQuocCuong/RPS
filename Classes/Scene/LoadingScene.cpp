#include "LoadingScene.h"
#include "GameScene.h"
#include "LoginScene.h"

Scene* LoadingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = LoadingScene::create();
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoadingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	Size ws = Director::getInstance()->getWinSize();
	m_lblPercent = Label::createWithTTF("Loading: 0%", "fonts/arial.ttf", 30);
	m_lblPercent->setPosition(ws / 2.0f);
	addChild(m_lblPercent);
	m_lastPercent = 0;
	loadResources();
	scheduleUpdate();
    return true;
}


void LoadingScene::update(float dt){
	int percent = GC::gI()->resoure()->getPercent();
	if (m_lastPercent != percent) {
		if (percent < 0) {
			m_lblPercent->setString("Loading Resources Failed!!!");
		}
		else {
			m_lblPercent->setString(StringUtils::format("Loading: %d", percent));
			if (percent >= 100) {
				unscheduleUpdate();
				Director::getInstance()->replaceScene(LoginScene::createScene());
			}
		}
		m_lastPercent = percent;
	}
}

void LoadingScene::loadResources() {
	vector<string> paths;
	paths.push_back("res/res");
	GC::gI()->resoure()->loadResource(paths);
}