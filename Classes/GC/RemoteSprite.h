#ifndef __REMOTE_SPRITE_H__
#define __REMOTE_SPRITE_H__

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "network/HttpResponse.h"
class RemoteSprite : public cocos2d::Sprite
{
	cocos2d::network::HttpRequest *m_httpRequest;
	std::string m_url;
	int m_numberOfFails;
	void download(std::string url);
	void callBackDownloadImage(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);
public:
	RemoteSprite();
	static RemoteSprite *createWithURL(std::string url, std::string defaultImg = "loading_1.png");
};

#endif // __HELLOWORLD_SCENE_H__
