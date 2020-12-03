#include <QtTest/QtTest>
#include <TaskItem.hpp>
#include <QWidget>
#include <QMainWindow>
#include <QThread>
#include <QPushButton>
#include <QtGui>
namespace bookfiler {
namespace widget {
class WidgetTaskItemTest : public QMainWindow {
  Q_OBJECT

private:
    TaskItem* m_unit;
public:

    WidgetTaskItemTest():QMainWindow()
    {
        m_unit=new TaskItem(this);
        this->setCentralWidget(m_unit);       
        this->centralWidget()->show();
        this->setWindowTitle("WidgetTaskItemTest");
    }

private slots:
    void initTestCase ()
    {



    }
    void init(){

    }
    void TestConstruction()
    {
        QVERIFY2(m_unit->lbl_title->text()=="Unknown"," Wrong title at construction");
        QVERIFY2(m_unit->lbl_percentage_complete->text()=="50%", "Wrong percentage at construction");
        QVERIFY2(m_unit->progress_bar->value()==50,"Wrong value at construction");
        QVERIFY2(m_unit->isVisible()==true,"Not visile at construction");
        QVERIFY2(m_unit->lbl_description->text()=="Description Unknown","Wrong description at construction");
        QVERIFY2(m_unit->lbl_remaining_time->text()=="0s","Wrong remaining time at construction");
    }
    void TestSetTitle()
    {
        m_unit->setTitle("MyTitle");
        QVERIFY2(m_unit->lbl_title->text()=="MyTitle","Wrong title after setting");
    }
    void TestSetDescription()
    {
        m_unit->setDescription("My Description");
        QVERIFY2(m_unit->lbl_description->text()=="My Description","Wrong description after construction");
    }
    void TestsetProgressBarValues()
    {
        m_unit->setProgressBarValues("30","32");
        QVERIFY2(m_unit->progress_bar->maximum()==32,"Total value not set");
        QVERIFY2(m_unit->progress_bar->value()==30,"Done value not set");
    }
    void TestsetProgressBarValues_TotalLowerThenDone()
    {
        m_unit->setProgressBarValues("32","30");
        QVERIFY2(m_unit->progress_bar->maximum()==30,"Total value not set");
        QVERIFY2(m_unit->progress_bar->value()==30,"Done value not set");
    }
    void TestsetRemainingTime()
    {
        m_unit->setRemainingTime("8");
        QCOMPARE("8 s",m_unit->lbl_remaining_time->text());
    }
    void TestsetRemainingTime_NULL()
    {
        m_unit->setRemainingTime("NULL");
        QCOMPARE("? s",m_unit->lbl_remaining_time->text());
    }
    void TestsetCancelIcon()
    {
        m_unit->setCancelIcon("1");
        QVERIFY2(true==m_unit->btn_cancel_button->isVisible(),"Cancel button not visible after it has been set to 1");
        m_unit->setCancelIcon("0");
        QVERIFY2(false==m_unit->btn_cancel_button->isVisible(),"Cancel button not hidden after it has been set to 0");
    }
    void TestsetStatus()
    {
        m_unit->setStatus("NULL");
        QCOMPARE(false,m_unit->btn_status->isVisible());
        m_unit->setStatus("2");
        QCOMPARE(true,m_unit->btn_status->isVisible());
        m_unit->setStatus("3");
        QCOMPARE(true,m_unit->btn_status->isVisible());
        m_unit->setStatus("4");     
        QCOMPARE(true,m_unit->btn_status->isVisible());
    }
};


}
}
QTEST_MAIN(bookfiler::widget::WidgetTaskItemTest)
#include "WidgetTaskItemTest.moc"
