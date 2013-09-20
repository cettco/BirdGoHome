#ifndef __MainLayer_H__
#define __MainLayer_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#define PTM_RATIO 32.0
using namespace cocos2d;
using namespace cocos2d::extension;
class MainLayer : public cocos2d::CCLayer
	,public cocos2d::extension::CCBSelectorResolver
	,public cocos2d::extension::CCBMemberVariableAssigner
{
public:
	MainLayer()
	{

	}
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainLayer,create);
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
	void buttonPressed(cocos2d::CCObject* sender);
	static cocos2d::CCScene* scene();
	virtual bool init();
};

class MainLayerLoader:public cocos2d::extension::CCLayerLoader {

public:

	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainLayerLoader, loader);
	//void press();
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainLayer);

};

#endif  // __MainLayer_SCENE_H__