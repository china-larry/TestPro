﻿/*****************************************************
  * Copyright: 万孚生物
  * Author: 刘青
  * Date: 2017-7-9
  * Description: 实现测试页功能，用户数据输入，测试流程操作，测试数据显示
  * -------------------------------------------------------------------------
  * History:
  *
  *
  *
  * -------------------------------------------------------------------------
  ****************************************************/
#ifndef CDETECTORPAGE_H
#define CDETECTORPAGE_H

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QMenu>
#include <QComboBox>
#include <QTableWidget>
#include <QList>
#include <QPrinter>
#include <QShowEvent>
#include "CommonDataWidget/CLabelLineEditWidget.h"
#include "CommonDataWidget/CLabelDateWidget.h"
#include "CommonDataWidget/CLabelDateTimeWidget.h"
#include "CommonDataWidget/CLabelCommoBoxWidget.h"
#include "AdjustLight/testing/ThreadTesting.h"
#include "PublicFunction.h"
#include "AdjustLight/VideoThread.h"
#include "DetectorPage/manualsetdialog.h"

struct PrintData
{
    QString strCupTyle;
    QString strDonorFN;
    QString strDonorLN;
    QString strOperatorID;
    QDate   qTestDate;
    QTime   qTestTime;
    QString strDonorID;
    QString strEmail;
    QString strAddress;
    QString strTestingSite;
    bool    bUrineCheck;
    bool    bSalivaCheck;
    QString strTestReason;
    QString strProductID;
    QString strProductLot;
    QDate  qExpirationDate;
    bool   bTemperatureinRangeYesCheck;
    bool   bTemperatureinRangeNoCheck;
    bool   bOxidantCheck;
    bool   bOxidantNolCheck;
    bool   bPHCheck;
    bool   bPHNolCheck;
    bool   bNitriteCheck;
    bool   bNitriteNolCheck;
    bool   bCreatinineCheck;
    bool   bCreatinineNolCheck;
};
//
class CDetectorPage : public QWidget
{
    Q_OBJECT
public:
    explicit CDetectorPage(QWidget *parent = 0);
    ~CDetectorPage();


signals:
    void SignalStartTest(int iTestDelayTime);// 开始测试
    void SignalStartQRCode();// 开始获取二维码
    void SignalHaveQRCodeInfo(int iProgramCount, int iTestDelayTime);// 获得二维码，告知主界面，项目总数，进度条进度
    void SignalTestProgramIndex(int iProgramIndex);// 测试结果Index，用于主界面状态栏显示
    void SignalEndTest();// 流程测试结束，数据传输main
    void SignalStopTest();// 主动停止测试
public slots:
    void SlotStartQRCode();// 开始查找二维码
    void SlotReceiveQRCodeImage(QString strImagePath);// 接受二维码图片数据
    void SlotReceiveQRCodeInfo(QRCodeInfo sQRCodeInfoStruct);// 接受二维码信息
    void SlotReceiveTestResultData(TestResultData sTestResultDataStruct);// 接受每条测试结果数据
    void SlotReceiveSCupImagePath(QString strImagePath);// 方杯两个图片数据
    void SlotEndTest();// 流程测试结束
    void SlotReceiveTestError(ENUM_ERR eTestError);// 错误信号
    void SlotFuseImageOK();// 拼接完成
    void SlotDeleteImageOK();// 删除完成
    void SlotStopBegin();
    void SlotStopEnd();
    void SlotReceiveProjectName(QString strCupType,QString strProjectName);
    void SlotOxidantNoRButton(bool);
    void SlotPHNoRButton(bool);
    void SlotNitriteNoRButton(bool);
    void SlotCreatinineNoRButton(bool);
    void SlotTempNoValRButton(bool);

private slots:
    // 控件
    void _SlotCheckReadTestDevice();// 开始测试
    void _SlotStopTest();// 主动停止测试
    void _SlotClearData();// 清空数据
    void _SlotOtherReasonChange(int iIndex);// 动态显示other line edit
    // 打印PDF
    void _SlotPrintToPDF();
    //手动修改结果
    void _SlotManualSetData();
public:
    QList<TestResultData*> GetTestResultData();// 获得测试结果
    DetectorPageUserData GetUserData(); // 获得被测者信息
    QString GetTestPrintImagePath();// 获取需要打印的图片路径
    void SetCupType(QStringList strCupTypeList);// 设置杯类型
    void StopTest();// 主动停止测试，关闭UI
    void SetAutoTest(bool bAutoTest);
    int GetAutoTestTimes();//
    void SetUserName(QString strUserName);
    void SetTestDelayTime(int iTime);
    void InitTestStates();
    void PowerOffStates();

private:
    void _LoadQss();
    QGroupBox *_CreateDonorDetailsGroup();
    QGroupBox *_CreateProductDetailsGroup();
    QGroupBox *_CreateResultsGroup();
    void _InitWidget();
    void _InitLayout();
    // 数据输入判定
    bool _GetValidData();
    void _InitThreadTesting();// 初始化测试线程
    // 更新摄像头图片
    void _SetCamaraImage(QString strImagePath);

