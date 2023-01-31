//Saganenko AV IKPI 04
//var. 20
//built with MinGw x64
//editdialog.cpp

//parent forms
#include "editdialog.h"
#include "ui_editdialog.h"
#include "queue.h"

//Qt libraries
#include <QFileDialog>
#include <QMessageBox>

//C++ STL library
#include <vector>

EditDialog::EditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);
}

EditDialog::~EditDialog()
{
    delete ui;
}

/*  it was the most difficult part of the entire project so there might be some problems cuzed
    by not proper testing.  */

//func. to clear all the fields simple ====================================================================================================
void EditDialog::ClearLabels()
{
    ui->NameField->setText("");
    ui->TypeField->setText("");
    ui->SubField->setText("");
    ui->RadiusField->setText("");
    ui->WeightField->setText("");
    ui->MoonsField->setText("");
    ui->PopulationField->setText("");
    ui->RotationField->setText("");
    ui->TemperatureField->setText("");
    ui->ImageField->setText("");
}

//func. to set all the parameters to labels ===============================================================================================
void EditDialog::SetLabels()
{
    QString thisstring = MainVector[localwideindex];
    QStringList ThisVector = thisstring.split(";");

    ui->NameField->setText(ThisVector[0]);
    ui->TypeField->setText(ThisVector[1]);
    ui->SubField->setText(ThisVector[2]);
    ui->RadiusField->setText(ThisVector[3]);
    ui->WeightField->setText(ThisVector[4]);
    ui->MoonsField->setText(ThisVector[5]);
    ui->PopulationField->setText(ThisVector[6]);
    ui->RotationField->setText(ThisVector[7]);
    ui->TemperatureField->setText(ThisVector[8]);
    ui->ImageField->setText(ThisVector[9]);
}

//func. to open new file ==================================================================================================================
void EditDialog::on_openDBButton_clicked()
{
    //if file wasn't saved ask whether user wants to save it or proceed saving not
    if(unsaved == false)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Warning","You have unsaved progress!\nDo you want to proceed and delete this database or save it?",QMessageBox::Yes | QMessageBox::No);
        //if the answer is yes then this currently unsaved database will be deleted!
        //want to save? - initialize on_SaveButton_clicked();
        if (reply == QMessageBox::Yes)
            on_saveDBButton_clicked();
        else
            return;
    }
    //if previous condition is not called or file was saved proceed here
    ClearLabels();
    QString OpenFile_Filter = "Text File (*.txt) ;; CSV File (*.csv) ;; All File (*.*)";
    OpenFile_Path = QFileDialog::getOpenFileName(this,"Open a file","/",OpenFile_Filter);

    QFile File(OpenFile_Path);
    if(!File.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Error","ActionOpenFile::The file wasn't chosen!!\nCode ER:1");
        OpenFile_Path=NULL;
        return;
    }
    else
    {
        QFileInfo ThisFile(OpenFile_Path);
        if (ThisFile.suffix()!="txt")
        {
            QMessageBox::warning(this,"Error","ActionOpenFile::The file has wrong type!\nCode ER:2");
            OpenFile_Path=NULL;
            return;
        }
        QTextStream in(&File);

        while(!in.atEnd())
        {
            QString FileLine = in.readLine();
            QStringList LineList = FileLine.split(";");
            if (LineList.length()<10 || LineList.length()%10!=0)
                {
                QMessageBox::warning(this,"Error","ActionOpenFile::The file has incorrect text!\nCode ER:3");
                File.close();
                ClearLabels();
                OpenFile_Path=NULL;
                FileLine=NULL;
                LineList.clear();
                MainVector.clear();
                return;
                }
            if (LineList.contains(" ") || LineList.contains(""))
            {
                QMessageBox::warning(this,"Warning","ActionOpenFile::Some parameters are not specified!\nCode WR:4");
            }
            MainVector.push_back(FileLine);
            ui->mainbox->addItem(FileLine);
        }
        //so the main idea of this editing mode is its ability to add new object to database. so in order to create new object
        //one must select "<add>" item of list and then save the labels - not very convenient yet there's worst ways
        ui->mainbox->addItem("<add>");
        localwideindex = 0;
        SetLabels();
        File.close();
        ui->DeleteThisButton->setEnabled(1);
        ui->SaveChangesButton->setEnabled(1);
    }
}

