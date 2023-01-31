#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    //menu bar functuions
    void on_actionOpen_triggered();
    void on_actionExit_triggered();
    void on_actionClose_triggered();

    //buttons to manipulate view
    void on_buttonNextPlanet_clicked();
    void on_buttonPrevPlanet_clicked();

    //actions to manipulate views
    void on_objectsList_currentIndexChanged(int index);

    //actions to open another forms
    void on_actionShow_about_triggered();
    void on_actionShow_sources_triggered();
    void on_actionOpenEdit_triggered();
    void on_actionCreate_triggered();

    void on_actionLook_triggered();

private:
    Ui::MainWindow *ui;

    int wideindex = 0;
    QStringList widelist;

    void SetLabels();
    void ClearLabels();
};
#endif // MAINWINDOW_H
