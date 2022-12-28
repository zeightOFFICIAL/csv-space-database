#include "sourcedialog.h"
#include "ui_sourcedialog.h"

sourcedialog::sourcedialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sourcedialog)
{
    ui->setupUi(this);
}

sourcedialog::~sourcedialog()
{
    delete ui;
}

//func. to close this window in order to return to view window
void sourcedialog::on_pushButton_clicked()
{
    this->close();
}

