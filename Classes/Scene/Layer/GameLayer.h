#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "../GameDelegate.h"
#include "../../GC/GC.h"

class GameLayer : public Node
{
protected:
	Button *m_btnBack;
	GameDelegate *m_delegate;
public:
	void setDelegate(GameDelegate *del) {
		m_delegate = del;
	}
	virtual bool init();
	virtual void show();
	virtual void hide();
	void enableBackButton(bool value);
	CREATE_FUNC(GameLayer);
};

#endif // __GAME_LAYER_H__
