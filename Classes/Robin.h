#pragma once
#include "cocos2d.h"

class Robin : public cocos2d::Sprite 
{
public:
	int State;
	static Robin* createWithFileName(char *fileName);
	void Update(float dt);
	void Reset();
	void SetStartSpeed(float addSpeed);
	void SetParams(const float tos);
	cocos2d::Rect TubeCollisionBox();

private:
	float  _speedY;
	float _topOfScreen;
public:
	Robin();
	~Robin();
};

