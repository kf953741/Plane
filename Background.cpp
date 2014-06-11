//
//  Background.cpp
//  feiji
//
//  Created by kf on 14-5-29.
//
//

#include "Background.h"
Background::Background(void)
{
    
}
Background::~Background(void)
{
    
}
bool Background::init()
{
    if (!Layer::init()) {
       return false;
    }
    
    m_size =Director::getInstance()->getWinSize();
    m_background_1 = Sprite::create("background2.png");
   
    m_background_1->setAnchorPoint(CCPoint::ZERO);
    m_background_1->setPosition(Point::ZERO);
 
    m_background_1->getTexture()->setAliasTexParameters();
    this->addChild(m_background_1);
    m_background_2 = Sprite::create("background2.png");
    m_background_2->setAnchorPoint(Point::ZERO);
    //不出现黑线
    m_background_2->setPosition(Point(0,m_background_1->getContentSize().height-2));
    m_background_2->getTexture()->setAliasTexParameters();
    this->addChild(m_background_2);
    return true;

}
void Background::onEnterTransitionDidFinish(){
    Layer::onEnterTransitionDidFinish();
    this->schedule(SEL_SCHEDULE(&Background::move),0.01f);
}

void Background::move(float tm){
    float y1 = m_background_1->getPositionY()-OFFSET;
    float y2 = m_background_2->getPositionY()-OFFSET;
    m_background_1->setPositionY(y1);
    m_background_2->setPositionY(y2);
    if (y1<-m_background_1->getContentSize().height) {
        m_background_1->setPositionY(m_background_2->getPositionY()+m_background_2->getContentSize().height-2);
    }
    else if (y2<-m_background_2->getContentSize().height)
    {
        m_background_2->setPositionY(m_background_1->getPositionY()+m_background_2->getContentSize().height-2);
    }
}













