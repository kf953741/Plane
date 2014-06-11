//
//  MainGame.h
//  feiji
//
//  Created by kf on 14-5-29.
//
//

#ifndef __feiji__MainGame__
#define __feiji__MainGame__

#include "cocos2d.h"
#include "Background.h"
#include "StartGame.h"
#include "Player.h"
#include "EnemyBase.h"
#include "Bullet.h"
#include "Manager.h"
#include "Ufo.h"
USING_NS_CC;

class MainGame :public Layer {
    
    
public:
    MainGame(void);
    ~MainGame(void);
    CREATE_FUNC(MainGame);
    bool init();
    static Scene*createScene();
    void onKeyReleased(EventKeyboard::KeyCode keycode,Event*pEvent);
    bool onTouchBegan(Touch*touch,Event*pEvent);
    void onTouchMoved(Touch*touch,Event*pEvent);
    void onEnterTransitionDidFinish();
    void addEnemy(float tm);
    void addBullet(float tm);
    void isHitEnemy(float tm);
    void addUfo(float tm);
    void addBulletByUfo(float tm);
   // Bullet m_bulletName;
private:
    EventListenerKeyboard *m_listener;
    EventListenerTouchOneByOne *m_touchListener;
    Player*m_player;
    Size m_size;
    Ufo * m_ufo;
   std::string m_bulletName;
};




#endif /* defined(__feiji__MainGame__) */
