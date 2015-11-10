#include "SpriteController.h"
RemoteSprite *SpriteController::createWithURL(std::string url, std::string defaultImg) {
    if(url.compare("") == 0) {
        return RemoteSprite::createWithURL(url);
    }
    return RemoteSprite::createWithURL(url, defaultImg);
}