/*
 * @name BookFiler Widget w/ QT - Task Manager
 * @version 1.00
 * @license MIT
 * @brief Task Manager Widget tracks task progress
 */

/* QT 5.13.2
 * License: LGPLv3
 */
#include <QHBoxLayout>
#include <QDebug>
#include <QSpacerItem>

// Local Project
#include "TaskItem.hpp"

/*
 * bookfiler - widget
 */
namespace bookfiler {
namespace widget {

TaskItem::TaskItem(QWidget * parent){

    first_row=new QWidget(this);
    second_row=new QWidget(this);
    lbl_title=new QLabel(first_row);
    progress_bar=new QProgressBar(first_row);
    lbl_percentage_complete=new QLabel(first_row);
    btn_cancel_button=new QPushButton(first_row);
    lbl_description=new QLabel(second_row);
    lbl_remaining_time= new QLabel(second_row);
    btn_status=new QPushButton();
    btn_status->setFlat(true);
    btn_status->setCheckable(false);

    setFixedWidth(600);
    setFixedHeight(100);
    progress_bar->setValue(50);
    progress_bar->setMaximum(100);
    progress_bar->setMinimum(0);
    lbl_percentage_complete->setText("50%");
    lbl_title->setText("Unknown");
    lbl_description->setText("Description Unknown");
    lbl_remaining_time->setText("0s");
    btn_cancel_button->setIcon(QIcon("resources/icons/Error@2x.png"));
    btn_cancel_button->setCheckable(false);

    first_row->setLayout(new QHBoxLayout);
    first_row->layout()->addWidget(lbl_title);
    first_row->layout()->addWidget(progress_bar);
    first_row->layout()->addWidget(lbl_percentage_complete);
    first_row->layout()->addWidget(btn_cancel_button);
    second_row->setLayout(new QHBoxLayout);
    second_row->layout()->addWidget(btn_status);
    second_row->layout()->addWidget(lbl_description);
    dynamic_cast<QHBoxLayout*>(second_row->layout())->addStretch();
    second_row->layout()->addWidget(lbl_remaining_time);
    setLayout(new QVBoxLayout);
    layout()->addWidget(first_row);
    layout()->addWidget(second_row);
    show();

    connect(this->btn_cancel_button,&QPushButton::clicked,this,&TaskItem::cancel);
}
TaskItem::~TaskItem(){}

void TaskItem::cancel()
{
    qDebug()<<lbl_title->text()<<" has been canceld";
    //doCancel(); //Uncomment this when the logic to set this exist
}

int TaskItem::setTitle(std::string title) {
    lbl_title->setText(QString::fromStdString(title));
    return 0;
}

std::string TaskItem::getTitle() { return lbl_title->text().toStdString(); }

int TaskItem::setDescription(std::string description) { lbl_description->setText(QString::fromStdString(description));return 0; }

std::string TaskItem::getDescription() { return lbl_description->text().toStdString(); }

} // namespace widget
} // namespace bookfiler
