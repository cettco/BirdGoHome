#include "LineLayer.h"
#include "HelloWorldScene.h"
#include "GameMenu.h"
#include "Levels.h"
#define PTM_RATIO 32.0
//void LineLayer::draw()
//{
//	//CCLayer::draw();
//	/*ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
//	kmGLPushMatrix();
//	glLineWidth(3.0f);
//	world->DrawDebugData();
//	kmGLPopMatrix();
//	if(canFly==1)
//	{
//		CCLog("draw");
//		glLineWidth(4.0f);
//		ccDrawColor4B(255,0,0,255);
//		ccDrawLine( ccpAdd(birdCenter,ccp(bird->getContentSize().width/3,0)), bird->getPosition() );
//		ccDrawLine( ccpAdd(birdCenter,ccp(-bird->getContentSize().width/3,0)), bird->getPosition() );
//	}*/
//}
void LineLayer::createWithPoints(CCPoint start,CCPoint end1,CCPoint end2)
{
	this->start = start;
	this->end1 = end1;
	this->end2 = end2;
}
void LineLayer::draw()
{
	glLineWidth(4.0f);
	ccDrawColor4B(255,0,0,255);
	//ccDrawLine( ccpAdd(point,ccp(x,0)), position );
	//ccDrawLine( ccpAdd(point,ccp(-x,0)),position );
	ccDrawLine(this->start,this->end1);
	ccDrawLine(this->start,this->end2);
}