#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

namespace Ui {
class editdialog;
}

class editdialog : public QDialog
{
    Q_OBJECT

public:
    explicit editdialog(QWidget *parent = nullptr);
    ~editdialog();

private slots:
    //funcs. to manipulate files
    void on_OpenButton_clicked();
    void on_SaveButton_clicked();
    void on_mergeButton_clicked();

    //funcs. to manipulate objects
    void on_SaveChangesButton_clicked();
    void on_DeleteThisButton_clicked();

    //crucial navigator
    void on_mainbox_currentIndexChanged(int index);

private:
    Ui::editdialog *ui;

    //extra tools
    void ClearLabels();
    void SetLabels();

    //local vars
    std::vector<QString> MainVector;
    size_t localwideindex = 0;
    QString OpenFile_Path;
    bool unsaved = true;
};

#endif // EDITDIALOG_H
