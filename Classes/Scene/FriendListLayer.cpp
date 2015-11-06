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
    std::map<std::string, std::string> params;
    params.insert(std::pair<std::string, std::string>("limit", "50"));
    GC::gI()->fb()->requestInvitableFriends(params);
    return true;
}
