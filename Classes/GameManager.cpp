#include "GameManager.h"
#include "cocos2d.h"
#include "Constants.h"
#include "HelloWorldScene.h"
#include "SettingsScene.h"
#include "SplashScene.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

#define kEXTHD "-HD"
#define kEXTUHD "-UHD"
#define kEXTND "-ND"


#define kNumExplosions	2
#define kNumRobinTap	1
#define kNumSuccess		2

GameManager *GameManager::_Instance = NULL;



void GameManager::RunScene(const int sceneNum){
	Scene *pScene = NULL;
	if (sceneNum == kSceneGame){
		pScene = HelloWorld::createScene();
	}
	else if (sceneNum == kSceneSettings){
		pScene = SettingsScene::createScene();
	}
	else if (sceneNum == kSceneSplash){
		pScene = SplashScene::createScene();
	}
	if (pScene != NULL){
		if (Director::getInstance()->getRunningScene() == NULL){
			Director::getInstance()->runWithScene(pScene);
		}
		else{
			Director::getInstance()->replaceScene(pScene);
		}
	}
}


GameManager *GameManager::Instance() {
	if (!_Instance){
		_Instance = new GameManager;
	}
	return _Instance;
}

float GameManager::GetScaleX(){
	return scaleX;
}
float GameManager::GetScaleY(){
	return scaleY;
}
float GameManager::GetScaleFactor(){
	return scaleFactor;
}

void GameManager::SetUpScaleFactors(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
//	scaleFactor = 1.0;
	_ext = (char*)kEXTHD;

	if (visibleSize.width * visibleSize.height > 960 * 640){
//		scaleFactor = 2.0;
		_ext = (char*)kEXTUHD;
	}
	else if (visibleSize.width * visibleSize.height > 480 * 320){
//		scaleFactor = 0.5;
		_ext = (char*)kEXTND;
	}


	scaleX = visibleSize.width / 960;
	scaleY = visibleSize.height / 640;

	CCLOG("_scaleX:%.2f, _scaleY:%.2f", scaleX, scaleY);
}

void GameManager::GetFileName(char *array, const int len, const char*name, const char *fileExt)
{
	memset(array, 0, sizeof(char)*len);
	sprintf(array, "%s%s%s", name, _ext, fileExt);

}


void GameManager::LateInit(){
	int index = 0;
	for (index = 0; index < kNumExplosions; ++index){
		PreLoadEffect("Explosion", index + 1);
	}
	for (index = 0; index < kNumRobinTap; ++index){
		PreLoadEffect("RobinTap", index + 1);
	}
	for (index = 0; index < kNumSuccess; ++index){
		PreLoadEffect("Success", index + 1);
	}

	_musicVol = 5;
	_effectsVol = 5;

	StartBGMusic();

}


void GameManager::StartBGMusic() {
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume((float)_musicVol / 10);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BGMusic.mp3");
}

void GameManager::PlayEffect(const int num){
	switch (num)
	{
	case kEffectExplosion:
		PlayEffectName("Explosion", kNumExplosions);
		break;
	case kEffectRobinTap:
		PlayEffectName("RobinTap", kNumRobinTap);
		break;
	case kEffectSuccess:
		PlayEffectName("Success", kNumSuccess);
		break;
	}
}

void GameManager::PreLoadEffect(const char* name, const int num){
	char EffectName[32];
	memset(EffectName, 0, sizeof(EffectName));
	sprintf(EffectName, "%s%d.wav", name, num);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(EffectName);
}

void GameManager::PlayEffectName(const char* name, const int num){
	int randnum = rand() % num + 1;
	char EffectName[32];
	memset(EffectName, 0, sizeof(EffectName));
	sprintf(EffectName, "%s%d.wav", name, num);
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume((float)_effectsVol / 10);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(EffectName);
}


int GameManager::GetVol(const int volType){
	if (volType == kVolTypeMusic){
		return _musicVol;
	}
	else if (volType == kVolTypeEffect){
		return	_effectsVol;
	}
}
void GameManager::SetVol(const int volType, const int val){
	if (volType == kVolTypeMusic){
		_musicVol = val;
		CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume((float)_musicVol / 10);
	}
	else if (volType == kVolTypeEffect){
		_effectsVol = val;
		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume((float)_effectsVol / 10);
	}
}



int GameManager::GetHighScore() {
	return _highScore;
}

void GameManager::SetHighScore(const int score) {
	if (score > _highScore) {
		_highScore = score;
	}
}






