/*
 * @name BookFiler Widget w/ QT - Task Manager
 * @version 1.00
 * @license MIT
 * @brief Task Manager Widget tracks task progress
 */

#ifndef BOOKFILER_WIDGET_QT_TASK_MANAGER_TASK_ITEM_H
#define BOOKFILER_WIDGET_QT_TASK_MANAGER_TASK_ITEM_H

// config
#include "../core/config.hpp"

// C++17
#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>

/* QT 5.13.2
 * License: LGPLv3
 */
#include <QVBoxLayout>
#include <QProgressBar>
#include <QWidget>
#include <QLabel>
#include <QPushButton>

// Local Project
// #include "Item.hpp"

/*
 * bookfiler - widget
 */

namespace bookfiler {
namespace widget {

class Q_DECL_EXPORT TaskItem : public QWidget {
  Q_OBJECT
private:
  /* getProgress() is called periodically id task polling is enabled. Most tasks
   * should already signal changes for their progress to their associated
   * TaskItem.
   * @param partsDone parts done of the parts total. This could represent a
   * percent completion or bytes loaded or any other unit.
   * @param partsTotal parts total to complete
   * @param timeRemaining time in milliseconds remaining for the task.
   * @return 0 on success, else error code
   */
  std::function<int(int &partsDone, int &partsTotal,
                    std::chrono::milliseconds &timeRemaining)>
  getProgress();
  std::function<int()> doCancel();
  std::function<int()> doPause();
  
  QVBoxLayout* vbox_layout{};
  QWidget* first_row{};
  QWidget* second_row{};
  QLabel* lbl_title{};
  QProgressBar* progress_bar{};
  QLabel* lbl_percentage_complete{};
  QPushButton* btn_cancel_button{};
  QLabel* lbl_description{};
  QLabel* lbl_remaining_time{};
  QPushButton* btn_status{};

  void cancel(); // a Wrapper aroung doCancel

public:
  explicit TaskItem(QWidget * parent = nullptr);
  ~TaskItem();

  /* Sets the task title
   * @param title task title
   * @return 0 on success, else error code
   */
  int setTitle(std::string title);
  /* Gets the task title
   * @return task title
   */
  std::string getTitle();
  /* Sets the task description
   * @param title task description
   * @return 0 on success, else error code
   */
  int setDescription(std::string title);
  /* Gets the task description
   * @return task description
   */
  std::string getDescription();

  /*Set the maxium value of the progress bar
   * @param done how much has been done
   * @param total how much is to be done
   */
   void setProgressBarValues(const std::string done, const std::string total)
   {
       progress_bar->setMaximum(QString::fromStdString(total).toInt());
       progress_bar->setValue(QString::fromStdString(done).toInt());
   }
   /*Set the remaining tiem for the item
    * @param time for instance "8" for 8 secongds
    */
   void setRemainingTime(const std::string remaining_time)
   {
       QString time=QString::fromStdString(remaining_time);
       time=time=="NULL"?"?":time;
        lbl_remaining_time->setText(time+" s");
   }

   /*Set the status of the cancel button
    * @param can_cancel "1" if cancel "0" if not
    */

   void setCancelIcon(const std::string can_cancel)
   {
       const int can_cancel_value=QString::fromStdString(can_cancel).toInt();
       if (can_cancel_value>0)
       {
           btn_cancel_button->show();
       }
       else
       {
           btn_cancel_button->hide();
       }
   }

   /* Set the status of the task
    * @param status "NULL" if ongoing "2" if succedde "3" if cancelled "4" if failed
    */

   void setStatus(const std::string status)
   {
       btn_status->setVisible(status!="NULL");
       if (status=="2")
       {
           btn_status->setIcon(QIcon("resources/icons/CompletedTask@2x.png"));
       }
       if (status=="3")
       {
           btn_status->setIcon(QIcon("resources/icons/Error@2x.png"));
       }
       if (status=="4")
       {
           btn_status->setIcon(QIcon("resources/icons/Warning@2x.png"));
       }
   }


  friend class WidgetTaskItemTest;
  friend class WidgetTaskListTest;
};


} // namespace widget
} // namespace bookfiler

#endif
// end BOOKFILER_WIDGET_QT_TASK_MANAGER_TASK_ITEM_H
