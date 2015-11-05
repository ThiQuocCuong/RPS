#ifndef __BUTTON_CONTROLLER_H__
#define __BUTTON_CONTROLLER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
using namespace std;

class ButtonController
{
public:
	Button *create(const std::string& normalImage,
		const std::string& selectedImage = "",
		const std::string& disableImage = "");
};

#endif // __BUTTON_CONTROLLER_H__
