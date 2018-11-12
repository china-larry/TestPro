#ifndef CDONORDETAILSDLG_H
#define CDONORDETAILSDLG_H

#include <QWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QCheckBox>
#include "CommonDataWidget/CLabelLineEditWidget.h"
#include "CommonDataWidget/CLabelDateWidget.h"
#include "CommonDataWidget/CLabelDateTimeWidget.h"
#include "CommonDataWidget/CLabelCommoBoxWidget.h"
struct SDonorDlgData
{
    QString strDonorFN;
    QString strDonorLN;
    QDate   qTestDate;
    QTime   qTestTime;
    QString strDonorID;
    QString strEmail;
    QString strAddress;
    QString strTestingSite;
    bool    bUrineCheck;
    bool    bSalivaCheck;
    QString strTestReason;
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
class CDonorDetailsDlg : public QWidget
{
    Q_OBJECT
public:
    explicit CDonorDetailsDlg(QWidget *parent = nullptr);

signals:

public slots:

public:
    QString GetProductDefinitionText();
    // 数据
    SDonorDlgData GetDlgData();

private:
    void _InitWidget();
    void _InitLayout();

private:
    // donor details 1line
    QLabel *m_pDonorDetailsLabel;
    QLabel *m_pTempInRangeLabel;
    QButtonGroup *m_pTempInRangeBGroup;
    QRadioButton *m_pTempValRButton;
    QRadioButton *m_pTempNoValRButton;
    // last first donor id
    CHLabelLineEditWidget *m_pLastNameWidget;
    CHLabelLineEditWidget *m_pFirstNameWidget;
    CHLabelLineEditWidget *m_pDonorIDWidget;
    // data of birth email
    CLabelDateWidget *m_pBirthDateWidget;
    CHLabelLineEditWidget *m_pEmailWidget;
    CHLabelLineEditWidget *m_pAddressWidget;
    // test time
    CLabelDateTimeWidget *m_pTestTimeWidget;
    CHLabelLineEditWidget *m_pTestingSiteWidget;
    // adulterants
    QLabel *m_pAdulterantsLabel;
    QCheckBox *m_pOxidantRButton;
    QCheckBox *m_pPHRButton;
    QCheckBox *m_pNitriteRButton;
    QCheckBox *m_pCreatinineRButton;

    // reason of test
    CLabelCommoBoxWidget *m_pReasonForTestWidget;
    QStringList m_strReasonForTestList;
    //////////////////////////////////////
    SDonorDlgData m_sDonorDlgData;
};

#endif // CDONORDETAILSDLG_H
