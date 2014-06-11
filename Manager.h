//
//  Manager.h
//  feiji
//
//  Created by kf on 14-6-8.
//
//

#ifndef __feiji__Manager__
#define __feiji__Manager__

#include "cocos2d.h"
#include"Bullet.h"
#include "EnemyBase.h"
USING_NS_CC;
//管理器做成单例模式
class Manager
{
public:
    static Manager*getInstance();
    static void  freeInstance(void);
    Vector<EnemyBase*>& getEnemyVector(){return m_enemyVector;};
    Vector<Bullet*> &getBulletVector(){return m_bulletVector;};
    
private:
    Vector<EnemyBase*> m_enemyVector;
    Vector<Bullet*> m_bulletVector;
    static Manager*m_manager;
    Manager();
    bool init();
};

#endif /* defined(__feiji__Manager__) */
