#include "Levels.h"
#include "HelloWorldScene.h"
#include "GameMenu.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#define PTM_RATIO 32.0
void Levels::pressed(cocos2d::CCObject* pSender)
{
	CCMenuItemImage *menu = (CCMenuItemImage*)pSender;
	switch (menu->getTag())
	{
		case 0:
		CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInL::create(1,GameMenu::scene()));
		break;
	case 1:
		CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(1,Level1::scene()));
		break;
	case 2:
		CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(1,Level2::scene()));
		break;
	case 3:
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,Level3::scene(),false));
		break;
	case 4:
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,Level5::scene(),false));
		break;
	case 5:
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,Level4::scene(),false));
		break;
	case 6:
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,HelloWorld::scene(),false));
		break;
	/*case 0:
		CCScene *pscene = GameMenu::scene();
		CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInL::create(1,pscene));
		break;
	case 1:
		CCScene *pscene = HelloWorld::scene();
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,pscene,false));
		break;
	case 2:
		CCScene *pscene = HelloWorld::scene();
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,pscene,false));
		break;
	case 3:
		CCScene *pscene = HelloWorld::scene();
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,pscene,false));
		break;
	case 4:
		CCScene *pscene = HelloWorld::scene();
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,pscene,false));
		break;
	case 5:
		CCScene *pscene = HelloWorld::scene();
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,pscene,false));
		break;
	case 6:
		CCScene *pscene = HelloWorld::scene();
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,pscene,false));
		break;*/
	}
	/*if(menu->getTag()==1)
	{
	CCScene *pscene = HelloWorld::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,pscene,false));
	}*/
	//this->i++;
}
CCScene* Levels::scene()
{
	//场景转换
	CCScene *scene = CCScene::create();
	CCNodeLoaderLibrary *lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	lib->registerCCNodeLoader("Levels", LevelsLayerLoader::loader());
	CCBReader *reader = new CCBReader(lib);
	CCNode *node = reader->readNodeGraphFromFile("Levels1.ccbi", scene);
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
bool Levels::init()
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
		//[self addChild:_ball];

		// Create a world
		//b2Vec2 gravity = b2Vec2(0.0f, -30.0f);
		////bool doSleep =true;
		//_world =new b2World(gravity);
		//_world->SetAllowSleeping(true);
		//_world->SetContinuousPhysics(true);

		//// Create edges around the entire screen
		//b2BodyDef groundBodyDef;
		//groundBodyDef.position.Set(0,0);
		//b2Body *groundBody = _world->CreateBody(&groundBodyDef);
		//b2PolygonShape groundBox;
		//b2FixtureDef boxShapeDef;
		//boxShapeDef.shape =&groundBox;
		////groundBox.SetAsBox
		////groundBox.SetAsBox
		//groundBox.SetAsBox(winSize.width/PTM_RATIO,0, b2Vec2(0, 0),0);
		//groundBody->CreateFixture(&boxShapeDef);
		//groundBox.SetAsBox(winSize.width/PTM_RATIO,0, b2Vec2(0, winSize.height/PTM_RATIO),0);
		//groundBody->CreateFixture(&boxShapeDef);
		//groundBox.SetAsBox(0, winSize.height/PTM_RATIO,b2Vec2(0,0),0);
		//groundBody->CreateFixture(&boxShapeDef);
		//groundBox.SetAsBox(0, 
		//	winSize.height/PTM_RATIO, b2Vec2(winSize.width/PTM_RATIO, 0),0);
		//groundBody->CreateFixture(&boxShapeDef);

		//// Create ball body and shape
		//b2BodyDef ballBodyDef;
		//ballBodyDef.type = b2_dynamicBody;
		//ballBodyDef.position.Set(100/PTM_RATIO, 100/PTM_RATIO);
		//ballBodyDef.userData = _ball;
		//_body = _world->CreateBody(&ballBodyDef);

		//b2CircleShape circle;
		//circle.m_radius =26.0/PTM_RATIO;

		//b2FixtureDef ballShapeDef;
		//ballShapeDef.shape =&circle;
		//ballShapeDef.density =1.0f;
		//ballShapeDef.friction =0.2f;
		//ballShapeDef.restitution =0.8f;
		//_body->CreateFixture(&ballShapeDef);
		//scheduleUpdate();
		bRet = true;
	} while (0);

	return bRet;
}
/*void Levels::update(float dt) 
{ 
int velocityIterations = 8; 
int positionIterations = 1; 

_world->Step(0.03f, velocityIterations, positionIterations); 
for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext()) 
{ 
if (b->GetUserData() != NULL) 
{ 
CCSprite *sprite = (CCSprite*)b->GetUserData(); 
sprite->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) ); 
sprite->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) ); 
} 
} 
}*/ 
//void Levels::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
//{
//	CCLog("touch");
//	CCTouch * touch = (CCTouch*)(pTouches->anyObject());
//	CCPoint location = touch->getLocationInView();
//	location = CCDirector::sharedDirector()->convertToGL(location);
//	this->label->setPosition(ccp(location.x,location.y));
//	/*ccBezierConfig bezier;
//	bezier.controlPoint_1 = ccp(0,0);
//	bezier.controlPoint_2 = ccp(location.x,location.y);
//	bezier.endPosition = ccp(400,50);*/
//	/*glLineWidth(5.0f);
//	glColor4f(1.0,0.0,0.0,1.0);
//	ccDrawLine(ccp(0,0),ccp(location.x,location.y));*/
//	//this->label->setPosition(ccp(location.x,location.y));
//}
SEL_MenuHandler Levels::onResolveCCBCCMenuItemSelector(CCObject * pTarget,const char * pSelectorName){

	//Bind Menu Events，绑定一个menu，点击方法是press，以下同理
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pressed",Levels::pressed);
	//CCB_SELECTORRESOLVER_CCMENUITEM_GLUE\

	return NULL;

}

extension::SEL_CCControlHandler Levels::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName){

	//CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"buttonPressed",Levels::buttonPressed);
	//CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"buttonPressed",Levels::buttonPressed);

	return NULL;

}
bool Levels::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"sprite1",CCSprite*,this->msprite);
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"mlabel",CCLabelTTF*,this->label);
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"msprite",CCSprite*,this->my);
	return true;
}

