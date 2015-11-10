#include "SpriteController.h"
RemoteSprite *SpriteController::createWithURL(std::string url, std::string defaultImg) {
	if (defaultImg.compare("") == 0) {
        return RemoteSprite::createWithURL(url);
    }
    return RemoteSprite::createWithURL(url, defaultImg);
}