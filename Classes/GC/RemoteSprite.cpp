#include "RemoteSprite.h"
#include "GC.h"
using namespace cocos2d;
using namespace std;

#define MAX_RETRY 3

RemoteSprite::RemoteSprite() {
	m_httpRequest = nullptr;
	m_numberOfFails = 0;
	m_url = "";
}
RemoteSprite *RemoteSprite::createWithURL(std::string url, std::string defaultImg) {
	auto mySprite = new RemoteSprite();
	mySprite->m_url = url;
	auto texture = Director::getInstance()->getTextureCache()->getTextureForKey(url);
	bool didSpriteInitSucceed = false;
	if (texture) {
		mySprite->initWithTexture(texture);
		didSpriteInitSucceed = true;
	}
	else {
		didSpriteInitSucceed = mySprite->initWithSpriteFrameName(defaultImg);
		if (didSpriteInitSucceed) {
			Animate *anim = GC::gI()->anim()->create("loading", 17, 0.1, 1);
			mySprite->runAction(RepeatForever::create(anim));
		}
		mySprite->download(url);
	}

	if (didSpriteInitSucceed) {
		mySprite->autorelease();
		return mySprite;
	}

	CC_SAFE_DELETE(mySprite);
	return NULL;
}

void RemoteSprite::download(std::string url)  {
	if (!m_httpRequest) {
		m_httpRequest = new network::HttpRequest();
		m_httpRequest->setRequestType(cocos2d::network::HttpRequest::Type::GET);
		m_httpRequest->setResponseCallback(CC_CALLBACK_2(RemoteSprite::callBackDownloadImage, this));
	}
	m_httpRequest->setUrl(url.c_str());

	//// Add the fail number to the end of the URL so that we can create a new HttpRequest while
	//// processing the result of the last one which failed.
	//auto tagString = url + (std::to_string(_numberOfFails));
	//_httpRequest->setTag(url.c_str());


	cocos2d::network::HttpClient::getInstance()->send(m_httpRequest);
}
void RemoteSprite::callBackDownloadImage(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response) {
	if (response->isSucceed()) {
		auto buffer = response->getResponseData();

		cocos2d::Image * img = new cocos2d::Image;
		img->initWithImageData(reinterpret_cast<unsigned char*>(&(buffer->front())), buffer->size());

		auto textureCache = cocos2d::Director::getInstance()->getTextureCache();

		/*auto previousTexture = textureCache->getTextureForKey(url);
		if (previousTexture)
		{
		textureCache->removeTextureForKey(url);			}*/

		cocos2d::Texture2D* texture = textureCache->addImage(img, m_url);

		img->release();
		if (texture) {
			stopAllActions();
			setTexture(texture);
		}
	}
	else {
		if (m_numberOfFails < MAX_RETRY) {
			m_numberOfFails++;
			download(m_url);
		}
		else {
			stopAllActions();
			setSpriteFrame("loading_error.png");
		}
	}
}
