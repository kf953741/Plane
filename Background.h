//
//  Background.h
//  feiji
//
//  Created by kf on 14-5-29.
//
//

#ifndef __feiji__Background__
#define __feiji__Background__

#include "cocos2d.h"
#include "MainGame.h"
#include "StartGame.h"
USING_NS_CC;
class Background :public Layer
{
public:
    Background(void);
    ~Background(void);
    bool init();
    CREATE_FUNC(Background);
    void move(float tm);
    void onEnterTransitionDidFinish();
private:
    Sprite *m_background_1;
    Sprite *m_background_2;
    Size m_size;
    enum{OFFSET = 3};
};


#endif /* defined(__feiji__Background__) */
