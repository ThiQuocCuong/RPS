#include "ButtonController.h"

Button *ButtonController::create(const std::string& normalImage, const std::string& selectedImage, const std::string& disableImage) {
	return Button::create(normalImage, selectedImage, disableImage, Widget::TextureResType::PLIST);
}