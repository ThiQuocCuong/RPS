#include "AnimationController.h"
using namespace cocos2d;
using namespace std;
Animate *AnimationController::create(string prefix, int frameCount, float delay, int startIndex) {
    Vector<SpriteFrame *> frames;
    for(int i=startIndex;i<startIndex+frameCount;i++) {
        string name = StringUtils::format("%s_%d.png", prefix.c_str(), i);
        SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
        frames.pushBack(frame);
    }
    Animation *animation = Animation::createWithSpriteFrames(frames);
    return Animate::create(animation);
}