#include "aboutdialog.h"
#include "ui_aboutdialog.h"

aboutdialog::aboutdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutdialog)
{
    ui->setupUi(this);
}

aboutdialog::~aboutdialog()
{
    delete ui;
}

//func. to close this window in order to return to view window
void aboutdialog::on_pushButton_clicked()
{
    this->close();
}

