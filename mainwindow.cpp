#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "klee.h"
#include "actionbutton.h"
#include "QGraphicsPixmapItem"
#include <QScreen>
#include <QTimer>
#include <QGraphicsScene>
#include <QCursor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //debug with - QTextStream(stdout) << "text";
    //QTextStream(stdout) << QGuiApplication::primaryScreen()->geometry().height();
    QScreen *screen = QGuiApplication::primaryScreen();

    //fully taransparent window
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    ui->horizontalLayout->setContentsMargins(0,0,0,0);
    ui->graphicsView->setContentsMargins(0,0,0,0);

    //destroy statusbar and menubar
    ui->statusbar->~QStatusBar();
    ui->menubar->~QMenuBar();

    //scene transparency
    setStyleSheet("background:transparent;");

    //creating scene
    scene = new Scene(this);
    scene->setSceneRect(screen->geometry());

    ui->graphicsView->setScene(scene);
    //scene->addItem(new Klee(screen));
    scene->addItem(new ActionButton(screen));
    scene->addItem(new Klee(screen));

}

MainWindow::~MainWindow()
{
    delete ui;
}


