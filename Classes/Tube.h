#pragma once
#include "cocos2d.h"

class Tube : public cocos2d::Sprite
{
public:
	int State;
	bool Scored;

	static Tube* createWithFileName(char *fileName);

	void Start();
	void Stop();
	void Initialise(const float speed, const float width);


	Tube();
	~Tube();

private:

	void ReachedDestination();

	float _speed;
	float _screenWidth;
	float _xOffSet;

};

