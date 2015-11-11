//
//  FriendListLayer.cpp
//  RPS
//
//  Created by Tung Huynh Thanh on 11/6/15.
//
//

#include "ShopItemCell.h"

bool ShopItemCell::init() {
	if (!MyCustomCell::init()) {
		return false;
	}
	m_bg = ui::Scale9Sprite::createWithSpriteFrameName("ui_panel_2.png");
	addChild(m_bg);
	m_bg->setAnchorPoint(Point::ZERO);

	m_avarta = Sprite::createWithSpriteFrameName("avarta_3.png");
	addChild(m_avarta);
	m_avarta->setAnchorPoint(Point(0.5, 1));

	m_lblName = Label::createWithTTF("Item", "fonts/arial.ttf", 30);
	addChild(m_lblName);
	m_lblName->setAnchorPoint(Point(0.5, 1));

	m_btnBuy = GC::gI()->btn()->create("btn_yellow.png");
	addChild(m_btnBuy);
	m_btnBuy->setAnchorPoint(Point(0.5, 0));
	m_btnBuy->setScale9Enabled(true);

	m_lblCost = Label::createWithTTF("000000", "fonts/arial.ttf", 20);
	m_lblCost->setAnchorPoint(Point(0, 0.5));
	addChild(m_lblCost);
	m_lblCost->setAnchorPoint(Point(0, 0.5));

	m_sprUnit = Sprite::createWithSpriteFrameName("icon_lock.png");
	addChild(m_sprUnit);
	m_sprUnit->setAnchorPoint(Point(0, 0.5));
	
	return true;
}

void ShopItemCell::setModel(ShopItemModel *model) {
	m_lblCost->setString(StringUtils::format("%d", model->m_cost));
	m_lblName->setString(model->m_name);
	switch (model->m_type)
	{
	case ShopItemType::HAT: {
		m_avarta->setSpriteFrame("item_2.png");
		break;
	}
	default:{
		m_avarta->setSpriteFrame("item_1.png");
		break;
	}
	}
}

void ShopItemCell::layout(Size cellSize) {
	m_bg->setContentSize(Size(0.9*cellSize));
	m_bg->setPosition(Point(0.05*cellSize));
	m_cellSize = m_bg->getContentSize();
	m_avarta->setPosition(m_cellSize.width / 2.0f, m_cellSize.height - 10);
	m_btnBuy->setContentSize(Size(0.9*m_cellSize.width, 1.5*m_sprUnit->getContentSize().height));
	m_btnBuy->setPosition(m_bg->getPosition() + Point(m_cellSize.width / 2.0f, 0));
	m_sprUnit->setPosition(m_btnBuy->getPosition() + Point(0.05*m_sprUnit->getContentSize().width - m_btnBuy->getContentSize().width/2.0f, m_btnBuy->getContentSize().height / 2.0f));
	m_lblCost->setPosition(m_sprUnit->getPosition() + Point(1.05* m_sprUnit->getContentSize().width, 0));
	float avaibleSpaceH = m_avarta->getPositionY() - m_avarta->getContentSize().height - m_btnBuy->getContentSize().height;
	m_lblName->setPosition(m_cellSize.width / 2.0f, m_btnBuy->getPositionY() + m_btnBuy->getContentSize().height + avaibleSpaceH / 2.0f);
}