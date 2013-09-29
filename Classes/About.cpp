#include "About.h"
#include "GameMenu.h"
#define PTM_RATIO 32.0
void About::pressed(cocos2d::CCObject* pSender)
{
	CCMenuItemImage *menu = (CCMenuItemImage*)pSender;
	CCLog("clicked");
	switch (menu->getTag())
	{
	case 0:
		CCDirector::sharedDirector()->replaceScene(CCTransitionRotoZoom::create(1,GameMenu::scene()));
	}
}
CCScene* About::scene()
{
	//场景转换
	CCScene *scene = CCScene::create();
	CCNodeLoaderLibrary *lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	lib->registerCCNodeLoader("About", AboutLayerLoader::loader());
	CCBReader *reader = new CCBReader(lib);
	CCNode* node = reader->readNodeGraphFromFile("About.ccbi", scene);
	reader->release(); //注意手动释放内存
	if (node!=NULL)
	{
		scene->addChild(node,-10,1); //将node 添加到scene中
		CCBAnimationManager*animationManager = (CCBAnimationManager*)node->getUserObject();
		//animationManager->runAnimationsForSequenceNamed("over");
	}
	return scene;
}
bool About::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(! CCLayer::init());
		setTouchEnabled(true);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("back.mp3",true);
		CCSprite *sprite = CCSprite::create("back.png");
		sprite->setPosition(ccp(500,600));
		this->addChild(sprite,100);
		bRet = true;
	} while (0);

	return bRet;
}
SEL_MenuHandler About::onResolveCCBCCMenuItemSelector(CCObject * pTarget,const char * pSelectorName){

	//Bind Menu Events，绑定一个menu，点击方法是press，以下同理
	//CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "buttonPressed",About::pressed);

	return NULL;

}

extension::SEL_CCControlHandler About::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName)
{
	return NULL;
}
bool About::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
	return true;
}

