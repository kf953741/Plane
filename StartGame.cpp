//
//  StartGame.cpp
//  feiji
//
//  Created by kf on 14-5-26.
//
//

#include "StartGame.h"

StartGame::StartGame(void)
{
    
}
StartGame::~StartGame(void)
{
   // Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}
Scene*StartGame::createScene()
{
    auto scene = Scene::create();
    auto layer = StartGame::create();
    scene->addChild(layer);
     
    return scene;
}
    bool StartGame::init()
{
    if (!Layer::init()) {
        return false;
    }
 
    auto size = Director::getInstance()->getWinSize();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui.plist");
  // auto background =Sprite::createWithSpriteFrameName("background2.png");
    auto background = Sprite::create("background2.png");
   // background->setPosition(Point(size.width, size.height));
    background->setPosition(size.width/2,size.height/2);
      // background->setScale(size.width/background->getContentSize().width, size.height/background->getContentSize().height);
    this->addChild(background);
    //设置logo
    auto logo = Sprite::createWithSpriteFrameName("shoot_copyright.png");
    logo->setPosition(Point(size.width/2,size.height-logo->getContentSize().height));
    //logo->setOpacity(0);
    this->addChild(logo);
    auto fade = FadeIn::create(2.0f);
    logo->runAction(fade);
    
    auto playText =LabelTTF::create("开始游戏", "HiraKakuProN-W6", 40);
   
    playText->setColor(Color3B(100,100,100));
    auto playMenu = MenuItemLabel::create(playText,CC_CALLBACK_1(StartGame::play, this));
    auto menu = Menu::create(playMenu,NULL);
    menu->setPosition(size.width/2,size.height*0.3);
    this->addChild(menu);
    auto listener = EventListenerKeyboard::create();
    //和回调函数的绑定
    listener->onKeyPressed = CC_CALLBACK_2(StartGame::onKeyReleased, this);
      //log("play game!");
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}
void StartGame::onKeyReleased(EventKeyboard::KeyCode keycode,Event*pEvent){
    Director::getInstance()->end();

}
void StartGame::play(Ref * ref)

{
    
    log("play game!");
   // Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0f,MainGame::createScene(),false));
    Director::getInstance()->replaceScene(MainGame::createScene());
  
}








