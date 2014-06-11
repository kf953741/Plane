//
//  Ufo.h
//  feiji
//
//  Created by kf on 14-6-9.
//
//

#ifndef __feiji__Ufo__
#define __feiji__Ufo__

#include "cocos2d.h"
USING_NS_CC;
class Ufo:public Sprite
{
    
public:
    Ufo(void);
    ~Ufo(void);
    bool init();
    CREATE_FUNC(Ufo);
  //根据不同的纹理初始化不同的ufo和炸弹
    void initUfo(std::string name);
    int getRandomNumber(int start,int end);
    
    CC_SYNTHESIZE_READONLY(std::string,m_name,Name);
    
    
};

#endif /* defined(__feiji__Ufo__) */
