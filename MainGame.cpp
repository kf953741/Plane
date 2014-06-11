//
//  MainGame.cpp
//  feiji
//
//  Created by kf on 14-5-29.
//
//

#include "MainGame.h"
MainGame::MainGame (void){
 
    
}
MainGame::~MainGame(void){
    //移除事件监听器
    Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
    Director::getInstance()->getEventDispatcher()->removeEventListener(m_touchListener);
    Manager::freeInstance();
}
Scene*MainGame::createScene(){
    auto scene = Scene::create();
    auto layer = MainGame::create();
    scene->addChild(layer);
    return scene;
}
bool MainGame::init()
{
	if(!Layer::init())
		return false;
    
	m_size = Director::getInstance()->getWinSize();
    
	//添加地图层
	auto background = Background::create();
	this->addChild(background);
    
	//添加android返回键的监听器
	m_listener = EventListenerKeyboard::create();
	m_listener->onKeyReleased = CC_CALLBACK_2(MainGame::onKeyReleased,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_listener,this);
    
	//加载精灵帧缓存
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");
    
	//添加玩家飞机
    this->m_ufo = NULL;
    this->m_bulletName = "bullet1.png";
	m_player = Player::create();
	m_player->setPosition(Point(m_size.width/2,m_size.height*0.2));
	this->addChild(m_player);
   // this->m_bulletName="bullet1.png";
    
	//单点触摸的监听器
	m_touchListener = EventListenerTouchOneByOne::create();
	m_touchListener->onTouchBegan = CC_CALLBACK_2(MainGame::onTouchBegan,this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(MainGame::onTouchMoved,this);
	//设置吞噬触摸
	m_touchListener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_touchListener,this);
  
    
	return true;
}

//android返回键的监听
void MainGame::onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent)
{
	//切换到开始游戏场景
	Director::getInstance()->replaceScene(StartGame::createScene());
}

//单点触摸的监听函数
bool MainGame::onTouchBegan(Touch * touch,Event * pEvent)
{
	//判断手指点击的区域是否在飞机上
	auto point = touch->getLocation();
	auto rect = m_player->getBoundingBox();
	if(rect.containsPoint(point))
		return true;
    
	return false;
}
void MainGame::onTouchMoved(Touch * touch,Event * pEvent)
{
	//跟随手指移动飞机的位置
	auto addPoint = touch->getLocation()-touch->getPreviousLocation();
	m_player->setPosition(m_player->getPosition()+addPoint);
    
	//判断飞机移动的范围，不要超出了边界
	auto size = m_player->getContentSize();
	//如果x方向的坐标小于了它自己宽度的一般，或者是大于了屏幕的宽度减去自己宽度的一半的大小就越界了
	if(m_player->getPositionX() < size.width/2)
	{
		m_player->setPositionX(size.width/2);
	}
	else if(m_player->getPositionX() > m_size.width-size.width/2)
	{
		m_player->setPositionX(m_size.width-size.width/2);
	}
	//y方向根据x方向的判断方法进行类推
	if(m_player->getPositionY() < size.height/2)
	{
		m_player->setPositionY(size.height/2);
	}
	else if(m_player->getPositionY() > m_size.height-size.height/2)
	{
		m_player->setPositionY(m_size.height-size.height/2);
	}
}

