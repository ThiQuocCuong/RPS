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
	return true;
}

void MyCustomCell::setDelegate(GameDelegate *del) {
	m_delegate = del;
}