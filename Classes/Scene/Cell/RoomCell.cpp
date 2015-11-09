//
//  FriendListLayer.cpp
//  RPS
//
//  Created by Tung Huynh Thanh on 11/6/15.
//
//

#include "RoomCell.h"

bool RoomCell::init() {
	if (!MyCustomCell::init()) {
		return false;
	}
	m_bg = ui::Scale9Sprite::createWithSpriteFrameName("ui_panel_2.png");
	addChild(m_bg);
	m_bg->setAnchorPoint(Point::ZERO);

	m_avarta = Sprite::createWithSpriteFrameName("avarta_3.png");
	addChild(m_avarta);

	m_lblName = Label::createWithTTF("Room 1", "fonts/arial.ttf", 30);
	addChild(m_lblName);
	m_lblName->setAnchorPoint(Point(0.5, 1));

	m_lblStatus = Label::createWithTTF("Waiting", "fonts/arial.ttf", 30);
	addChild(m_lblStatus);
	m_lblStatus->setAnchorPoint(Point(0.5, 0));

	m_sprIcon = Sprite::createWithSpriteFrameName("icon_lock.png");
	addChild(m_sprIcon);
	
	return true;
}

void RoomCell::setModel(RoomModel *model) {
	m_lblName->setString(model->m_name);
	RoomStatus status = (RoomStatus)model->m_status;
	switch (status)
	{
	case RoomStatus::PLAYING: {
		m_lblStatus->setString("Playing");
		break;
	}
	case RoomStatus::WAITING: {
		m_lblStatus->setString("Waiting");
		break;
	}
	default:
		break;
	}
}

void RoomCell::layout(Size cellSize) {
	m_bg->setContentSize(Size(0.9*cellSize));
	m_bg->setPosition(Point(0.05*cellSize));
	m_cellSize = 0.9*cellSize;
	m_lblName->setPosition(m_bg->getPosition() + Point(m_cellSize.width / 2.0f, m_cellSize.height - m_lblName->getContentSize().height / 2.0f));
	m_lblStatus->setPosition(m_bg->getPosition() + Point(m_cellSize.width / 2.0f, m_lblStatus->getContentSize().height / 2.0f));
	m_sprIcon->setPosition(m_bg->getPosition() + Point(m_cellSize) - m_sprIcon->getContentSize());
	m_avarta->setPosition(m_bg->getPosition() +  Point(m_cellSize / 2.0f));
}