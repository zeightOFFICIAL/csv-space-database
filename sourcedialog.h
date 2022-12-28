#ifndef SOURCEDIALOG_H
#define SOURCEDIALOG_H

#include <QDialog>

namespace Ui {
class sourcedialog;
}

class sourcedialog : public QDialog
{
    Q_OBJECT

public:
    explicit sourcedialog(QWidget *parent = nullptr);
    ~sourcedialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::sourcedialog *ui;
};

#endif // SOURCEDIALOG_H
