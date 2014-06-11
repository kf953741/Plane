//
//  Player.h
//  feiji
//
//  Created by kf on 14-5-31.
//
//

#ifndef __feiji__Player__
#define __feiji__Player__
#include "cocos2d.h"
USING_NS_CC;
class Player:public Sprite {
    
    
public:
    Player(void);
    ~Player(void);
    bool init();
    CREATE_FUNC(Player);
    //飞机动作
    void flyAction();
};

#endif /* defined(__feiji__Player__) */
