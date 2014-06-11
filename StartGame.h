//
//  StartGame.h
//  feiji
//
//  Created by kf on 14-5-26.
//
//

#ifndef __feiji__StartGame__
#define __feiji__StartGame__
#include "cocos2d.h"
#include "Background.h"
#include "MainGame.h"
#include "Player.h"
USING_NS_CC;
class StartGame :public Layer {
    
    
public:
    static Scene*createScene();
    bool init();
    CREATE_FUNC(StartGame);
    StartGame(void);
    ~StartGame(void);
    void play(Ref*ref);
   void onKeyReleased(EventKeyboard::KeyCode keycode,Event*pEvent);
};

#endif /* defined(__feiji__StartGame__) */
