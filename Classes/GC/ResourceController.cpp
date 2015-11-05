#include "ResourceController.h"

void ResourceController::loadResource(vector<string> paths) {
	m_percent = 0;
	m_ratio = 100.0f / paths.size();
	m_paths = paths;
	string firstPath = paths.back();
	Director::getInstance()->getTextureCache()->addImageAsync(StringUtils::format("%s.png", firstPath.c_str()), CC_CALLBACK_1(ResourceController::doneLoadTexture, this));
}

void ResourceController::doneLoadTexture(Texture2D *texture) {
	string path = m_paths.back();
	m_paths.pop_back();
	if (texture) {
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(StringUtils::format("%s.plist", path.c_str()), texture);
		m_percent += m_ratio;
		if (m_paths.size() > 0) {
			string nextPath = m_paths.back();
			Director::getInstance()->getTextureCache()->addImageAsync(StringUtils::format("%s.png", nextPath.c_str()), CC_CALLBACK_1(ResourceController::doneLoadTexture, this));
		}
		else {
			m_percent = 100;
		}
	}
	else {
		m_percent = -1;
	}
}

int ResourceController::getPercent() {
	return m_percent;
}