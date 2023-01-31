#include <QFontDatabase>
#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":/fonts/volume1/venus_uprising.otf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont f(family);
    f.setPointSize(16);
    f.setBold(false);
    ui->mainText->setFont(f);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_closeButton_clicked()
{
    this->close();
}