void  MainGame::onEnterTransitionDidFinish()
{
    //必须调用父类的函数
    Layer::onEnterTransitionDidFinish();
    //添加敌机,每秒添加一个
    this->schedule(SEL_SCHEDULE(&MainGame::addEnemy),1.0f);
    //添加子弹
    this->schedule(SEL_SCHEDULE(&MainGame::addBullet),0.08f);
    	this->schedule(SEL_SCHEDULE(&MainGame::isHitEnemy));
    this->schedule(SEL_SCHEDULE(&MainGame::addUfo),10.0f);
    //this->schedule(SEL_SCHEDULE(&MainGame::addBulletByUfo),0.50f);
}
//碰撞检测
void MainGame::isHitEnemy(float tm)
{
    
    //从管理器中获得子弹和敌机数组的引用
    auto &enemyVector = Manager::getInstance()->getEnemyVector();

    auto &bulletVector = Manager::getInstance()->getBulletVector();
    for (int i = enemyVector.size()-1; i>=0; i--) {
        
        //如果敌机毁灭会播放动画暂时不会从管理器中移除,判断是否毁灭
        if (enemyVector.at(i)->getHp()==0) {
           continue;
       }
        //获得敌机的rect
        auto rect = enemyVector.at(i)->getBoundingBox();
        for (int j = bulletVector.size()-1; j>=0; j--) {
           
            //判断是否在rect内
            auto point = bulletVector.at(j)->getPosition();
            if (rect.containsPoint(point)) {
                //敌机的生命值减掉
                enemyVector.at(i)->setHp(enemyVector.at(i)->getHp()-1);
                //从屏幕和管理器中移除子弹
                bulletVector.at(j)->removeFromParentAndCleanup(true);
                bulletVector.eraseObject(bulletVector.at(j));
                //生命值为0敌机爆炸,如果敌机已经死亡就不要和剩下的子弹进行判断 所以是break
                if (enemyVector.at(i)->getHp()==0) {
                    enemyVector.at(i)->blowUp();
                    break;
                }
                else
                {
                  //播放敌机受伤的画面
                    enemyVector.at(i)->hit();
                    
                }
            }
        }
    }
    if (m_ufo!=NULL) {
        auto rect = m_player->getBoundingBox();
        auto point = m_ufo->getPosition();
        if (rect.containsPoint(point)) {
            if (m_ufo->getName()=="ufo1.png") {
                m_bulletName="bullet2.png";
            }
            else if (m_ufo->getName()=="ufo2.png"){
                m_bulletName = "bullet1.png";
            }
            else{
                
            }
            this ->schedule(SEL_SCHEDULE(&MainGame::addBulletByUfo),0.1f,40,0);
            m_ufo->setVisible(false);
            m_ufo=NULL;
        }
        if (m_ufo!=NULL &&point.y<-m_ufo->getContentSize().height/2) {
            m_ufo=NULL;
        }
    }
}
//当玩家飞机和ufo碰撞后添加子弹
void MainGame::addBulletByUfo(float tm)
{
    //log("kf");
    //创建双发子弹
    auto bullet1 = Bullet::create();
    bullet1->initBullet(m_bulletName);
    auto bullet2 = Bullet::create();
    bullet2->initBullet(m_bulletName);
    //设置位置
    auto point1 = Point(m_player->getPositionX()-23,m_player->getPositionY()+m_player->getContentSize().height/2);
    bullet1->setPosition(point1);
    auto point2 =Point(m_player->getPositionX()+23,m_player->getPositionY()+m_player->getContentSize().height/2);
    bullet2->setPosition(point2);
    this->addChild(bullet1);
    this->addChild(bullet2);
    //将子弹添加到管理器中
    auto &vector = Manager::getInstance()->getBulletVector();
    vector.pushBack(bullet1);
    vector.pushBack(bullet1);
}
//添加Ufo
void MainGame::addUfo(float tm)
{
   m_ufo = Ufo::create();
    int num = CCRANDOM_0_1()*3+1;
    if (num==1) {
        m_ufo->initUfo("ufo1.png");
        
    }else if(num==2)
    {
        m_ufo->initUfo("ufo2.png");
    }
    else
    {
        m_ufo->initUfo("bomb.png");
    }
    this->addChild(m_ufo);
    
}
//添加子弹
void MainGame::addBullet(float tm)
{
    auto bullet = Bullet::create();
   bullet->initBullet("bullet1.png");
   // bullet ->initBullet(_name);
    auto point = Point(m_player->getPositionX(),m_player->getPositionY()+m_player->getContentSize().height/2+15);
    bullet->setPosition(point);
    this->addChild(bullet);
    auto &vector = Manager::getInstance()->getBulletVector();
    vector.pushBack(bullet);
    
}


//添加敌机
void MainGame::addEnemy(float tm)
{
    //根据分数来改变敌机出现的快慢,后期添加了分数再来做
    static int score = 0;
    score++;
    if (score>50) {
        //重新调用schedule更新时间
        this ->schedule(SEL_SCHEDULE(&MainGame::addEnemy),0.8f);
    }
    else if(score>100)
    {
        this->schedule(SEL_SCHEDULE(&MainGame::addEnemy),0.6f);
    }
    else if(score>200 )
    {
        this->schedule(SEL_SCHEDULE(&MainGame::addEnemy),0.5f);
    }
    else if(score>400)
    {
        this->schedule(SEL_SCHEDULE(&MainGame::addEnemy),0.3f);
    }
    
    auto enemy = EnemyBase::create();
    //根据不同概率来添加你不同种类的飞机
    int enemy_x = CCRANDOM_0_1()*9+1;
    int count= 0;
    if (enemy_x>0&&enemy_x<7) {
        enemy_x=1;
        count =4;
    }
    else if (enemy_x>=7&&enemy_x<9)
    {
        enemy_x= 2;
        count =4;
    }
    else
    {
        //敌机三
        count = 6;
        enemy->initEnemy("enemy3_n1",count);
        //创建敌机三的动画
        Vector<SpriteFrame*>vector;
        vector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));
        vector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png"));
        auto animation = Animation::createWithSpriteFrames(vector,0.2f,-1);
        auto animate = Animate::create(animation);
        enemy->runAction(animate);
        this->addChild(enemy);
        return;
    }
    auto str = __String::createWithFormat("enemy%d",enemy_x);
    enemy->initEnemy(str->getCString(),count);
    this->addChild(enemy);
    auto &vector = Manager::getInstance()->getEnemyVector();
    vector.pushBack(enemy);
    
}


































