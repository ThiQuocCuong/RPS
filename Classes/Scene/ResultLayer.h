#ifndef __RESULT_LAYER_H__
#define __RESULT_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameDelegate.h"
#include "../Prefix.h"
using namespace cocos2d;
using namespace ui;

class ResultLayer : public Layer
{
	Label *m_lblNotify;
	GameDelegate *m_delegate;
public:
	void setDelegate(GameDelegate *del) {
		m_delegate = del;
	}
	virtual bool init();
	void show(BattleResult result);
	CREATE_FUNC(ResultLayer);
};

#endif // __RESULT_LAYER_H__
