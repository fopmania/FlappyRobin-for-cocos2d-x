//
//  SplashScene.cpp
//  SimpleFlappyRobin
//
//  Created by ScreenCast on 16/06/14.
//
//

#include "SplashScene.h"

#include "Constants.h"
#include "GameManager.h"
#include "Robin.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();
	
    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
		{
        return false;
		}
	
	char FileName[32];
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	GameManager::Instance()->SetUpScaleFactors();
	
//	GETFILENAME(FileName, 32, "BG", ".png");
	auto bgSprite = Sprite::create(kFileBG);
	SCALENODE_XY(bgSprite);
	bgSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	bgSprite->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(bgSprite, kindexBG);
	
//	GETFILENAME(FileName, 32, "Floor", ".png");
	auto floorSprite = Sprite::create(kFileFloor);
	SCALENODE_XY(floorSprite);
	floorSprite->setPosition(Vec2(visibleSize.width / 2, 0.0));
	floorSprite->setAnchorPoint(Vec2(0.5, 0.0));
	this->addChild(floorSprite, kindexFloor);
	
//	GETFILENAME(FileName, 32, "Robin", ".png");
	auto robin = Robin::createWithFileName(kFileRobin);
	SCALENODE_Y(robin);
	this->addChild(robin, kindexRobin);
	robin->setPosition(Vec2(visibleSize.width / 4 , visibleSize.height / 2));
	
//	GETFILENAME(FileName, 32, "Cloud", ".png");
	auto cloud1 = Sprite::create(kFileCloud);
	SCALENODE_Y(cloud1);
	this->addChild(cloud1, kindexRobin);
	cloud1->setPosition(SCALEPOS(400,550));
	
//	GETFILENAME(FileName, 32, "Cloud", ".png");
	auto cloud2 = Sprite::create(kFileCloud);
	SCALENODE_Y(cloud2);
	this->addChild(cloud2, kindexRobin);
	cloud2->setPosition(SCALEPOS(700,500));

	Label *theLabel = Label::createWithTTF("SIMPLE FLAPPY ROBIN", kFontName,
										   50 * GETSCALEY * GETSCALEFAC);
	theLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 +
							   visibleSize.height / 6));
	theLabel->setColor(Color3B::RED);
	this->addChild(theLabel, kindexRobin);
	
	Label *theLabel2 = Label::createWithTTF("... A Tutorial App By BlueFeverSoft", kFontName,
											30 * GETSCALEY * GETSCALEFAC);
	theLabel2->setPosition(Vec2(visibleSize.width / 2,
								visibleSize.height / 2 - visibleSize.height / 4));
	theLabel2->setColor(Color3B::RED);
	this->addChild(theLabel2, kindexRobin);

	this->scheduleOnce(schedule_selector(SplashScene::RunGameScreen), 4.0f);
	
    return true;
}

void SplashScene::RunGameScreen(float dt){
	GameManager::Instance()->RunScene(kSceneGame);
}















