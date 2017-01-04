#include "HelloWorldScene.h"
#include "cocos2d.h"
#include "Constants.h"
#include "GameManager.h"
#include "Robin.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Size visibleSize =  Size(kDesignSizeW, kDesignSizeH);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//Widget* ui = GUIReader::getInstance()->widgetFromJsonFile("equip/SampleChangeEquip.json");
	//ui->setScale(visibleSize.width / 480.0f, visibleSize.height / 320.0f);
	//this->addChild(ui);
	//Button* btnClose = (Button*)Helper::seekWidgetByName(ui, "closebutton");
	//btnClose->addTouchEventListener(this, toucheventselector(HelloWorld::CloseButtonTouch));

	MenuItemImage *pCloseItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
//   pCloseItem->setScale(visibleSize.width / 960.0f, visibleSize.height / 640.0f);
    SCALENODE_Y(pCloseItem);
	pCloseItem->setPosition(Point(origin.x + visibleSize.width - pCloseItem->getContentSize().width*pCloseItem->getScale() / 2,
		origin.y + pCloseItem->getContentSize().height*pCloseItem->getScale() / 2));
    
    Menu* pMenu = Menu::create(pCloseItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu, kindexFloor+1);

    float sf = 1.0; //GETSCALEY * GETSCALEFAC;
	const float LabelFontSize = 40 * sf;
	const float ScorePositionX = 24 * sf;
	const float ScorePositionY = 12 * sf;
	const float SettingsGap = 24 * sf;

	auto bgSprite = Sprite::create(kFileBG);
	bgSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
//    bgSprite->setScale(visibleSize.width / kDesignSizeW, visibleSize.height / kDesignSizeH);
    SCALENODE_Y(bgSprite);
//	bgSprite->setScale(visibleSize.width / 960.0f, visibleSize.height / 640.0f);
	bgSprite->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(bgSprite, kindexBG);

	//char FileName[32];
	//GETFILENAME(FileName, 32, "BG", ".png");
	auto bgFloor = Sprite::create(kFileFloor);
	bgFloor->setPosition(Vec2(visibleSize.width / 2, 0.0));
//    bgFloor->setScale(visibleSize.width / kDesignSizeW, visibleSize.height / kDesignSizeH);
	SCALENODE_Y(bgFloor);
	bgFloor->setAnchorPoint(Vec2(0.5, 0.0));
	this->addChild(bgFloor, kindexFloor);
	_floorBottom = bgFloor->getBoundingBox().size.height / 2;

	_robin = Robin::createWithFileName(kFileRobin);
//    _robin->setScale(visibleSize.width / kDesignSizeW, visibleSize.height / kDesignSizeH);
    SCALENODE_Y(_robin);
    CCLOG("Robin BBox Height = %f", ((cocos2d::Rect)_robin->getBoundingBox()).size.height);
	this->addChild(_robin, kindexRobin);
	_robin->Reset();
	_robin->SetParams(visibleSize.height);
	_robin->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 2));
    cocos2d::Rect rect = _robin->getBoundingBox();
    

//    _robin->setScale(<#float scale#>)
//    _robin->setBoun
//    ((cocos2d::Rect)_robin->getBoundingBox())

	_scoreLabel = AddLabel(LabelFontSize, "Score 0", Vec2(0.0, 1.0), Vec2(ScorePositionX, visibleSize.height - ScorePositionY));
	_highScoreLabel = AddLabel(LabelFontSize, "Best 0", Vec2(0.0, 1.0), Vec2(ScorePositionX, visibleSize.height - ScorePositionY - _scoreLabel->getBoundingBox().size.height));
	_gameOverLabel = AddLabel(LabelFontSize, "Game Over", Vec2(0.5, 0.5), Vec2(visibleSize.width/2, visibleSize.height /2 ));
	_startLabel = AddLabel(LabelFontSize, "Tap The Scrren To Start", Vec2(0.5, 0.5), Vec2(visibleSize.width / 2, visibleSize.height *3/5));
	_settingsLabel = AddLabel(LabelFontSize, "SETTINGS", Vec2(1.0, 1.0), Vec2(visibleSize.width - SettingsGap, visibleSize.height - SettingsGap));
//	_exitLabel = AddLabel(LabelFontSize, "EXIT", Vec2(1.0, 0.0),
//		Vec2(visibleSize.width - SettingsGap, SettingsGap));

	_gameOverLabel->setVisible(false);

	updateHighScoreLabel();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	_gameOver = true;
	_acceptTouches = true;
	_gameTime = 0;
	_middleY = visibleSize.height / 2;
	_lastSpawnTime = 0;
	_nextSpawnTime = 0.2;
	_tubes = Vector<Tube*>{30};
	CreateClouds();
    _gameScore = 0;

	schedule(schedule_selector(HelloWorld::gameUpdate));
    
   


	return true;
}
void HelloWorld::CloseButtonTouch(Ref* pSender, TouchEventType type)
{
	switch(type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		Director::getInstance()->end();
		break;
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	}
}


