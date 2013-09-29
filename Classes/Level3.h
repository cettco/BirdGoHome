#ifndef __Level3_H__
#define __Level3_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "LineLayer.h"
using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;
class Level3 : public cocos2d::CCLayer
	,public cocos2d::extension::CCBSelectorResolver
	,public cocos2d::extension::CCBMemberVariableAssigner
{
public:
	Level3()
	{
		//注意要初始化为NULL
		shooter1 = NULL;
		shooter2 = NULL;
		obstacle1 = NULL;
		obstacle2 = NULL;
		obstacle3 = NULL;
		obstacle4 = NULL;
		obstacle5 = NULL;
		obstacle6 = NULL;
		bomb1 = NULL;
		bomb2 = NULL;
		rotate1 = NULL;
		rotate2 = NULL;
		bird = NULL;
		home = NULL;
		s1l =NULL;
		s1r = NULL;
		star1= NULL;
		star2 = NULL;
		star3= NULL;
		timeLabel = NULL;
		birdBody = NULL;
		rotate1Body = NULL;
	    rotate2Body = NULL;
		layer = new LineLayer();
		i=0;
		turn = 1;
		time = 15;
		canFly = 0;
		endLayer = NULL;
	}
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Level3,create);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
	void pressed(cocos2d::CCObject* pSender);
	static cocos2d::CCScene* scene();
	void initWorld();
	virtual bool init();
	void createStaticBody(CCSprite*sprite,float x,float y);
	b2Body * createMoveStaticBody(CCSprite*sprite,float x,float y);
	void createDynamicBody(b2Body* body,CCSprite*sprite,float x,float y,b2Vec2 vec);
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	void update(float dt);
	void initBody();
	void setMTime(float dt);
protected:
	CCSize size;
	CCSprite *shooter1;
	CCSprite *shooter2;
	CCSprite *obstacle1;
	CCSprite *obstacle2;
	CCSprite *obstacle3;
	CCSprite *obstacle4;
	CCSprite *obstacle5;
	CCSprite *obstacle6;
	CCSprite *rotate1;
	CCSprite *rotate2;
	CCSprite *home;
	CCSprite *bird;
	CCSprite *s1r;
	CCSprite *s1l;
	CCSprite *star1;
	CCSprite *star2;
	CCSprite *star3;
	CCSprite *bomb1;
	CCSprite *bomb2;
	CCLabelTTF *timeLabel;
	CCLayer *endLayer;
public:
	b2World *world;
	b2Body *groundBody;
	b2Body *birdBody;
	b2Body *rotate1Body;
	b2Body *rotate2Body;
	bool isPulling;
	int canFly;
	CCPoint birdCenter;
protected:
	LineLayer *layer;
	int i;
	int turn;
	int time;
};

class Level3LayerLoader:public cocos2d::extension::CCLayerLoader {

public:

	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(Level3LayerLoader, loader);
	//void press();
protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Level3);

};
#endif