#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>

Controls control;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap cover(":/V-Cover-Art-dev.png");
    ui->labelCover->setPixmap(cover.scaled(400,400,Qt::KeepAspectRatio));
    std::string dir = QCoreApplication::applicationDirPath().toStdString();
    qDebug() << QCoreApplication::applicationFilePath().toStdString();
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_PlayPauseButton_clicked()
{
    control.onPlay = !control.onPlay;
    if(control.onPlay){
        ui->PlayPauseButton->setIcon(QIcon::fromTheme("media-playback-pause"));
    }else {
        ui->PlayPauseButton->setIcon(QIcon::fromTheme("media-playback-start"));
    }
    qDebug() << "Play is set to" << (control.onPlay ? "True (Playing)" : "False (Not playing)");
}


void MainWindow::on_widget_4_windowIconTextChanged(const QString &iconText)
{

}


void MainWindow::on_widget_4_windowIconChanged(const QIcon &icon)
{

}

