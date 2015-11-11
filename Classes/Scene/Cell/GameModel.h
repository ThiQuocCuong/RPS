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
	UserModel() {
		m_id = "";
		m_name = "";
		m_level = 0;
	}
	UserModel(string id, string name, int level) {
		m_id = id;
		m_name = name;
		m_level = level;
	}
	string m_id;
	string m_name;
	int m_level;
};

class FBUserModel: public Ref {
public:
    string m_id;
    string m_name;
    bool m_is_silhouette;
    string m_imgURL;
};

class RoomModel : public Ref {
public:
	string m_id;
	string m_name;
	int m_status;
};


enum class ShopItemType {
	HAT = 0,
	PAN
};
class ShopItemModel: public Ref {
public:
	ShopItemModel(ShopItemType type = ShopItemType::HAT,
				  string id = "",
				  string name = "",
				  int cost = 0,
				  int unit = 0) {
		m_type = type;
		m_name = name;
		m_cost = cost;
		m_unit = unit;
	}
	ShopItemType m_type;
	string m_id;
	string m_name;
	int m_cost;
	int m_unit;
};

#endif /* defined(__RPS__FriendListLayer__) */
