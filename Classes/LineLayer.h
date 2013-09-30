#ifndef __LineLayer_H__
#define __LineLayer_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace cocos2d::extension;
class LineLayer : public cocos2d::CCLayer
{
public:
	LineLayer()
	{
	}
	void createWithPoints(CCPoint start,CCPoint end1,CCPoint end2);
	virtual void draw();
private:
	CCPoint start;
	CCPoint end1;
	CCPoint end2;
};
#endif