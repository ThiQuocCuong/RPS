#ifndef __RESOURCE_CONTROLLER_H__
#define __RESOURCE_CONTROLLER_H__

#include "cocos2d.h"

class ResourceController
{
	int m_ratio;
	int m_percent;
	std::vector<std::string> m_paths;
	void doneLoadTexture(cocos2d::Texture2D *texture);
public:
	void loadResource(std::vector<std::string> paths);
	int getPercent();
};

#endif // __RESOURCE_CONTROLLER_H__
