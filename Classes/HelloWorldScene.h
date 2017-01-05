#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "Robin.h"
#include "BGObject.h"
#include "Tube.h"

using namespace cocos2d;
using namespace ui;
using namespace cocostudio;

class HelloWorld : public cocos2d::Layer
{
private :
	Robin *_robin;

	void gameUpdate(float dt);

	bool _gameOver;
	float _floorBottom;

	bool _acceptTouches;

	cocos2d::Vector<BGObject*> _clouds;
	cocos2d::Vector<Tube*> _tubes;
	cocos2d::Label *_scoreLabel;
	cocos2d::Label *_highScoreLabel;
//	cocos2d::Label *_exitLabel;
	cocos2d::Label *_startLabel;
	cocos2d::Label *_gameOverLabel;
	cocos2d::Label *_settingsLabel;
    cocos2d::MenuItemImage   *_close;


	float _nextSpawnTime;
	float _lastSpawnTime;
	float _lastGetUnderY;
	float _gameTime;
	int _lastTubeType;
	float _middleY;
	int		_gameScore;


	void AddCloud(const float speed, const cocos2d::Vec2 position, const float scale, const int zIndex, char *fileName);
	void StartClouds();
	void StopClouds();
	void CreateClouds();


	void SetSpawnTime();
	void SpawnNewTubes();
	void SpawnUpperOrLower(bool isUpper);
	void SpawnTubePair();
	Tube *SpawnATube(bool isUpper, float Ypos);
	Tube *getNextTube();

	void StartGame();
	void StopGame();
	void GameOver();
	void ReEnableAfterGameOver(float dt);

	cocos2d::Label* AddLabel(const float fontSize, const char *text,
						const cocos2d::Vec2 ancher, const cocos2d::Vec2 poosition);

	void updateScoreLabel();
	void updateHighScoreLabel();

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
	void CloseButtonTouch(Ref* pSender, TouchEventType type);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif // __HELLOWORLD_SCENE_H__
