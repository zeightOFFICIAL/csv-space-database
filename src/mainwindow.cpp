//Saganenko AV IKPI 04
//var. 20
//built with MinGw x64
//mainwindow.cpp

//parent forms
#include "mainwindow.h"
#include "ui_mainwindow.h"

//extra forms
#include "aboutdialog.h"
#include "editdialog.h"
#include "createdialog.h"
#include "sourcedialog.h"
#include "csvview.h"

//Qt libraries
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*  this line below typically visualize how should the csv-database one line look like.
    name;type;subtype;radius;weight;moons;population;rotation;temperature;image
    whatever deviation met will result in program complete collapse (now it's prevented)    */

//func. to open a read-only file and represent parameters in window 1 (view-window) ===========================================================
void MainWindow::on_actionOpen_triggered()
{
    using namespace std;
    //stage 1 - open file dialog and get the name, full path. (step 1.1)
    ClearLabels();
    ui->objectsList->clear();
    QString OpenFile_Filter = "Text File (*.txt) ;; CSV File (*.csv) ;; All File (*.*)";
    QString OpenFile_Path = QFileDialog::getOpenFileName(this,"Open a file","/",OpenFile_Filter);

    //stage 2 - opening file. (step 1.2)
    QFile File(OpenFile_Path);
    //check if file was actually opened
    if(!File.open(QFile::ReadOnly | QFile::Text))
    {   QMessageBox::warning(this,"Error","ActionOpenFile::The file wasn't chosen!!\nCode ER:1");
        OpenFile_Path=NULL;
        return;    }
    else
    {
        QFileInfo ThisFile(OpenFile_Path);
        //check file format if it isn't txt - full function stop. (step 1.2.ER)
        if (ThisFile.suffix()!="txt")
        {   QMessageBox::warning(this,"Error","ActionOpenFile::The file has wrong type!\nCode ER:2");
            OpenFile_Path=NULL;
            return;   }
        QTextStream in(&File);

        //stage 3 - reading file. (step 1.3)
        while(!in.atEnd())
        {
            QString FileLine = in.readLine();
            QStringList LineList = FileLine.split(";");
            //single try to prevent program work with wrong csv file (step 1.3.ER)
            if (LineList.length()<10 || LineList.length()%10!=0)
                {
                QMessageBox::warning(this,"Error","ActionOpenFile::The file has incorrect text!\nCode ER:3");
                File.close();
                ClearLabels();
                OpenFile_Path=NULL;
                FileLine=NULL;
                LineList.clear();
                widelist.clear();
                return;
                }
            //check if file has empty fields - throws a warning (step 1.3.ER2)
            if (LineList.contains(" ") || LineList.contains(""))
                QMessageBox::warning(this,"Warning","ActionOpenFile::Some parameters are not specified!\nCode WR:4");
            widelist.append(FileLine);
            ui->objectsList->addItem(LineList[1]+" ("+LineList[2]+") named "+LineList[0]);
        }
        //close file (it isn't required cuz it is closed in ~destructor()
        File.close();
        //set default (starting index)
        wideindex = 0;

        //stage 4 - setting up the labels. (step 1.4)
        SetLabels();
        //somekind of crutch - to prevent out of range (nasty thing)
        if (widelist.length()!=1)
        {ui->buttonNextPlanet->setEnabled(1);
        ui->buttonPrevPlanet->setEnabled(1);}
    }
}

//func. to exit application (simple as one line yep) ==========================================================================================
void MainWindow::on_actionExit_triggered()
{ QCoreApplication::exit(); }

//func. to close current csv database =========================================================================================================
void MainWindow::on_actionClose_triggered()
{
    if (widelist.isEmpty())
        QMessageBox::warning(this,"Warning","ActionCloseFile::The list is empty or the file wasn't opened.\nNo need to close anything!\nCode WR:5");
    ClearLabels();
    ui->buttonNextPlanet->setEnabled(0);
    ui->buttonPrevPlanet->setEnabled(0);
}

//func. to show next object ===================================================================================================================
void MainWindow::on_buttonNextPlanet_clicked()
{
    //stage 1 - increment index (step 2.1)
    wideindex++;
    //stage 2 - check if index is bigger than maxindex - then index=0 so there is no out of range (step 2.2)
    if (wideindex==widelist.length())
        wideindex=0;
    //stage 3 - set fields (step 2.3)
    SetLabels();
    //change combobox's current index - current chosen object
    ui->objectsList->setCurrentIndex(wideindex);
}

//func. to show previous object ===============================================================================================================
void MainWindow::on_buttonPrevPlanet_clicked()
{
    //stage 1 - decrement index (step 3.1)
    wideindex--;
    //stage 2 - check if index is lesser than minindex - then index=maxindex so there is no out of range (step 3.2)
    if (wideindex<0)
        wideindex=widelist.length()-1;
    //stage 3 set fields (step 3.3)
    SetLabels();
    //change combobox's current index - current chosen object
    ui->objectsList->setCurrentIndex(wideindex);
}

//func. to show specific (chosen in list) object ==============================================================================================
void MainWindow::on_objectsList_currentIndexChanged(int index)
{
    //stage 1 - change selected object by the index in combobox (step 4.1)
    wideindex = index;
    //stage 2 - set labels if wideindex is within range "0<"???? Kinda strange thing that it's required (step 4.2)
    if (0<wideindex<(widelist.length()))
        SetLabels();
}

//func. to get parameters from csv-database and set to labels on window 1 (view-window) =======================================================
void MainWindow::SetLabels()
{
    //index is universal, so it is changed depending on button and list funcs.
    //this func. is mere sets the labels of the line(one string) with this index
    QString ThisString = widelist[wideindex]; //chosing this object out of all
    QStringList ThisList = ThisString.split(";"); //split this object by parameters

    //setting up the texts in labels
    ui->NameObject->setText(ThisList[0]);
    ui->TypeObject->setText(ThisList[1]);
    ui->SubTypeObject->setText(ThisList[2]);
    ui->RadiusObject->setText(ThisList[3]);
    ui->WeightObject->setText(ThisList[4]);
    ui->MoonsObject->setText(ThisList[5]);
    ui->PopulationObject->setText(ThisList[6]);
    ui->RotationObject->setText(ThisList[7]);
    ui->TemperatureObject->setText(ThisList[8]);

    //setting up the image in pixmap - check whether the file exists
    if (QFile::exists(ThisList[9]))
    {   QPixmap image(ThisList[9]);
        ui->ImageObject->setPixmap(image);    }
    else //if not the code below sets default picture
    {
        QPixmap image(":/pack1/iconmark.png");
        ui->ImageObject->setPixmap(image);
    }
}

//func. to clear all the labels ===============================================================================================================
void MainWindow::ClearLabels()
{
    //extra tool - required for closing and opening new databases
    //clear all lists and labels
    widelist.clear();
    ui->objectsList->clear();
    ui->objectsList->addItem("Planet named Earth");

    //setting up default names
    ui->NameObject->setText("Earth");
    ui->TypeObject->setText("Planet");
    ui->SubTypeObject->setText("Exoplanet");
    ui->RadiusObject->setText("6371 km");
    ui->WeightObject->setText("5.972e24 kg");
    ui->MoonsObject->setText("1 (Moon)");
    ui->PopulationObject->setText("7 500 000 000");
    ui->RotationObject->setText("23:56:04");
    ui->TemperatureObject->setText("14 celsius");

    //setting up default images
    QPixmap image(":/pack1/planetDefault.png");
    ui->ImageObject->setPixmap(image);
}

//func. to open about window ==================================================================================================================
void MainWindow::on_actionShow_about_triggered()
{
    //simple open new dialog (about dialog)
    AboutDialog aboutdialog;
    //so has forced focus while mainwindow is disabled
    aboutdialog.setModal(true);
    //execution of dialog
    aboutdialog.exec();
}

//func. to open edit window ==================================================================================================================
void MainWindow::on_actionOpenEdit_triggered()
{
    //pretty much the same. BUT it closes current opened csv-base
    ClearLabels();
    ui->buttonNextPlanet->setEnabled(0);
    ui->buttonPrevPlanet->setEnabled(0);
    EditDialog editdialog;
    editdialog.setModal(true);
    editdialog.exec();
}

//func. to open create window ================================================================================================================
void MainWindow::on_actionCreate_triggered()
{
    //exactly the same as one before
    ClearLabels();
    ui->buttonNextPlanet->setEnabled(0);
    ui->buttonPrevPlanet->setEnabled(0);
    CreateDialog createdialog;
    createdialog.setModal(true);
    createdialog.exec();
}

//func. to show sources window ===============================================================================================================
void MainWindow::on_actionShow_sources_triggered()
{
    sourcedialog sourcedialog;
    sourcedialog.setModal(true);
    sourcedialog.exec();
}

//func. to show csv-view window ===========================================================================================================

void MainWindow::on_actionLook_triggered()
{
    QString string = widelist.join("");
    CsvView csvview(this,string);
    csvview.setModal(true);
    csvview.exec();
}

