//Saganenko AV IKPI 04
//var. 20
//built with MinGw x64
//createdialog.cpp

//parent forms
#include "createdialog.h"
#include "ui_createdialog.h"

//internal container
#include "queue.h"

//Qt libraries
#include <QMessageBox>
#include <QFileDialog>

createdialog::createdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createdialog)
{
    ui->setupUi(this);
}

createdialog::~createdialog()
{
    delete ui;
}

//func. to create a new database with a check whether the old one was saved ===============================================================
void createdialog::on_createButton_clicked()
{
    //check if textbrowser is empty - this is a sign that it WAS CLOSED or SAVED
    if (!ui->textWhole->toPlainText().isEmpty())
    {
        //if not - call dialogue window QMessageBox::questuion
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Warning","You have unsaved progress!\nDo you want to proceed and delete this database?",QMessageBox::Yes | QMessageBox::No);
        //if the answer is yes then this currently unsaved database will be deleted!
        if (reply == QMessageBox::Yes)
           totalWipe();
        //otherwise return to editing
        else return;
    }
}

//func. to save recently created database =================================================================================================
void createdialog::on_saveasButton_clicked()
{
    if (EditLine.size()>0)
    {
        //stage 1 - open SaveFileDialog (step 5.1)
        QString SaveFile_Filter = "Text File (*.txt) ;; CSV File (*.csv) ;; All File (*.*)";
        QString SaveFile_Path = QFileDialog::getSaveFileName(this,"Save file","/",SaveFile_Filter);

        //stage 2 - choose file by the path (step 5.2)
        QFile File(SaveFile_Path);

        //check whether the file is avaiable
        if(!File.open(QFile::WriteOnly | QFile::Text))
        {
            QMessageBox::warning(this,"Error","SaveAs::The file wasn't chosen!\nCode ER:1");
            SaveFile_Path=NULL;
            return;
        }

        //stage 3 - writing the info into the file (step 5.3)
        QTextStream out(&File);
        for (size_t i = 0; i<locallength;i++)
        {
            QString ThisLine = EditLine.getSpecific(i);
            out << ThisLine << "\n";
        }

        //stage 4 - closing the file and wipe all the information (step 5.4)
        File.close();
        totalWipe();
    }
    else QMessageBox::warning(this,"Error","SaveAs::Database is empty!\nCode ER:6");
}

//func. to add object to database using queue container ===================================================================================
void createdialog::on_addObject_clicked()
{
    //stage 1 - check if fields are not empty - if so, set default param. (step 6.1)
    QString localline;
    if(ui->nameField->text().isEmpty() || ui->TypeList->currentText().isEmpty() || ui->SubtypeList->currentText().isEmpty()
            || ui->RadiusField->text().isEmpty() || ui->WeightField->text().isEmpty() || ui->MoonsField->text().isEmpty() ||
            ui->PopulationField->text().isEmpty() || ui->RotationField->text().isEmpty() || ui->TemperatureField->text().isEmpty() ||
            ui->ImageField->text().isEmpty())
    {
        QMessageBox::warning(this,"Warning","ActionOpen::Some fields are empty!\nCode WR:ADD");
        if(ui->nameField->text().isEmpty())
            ui->nameField->setText("Unknown");
        if(ui->TypeList->currentText().isEmpty())
            ui->TypeList->setCurrentIndex(10);
        if(ui->SubtypeList->currentText().isEmpty())
            ui->SubtypeList->setCurrentText("Unknown");
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

    //stage 2 - create a line consisting of these parametrs (step 6.2)
    localline=localline+ui->nameField->text()+";"+ui->TypeList->currentText()+";"+ui->SubtypeList->currentText()+
            ";"+ui->RadiusField->text()+";"+ui->WeightField->text()+";"+ui->MoonsField->text()+";"+ui->PopulationField->text()+";"+
            ui->RotationField->text()+";"+ui->TemperatureField->text()+";"+ui->ImageField->text();

    //stage 3 - write lines into the queue container (step 6.3)
    EditLine.push(localline);
    //increasing total length;
    locallength++;
    //update textbrowser
    updateTextWhole(localline);
    clearLabels();
}

//func. to clear name fields ==============================================================================================================
void createdialog::on_clearFields_clicked()
{
    clearLabels(); //as simple as remove all field's data
}

//func. to save and close =================================================================================================================
void createdialog::on_ApplyButton_clicked()
{
    //so if we need to firstly save then close is calls the function to save database and closes the app.
    on_saveasButton_clicked();
    //there is a nasty bug -- i'm to tired to fix it
    this->close();
}

//func. to close ==========================================================================================================================
void createdialog::on_CloseButton_clicked()
{
    //if there is no file inside the textbox -> so there is no database which is being edit.
    if (!ui->textWhole->toPlainText().isEmpty())
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Warning","You have unsaved progress!\nDo you want to proceed and delete the progress?",QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
           on_saveasButton_clicked();
           this->close();
           return;
        }
        //otherwise return to editing
    }
    //if not close this all to shit
    this->close();
}

//func. to clear name fields ==============================================================================================================
void createdialog::clearLabels()
{
    ui->nameField->clear();
    ui->RotationField->clear();
    ui->PopulationField->clear();
    ui->TemperatureField->clear();
    ui->TempSlider->setValue(0);
    ui->PopSlider->setValue(0);
    ui->RotationField->clear();
    ui->ImageField->clear();
    ui->SubtypeList->clear();
    ui->TypeList->setCurrentIndex(0);
    ui->RadiusField->clear();
    ui->MoonsField->clear();
    ui->WeightField->clear();
}

