#include "Tube.h"


#include "Constants.h"
#include "GameManager.h"

USING_NS_CC;

Tube* Tube::createWithFileName(char *fileName) {
	auto sprite = new Tube;
	if (sprite && sprite->initWithFile(fileName)) {
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Tube::Start() {
	this->stopAllActions();

	float distance = _xOffSet + _screenWidth + _xOffSet;
	float time = distance / _speed;
	Vec2 destination = Vec2(-_xOffSet, this->getPositionY());
	this->setPosition(Vec2(_xOffSet + _screenWidth, this->getPositionY()));

	State = kTubeStateActive;

	MoveTo *actionMove = MoveTo::create(time, destination);
	CallFunc *actionMoveDone = CallFunc::create(CC_CALLBACK_0(Tube::ReachedDestination, this));
	this->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}

void Tube::Stop() {
//	this->setVisible(false);
	State = kTubeStateInActive;
	this->setPosition(Vec2(kTubeInActiveX, this->getPositionY()));
	Scored = false;
}

void Tube::Initialise(const float speed, const float width) {
	_speed = speed;
	_screenWidth = width;
	_xOffSet = this->getBoundingBox().size.width;
	State = kTubeStateInActive;
	Scored = false;
}

void Tube::ReachedDestination() {
	Stop();
}




Tube::Tube() :
pairTube(NULL)
{
}

void Tube::setPair(Tube* tb){
    pairTube = tb;
    tb->pairTube = this;
}



Tube::~Tube()
{
}
