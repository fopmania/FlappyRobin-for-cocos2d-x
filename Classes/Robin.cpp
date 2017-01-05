#include "Robin.h"
#include "GameManager.h"
#include "Constants.h"



USING_NS_CC;

Robin* Robin::createWithFileName(char *fileName)
{
	auto sprite = new Robin;
	if (sprite && sprite->initWithFile(fileName)){
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Robin::Update(float dt)
{
	if (State == kRobinStateMoving) {
		// s = ut + 0.5 * a * t * t
		// v = u + a * t

		float distance = 0;
		float newSpeed = 0;
        
        float gt = GRAVITY;

		distance = _speedY * dt + gt * dt * dt;
		newSpeed = _speedY + gt * dt;

		this->setPositionY(this->getPositionY() + distance);
		_speedY = newSpeed;

		if (this->getPositionY() > _topOfScreen) {
			this->setPositionY(_topOfScreen);
			_speedY = 0.0;
		}

	}
}
void Robin::Reset()
{
	State = kRobinStateStopped;
	SetStartSpeed(0);
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//	this->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 2));
}
void Robin::SetStartSpeed(float addSpeed)
{
	_speedY = kRobinStartSpeedY + addSpeed;
}
void Robin::SetParams(const float tos)
{
	_topOfScreen = tos;
}

cocos2d::Rect Robin::TubeCollisionBox(){
	return Rect(
		this->getBoundingBox().origin.x + 25,
		this->getBoundingBox().origin.y + 5,
		this->getBoundingBox().size.width - 35,
		this->getBoundingBox().size.height - 15
		);
}


Robin::Robin()
{
}


Robin::~Robin()
{
}
