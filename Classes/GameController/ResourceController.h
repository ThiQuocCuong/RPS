#ifndef __RESOURCE_CONTROLLER_H__
#define __RESOURCE_CONTROLLER_H__

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

class ResourceController
{
	int m_ratio;
	int m_percent;
	vector<string> m_paths;
	void doneLoadTexture(Texture2D *texture);
public:
	void loadResource(vector<string> paths);
	int getPercent();
};

#endif // __RESOURCE_CONTROLLER_H__
