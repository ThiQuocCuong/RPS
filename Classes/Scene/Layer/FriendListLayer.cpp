//
//  FriendListLayer.cpp
//  RPS
//
//  Created by Tung Huynh Thanh on 11/6/15.
//
//

#include "FriendListLayer.h"

bool FriendListLayer::init() {
    if(!GameLayer::init()) {
        return false;
    }
    std::map<std::string, std::string> params;
    //params.insert(std::pair<std::string, std::string>("limit", "50"));
    params.insert(std::pair<std::string, std::string>("fields","id,name,picture.width(160).height(160)"));
    GC::gI()->fb()->api(API_INVITABLE_FRIENDS, "GET", params, TAG_API_INVITE_FRIEND);
    
    
    Size ws = Director::getInstance()->getWinSize();
    
    ui::Scale9Sprite *bg = ui::Scale9Sprite::createWithSpriteFrameName("ui_panel.png");
    addChild(bg);
    bg->setContentSize(Size(0.8*ws));
    bg->setAnchorPoint(Point::ZERO);
    bg->setPosition(0.1*ws);
    
    FriendCell *cell = FriendCell::create(ws);
    m_cellSize = cell->getCellSize();
    m_cellSize.width = 0.9*bg->getContentSize().width;
    
    m_friendModels.pushBack(new FBUserModel());
    m_friendModels.back()->release();
    
    m_tbw = TableView::create(this, Size(0.9*bg->getContentSize()));
    addChild(m_tbw);
    m_tbw->setDelegate(this);
    m_tbw->setAnchorPoint(Point::ZERO);
    m_tbw->setPosition(bg->getPosition() + Point(0.05*bg->getContentSize()));
    m_tbw->setBounceable(true);
    
    setVisible(false);
    return true;
}

void FriendListLayer::onReceivedInvitableFriends(string json) {
    GC::gI()->json()->read(json);
    if(!GC::gI()->json()->isNull("data")) {
        m_friendModels.clear();
        //Get array data
        rapidjson::Value &data = GC::gI()->json()->getObject("data");
        int size = data.Size();
        for(int i=0;i<size;i++) {
            FBUserModel *model = new FBUserModel();
            if(!GC::gI()->json()->isNull(data, i)) {
                rapidjson::Value &obj = GC::gI()->json()->getObject(data, i);
                string id = GC::gI()->json()->getString(obj, "id");
                string name = GC::gI()->json()->getString(obj, "name");
                model->m_id = id;
                model->m_name = name;
                if(!GC::gI()->json()->isNull(obj, "picture")) {
                    rapidjson::Value &picture = GC::gI()->json()->getObject(obj, "picture");
                    if(!GC::gI()->json()->isNull(picture, "data")) {
                        rapidjson::Value &pictureData = GC::gI()->json()->getObject(picture, "data");
                        string url = GC::gI()->json()->getString(pictureData, "url");
                        bool is_silhouette = GC::gI()->json()->getBool(pictureData, "is_silhouette");
                        model->m_is_silhouette = is_silhouette;
                        model->m_imgURL = url;
                    }
                }
            }
            m_friendModels.pushBack(model);
            model->release();
        }
        m_tbw->reloadData();
    }
}

void FriendListLayer::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell) {
    
}
TableViewCell* FriendListLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx) {
    FriendCell *cell = (FriendCell *)table->dequeueCell();
    if (!cell) {
        cell = FriendCell::create(m_cellSize);
    }
    FBUserModel *model = m_friendModels.at(idx);
    cell->setModel(model);
    return cell;
}
ssize_t FriendListLayer::numberOfCellsInTableView(cocos2d::extension::TableView *table) {
    return m_friendModels.size();
}
Size FriendListLayer::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx) {
    return m_cellSize;
}
