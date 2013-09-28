#include "MainLayer.h"
//#include "About.h"
//#include "Play.h"
#define playPressed 1
#define aboutPressed 2
#define mutePressed 3
void MainLayer::buttonPressed(cocos2d::CCObject* sender)
{

	/*if(sender->getTag()==playPressed)
	{
		CCScene *pScene = Play::scene();
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,pScene,false));
	}
	else if(sender->getTag()==aboutPressed)
	{
		CCScene *pScene = About::scene();
		CCDirector::sharedDirector()->replaceScene(CCTransitionJumpZoom::create(1,pScene));
	}
	else if(sender->getTag()==mutePressed)
	{
	}*/

}
CCScene* MainLayer::scene()
{
	//场景转换
	CCScene *scene = CCScene::create();
	CCNodeLoaderLibrary *lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	CCLog("scene");
	lib->registerCCNodeLoader("Main", MainLayerLoader::loader());
	CCLog("scene2");
	CCBReader *reader = new CCBReader(lib);
	CCLog("scene3");
	CCNode *node = reader->readNodeGraphFromFile("Main1.ccbi", scene);
	CCLog("scene4");
	reader->release(); //注意手动释放内存
	if (node!=NULL)
	{
		scene->addChild(node,-2); //将node 添加到scene中
		/*CCBAnimationManager* animationManager = (CCBAnimationManager*)node->getUserObject();
		animationManager->runAnimationsForSequenceNamed("Info");*/
	}
	return scene;
	//CCScene * scene = NULL;
 //   do 
 //   {
 //       // 'scene' is an autorelease object
 //       scene = CCScene::create();
 //       CC_BREAK_IF(! scene);

 //       // 'layer' is an autorelease object
	//	MainLayer *layer = MainLayer::create();
 //       CC_BREAK_IF(! layer);

 //       // add layer as a child to scene
 //       scene->addChild(layer);
 //   } while (0);

 //   // return the scene
 //   return scene;
}
bool MainLayer::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());
		setTouchEnabled(true);
		CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
		pLabel->setString("It's a test");
		pLabel->setPosition(ccp(300,300));
		this->addChild(pLabel,10);
		CCSprite *sprite = CCSprite::create("CloseNormal.png");
		sprite->setPosition(ccp(200,200));
		this->addChild(sprite);
        bRet = true;
    } while (0);

    return bRet;
}
SEL_MenuHandler MainLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget,const char * pSelectorName){

	//Bind Menu Events，绑定一个menu，点击方法是press，以下同理

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "buttonPressed",MainLayer::buttonPressed);
	//CCB_SELECTORRESOLVER_CCMENUITEM_GLUE\

	return NULL;

}

SEL_CCControlHandler MainLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName){

	//CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "buttonPressed",MainLayer::buttonPressed);

	return NULL;

}
bool MainLayer::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "sprite1", CCSprite*, msprite);
	//CCLog("assign2");
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"mylabel",CCLabelTTF*,this->label);
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"msprite",CCSprite*,this->my);
	return true;
}

