#include "BGObject.h"

USING_NS_CC;


BGObject* BGObject::createWithFileName(char *fileName) {
	auto sprite = new BGObject;
	if (sprite && sprite->initWithFile(fileName)) {
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}



void BGObject::Start() {
	this->stopAllActions();
	float currentX = this->getPositionX();
	float distance = currentX + _xOffSet;
	float time = distance / _speed;
	Vec2 destination = Vec2(-_xOffSet, this->getPositionY());

	MoveTo *actionMove = MoveTo::create(time, destination);
	CallFunc *actionMoveDone = CallFunc::create(CC_CALLBACK_0(BGObject::ReachedDestination, this));
	this->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}

void BGObject::Stop() {
	this->stopAllActions();
}

void BGObject::SetSpeedAndWidth(const float speed, const float width) {
	_speed = speed;
	_screenWidth = width;
	_xOffSet = this->getBoundingBox().size.width;
}

void BGObject::ReachedDestination() {
	this->setPositionX(_xOffSet + _screenWidth);
	this->Start();
}



BGObject::BGObject()
{
}


BGObject::~BGObject()
{
}
