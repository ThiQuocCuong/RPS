#ifndef __RESULT_LAYER_H__
#define __RESULT_LAYER_H__

#include "GameLayer.h"

class ResultLayer : public GameLayer
{
	Label *m_lblNotify;
public:
	virtual bool init();
	void show(BattleResult result);
	CREATE_FUNC(ResultLayer);
};

#endif // __RESULT_LAYER_H__
