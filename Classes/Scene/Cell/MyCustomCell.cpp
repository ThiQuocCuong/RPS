//
//  FriendListLayer.cpp
//  RPS
//
//  Created by Tung Huynh Thanh on 11/6/15.
//
//

#include "MyCustomCell.h"
using namespace cocos2d;
using namespace extension;

bool MyCustomCell::init() {
	if (!TableViewCell::init()) {
		return false;
	}
	m_bg = nullptr;
	m_isHighlight = false;
	return true;
}

void MyCustomCell::setDelegate(GameDelegate *del) {
	m_delegate = del;
}

void MyCustomCell::highlight(bool value) {
	if (!m_bg || m_isHighlight == value) {
		return;
	}
	m_isHighlight = value;
	Size originalSize = m_bg->getContentSize();
	if (!value) {
		SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_panel_2.png");
		m_bg->setSpriteFrame(frame);
	}
	else {
		SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("ui_panel.png");
		m_bg->setSpriteFrame(frame);
	}
	m_bg->setContentSize(originalSize);
}