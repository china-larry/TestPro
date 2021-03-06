﻿/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 设置页面Widget，版本信息，调光，校正等操作
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#include "CSettingPage.h"
#include <QBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "PublicFunction.h"

CSettingPage::CSettingPage(QWidget *parent) : QWidget(parent)
{
    //应用样式 apply the qss style
    _LoadQss();
    _InitWidget();
    _InitLayout();    
}



bool CSettingPage::GetAutoTestFalg()
{
    return m_pTestModeWidget->GetAutoTestFlag();
}

void CSettingPage::SetAccountHide()
{
    qDebug() << "remov 1";
    m_pSetTabWidget->removeTab(1);
    m_pSetTabWidget->removeTab(2);
    this->update();
}

int CSettingPage::GetTestDelayTime()
{
    return m_pTestModeWidget->GetIncubatingTime();
}

//QString CSettingPage::GetPisServerIP()
//{
//    return m_pSetupWindowsWidget->GetPisServer();
//}

QString CSettingPage::GetPoctServerIP()
{
    return m_pSetupWindowsWidget->GetPoctServer();
}

//int CSettingPage::GetPisPort()
//{
//    return m_pSetupWindowsWidget->GetPisPort();
//}

int CSettingPage::GetPoctPort()
{
    return m_pSetupWindowsWidget->GetPoctPort();
}

bool CSettingPage::GetUpdateStates()
{
    bool bUpdatestates = false;
    bUpdatestates = m_pCUpdateSettingWidget->GetUpdateStates();
    return bUpdatestates;
}


void CSettingPage::_LoadQss()
{
    LoadQss(this, ":/qss/SettingPage/SettingPage.qss");
}
/**
  * @brief 初始化控件
  * @param
  * @return
  */
void CSettingPage::_InitWidget()
{
    SetWidgetBackColor(this, QColor(240, 240, 240));
    // test
    m_pSetupWindowsWidget = new CSettingSetupWindowWidget;
    SetWidgetBackColor(m_pSetupWindowsWidget, QColor(240, 240, 240));
//    connect(m_pSetupWindowsWidget, &CSettingSetupWindowWidget::SignalAutoConnetPis,
//            this, &CSettingPage::SignalAutoConnectPis);
    connect(m_pSetupWindowsWidget, &CSettingSetupWindowWidget::SignalAutoConnetPoct,
            this, &CSettingPage::SignalAutoConnectPoct);
    m_pAccountManagementWidget = new CAccountManagementWidget;
    SetWidgetBackColor(m_pAccountManagementWidget, QColor(240, 240, 240));
    m_pTestModeWidget = new CTestModeWidget;
    SetWidgetBackColor(m_pTestModeWidget, QColor(240, 240, 240));
    connect(m_pTestModeWidget, &CTestModeWidget::SigConfirmTestMode, this, &CSettingPage::SignalTestMode);

    m_pCUpdateSettingWidget = new CUpdateSettingWidget;
    SetWidgetBackColor(m_pCUpdateSettingWidget, QColor(240, 240, 240));
    // tab
    m_pSetTabWidget = new QTabWidget(this);
    SetWidgetBackColor(m_pSetTabWidget, QColor(240, 240, 240));
    /// 添加两个无效的，便于背景色
    m_pSetTabWidget->addTab(m_pSetupWindowsWidget, tr("Setup Window"));
    m_pSetTabWidget->addTab(m_pAccountManagementWidget, tr("Account Management"));
    m_pSetTabWidget->addTab(m_pTestModeWidget, tr("Test Mode"));
    m_pSetTabWidget->addTab(m_pCUpdateSettingWidget, tr("Upgrade"));
}

void CSettingPage::_InitLayout()
{
    // layout
    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setMargin(0);
    pLayout->addWidget(m_pSetTabWidget);
    this->setLayout(pLayout);
}

