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

void GameManager::Init(){
}

void GameManager::Uninit(){
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
	scaleFactor = 1.0;
	_ext = (char*)kEXTHD;
    
    
    float vratio = visibleSize.width/visibleSize.height;
  
    float dH = kDesignSizeH;
//    if(visibleSize.height > 1080)   bH = 1080;
//    if(visibleSize.height > 2160)   bH = 2160;
    
    float rW = vratio*dH;
    

	if (visibleSize.height >= dH){
        auto resourceSize = Size(kDesignSizeW, kDesignSizeH);
//        searchPaths.push_back("hd");
//        searchPaths.push_back("ccs-res/hd");
//        searchPaths.push_back("ccs-res");
//        searchPaths.push_back("Manifests");
		scaleFactor = visibleSize.height/dH;
		_ext = (char*)kEXTUHD;
	}
	else{
//        searchPaths.push_back("ccs-res");
//		scaleFactor = 0.5;
		_ext = (char*)kEXTND;
	}


	scaleX = visibleSize.width / kDesignSizeW;
	scaleY = visibleSize.height / kDesignSizeH;

	CCLOG("_scaleX:%.2f, _scaleY:%.2f", scaleX, scaleY);
}

void GameManager::GetFileName(char *array, const int len, const char*name, const char *fileExt)
{
	memset(array, 0, sizeof(char)*len);
	sprintf(array, "%s%s%s", name, _ext, fileExt);

}


void GameManager::LateInit(){
//	int index = 0;
//	for (index = 0; index < kNumExplosions; ++index){
//		PreLoadEffect("Explosion", index + 1);
//	}
//	for (index = 0; index < kNumRobinTap; ++index){
//		PreLoadEffect("RobinTap", index + 1);
//	}
//	for (index = 0; index < kNumSuccess; ++index){
//		PreLoadEffect("Success", index + 1);
//	}
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(kEffectJump);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(kEffectClick);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(kEffectSuccess);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(kEffectExplosion);
    
    
    int volM = UserDefault::getInstance()->getIntegerForKey(US_VOL_MUSIC, 3);
    if( volM < 0 || volM > 5)   volM = 3;
    SetVol(kVolTypeMusic, volM);
    
    int volE = UserDefault::getInstance()->getIntegerForKey(US_VOL_EFFECT, 3);
    if( volE < 0 || volE > 5)   volE = 3;
    SetVol(kVolTypeEffect, volE);
    
    _highScore = UserDefault::getInstance()->getIntegerForKey(US_HIGH_SCORE, 0);
}


void GameManager::StartBGMusic() {
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume((float)_musicVol / 10);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(kFileBGM);
}

void GameManager::StopBGMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}


//void GameManager::PlayEffect(const int num){
//	switch (num)
//	{
//	case kEffectExplosion:
//		PlayEffectName("Explosion", kNumExplosions);
//		break;
//	case kEffectRobinTap:
//		PlayEffectName("RobinTap", kNumRobinTap);
//		break;
//	case kEffectSuccess:
//		PlayEffectName("Success", kNumSuccess);
//		break;
//    }
//}
//
//void GameManager::PreLoadEffect(const char* name, const int num){
//	char EffectName[32];
//	memset(EffectName, 0, sizeof(EffectName));
//	sprintf(EffectName, "%s%d.wav", name, num);
//	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(EffectName);
//}

//void GameManager::PlayEffectName(const char* name, const int num){
//	int randnum = rand() % num + 1;
//	char EffectName[32];
//	memset(EffectName, 0, sizeof(EffectName));
//	sprintf(EffectName, "%s%d.wav", name, num);
//	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume((float)_effectsVol / 10);
//	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(EffectName);
//}

void GameManager::PlayEffect(const char* name){
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume((float)_effectsVol / 10);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(name);
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
        UserDefault::getInstance()->setIntegerForKey(US_VOL_MUSIC, _musicVol);
	}
	else if (volType == kVolTypeEffect){
		_effectsVol = val;
		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume((float)_effectsVol / 10);
        UserDefault::getInstance()->setIntegerForKey(US_VOL_EFFECT, _effectsVol);
	}
}


int GameManager::GetHighScore() {
	return _highScore;
}

void GameManager::SetHighScore(const int score) {
	if (score > _highScore) {
		_highScore = score;
        UserDefault::getInstance()->setIntegerForKey(US_HIGH_SCORE, _highScore);
	}
}


void GameManager::SaveSettings(int volM, int volE){
    UserDefault::getInstance()->setIntegerForKey(US_VOL_MUSIC, volM);
    UserDefault::getInstance()->setIntegerForKey(US_VOL_EFFECT, volE);
}