//func. to properly place subtype list depending on type list =============================================================================
void createdialog::on_TypeList_currentIndexChanged(int index)
{
    //so to arrange the subtype list obiously if type changes so do the subtype this is VERY plain approach nevertheless it works perfectly
    QComboBox *sl = ui->SubtypeList;

    if(index==0)
    {
        sl->clear();
    }
    if(index==1)
    {
        sl->clear();
        sl->addItem("Blue giant");
        sl->addItem("Red giant");
        sl->addItem("Orange giant");
        sl->addItem("Blue dwarf");
        sl->addItem("Red dwarf");
        sl->addItem("Yellow dwarf");
        sl->addItem("Brown dwarf");
        sl->addItem("White dwarf");
        sl->addItem("Neutron");
        sl->addItem("Blue supergiant");
        sl->addItem("Red supergiant");
        sl->addItem("Magenta dwarf");
        sl->addItem("Unlisted");
    }
    if(index==2)
    {
        sl->clear();
        sl->addItem("Exoplanet");
        sl->addItem("Rocky");
        sl->addItem("Greenhouse");
        sl->addItem("Gas giant");
        sl->addItem("Artificial");
        sl->addItem("Ocean world");
        sl->addItem("Lava world");
        sl->addItem("Rogue");
        sl->addItem("Unlisted");
    }
    if(index==3)
    {
        sl->clear();
        sl->addItem("Large (<200km");
        sl->addItem("Medium (<3km)");
        sl->addItem("Small (<100m)");
    }
    if(index==4)
    {
        sl->clear();
        sl->addItem("Great");
        sl->addItem("Sungrazing");
        sl->addItem("Unusual");
        sl->addItem("Centaurs");
        sl->addItem("Huge sized");
    }
    if(index==5)
    {
        sl->clear();
        sl->addItem("Elleptical");
        sl->addItem("Spiral");
        sl->addItem("Irregular");
        sl->addItem("Lenticular");
        sl->addItem("Barred spiral");
        sl->addItem("Peculiar");
        sl->addItem("Unlised");
    }
    if(index==6)
    {
        sl->clear();
        sl->addItem("Flux");
        sl->addItem("Diffuse");
        sl->addItem("Planetary");
        sl->addItem("Protoplanetary");
        sl->addItem("Supernova remnants");
        sl->addItem("Unlised");
    }
    if(index==7)
    {
        sl->clear();
        sl->addItem("Standard");
    }
    if(index==8)
    {
        sl->clear();
        sl->addItem("Dreadnought");
        sl->addItem("Cruiser");
        sl->addItem("Destroyer");
        sl->addItem("Frigate");
        sl->addItem("Corvette");
        sl->addItem("Fighter");
        sl->addItem("Bombarder");
        sl->addItem("Cruise ship");
        sl->addItem("Stealth");
        sl->addItem("Cargo ship");
        sl->addItem("Unknown");
    }
    if(index==9)
    {
        sl->clear();
        sl->addItem("Stellar");
        sl->addItem("Intermediate");
        sl->addItem("Supermassive");
        sl->addItem("Miniature");
        sl->addItem("Unlisted");
    }
    if(index==10)
    {
        sl->clear();
        sl->addItem("Unknown subtype");
    }
}

//func. to change value depending on slider ===============================================================================================
void createdialog::on_PopSlider_sliderMoved(int position)
{
    //we have slider on creationform which utterly arranges the value. it might be more quick and cozy
    ui->PopulationField->setText(QString::number(position)+"0"); //slider has limit of 1000000000 so I need to increase it (this is population after all)
}

//func. to change value depending on slider ===============================================================================================
void createdialog::on_TempSlider_sliderMoved(int position)
{
    //the same as before - only difference is that Temperature is limited within -273 .. 10000 great!
    ui->TemperatureField->setText(QString::number(position)+"C");
}

//func. to navigate and chose image for current object ====================================================================================
void createdialog::on_chooseFile_clicked()
{
    //we actually needed to add such a way to improve undersantding and simplify the process of chosing the right image
    ui->ImageField->clear();
    //pretty simple - like opening csv(txt) file.
    QString OpenFile_Filter = "PNG File (*.png) ;; Image File (*.jpeg *.jpg *.png *.bmp *.bwm5)";
    QString OpenFile_Path = QFileDialog::getOpenFileName(this,"Select a file","/",OpenFile_Filter);
    QFileInfo ThisFile(OpenFile_Path);
    if(!ThisFile.exists())
    {
        QMessageBox::warning(this,"Error","ChoseFile::File does not exist!\nCode ER:IMAGE");
        return;
    }
    ui->ImageField->setText(OpenFile_Path);
}

//func. to clear everything data from form ================================================================================================
void createdialog::totalWipe()
{
    //CLEAR EVERYTHING - JUST INTO ABYSS
    clearLabels();
    ui->textWhole->clear();
    locallength = 0;
    EditLine.clearAll();
}

//func. to update information in textbrowser ==============================================================================================
void createdialog::updateTextWhole(QString string)
{
    ui->textWhole->moveCursor(QTextCursor::End);
    ui->textWhole->insertPlainText(string+"\n");
    ui->textWhole->moveCursor(QTextCursor::End);
}
