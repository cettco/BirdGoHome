#include "Level1.h"
#include "HelloWorldScene.h"
#include "GameMenu.h"
#include "Levels.h"
#include "Level2.h"
#define PTM_RATIO 32.0
void Level1::pressed(cocos2d::CCObject* pSender)
{
	CCMenuItemImage *menu = (CCMenuItemImage*)pSender;
	switch (menu->getTag())
	{
		CCLog("tag %d",menu->getTag());
	case 10:
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,Level1::scene(),false));
	case -1:
		initBody();
	case 0:
		CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInL::create(1,Levels::scene()));
		break;
	case 1:
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,Levels::scene(),false));
		break;
	case 2:
		CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInL::create(1,Level1::scene()));
		break;
	case 3:
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,Level2::scene(),false));
		break;
	}
}
CCScene* Level1::scene()
{
	//场景转换
	CCScene *scene = CCScene::create();
	CCNodeLoaderLibrary *lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	lib->registerCCNodeLoader("Level1", Level1LayerLoader::loader());
	CCBReader *reader = new CCBReader(lib);
	CCNode* node = reader->readNodeGraphFromFile("Level11.ccbi", scene);
	reader->release(); //注意手动释放内存
	if (node!=NULL)
	{
		scene->addChild(node,-10,1); //将node 添加到scene中
		CCBAnimationManager*animationManager = (CCBAnimationManager*)node->getUserObject();
		//animationManager->runAnimationsForSequenceNamed("over");
	}
	return scene;
}
bool Level1::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(! CCLayer::init());
		setTouchEnabled(true);
		this->size = CCDirector::sharedDirector()->getWinSize();
		initWorld();
		this->addChild(layer,10);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("back.mp3",true);
		schedule(schedule_selector(Level1::setMTime),1.0f);
		scheduleUpdate();
		bRet = true;
	} while (0);

	return bRet;
}
void Level1::setMTime(float dt)
{
	char mTime[10]={};
	sprintf(mTime,"%d",time);
	timeLabel->setString(mTime);
	time--;
}
void Level1::initWorld()
{
	b2Vec2 gravity;
	gravity.Set(0,-10.0f);
	this->world = new b2World(gravity);
	bool doSleep = true;
	this->world->SetAllowSleeping(doSleep);
	this->world->SetContinuousPhysics(true);

}
void Level1::initBody()
{
	createStaticBody(obstacle1,obstacle1->getPosition().x,obstacle1->getPosition().y);
	createStaticBody(obstacle2,obstacle2->getPosition().x,obstacle2->getPosition().y);
}
void Level1::createStaticBody(CCSprite*sprite,float x,float y)
{
	b2Body *body;
	b2BodyDef bodyDef; 
	bodyDef.type = b2_staticBody;
	//bodyDef.bullet = true; 
	//sprite->setAnchorPoint(CCPointZero);
	bodyDef.position.Set(sprite->getPosition().x/PTM_RATIO,sprite->getPosition().y/PTM_RATIO); 
	bodyDef.userData = sprite; 

	body = this->world->CreateBody(&bodyDef); 
	body->SetAwake(true);
	b2FixtureDef boxDef;
	b2PolygonShape box; 
	boxDef.shape = &box;
	CCPoint spritePosition = sprite->getPosition();
	box.SetAsBox(sprite->getContentSize().width/2/PTM_RATIO,sprite->getContentSize().height/2/PTM_RATIO);
	body->CreateFixture(&box,0.5f);
}
void Level1::createDynamicBody(b2Body* body,CCSprite*sprite,float x,float y,b2Vec2 vec)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody; 
	bodyDef.bullet = true; 
	bodyDef.position.Set(x,y); 
	bodyDef.userData = sprite; 

	birdBody = this->world->CreateBody(&bodyDef);
	birdBody->SetActive(true); 

	b2CircleShape circle; 
	circle.m_radius = 15.0/PTM_RATIO; 

	b2FixtureDef ballShapeDef; 
	ballShapeDef.shape = &circle; 
	ballShapeDef.density = 0.8f; 
	ballShapeDef.restitution = 0.8f; 
	ballShapeDef.friction = 0.99f; 
	birdBody->CreateFixture(&ballShapeDef);
	birdBody->ApplyForce(vec,birdBody->GetWorldCenter());
}
void Level1::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	if(i==0)
	{
		initBody();
		i=1;
	}
	birdCenter = bird->getPosition();
	CCTouch *touch=(CCTouch*)pTouches->anyObject();
	CCPoint pt1=touch->getLocationInView();
	pt1=CCDirector::sharedDirector()->convertToGL(pt1);
	if(bird->boundingBox().containsPoint(pt1))
	{
		CCLog("can");
		canFly = 1;
		//bird->setPosition(pt1);
	}
	else{
		CCLog("not");
		canFly = 0;
		return;
	}
}
void Level1::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	if(canFly==0)return;
	CCTouch *touch=(CCTouch*)pTouches->anyObject();
	CCPoint pt1=touch->getLocationInView();
	pt1=CCDirector::sharedDirector()->convertToGL(pt1);
	if(bird->boundingBox().containsPoint(pt1))
	{
		canFly = 1;
		float distance = ccpDistance(pt1,birdCenter);
		float height = bird->boundingBox().size.height;
		if(distance<height)
		{
			bird->setPosition(pt1);
			if(turn==1)
			{
				layer->createWithPoints(bird->getPosition(),this->s1l->getPosition(),this->s1r->getPosition());
			}
		}
		else
		{
			CCLog("else");
			float x = height/distance*(pt1.x-birdCenter.x)+birdCenter.x;
			float y = height/distance*(pt1.y-birdCenter.y)+birdCenter.y;
			bird->setPosition(ccp(x,y));
			layer->createWithPoints(bird->getPosition(),this->s1l->getPosition(),this->s1r->getPosition());
		}
	}
	else
	{
		return;
	}
	if(turn==1)
	{
		layer->createWithPoints(bird->getPosition(),this->s1l->getPosition(),this->s1r->getPosition());
	}
	if(turn==2)
	{
		layer->createWithPoints(bird->getPosition(),this->s2l->getPosition(),this->s2r->getPosition());
	}

	/*CCLayer *line = LineLayer::createWithPoints(_currBird->getPosition(), ccp(_slingshot->getPositionX() - 10, FLOOR_HEIGHT + _slingshot->getPositionY() * 0.81f), ccp(_slingshot->getPositionX() + 10, FLOOR_HEIGHT + _slingshot->getPositionY() * 0.81f));  
	addChild(line, 1000, 77);  */
}
void Level1::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	if(canFly==0)return;
	CCTouch *touch=(CCTouch*)pTouches->anyObject();
	CCPoint pt1=touch->getLocationInView();
	pt1=CCDirector::sharedDirector()->convertToGL(pt1);
	if(canFly==0)
	{
		return;
	}
	else
	{
		canFly =0;
	}
	bird->setPosition(pt1);
	float x = pt1.x;
	float y = pt1.y;
	float distance = ccpDistance(pt1,birdCenter);
	float cos=(pt1.x-birdCenter.x)/distance,sin=(pt1.y-birdCenter.y)/distance;
	createDynamicBody(birdBody,bird,x/PTM_RATIO,y/PTM_RATIO,b2Vec2(-3.0f*distance*cos,-3.0f*distance*sin));
	if(turn==1)
	{
		layer->createWithPoints(s1l->getPosition(),s1l->getPosition(),s1r->getPosition());
	}
	if(turn==2)
	{
		layer->createWithPoints(s2l->getPosition(),s2l->getPosition(),s2r->getPosition());
	}
}
void Level1::update(float dt)
{
	int velocityIterations = 8; 
	int positionIterations = 1;

	world->Step(0.03f, velocityIterations, positionIterations); 
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) 
	{ 
		if (b->GetUserData() != NULL) 
		{ 
			CCSprite *sprite = (CCSprite*)b->GetUserData(); 
			sprite->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) ); 
			sprite->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) ); 
		} 
	}
	if(time==-1)
	{
		time=-2;
		this->unschedule(schedule_selector(Level1::setMTime));
		CCNode*node= this->getParent()->getChildByTag(1);
		CCBAnimationManager*animationManager = (CCBAnimationManager*)node->getUserObject();
		if(endLayer==NULL)
		{
			CCLog("null");
		}
		endLayer->setVisible(true);
		animationManager->runAnimationsForSequenceNamed("over");
		star1->setVisible(false);
		star2->setVisible(false);
		star3->setVisible(false);
	}
	if(birdBody!=NULL)
	{
		CCSprite *birdsprite =(CCSprite*)birdBody->GetUserData();
		if(birdsprite->boundingBox().intersectsRect(this->shooter2->boundingBox()))
		{
			if(turn!=2)
			{
				this->world->DestroyBody(birdBody);
				birdBody=NULL;
				bird->setPosition(s2l->getPosition());
				canFly = 1;
				turn = 2;
			}
		}
		if(birdsprite->boundingBox().intersectsRect(this->shooter1->boundingBox()))
		{
			if(turn!=1)
			{
				this->world->DestroyBody(birdBody);
				birdBody=NULL;
				bird->setPosition(s1l->getPosition());
				canFly = 1;
				turn = 1;
			}
		}
		if(birdsprite->boundingBox().intersectsRect(this->home->boundingBox()))
		{
			this->world->DestroyBody(birdBody);
			birdBody=NULL;
			bird->setVisible(false);
			CCNode*node= this->getParent()->getChildByTag(1);
			CCBAnimationManager*animationManager = (CCBAnimationManager*)node->getUserObject();
			endLayer->setVisible(true);
			animationManager->runAnimationsForSequenceNamed("over");
			this->unschedule(schedule_selector(Level1::setMTime));
			if(time>=10)
			{
				star1->setVisible(true);
				star2->setVisible(true);
				star3->setVisible(true);
			}
			if(time<10&&time>=7)
			{
				star1->setVisible(true);
				star2->setVisible(true);
				star3->setVisible(false);
			}
			if(time<7&&time>=3)
			{
				star1->setVisible(true);
				star2->setVisible(false);
				star3->setVisible(false);
			}
			if(time<3)
			{
				star1->setVisible(false);
				star2->setVisible(false);
				star3->setVisible(false);
			}
		}
	}
}
//void Level1::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
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
SEL_MenuHandler Level1::onResolveCCBCCMenuItemSelector(CCObject * pTarget,const char * pSelectorName){

	//Bind Menu Events，绑定一个menu，点击方法是press，以下同理
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pressed",Level1::pressed);

	return NULL;

}

extension::SEL_CCControlHandler Level1::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName){

	//CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"buttonPressed",Level1::buttonPressed);
	//CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"buttonPressed",Level1::buttonPressed);

	return NULL;

}
bool Level1::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"bird",CCSprite*,this->bird);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"home",CCSprite*,this->home);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"shooter1",CCSprite*,this->shooter1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"shooter2",CCSprite*,this->shooter2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"obstacle1",CCSprite*,this->obstacle1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"obstacle2",CCSprite*,this->obstacle2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"s1l",CCSprite*,this->s1l);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"s1r",CCSprite*,this->s1r);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"s2l",CCSprite*,this->s2l);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"s2r",CCSprite*,this->s2r);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"timeLabel",CCLabelTTF*,this->timeLabel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"star1",CCSprite*,this->star1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"star2",CCSprite*,this->star2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"star3",CCSprite*,this->star3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"EndLayer",CCLayer*,this->endLayer);
	return true;
}

