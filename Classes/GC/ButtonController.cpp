#include "ButtonController.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

Button *ButtonController::create(const std::string& normalImage, const std::string& selectedImage, const std::string& disableImage) {
	return Button::create(normalImage, selectedImage, disableImage, Widget::TextureResType::PLIST);
}