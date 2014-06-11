//
//  Manager.cpp
//  feiji
//
//  Created by kf on 14-6-8.
//
//

#include "Manager.h"
Manager*Manager::m_manager=NULL;
//在构造函数的初始化列表中初始化数组
Manager::Manager():m_enemyVector(),m_bulletVector()
{
    
}
Manager*Manager::getInstance()
{
    if (m_manager==NULL) {
        m_manager=new Manager();
        
    }
    return m_manager;
}
void Manager::freeInstance(void)
{
    if (m_manager!=NULL) {
        delete m_manager;
        m_manager=NULL;
    }
}