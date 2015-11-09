//
//  FriendListLayer.cpp
//  RPS
//
//  Created by Tung Huynh Thanh on 11/6/15.
//
//

#include "FriendListLayer.h"
bool FriendListLayer::init() {
    if(!Node::init()) {
        return false;
    }
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::map<std::string, std::string> params;
    GC::gI()->fb()->api("/me/invitable_friends", "GET", params, "bla_bla");
#endif
    return true;
}