void HelloWorld::updateScoreLabel(){
	char ScoreString[64];
	sprintf(ScoreString, "Score %d", _gameScore);
	_scoreLabel->setString(ScoreString);
}


void HelloWorld::updateHighScoreLabel(){
	char ScoreString[64];
    sprintf(ScoreString, "Best %d", GameManager::Instance()->GetHighScore());
	_highScoreLabel->setString(ScoreString);
}



void HelloWorld::gameUpdate(float dt) {
	// CCLOG("HelloWorld::gameUpdate dt:%f",dt);
	if (_gameOver == false) {
		_gameTime += dt;
		_lastSpawnTime += dt;
		if (_lastSpawnTime > _nextSpawnTime) {
			SetSpawnTime();
			SpawnNewTubes();
		}
		if (_robin->getPositionY() < _floorBottom) {
			_gameOver = true;
		}
		else {
			for (auto tube : this->_tubes){
                
                
//                if (_robin->getBoundingBox().intersectsRect(tube->boundingBox())){
				if (_robin->TubeCollisionBox().intersectsRect(tube->boundingBox())){
					_gameOver = true;
					break;
				}
				else{
					if (tube->State == kTubeStateActive && tube->Scored == false){
						if (tube->getBoundingBox().origin.x + tube->getBoundingBox().size.width <
							_robin->getBoundingBox().origin.x){
							tube->Scored = true;
                            if(tube->pairTube != NULL){
                                tube->pairTube->Scored = true;
                            }
                                
							_gameScore += 1;
							GameManager::Instance()->PlayEffect(kEffectSuccess);
						}
					}
				}
			}
		}

		updateScoreLabel();

		if (_gameOver == false)
		{
			_robin->Update(dt);
		}
		else{
			GameOver();
		}
	}
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
	//CCLOG("HelloWorld::onTouchBegan x:%f y:%f", touch->getLocation().x, touch->getLocation().y);
	//CCLOG("gameOver = %d", _gameOver);
	if (!_acceptTouches)		return	false;

	Point tp = Point(touch->getLocation().x, touch->getLocation().y);
	if (_settingsLabel->getBoundingBox().containsPoint(tp)){
		GameManager::Instance()->RunScene(kSceneSettings);
        return  true;
	}


	if (_gameOver == true) {
		StartGame();
        return  true;
	}
	else {
		_robin->SetStartSpeed();
	}
    GameManager::Instance()->PlayEffect(kEffectJump);
	return true;
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}



void HelloWorld::AddCloud(const float speed, const cocos2d::Vec2 position, const float scale, const int zIndex, char *fileName) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	BGObject *cloud = BGObject::createWithFileName(fileName);
	cloud->SetSpeedAndWidth(speed, visibleSize.width);
	cloud->cocos2d::Node::setPosition(position);
	SCALENODE_Y(cloud);
	this->addChild(cloud, zIndex);
	_clouds.pushBack(cloud);
}

void HelloWorld::StartClouds() {
	for (auto cloud : this->_clouds) {
		cloud->Start();
	}
	for (auto tube : this->_tubes) {
		tube->Stop();
	}

}

void HelloWorld::StopClouds() {
	for (auto cloud : this->_clouds) {
		cloud->Stop();
	}
	for (auto tube : this->_tubes) {
		tube->stopAllActions();
	}
}

void HelloWorld::CreateClouds() {
	_clouds = Vector<BGObject*>{30};
	char FileName[32];
//	GETFILENAME(FileName, 32, "Cloud", ".png");
	sprintf(FileName, kFileCloud);

	AddCloud(kCloudSpeedSlow, Vec2(700, 610), kCloudScaleSlow, kindexCloudSlow, FileName);
	AddCloud(kCloudSpeedSlow, Vec2(150, 570), kCloudScaleSlow, kindexCloudSlow, FileName);

	AddCloud(kCloudSpeedFast, Vec2(150, 300), kCloudScaleFast, kindexCloudFast, FileName);
	AddCloud(kCloudSpeedFast, Vec2(400, 500), kCloudScaleFast, kindexCloudFast, FileName);
	AddCloud(kCloudSpeedFast, Vec2(880, 400), kCloudScaleFast, kindexCloudFast, FileName);

	sprintf(FileName, kFileMount);
//	GETFILENAME(FileName, 32, "Mount", ".png");
	AddCloud(kMountSpeed, Vec2(300, 170), kMountScale, kindexMount, FileName);
	AddCloud(kMountSpeed, Vec2(800, 170), kMountScale, kindexMount, FileName);

	sprintf(FileName, kFileTree);
//	GETFILENAME(FileName, 32, "Tree", ".png");
	AddCloud(kTreeSpeed, Vec2(128, 72), kTreeScale, kindexTree, FileName);
	AddCloud(kTreeSpeed, Vec2(624, 72), kTreeScale, kindexTree, FileName);
	AddCloud(kTreeSpeed, Vec2(864, 72), kTreeScale, kindexTree, FileName);
}