//func. to save changes OF THIS PARTICULAR OBJECT - might be changes or completely new object =============================================
void EditDialog::on_saveChangesButton_clicked()
{
    QString localline;
    if(ui->NameField->text().isEmpty() || ui->TypeField->text().isEmpty() || ui->SubField->text().isEmpty()
            || ui->RadiusField->text().isEmpty() || ui->WeightField->text().isEmpty() || ui->MoonsField->text().isEmpty() ||
            ui->PopulationField->text().isEmpty() || ui->RotationField->text().isEmpty() || ui->TemperatureField->text().isEmpty() ||
            ui->ImageField->text().isEmpty())
    {
        QMessageBox::warning(this,"Warning","ActionSave::Some fields are empty!\nCode WR:ADD");
        if(ui->NameField->text().isEmpty())
            ui->NameField->setText("Unknown");
        if(ui->TypeField->text().isEmpty())
            ui->TypeField->setText("Unknown");
        if(ui->SubField->text().isEmpty())
            ui->SubField->setText("Unknown");
        if(ui->RadiusField->text().isEmpty())
            ui->RadiusField->setText("Unknown");
        if(ui->WeightField->text().isEmpty())
            ui->WeightField->setText("Unknown");
        if(ui->MoonsField->text().isEmpty())
            ui->MoonsField->setText("Unknown");
        if(ui->PopulationField->text().isEmpty())
            ui->PopulationField->setText("Unknown");
        if(ui->RotationField->text().isEmpty())
            ui->RotationField->setText("Unknown");
        if(ui->TemperatureField->text().isEmpty())
            ui->TemperatureField->setText("Unknown");
        if(ui->ImageField->text().isEmpty())
            ui->ImageField->setText("none");
    }
    localline=localline+ui->NameField->text()+";"+ui->TypeField->text()+";"+ui->SubField->text()+
            ";"+ui->RadiusField->text()+";"+ui->WeightField->text()+";"+ui->MoonsField->text()+";"+ui->PopulationField->text()+";"+
            ui->RotationField->text()+";"+ui->TemperatureField->text()+";"+ui->ImageField->text();
    if (localwideindex<MainVector.size())
    {
        MainVector[localwideindex]=localline;
        ui->mainbox->setItemText(localwideindex,localline);
    }
    else
    {
        MainVector.push_back(localline);
        ui->mainbox->setItemText(localwideindex,localline);
        ui->mainbox->addItem("<add>");
        ui->DeleteThisButton->setEnabled(1);
    }
    QMessageBox::warning(this,"Success","This object was successefully reloaded!");
}

//func. to delete THIS CURRENLY CHOSEN OBJECT from list ===================================================================================
void EditDialog::on_DeleteThisButton_clicked()
{
    MainVector.erase(MainVector.begin()+localwideindex);
    ui->mainbox->removeItem(localwideindex);
}

//func. on the contrary to view or create forms this is the only way to navigate through elements =========================================
void EditDialog::on_mainbox_currentIndexChanged(int index)
{
    if(MainVector.size()==0)
        ui->DeleteThisButton->setEnabled(0);
    if(index<MainVector.size())
    {
        localwideindex = index;
        ui->DeleteThisButton->setEnabled(1);
    }
    else
    {
        if (index==MainVector.size())
        {
            localwideindex = index;
            ClearLabels();
            return;
        }
        ClearLabels();
        ui->DeleteThisButton->setEnabled(0);
        return;
    }
    SetLabels();
}

//func. to save the file into the same place as the same file that was opened =============================================================
void EditDialog::on_saveDBButton_clicked()
{
    QFile LocalFile(OpenFile_Path);
    if(!LocalFile.open(QFile::WriteOnly|QFile::Truncate))
    {
        QMessageBox::warning(this,"Error","SaveAs::The file wasn't chosen!\nCode ER:1");
        OpenFile_Path=NULL;
        return;
    }
    QTextStream out(&LocalFile);
    for (size_t i = 0; i<MainVector.size();i++)
    {
        QString ThisLine = MainVector[i];
        out << ThisLine << "\n";
    }
    LocalFile.close();
    unsaved = true;
}

//func. to merge this current database with another one ===================================================================================
void EditDialog::on_mergeButton_clicked()
{
    QString SecondOpenFile_Filter = "Text File (*.txt) ;; CSV File (*.csv) ;; All File (*.*)";
    QString SecondOpenFile_Path = QFileDialog::getOpenFileName(this,"Open a file","/",SecondOpenFile_Filter);
    QFile File(SecondOpenFile_Path);
    if(!File.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Error","ActionOpen::File wasn't chosen!\nCode ER:1");
        OpenFile_Path=NULL;
        return;
    }
    QFileInfo ThisFile(SecondOpenFile_Path);
    if (ThisFile.suffix()!="txt")
    {   QMessageBox::warning(this,"Error","ActionOpenFile::The file has wrong type!\nCode ER:2");
        OpenFile_Path=NULL;
        return;   }
    QTextStream in(&File);
    int i=0;
    while(!in.atEnd())
    {
        QString FileLine = in.readLine();
        QStringList LineList = FileLine.split(";");
        if (LineList.length()<10 || LineList.length()%10!=0)
            {
            QMessageBox::warning(this,"Error","ActionOpenFile::The file has incorrect text!\nCode ER:3");
            File.close();
            SecondOpenFile_Path=NULL;
            FileLine=NULL;
            LineList.clear();
            return;
            }
        if (LineList.contains(" ") || LineList.contains(""))
            QMessageBox::warning(this,"Warning","ActionOpenFile::Some parameters are not specified!\nCode WR:4");
        if(i == 0)
        {
            ui->mainbox->removeItem(MainVector.size());
            i=1;
        }
        MainVector.push_back(FileLine);
        ui->mainbox->addItem(FileLine);

    }
    File.close();
    localwideindex=0;

    ui->mainbox->addItem("<add>");
}

