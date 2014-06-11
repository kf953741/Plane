//
//  Player.cpp
//  feiji
//
//  Created by kf on 14-5-31.
//
//

#include "Player.h"
Player::Player(void){
    
}
Player::~Player(void){
    
}
bool Player::init(){
    if (!Sprite::init()) {
        return false;
    }
    
    //调用父类的initwithSpriteFrameName函数
    this->initWithSpriteFrameName("hero1.png");
    //播放飞机画面
    this->flyAction();
    return true;
}
//飞机动画

void Player::flyAction(){
    Vector<SpriteFrame*> vector;
    for (int i=0; i<2; i++) {
        auto frameName = __String::createWithFormat("hero%d.png",i+1);
        auto temSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
        vector.pushBack(temSpriteFrame);
    }
    //设置不断的播放飞机的动画
    auto animation =  Animation::createWithSpriteFrames(vector,0.2f,-1);
    auto animate = Animate::create(animation);
    this->runAction(animate);
}






















