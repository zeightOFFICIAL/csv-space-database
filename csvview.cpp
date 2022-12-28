#include "csvview.h"
#include "ui_csvview.h"

csvview::csvview(QWidget *parent,QString line):
    QDialog(parent),
    ui(new Ui::csvview)
{
    ui->setupUi(this);
    ui->textBrowser->setPlainText(line);
}

csvview::~csvview()
{
    delete ui;
}

void csvview::on_pushButton_clicked()
{
    this->close();
}

