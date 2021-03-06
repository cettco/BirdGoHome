#ifndef __Level1_H__
#define __Level1_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "LineLayer.h"
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;
class Level1 : public cocos2d::CCLayer
	,public cocos2d::extension::CCBSelectorResolver
	,public cocos2d::extension::CCBMemberVariableAssigner
{
public:
	Level1()
	{
		//注意要初始化为NULL
		shooter1 = NULL;
		shooter2 = NULL;
		obstacle1 = NULL;
		obstacle2 = NULL;
		bird = NULL;
		home = NULL;
		s1l =NULL;
		s1r = NULL;
		s2l = NULL;
		s2r = NULL;
		star1= NULL;
		star2 = NULL;
		star3= NULL;
		timeLabel = NULL;
		birdBody = NULL;
		layer = new LineLayer();
		i=0;
		turn = 1;
		time = 15;
		endLayer = NULL;
	}
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(Level1,create);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
	void pressed(cocos2d::CCObject* pSender);
	static cocos2d::CCScene* scene();
	void initWorld();
	virtual bool init();
	void createStaticBody(CCSprite*sprite,float x,float y);
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
	CCSprite *home;
	CCSprite *bird;
	CCSprite *s1r;
	CCSprite *s1l;
	CCSprite *s2r;
	CCSprite *s2l;
	CCSprite *star1;
	CCSprite *star2;
	CCSprite *star3;
	CCLabelTTF *timeLabel;
	CCLayer *endLayer;
public:
	b2World *world;
	b2Body *groundBody;
	b2Body *birdBody;
	bool isPulling;
	int canFly;
	CCPoint birdCenter;
protected:
	LineLayer *layer;
	int i;
	int turn;
	int time;
};

class Level1LayerLoader:public cocos2d::extension::CCLayerLoader {

public:

	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(Level1LayerLoader, loader);
	//void press();
protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Level1);

};
#endif