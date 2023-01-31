#include "editdialog.h"
#include "ui_editdialog.h"
#include "queue.h"

#include <QFileDialog>
#include <QMessageBox>

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

/*  it was the most difficult part of the entire project so there might be some problems caused
    by not proper testing.  */

void EditDialog::cearAllLabels()
{
    ui->nameField->setText("");
    ui->typeField->setText("");
    ui->subField->setText("");
    ui->radiusField->setText("");
    ui->weightField->setText("");
    ui->moonsField->setText("");
    ui->populationField->setText("");
    ui->rotationField->setText("");
    ui->temperatureField->setText("");
    ui->imageField->setText("");
}

void EditDialog::loadLabels()
{
    QString thisString = mainContainer[localWideIndex];
    QStringList thisVector = thisString.split(";");

    ui->nameField->setText(thisVector[0]);
    ui->typeField->setText(thisVector[1]);
    ui->subField->setText(thisVector[2]);
    ui->radiusField->setText(thisVector[3]);
    ui->weightField->setText(thisVector[4]);
    ui->moonsField->setText(thisVector[5]);
    ui->populationField->setText(thisVector[6]);
    ui->rotationField->setText(thisVector[7]);
    ui->temperatureField->setText(thisVector[8]);
    ui->imageField->setText(thisVector[9]);
}

void EditDialog::on_openDBButton_clicked()
{
    //if file wasn't saved ask whether user wants to save it or proceed saving not
    if(isUnsaved == false)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Warning","You have unsaved progress!\nDo you want to save this database?",QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
            on_saveDBButton_clicked();
        else
            return;
    }
    //if previous condition is not called or file was saved proceed here
    cearAllLabels();
    QString openFileFilter = "Text File (*.txt) ;; CSV File (*.csv) ;; All File (*.*)";
    openFilePath = QFileDialog::getOpenFileName(this,"Open a file","/",openFileFilter);

    QFile file(openFilePath);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning","ActionOpenFile::The file wasn't chosen!\n(Code ER:1)");
        openFilePath=NULL;
        return;
    }
    else
    {
        QFileInfo thisFile(openFilePath);
        if (thisFile.suffix()!="txt" && thisFile.suffix()!="csv")
        {
            QMessageBox::warning(this,"Warning","ActionOpenFile::The file has wrong type!\n(Code ER:2)");
            openFilePath=NULL;
            return;
        }
        QTextStream in(&file);

        while(!in.atEnd())
        {
            QString fileLine = in.readLine();
            QStringList lineList = fileLine.split(";");
            if (lineList.length()<10 || lineList.length()%10!=0)
                {
                QMessageBox::warning(this,"Warning","ActionOpenFile::The file has incorrect text!\n(Code ER:3)");
                file.close();
                cearAllLabels();
                openFilePath=NULL;
                fileLine=NULL;
                lineList.clear();
                mainContainer.clear();
                return;
                }
            if (lineList.contains(" ") || lineList.contains(""))
            {
                QMessageBox::warning(this,"Warning","ActionOpenFile::Some parameters are not specified!\n(Code WR:4)");
            }
            mainContainer.push_back(fileLine);
            ui->mainbox->addItem(fileLine);
        }
        //so the main idea of this editing mode is its ability to add new object to database. so in order to create new object
        //one must select "<add>" item of list and then save the labels - not very convenient yet there're worse ways
        ui->mainbox->addItem("<add>");
        localWideIndex = 0;
        loadLabels();
        file.close();
        ui->deleteObjectButton->setEnabled(1);
        ui->saveChangesButton->setEnabled(1);
    }
}

