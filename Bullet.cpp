//
//  Bullet.cpp
//  feiji
//
//  Created by kf on 14-6-8.
//
//

#include "Bullet.h"
#include "Manager.h"
Bullet::Bullet(void)
{
    
}
Bullet::~Bullet(void)
{
    
}

bool Bullet::init()
{
    if (!Sprite::init()) {
        return false;
    }
    return true;
}
void Bullet::onEnterTransitionDidFinish()
{
    Sprite::onEnterTransitionDidFinish();
    this->schedule(SEL_SCHEDULE(&Bullet::move),0.08f);
}
//根据传入的纹理来初始化子弹
void Bullet::initBullet(std::string name)
{
    this->initWithSpriteFrameName(name);
}

//子弹移动
void Bullet::move(float tm)
{
    this->setPositionY(this->getPositionY()+OFFSET);
    if (this->getPositionY()>Director::getInstance()->getWinSize().height) {
        this->removeFromParentAndCleanup(true);
        //从管理器中移除出去
        auto &vector = Manager::getInstance()->getBulletVector();
        vector.eraseObject(this);
    }
}
















