//
//  FriendListLayer.h
//  RPS
//
//  Created by Tung Huynh Thanh on 11/6/15.
//
//

#ifndef __RPS__GameModel__
#define __RPS__GameModel__

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

class UserModel: public Ref {
public:
	string m_id;
	string m_name;
	int m_level;
};

class RoomModel : public Ref {
public:
	string m_id;
	string m_name;
	int m_status;
};

#endif /* defined(__RPS__FriendListLayer__) */
