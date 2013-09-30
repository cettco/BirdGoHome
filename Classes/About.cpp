#include "About.h"
#include "GameMenu.h"
using namespace cocos2d;

CCScene* About::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        About *layer = About::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool About::init()
{
    bool bRet = false;
    do
    {
		CCSprite *background=CCSprite::create("AboutBG.png");
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		background->setPosition(ccp(size.width/2,size.height/2));
		this->addChild(background,-1);
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "back.png",
            "back.png",
            this,
            menu_selector(About::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 100, 600));
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);
        this->addChild(pMenu, 1);

        bRet = true;
    } while (0);

    return bRet;
}

void About::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInL::create(1,GameMenu::scene()));
}

