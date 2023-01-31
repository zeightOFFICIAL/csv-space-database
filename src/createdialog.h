#ifndef CREATEDIALOG_H
#define CREATEDIALOG_H

#include <QDialog>
#include "queue.h"

namespace Ui {
class createdialog;
}

class createdialog : public QDialog
{
    Q_OBJECT

public:
    explicit createdialog(QWidget *parent = nullptr);
    ~createdialog();

private slots:

    //actions with file - save and new
    void on_createButton_clicked();
    void on_saveasButton_clicked();

    //buttons to manage fields to add to current database and just clear them
    void on_addObject_clicked();
    void on_clearFields_clicked();

    //lowside form actions to manipulate form - apply and close,close
    void on_ApplyButton_clicked();
    void on_CloseButton_clicked();

    //typelist -=- subtypelist proper correlation
    void on_TypeList_currentIndexChanged(int index);

    //chooseobject simplyfied
    void on_chooseFile_clicked();

private:
    Ui::createdialog *ui;

    //internal no-user-sided functions
    void on_PopSlider_sliderMoved(int position);
    void on_TempSlider_sliderMoved(int position);

    //tools - clearing ones
    void clearLabels();
    void totalWipe();

    //func. to update textbrowser
    void updateTextWhole(QString string);

    //internal vars.
    queue<QString> EditLine;
    size_t locallength = 0;
};

#endif // CREATEDIALOG_H
