//
//  SplashScene.h
//  SimpleFlappyRobin
//
//  Created by ScreenCast on 16/06/14.
//
//

#ifndef __SimpleFlappyRobin__SplashScene__
#define __SimpleFlappyRobin__SplashScene__


#include "cocos2d.h"

class SplashScene : public cocos2d::Layer
{
private:
	
	void RunGameScreen(float dt);
	
public:
    
    void onEnter() override ;
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);
	
	
};

#endif /* defined(__SimpleFlappyRobin__SplashScene__) */
