//
//  FriendListLayer.cpp
//  RPS
//
//  Created by Tung Huynh Thanh on 11/6/15.
//
//

#include "FriendCell.h"
using namespace cocos2d;
using namespace ui;

FriendCell *FriendCell::create(cocos2d::Size cellSize) {
    FriendCell * ret = new (std::nothrow) FriendCell();
    if (ret && ret->init(cellSize))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool FriendCell::init(cocos2d::Size cellSize) {
    if (!MyCustomCell::init()){
        return false;
    }
    
    Size ws = Director::getInstance()->getWinSize();
    if (!cellSize.equals(Size::ZERO)) {
        m_cellSize.width = cellSize.width;
    }
    
    float offset = 10;
    
    m_bg = ui::Scale9Sprite::createWithSpriteFrameName("ui_panel_2.png");
    addChild(m_bg);
    m_bg->setAnchorPoint(Point(0, 0.5));
    m_bg->setOpacity(200);
    
    Button *btnView = GC::gI()->btn()->create("btn_yellow_view.png");
    addChild(btnView);
    btnView->setScale(0.5);
    btnView->setPosition(Point(m_cellSize.width - btnView->getContentSize().width*btnView->getScale() / 2.0f - offset,
                               btnView->getContentSize().height*btnView->getScale() / 2.0f + offset / 2.0f));
    
    Button *btnChat = GC::gI()->btn()->create("btn_yellow_chat.png");
    addChild(btnChat);
    btnChat->setScale(0.5);
    btnChat->setPosition(Point(m_cellSize.width - btnChat->getContentSize().width*btnView->getScale() / 2.0f - offset,
                               -btnView->getContentSize().height*btnView->getScale() / 2.0f - offset / 2.0f));
    
    //	m_sprAvatar = Sprite::createWithSpriteFrameName("avarta_4.png");
    //	addChild(m_sprAvatar);
    
    m_lblInfo = Label::createWithTTF("Lvl15 Wonka Thi", FNT_TTF, 20);
    addChild(m_lblInfo);
    m_lblInfo->setAnchorPoint(Point(0, 0.5));
    
    m_cellSize.height = btnView->getContentSize().height*btnView->getScale() + btnChat->getContentSize().height*btnChat->getScale() + offset * 5;
    
    m_bg->setContentSize(m_cellSize - Size(0, 2*offset));
    m_sprAvatar = nullptr;
    
    return true;
}

void FriendCell::setModel(UserModel *model) {
    if (!m_sprAvatar) {
        m_sprAvatar = Sprite::createWithSpriteFrameName("avarta_4.png");
        addChild(m_sprAvatar);
        m_sprAvatar->setPosition(m_sprAvatar->getContentSize().width / 2.0f + 10, 0);
        m_lblInfo->setPosition(m_sprAvatar->getPosition() +
                               Point(m_sprAvatar->getContentSize().width / 2.0f + 10, 0));
    }
    m_lblInfo->setString(StringUtils::format("Lvl %d %s", model->m_level, model->m_name.c_str()));
}

void FriendCell::setModel(FBUserModel *model) {
    m_lblInfo->setString(StringUtils::format("%s", model->m_name.c_str()));
    if (!m_sprAvatar) {
        if (model->m_imgURL.compare("") == 0) {
            m_sprAvatar = Sprite::createWithSpriteFrameName("loading_1.png");
            Animate *anim = GC::gI()->anim()->create("loading", 17, 0.1, 1);
            m_sprAvatar->runAction(RepeatForever::create(anim));
        }
        else {
            m_sprAvatar = GC::gI()->spr()->createWithURL(model->m_imgURL, model->m_id);
            ((RemoteSprite *)m_sprAvatar)->setRemoteSpriteCallBack([=](bool result) {
                if(result) {
                    CCLOG("load %s 's picture succeed", model->m_name.c_str());
                } else {
                    CCLOG("load %s 's picture error", model->m_name.c_str());
                }
            });
        }
        addChild(m_sprAvatar);
    } else {
        m_sprAvatar->stopAllActions();
        Texture2D *texture = Director::getInstance()->getTextureCache()->getTextureForKey(model->m_imgURL);
        if(texture) {
            m_sprAvatar->setTexture(texture);
            m_sprAvatar->setTextureRect(Rect(0, 0, 160, 160));
        } else {
            GC::gI()->spr()->createWithURL(model->m_imgURL);
            m_sprAvatar->setSpriteFrame("loading_1.png");
            Animate *anim = GC::gI()->anim()->create("loading", 17, 0.1, 1);
            m_sprAvatar->runAction(RepeatForever::create(anim));
        }
    }
    
    if(m_sprAvatar->getContentSize().height >= MAX_HEIGHT_AVARTA) {
        m_sprAvatar->setScale(MAX_HEIGHT_AVARTA/m_sprAvatar->getContentSize().height);
    } else {
        m_sprAvatar->setScale(1);
    }
    
    if(m_sprAvatar) {
        m_sprAvatar->setPosition(m_sprAvatar->getContentSize().width*m_sprAvatar->getScale() / 2.0f + 10, 0);
        m_lblInfo->setPosition(m_sprAvatar->getPosition() +
                               Point(m_sprAvatar->getContentSize().width*m_sprAvatar->getScale() / 2.0f + 10, 0));
    }
}