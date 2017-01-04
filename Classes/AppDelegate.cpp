#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameManager.h"
#include "Constants.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
    GameManager::Instance()->Uninit();
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    
    GLView::setGLContextAttrs(glContextAttrs);
}


bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Simple Flappy Robbin");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    GameManager::Instance()->Init();
    
	GameManager::Instance()->LateInit();

    GameManager::Instance()->SetUpScaleFactors();
    
    float fact = GameManager::Instance()->GetScaleFactor();
    CCLOG("ScaleFactor = %f", fact);
    director->setContentScaleFactor(fact);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    // a bug in DirectX 11 level9-x on the device prevents ResolutionPolicy::NO_BORDER from working correctly
    glview->setDesignResolutionSize(kDesignSizeW, kDesignSizeH, ResolutionPolicy::SHOW_ALL);
#else
    glview->setDesignResolutionSize(kDesignSizeW, kDesignSizeH, ResolutionPolicy::EXACT_FIT);
#endif
    CCLOG("DesignSizeW = %d, kDesignSizeH = %d", kDesignSizeW, kDesignSizeH);
    
    // Enable Remote Console
    auto console = director->getConsole();
    console->listenOnTCP(5678);
    
/*
    auto scene = HelloWorld::createScene();
    director->runWithScene(scene);
	*/
    
	GameManager::Instance()->RunScene(kSceneSplash);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	// if you use SimpleAudioEngine, it must be pause
	//    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
