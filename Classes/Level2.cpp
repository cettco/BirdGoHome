#include "Level2.h"
#include "HelloWorldScene.h"
#include "GameMenu.h"
#include "Levels.h"
#include "Level3.h"
#define PTM_RATIO 32.0
void Level2::pressed(cocos2d::CCObject* pSender)
{
	CCMenuItemImage *menu = (CCMenuItemImage*)pSender;
	switch (menu->getTag())
	{
	case -2:
		CCDirector::sharedDirector()->replaceScene(CCTransitionRotoZoom::create(1,Level2::scene()));
	case -1:
		initBody();
	case 0:
		CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInL::create(1,Levels::scene()));
		break;
	case 1:
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,HelloWorld::scene(),false));
		break;
	case 2:
		CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInL::create(1,Levels::scene()));
		break;
	case 3:
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,Level3::scene(),false));
		break;
	case 4:
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,HelloWorld::scene(),false));
		break;
	case 5:
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,HelloWorld::scene(),false));
		break;
	case 6:
		CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1,HelloWorld::scene(),false));
		break;
	}
}
CCScene* Level2::scene()
{
	//场景转换
	CCScene *scene = CCScene::create();
	CCNodeLoaderLibrary *lib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	lib->registerCCNodeLoader("Level2", Level2LayerLoader::loader());
	CCBReader *reader = new CCBReader(lib);
	CCNode* node = reader->readNodeGraphFromFile("Level21.ccbi", scene);
	reader->release(); //注意手动释放内存
	if (node!=NULL)
	{
		scene->addChild(node,-10,1); //将node 添加到scene中
		CCBAnimationManager*animationManager = (CCBAnimationManager*)node->getUserObject();
		//animationManager->runAnimationsForSequenceNamed("over");
	}
	return scene;
}
bool Level2::init()
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
		schedule(schedule_selector(Level2::setMTime),1.0f);
		scheduleUpdate();
		bRet = true;
	} while (0);

	return bRet;
}
void Level2::setMTime(float dt)
{
	char mTime[10]={};
	sprintf(mTime,"%d",time);
	timeLabel->setString(mTime);
	time--;
}
void Level2::initWorld()
{
	b2Vec2 gravity;
	gravity.Set(0,-10.0f);
	this->world = new b2World(gravity);
	bool doSleep = true;
	this->world->SetAllowSleeping(doSleep);
	this->world->SetContinuousPhysics(true);

	//b2BodyDef groundBodyDef;  
	//groundBodyDef.position.Set(0,0);  
	//groundBody = world->CreateBody(&groundBodyDef);  
	//b2EdgeShape groundBox;
	//// b2PolygonShape groundBox;  
	//b2FixtureDef boxShapeDef;  
	//boxShapeDef.shape = &groundBox;  
	//groundBox.Set(b2Vec2(0,0), b2Vec2(size.width/PTM_RATIO, 0));  
	//groundBody->CreateFixture(&boxShapeDef);  
	//groundBox.Set(b2Vec2(0,0), b2Vec2(0, size.height/PTM_RATIO));  
	//groundBody->CreateFixture(&boxShapeDef);  
	//groundBox.Set(b2Vec2(0, size.height/PTM_RATIO),   
	//	b2Vec2(size.width/PTM_RATIO, size.height/PTM_RATIO));  
	//groundBody->CreateFixture(&boxShapeDef);  
	//groundBox.Set(b2Vec2(size.width/PTM_RATIO,   
	//	size.height/PTM_RATIO), b2Vec2(size.width/PTM_RATIO, 0));  
	//groundBody->CreateFixture(&boxShapeDef); 


}
void Level2::initBody()
{
	createStaticBody(obstacle1,obstacle1->getPosition().x,obstacle1->getPosition().y,0);
	createStaticBody(obstacle2,obstacle2->getPosition().x,obstacle2->getPosition().y,0);
	createStaticBody(obstacle3,obstacle3->getPosition().x,obstacle3->getPosition().y,1);
}
void Level2::createStaticBody(CCSprite*sprite,float x,float y,int n)
{
	if(n==0)
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
	else if(n==1)
	{
		CCLog("static");
		b2Body *body;
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position.Set(sprite->getPosition().x/PTM_RATIO,sprite->getPosition().y/PTM_RATIO); 
		bodyDef.userData = sprite; 

		body = this->world->CreateBody(&bodyDef);
		body->SetActive(true);

		b2CircleShape circle; 
		circle.m_radius = 50.0/PTM_RATIO; 

		b2FixtureDef ballShapeDef;
		ballShapeDef.shape = &circle; 
		ballShapeDef.density = 0.8f; 
		ballShapeDef.restitution = 0.8f; 
		ballShapeDef.friction = 0.99f; 
		body->CreateFixture(&ballShapeDef);
	}
}
void Level2::createDynamicBody(b2Body* body,CCSprite*sprite,float x,float y,b2Vec2 vec)
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
void Level2::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	if(i==0)
	{
		initBody();
		i=1;
	}
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
			float x = height/distance*(pt1.x-birdCenter.x)+birdCenter.x;
			float y = height/distance*(pt1.y-birdCenter.y)+birdCenter.y;
			bird->setPosition(ccp(x,y));
			layer->createWithPoints(bird->getPosition(),this->s1l->getPosition(),this->s1r->getPosition());
		}
	}
	else
	{
		canFly =0;
		return;
	}
	birdCenter = bird->getPosition();
}
void Level2::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
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
	/*if(turn==2)
	{
		layer->createWithPoints(bird->getPosition(),this->s2l->getPosition(),this->s2r->getPosition());
	}*/

	/*CCLayer *line = LineLayer::createWithPoints(_currBird->getPosition(), ccp(_slingshot->getPositionX() - 10, FLOOR_HEIGHT + _slingshot->getPositionY() * 0.81f), ccp(_slingshot->getPositionX() + 10, FLOOR_HEIGHT + _slingshot->getPositionY() * 0.81f));  
	addChild(line, 1000, 77);  */
}
void Level2::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
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
	createDynamicBody(birdBody,bird,x/PTM_RATIO,y/PTM_RATIO,b2Vec2(-5.5f*distance*cos,-5.5f*distance*sin));
	if(turn==1)
	{
		layer->createWithPoints(s1l->getPosition(),s1l->getPosition(),s1r->getPosition());
	}
	/*if(turn==2)
	{
		layer->createWithPoints(s2l->getPosition(),s2l->getPosition(),s2r->getPosition());
	}*/
}
void Level2::update(float dt)
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
		this->unschedule(schedule_selector(Level2::setMTime));
		CCNode*node= this->getParent()->getChildByTag(1);
		CCBAnimationManager*animationManager = (CCBAnimationManager*)node->getUserObject();
		endLayer->setVisible(true);
		animationManager->runAnimationsForSequenceNamed("over");
		star1->setVisible(false);
		star2->setVisible(false);
		star3->setVisible(false);
	}
	if(birdBody!=NULL)
	{
		CCSprite *birdsprite =(CCSprite*)birdBody->GetUserData();
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
			this->unschedule(schedule_selector(Level2::setMTime));
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
SEL_MenuHandler Level2::onResolveCCBCCMenuItemSelector(CCObject * pTarget,const char * pSelectorName){

	//Bind Menu Events，绑定一个menu，点击方法是press，以下同理
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pressed",Level2::pressed);

	return NULL;

}

extension::SEL_CCControlHandler Level2::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName){

	//CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"buttonPressed",Level2::buttonPressed);
	//CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this,"buttonPressed",Level2::buttonPressed);

	return NULL;

}
bool Level2::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
	CCLog("1");
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"bird",CCSprite*,this->bird);
	CCLog("2");
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"home",CCSprite*,this->home);
	CCLog("3");
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"shooter1",CCSprite*,this->shooter1);
	CCLog("4");
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"obstacle1",CCSprite*,this->obstacle1);
	CCLog("5");
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"obstacle2",CCSprite*,this->obstacle2);
	CCLog("6");
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"obstacle3",CCSprite*,this->obstacle3);
	CCLog("7");
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"s1l",CCSprite*,this->s1l);
	CCLog("8");
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"s1r",CCSprite*,this->s1r);
	CCLog("9");
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"timeLabel",CCLabelTTF*,this->timeLabel);
	CCLog("10");
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"star1",CCSprite*,this->star1);
	CCLog("11");
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"star2",CCSprite*,this->star2);
	CCLog("12");
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"star3",CCSprite*,this->star3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"EndLayer",CCLayer*,this->endLayer);
	CCLog("13");
	return true;
}

