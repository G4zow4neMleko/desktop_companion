#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <scene.h>
#include <klee.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    Scene * scene;
};
#endif // MAINWINDOW_H
