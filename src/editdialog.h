#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(QWidget *parent = nullptr);
    ~EditDialog();

private slots:
    //funcs. to manipulate files
    void on_openDBButton_clicked();
    void on_saveDBButton_clicked();
    void on_mergeButton_clicked();

    //funcs. to manipulate objects
    void on_saveChangesButton_clicked();
    void on_DeleteThisButton_clicked();

    //crucial navigator
    void on_mainbox_currentIndexChanged(int index);

private:
    Ui::EditDialog *ui;

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
