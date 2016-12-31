#pragma once

#include "cocos2d.h"

class BGObject : public cocos2d::Sprite
{
public:
	int State;

	static BGObject* createWithFileName(char *fileName);

	void Start();
	void Stop();
	void SetSpeedAndWidth(const float speed, const float width);


	BGObject();
	~BGObject();

private:

	void ReachedDestination();

	float _speed;
	float _screenWidth;
	float _xOffSet;

};

