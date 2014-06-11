//
//  EnemyBase.cpp
//  feiji
//
//  Created by kf on 14-6-2.
//
//

#include "EnemyBase.h"
#include "Manager.h"
USING_NS_CC;
EnemyBase::EnemyBase(void)
{
    
}
EnemyBase::~EnemyBase(void)
{
    
}
bool EnemyBase::init()
{
    if (!Sprite::init()) {
        return false;
    }
    return true;
}
//传入纹理的名称来初始化敌机
void EnemyBase::initEnemy(std::string name ,int count)
{
    auto size = Director::getInstance()->getWinSize();
    //为成员变量赋值
    m_frameName = name;
    m_count = count;
    m_hp = name[5]-'0';
   
    //使用精灵图片初始化
    std::string str = name+".png";
    this->initWithSpriteFrameName(str);
    //设置横纵坐标
    auto point = Point(getRandomNumber(this->getContentSize().width/2, size.width
                                       -this->getContentSize().width/2),size.height);
    this->setPosition(point);
    
    
}
//过得a-b之间的一个随机数,是ccrandom_0_1(b-a)+a
int EnemyBase::getRandomNumber(int start, int end)
{
    return CCRANDOM_0_1()*(end-start)+start;
}
//场景切换完调用
void EnemyBase::onEnterTransitionDidFinish()
{
    Sprite::onEnterTransitionDidFinish();
    //调用schedule函数,改变敌机的坐标
    this ->schedule(SEL_SCHEDULE(&EnemyBase::move));
}

void EnemyBase::move(float tm)
{
    auto point = this->getPositionY()-OFFSET;
    this->setPositionY(point);
    //如果移动出了屏幕则从父节点中移除
    if (point<-this->getContentSize().height) {
        this->removeFromParentAndCleanup(true);
    }
    
}
//敌机爆炸动画,这个类是敌机类的基类,所以敌机的名字和用到的动画帧数是不确定的,需要在参数中传递
void EnemyBase::blowUp()
{
    Vector<SpriteFrame*> vector;
    for (int i=0; i<m_count; i++) {
        auto frameName = __String ::createWithFormat("_down%d.png",i+1);
        std::string str = m_frameName+frameName->getCString();
        auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        vector.pushBack(spriteFrame);
    }
    //设置动画帧的间隔,同时动画只执行一次
    auto animation = Animation::createWithSpriteFrames(vector,0.2f,1);
    auto animate = Animate::create(animation);
    //移除自己的动作
    auto removeSelf = RemoveSelf::create();
    auto removeFromManager = CallFunc::create(CC_CALLBACK_0(EnemyBase::removeFromManager,this));
     auto sequence = Sequence::create(animate,removeSelf,removeFromManager, NULL);
    
    this->runAction(sequence);
    this->runAction(animate);
}


void EnemyBase::removeFromManager()
{
	auto & vector = Manager::getInstance()->getEnemyVector();
	vector.eraseObject(this);
}


void EnemyBase::hit()
{
    int index = m_frameName[5]-'0';
    //敌机没有受伤的画面
    if (index==1) {
        return;
        
    }
    auto animation = Animation::create();
    //使用下面两张图片来播放动画效果
    std::string frameName1 = m_frameName+"_hit.png";
    auto spriteFrame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName1);
    std::string frameName2 = m_frameName+".png";
    auto spriteFrame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName2);
    animation->addSpriteFrame(spriteFrame1);
    animation->addSpriteFrame(spriteFrame2);
    animation->setDelayPerUnit(0.05f);
    animation->setLoops(2);
    auto animate =Animate::create(animation);
    this->runAction(animate);
}



































