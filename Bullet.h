//
//  Bullet.h
//  feiji
//
//  Created by kf on 14-6-8.
//
//

#ifndef __feiji__Bullet__
#define __feiji__Bullet__

#include "cocos2d.h"
//#include "Manager.h"

USING_NS_CC;
class Bullet:public Sprite
{
public:
    Bullet(void);
    ~Bullet(void);
    bool init();
    CREATE_FUNC(Bullet);
    void onEnterTransitionDidFinish();
    void initBullet(std::string name);
    //子弹移动
    void move(float tm);
private:
    //子弹移动距离
    enum {OFFSET = 35};
    
};
#endif /* defined(__feiji__Bullet__) */














