//
//  EnemyBase.h
//  feiji
//
//  Created by kf on 14-6-2.
//
//

#ifndef __feiji__EnemyBase__
#define __feiji__EnemyBase__

#include "cocos2d.h"
USING_NS_CC;
class EnemyBase:public Sprite
{
public:
    EnemyBase(void);
    ~EnemyBase(void);
    bool init();
    CREATE_FUNC(EnemyBase);
   //爆炸画面
    void blowUp();
    void hit();
    void onEnterTransitionDidFinish();
    //改变敌机的坐标
    void move(float tm);
    //初始化敌机,传入要使用的纹理的名字,提供默认参数
    void initEnemy(std::string name="enemy1",int count =4 );
    void removeFromManager();
private:
    //获得start-end范围内的一个随机数
    int getRandomNumber(int start,int end);
    //敌机偏移量
    enum {OFFSET=5};
    //初始化敌机要用到的纹理名称
    std::string m_frameName;
    //爆炸效果的纹理数量
    int m_count;
    //敌机血量
  // int  m_hp=4;
    	CC_SYNTHESIZE(int,m_hp,Hp);
};
#endif /* defined(__feiji__EnemyBase__) */



