//to save changes OF THIS PARTICULAR OBJECT - might be changes or completely new object
void EditDialog::on_saveChangesButton_clicked()
{
    QString localline;
    if(ui->nameField->text().isEmpty() || ui->typeField->text().isEmpty() || ui->subField->text().isEmpty()
            || ui->radiusField->text().isEmpty() || ui->weightField->text().isEmpty() || ui->moonsField->text().isEmpty() ||
            ui->populationField->text().isEmpty() || ui->rotationField->text().isEmpty() || ui->temperatureField->text().isEmpty() ||
            ui->imageField->text().isEmpty())
    {
        QMessageBox::warning(this,"Warning","ActionSave::Some fields are empty!\nCode WR:ADD");
        if(ui->nameField->text().isEmpty())
            ui->nameField->setText("Unknown");
        if(ui->typeField->text().isEmpty())
            ui->typeField->setText("Unknown");
        if(ui->subField->text().isEmpty())
            ui->subField->setText("Unknown");
        if(ui->radiusField->text().isEmpty())
            ui->radiusField->setText("Unknown");
        if(ui->weightField->text().isEmpty())
            ui->weightField->setText("Unknown");
        if(ui->moonsField->text().isEmpty())
            ui->moonsField->setText("Unknown");
        if(ui->populationField->text().isEmpty())
            ui->populationField->setText("Unknown");
        if(ui->rotationField->text().isEmpty())
            ui->rotationField->setText("Unknown");
        if(ui->temperatureField->text().isEmpty())
            ui->temperatureField->setText("Unknown");
        if(ui->imageField->text().isEmpty())
            ui->imageField->setText("none");
    }
    localline=localline+ui->nameField->text()+";"+ui->typeField->text()+";"+ui->subField->text()+
            ";"+ui->radiusField->text()+";"+ui->weightField->text()+";"+ui->moonsField->text()+";"+ui->populationField->text()+";"+
            ui->rotationField->text()+";"+ui->temperatureField->text()+";"+ui->imageField->text();
    if (localWideIndex<mainContainer.size())
    {
        mainContainer[localWideIndex]=localline;
        ui->mainbox->setItemText(localWideIndex,localline);
    }
    else
    {
        mainContainer.push_back(localline);
        ui->mainbox->setItemText(localWideIndex,localline);
        ui->mainbox->addItem("<add>");
        ui->deleteObjectButton->setEnabled(1);
    }
    QMessageBox::warning(this,"Success","This object was successefully reloaded!");
}

void EditDialog::on_deleteObjectButton_clicked()
{
    mainContainer.erase(mainContainer.begin()+localWideIndex);
    ui->mainbox->removeItem(localWideIndex);
}

void EditDialog::on_mainbox_currentIndexChanged(int index)
{
    if(mainContainer.size()==0)
        ui->deleteObjectButton->setEnabled(0);
    if(index<mainContainer.size())
    {
        localWideIndex = index;
        ui->deleteObjectButton->setEnabled(1);
    }
    else
    {
        if (index==mainContainer.size())
        {
            localWideIndex = index;
            cearAllLabels();
            return;
        }
        cearAllLabels();
        ui->deleteObjectButton->setEnabled(0);
        return;
    }
    loadLabels();
}

void EditDialog::on_saveDBButton_clicked()
{
    QFile LocalFile(openFilePath);
    if(!LocalFile.open(QFile::WriteOnly|QFile::Truncate))
    {
        QMessageBox::warning(this,"Error","SaveAs::The file wasn't chosen!\nCode ER:1");
        openFilePath=NULL;
        return;
    }
    QTextStream out(&LocalFile);
    for (size_t i = 0; i<mainContainer.size();i++)
    {
        QString ThisLine = mainContainer[i];
        out << ThisLine << "\n";
    }
    LocalFile.close();
    QMessageBox::information(this,"Success","Database changed and saved!");
    isUnsaved = true;
}

void EditDialog::on_mergeButton_clicked()
{
    QString SecondOpenFile_Filter = "Text File (*.txt) ;; CSV File (*.csv) ;; All File (*.*)";
    QString SecondOpenFile_Path = QFileDialog::getOpenFileName(this,"Open a file","/",SecondOpenFile_Filter);
    QFile File(SecondOpenFile_Path);
    if(!File.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Error","ActionOpen::File wasn't chosen!\nCode ER:1");
        openFilePath=NULL;
        return;
    }
    QFileInfo ThisFile(SecondOpenFile_Path);
    if (ThisFile.suffix()!="txt")
    {   QMessageBox::warning(this,"Error","ActionOpenFile::The file has wrong type!\nCode ER:2");
        openFilePath=NULL;
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
            ui->mainbox->removeItem(mainContainer.size());
            i=1;
        }
        mainContainer.push_back(FileLine);
        ui->mainbox->addItem(FileLine);

    }
    File.close();
    localWideIndex=0;

    ui->mainbox->addItem("<add>");
}

