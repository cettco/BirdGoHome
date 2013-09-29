#include "GameMenu.h"
#include "HelloWorldScene.h"
#include "Levels.h"
#define PTM_RATIO 32.0
#define playPressed 1
#define aboutPressed 2
#define mutePressed 3
void GameMenu::pressed(cocos2d::CCObject* pSender)
{
	CCMenuItemImage *menu = (CCMenuItemImage*)pSender;
	if(menu->getTag()==playPressed)
	{
		CCScene *pscene = Levels::scene();
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,pscene,false));
	}
	//this->i++;
}
CCScene* GameMenu::scene()
{
	//场景转换
	CCScene *scene = CCScene::create();
	CCNodeLoaderLibrary *lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	lib->registerCCNodeLoader("Main", MainLayerLoader::loader());
	CCBReader *reader = new CCBReader(lib);
	CCNode *node = reader->readNodeGraphFromFile("Main1.ccbi", scene);
	reader->release(); //注意手动释放内存
	//CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
	//pLabel->setString
	if (node!=NULL)
	{
		scene->addChild(node,-2); //将node 添加到scene中
		/*CCBAnimationManager* animationManager = (CCBAnimationManager*)node->getUserObject();
		animationManager->runAnimationsForSequenceNamed("Info");*/
	}
	return scene;
}
bool GameMenu::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());
		setTouchEnabled(true);

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("back.mp3",true);
		bRet = true;
	} while (0);

	return bRet;
}
SEL_MenuHandler GameMenu::onResolveCCBCCMenuItemSelector(CCObject * pTarget,const char * pSelectorName){

	//Bind Menu Events，绑定一个menu，点击方法是press，以下同理
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pressed",GameMenu::pressed);
	//CCB_SELECTORRESOLVER_CCMENUITEM_GLUE\

	return NULL;

}

extension::SEL_CCControlHandler GameMenu::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName){

	//CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"buttonPressed",GameMenu::buttonPressed);
	//CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"buttonPressed",GameMenu::buttonPressed);

	return NULL;

}
bool GameMenu::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"sprite1",CCSprite*,this->msprite);
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"mlabel",CCLabelTTF*,this->label);
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"msprite",CCSprite*,this->my);
	return true;
}

