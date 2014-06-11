//
//  Ufo.cpp
//  feiji
//
//  Created by kf on 14-6-9.
//
//

#include "Ufo.h"
Ufo::Ufo(void)
{
    
}
Ufo::~Ufo(void)
{
    
}
bool Ufo::init()
{
    if (!Sprite::init()) {
        return false;
    }
    return true;
}

void Ufo::initUfo(std::string name)
{
    m_name=name;
    this ->initWithSpriteFrameName(name);
    //获得坐标
    auto size = Director::getInstance()->getWinSize();
    auto contentSize = this->getContentSize();
    //设置横纵坐标
    auto point = Point(getRandomNumber(contentSize.width/2, size.width-this->getContentSize().width/2),size.height);
    this->setPosition(point);
    //设置一个曲线让ufo来执行
    ccBezierConfig bezier;
   //贝尔曲线的两个控制点在屏幕
    bezier.controlPoint_1 = Point(getRandomNumber(contentSize.width/2,
                                                size.width-contentSize.
                                                  width/2),
                                  getRandomNumber(contentSize.height,
                                                  size.height-contentSize.
                                                  height/2));
    bezier.controlPoint_2 = Point(getRandomNumber(contentSize.width/2,
                                                  size.width-contentSize.
                                                  width/2),
                                  getRandomNumber(contentSize.height,
                                                  size.height-contentSize.
                                                  height/2));
    
    bezier.endPosition = Point(getRandomNumber(contentSize.width/2
                                               , size.width-contentSize
                                               .width/2),-contentSize.height);
    
    
    //使用BezierTo动作
    auto bezierAction = BezierTo::create(2.0f, bezier);
    //移除自己
    auto removeAction = RemoveSelf::create();
    auto action = Sequence::create(bezierAction,removeAction, NULL);
    this->runAction(action);
}
int Ufo::getRandomNumber(int start , int end)
{
    return CCRANDOM_0_1()*(end-start)+start;
}


























