//
//  SettingsScene.h
//  SimpleFlappyRobin
//
//  Created by ScreenCast on 16/06/14.
//
//

#ifndef __SimpleFlappyRobin__SettingsScene__
#define __SimpleFlappyRobin__SettingsScene__


#include "cocos2d.h"

class SettingsScene : public cocos2d::Layer
{
private:
	
	cocos2d::Label *_backLabel;
	cocos2d::Label *_musVolplusLabel;
	cocos2d::Label *_musVolMinusLabel;
	cocos2d::Label *_effVolPlusLabel;
	cocos2d::Label *_effVolMinusLabel;
	cocos2d::Label *_effValueLabel;
	cocos2d::Label *_musicValueLabel;

	cocos2d::Label* AddLabel(const float fontSize, const char *text,
							 const cocos2d::Vec2 anchor, const cocos2d::Vec2 position);
	void AddLabelVoid(const float fontSize, const char *text,
							 const cocos2d::Vec2 anchor, const cocos2d::Vec2 position);

	void SetLabelValues();
	void IncVol(const int type, const int inc);

	
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(SettingsScene);
	
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	
	
};

#endif /* defined(__SimpleFlappyRobin__SettingsScene__) */