    // 打印
    void _ReplaceCubeHtmlData(QString &strHtml);// 替换html中数据位测试数据, cube杯型，方杯
    void _ReplaceCupHtmlData(QString &strHtml);// 替换html中数据位测试数据, cup杯型， 圆杯
    // 测试结果打印格式（动态数量）
    QString _GetResultsDataHtml();
    // 拼接图片
    void _FuseTCupImage();// 圆杯
    void _FuseTCubeImage();// 方杯
    QString _GetSoftWareType();
    void GetReportTitle(bool &bIsDefault,QString &ReportTitle);

private:
    // donor details 1line
    QLabel *m_pTempInRangeLabel;
    QButtonGroup *m_pTempInRangeBGroup;
    QRadioButton *m_pTempValRButton;
    QRadioButton *m_pTempNoValRButton;
    // last first donor id
    CLabelLineEditWidget *m_pLastNameWidget;
    CLabelLineEditWidget *m_pFirstNameWidget;
    CLabelLineEditWidget *m_pDonorIDWidget;
    // data of birth email
    CLabelDateWidget *m_pBirthDateWidget;
    CLabelLineEditWidget *m_pEmailWidget;
    CLabelLineEditWidget *m_pAddressWidget;
    // test time
    CLabelDateTimeWidget *m_pTestTimeWidget;
    CLabelLineEditWidget *m_pTestingSiteWidget;
    // reason of test    
    CLabelCommoBoxWidget *m_pReasonForTestWidget;
    QStringList m_strReasonForTestList;
    QLineEdit *m_pOtherLineEdit;
    //////////////////////////////////////
    // adulterants
    QLabel *m_pAdulterantsLabel;
    QButtonGroup *m_pOxidantBGroup;
    QRadioButton *m_pOxidantRButton;
    QRadioButton *m_pOxidantNoRButton;

    QButtonGroup *m_pPHBGroup;
    QRadioButton *m_pPHRButton;
    QRadioButton *m_pPHNoRButton;

    QButtonGroup *m_pNitriteBGroup;
    QRadioButton *m_pNitriteRButton;
    QRadioButton *m_pNitriteNoRButton;

    QButtonGroup *m_pCreatinineBGroup;
    QRadioButton *m_pCreatinineRButton;
    QRadioButton *m_pCreatinineNoRButton;
    //////////////////////////////////////
    // Product Details
    QStringList m_strCupTypeList;// 杯类型数据
    CLabelCommoBoxWidget *m_pProductDefinitionWidget;
    CLabelLineEditWidget *m_pProductLotWidget;
    // expiration date
//    CLabelLineEditWidget *m_pExpirationWidget;
    CLabelDateWidget *m_pExpirationWidget;
    CLabelLineEditWidget *m_pProductIDWidget;
    //////////////////////////////////////
    // push button
    QPushButton *m_pReadTestDeviceButton;
    QPushButton *m_pStopTestButton;
    QPushButton *m_pClearDataButton;
    QPushButton *m_pPrintPriviewButton;
    QPushButton *m_pManualSetButton;
    //////////////////////////////////////
    // results
    QLabel *m_pCamaraLabel;// 摄像头
    QTableWidget *m_pResultsTableWidget;// 表格数据
    // 获取数据
    ThreadTesting *m_pThreadTesting; // 测试线程
    QRCodeInfo m_sQRCodeInfoStruct;       // 二维码数据，项目总数
    QList<TestResultData*> m_pTestResultDataList;// 下位机的测试结果列表
    DetectorPageUserData m_sDetectorPageUserDataStruct;// 用户列表数据
    QString m_strUserName;// 登陆用户名
    QStringList m_strSCupImagePathList;// 方杯的两个图片，单独发送拼接保存
    // 拼接图片
    CFuseImageThread *m_pFuseImageThread;
    QString m_strTestPrintImagePath;// 保存打印所需的测试过程图片，拼接合成，为当前时间，保存路径为result_image
    QString m_strTestResultImagePath;
    // 删除测试图片
    CDeleteImageThread *m_pDeleteImageThread;
    QString m_strTestImageDir;// 测试图片存放的目录
    // 初始化摄像头
    VideoThread *m_pVideoThread;
    // 自动测试
    bool m_bAutoTest;// 是否不停的测试
    int m_iTestDelayTime;// 测试延迟/孵化时间（秒）
    int iAutoTestCount;
    // 打印
    QString m_strHtml;

    //手动修改数据
    ManualSetDialog *pManualSetDialog;

    bool m_bIsManualSet;
    PrintData sPrintDataStruct;
};

#endif // CDETECTORPAGE_H