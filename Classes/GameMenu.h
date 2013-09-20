#ifndef __GAMEMENU_H__
#define __GAMEMENU_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace cocos2d::extension;
class GameMenu : public cocos2d::CCLayer
	,public cocos2d::extension::CCBSelectorResolver
	,public cocos2d::extension::CCBMemberVariableAssigner
{
public:
	GameMenu()
	{
		//this->label = NULL;
		//this->i=0;
	}
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameMenu,create);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
	void pressed(cocos2d::CCObject* pSender);
	static cocos2d::CCScene* scene();
	//cocos2d::CCLabelTTF *label;
	//static int i;
	virtual bool init();
	//virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);  
    //virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);  
    //virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);  
	//void update(float dt);
	//b2World *_world;
	//b2Body *_body;
	//CCSprite *_ball;
	//CCSprite *msprite;
   // virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
};

class MainLayerLoader:public cocos2d::extension::CCLayerLoader {

public:

	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainLayerLoader, loader);
	//void press();
protected:

	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameMenu);

};
#endif