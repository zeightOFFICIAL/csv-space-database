#ifndef CSVVIEW_H
#define CSVVIEW_H

#include <QDialog>

namespace Ui {
class csvview;
}

class csvview : public QDialog
{
    Q_OBJECT

public:
    explicit csvview(QWidget *parent = nullptr, QString list = "");
    ~csvview();

private slots:
    void on_pushButton_clicked();

private:
    Ui::csvview *ui;
};

#endif // CSVVIEW_H