void HelloWorld::SetSpawnTime() {
	_lastSpawnTime = 0;
	_nextSpawnTime = (float)(rand() % kTubeSpawnTimeVariance) / 10 + kTubeSpawnMinTime;
}

void HelloWorld::SpawnNewTubes() {
	int ourChance = rand() % 3 + 1;

	while (1) {
		if (_lastTubeType == kTubeTypeUpper && ourChance == 1) {
			ourChance = rand() % 3 + 1;
		}
		else if (_lastTubeType == kTubeTypeLower && ourChance == 2) {
			ourChance = rand() % 3 + 1;
		}
		else if (_lastTubeType == kTubeTypePair && ourChance == 3) {
			ourChance = rand() % 3 + 1;
		}
		else {
			break;
		}
	}

	if (ourChance == 1) {
		SpawnUpperOrLower(true);
	}
	else if (ourChance == 2) {
		SpawnUpperOrLower(false);
	}
	else {
		SpawnTubePair();
	}
}


void HelloWorld::SpawnUpperOrLower(bool isUpper) {
	_lastTubeType = isUpper == true ? kTubeTypeUpper : kTubeTypeLower;

	int YMax = isUpper == true ? _middleY : kSingleGapTop;
	int YMin = isUpper == true ? kSingleGapBottom : _middleY;

	if (isUpper == false) {
		if (YMax - _lastGetUnderY > kTubeMaxUpPixels) {
			YMax = _lastGetUnderY + kTubeMaxUpPixels;
		}
	}

	int YRange = abs(YMax - YMin);
	int Ypos = YMax - rand() % YRange;

	if (isUpper) {
		_lastGetUnderY = Ypos;
	}
	else {
		_lastGetUnderY = _middleY;
	}
	SpawnATube(isUpper, Ypos);
}


void HelloWorld::SpawnTubePair() {
	_lastTubeType = kTubeTypePair;

	int Gap = kDoubleGapMin + (rand() % (int)(kDoubleGapMax - kDoubleGapMin));
	int YRange = kDoubleGapTop - Gap - kDoubleGapBottom;
	int TopY = kDoubleGapTop - (rand() % YRange);
	int BottomY = TopY - Gap;

	_lastGetUnderY = TopY;

	SpawnATube(true, TopY)->setPair(SpawnATube(false, BottomY));
}


Tube *HelloWorld::SpawnATube(bool isUpper, float Ypos) {
	Tube *tube = getNextTube();

	if (isUpper) {
		tube->setAnchorPoint(Vec2(0.5, 0));
		tube->setFlippedY(false);
	}
	else {
		tube->setAnchorPoint(Vec2(0.5, 1));
		tube->setFlippedY(true);
	}

	tube->setPositionY(Ypos);
    SCALENODE_Y(tube);
	tube->Start();
    return tube;
}


Tube *HelloWorld::getNextTube() {
	for (auto tube : _tubes) {
		if (tube->State == kTubeStateInActive) {
			return tube;
		}
	}
	//char FileName[32];
	//GETFILENAME(FileName, 32, "Tube", ".png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Tube *newTube = Tube::createWithFileName(kFileTube);
	SCALENODE_Y(newTube);
	newTube->Initialise(kTreeSpeed, visibleSize.width);
	this->addChild(newTube, kindexTube);
	_tubes.pushBack(newTube);
	return newTube;
}


void HelloWorld::StartGame(){
	CCLOG("StartGame");
    _gameScore = 0;
    updateScoreLabel();
	_startLabel->setVisible(false);
    _robin->setPositionY(_middleY);
	_robin->State = kRobinStateMoving;
	_robin->setPositionY(_middleY);
	_gameOver = false;
	StartClouds();
    
    GameManager::Instance()->StartBGMusic();
    
}
void HelloWorld::StopGame(){
	_nextSpawnTime = 0.2;
	StopClouds();
    GameManager::Instance()->StopBGMusic();
}
void HelloWorld::GameOver(){
	GameManager::Instance()->PlayEffect(kEffectExplosion);
	_gameOverLabel->setVisible(true);
	_acceptTouches = false;
	_robin->Reset();
	GameManager::Instance()->SetHighScore(_gameScore);
	StopGame();
	scheduleOnce(schedule_selector(HelloWorld::ReEnableAfterGameOver), 1.5f);
    GameManager::Instance()->StopBGMusic();
}
void HelloWorld::ReEnableAfterGameOver(float dt){
	updateHighScoreLabel();
	_gameOverLabel->setVisible(false);
	_startLabel->setVisible(true);
	_acceptTouches = true;
}




cocos2d::Label* HelloWorld::AddLabel(const float fontSize, const char *text, const cocos2d::Vec2 ancher, const cocos2d::Vec2 poosition){
	Label *theLabel = Label::createWithTTF(text, kFontName, fontSize);
	theLabel->setAnchorPoint(ancher);;
	theLabel->setPosition(poosition);
	theLabel->setColor(Color3B::RED);
	this->addChild(theLabel, kindexRobin);
	return theLabel;
}
