#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QMediaFormat>

Controls control;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap cover(":/V-Cover-Art-dev.png"); // Setting up image file that will be used as cover art
    ui->labelCover->setPixmap(cover.scaled(400,400,Qt::KeepAspectRatio)); // Putting it into label
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
        player = new QMediaPlayer; // Only for testing, replace it in apropriate place later!
        audioOutput = new QAudioOutput;
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl("qrc:/Vision.mp3"));
        audioOutput->setVolume(50);
        player->play();
    }else {
        ui->PlayPauseButton->setIcon(QIcon::fromTheme("media-playback-start"));
        player->pause();
    }
    qDebug() << "Play is set to" << (control.onPlay ? "True (Playing)" : "False (Not playing)");
}


void MainWindow::on_widget_4_windowIconTextChanged(const QString &iconText)
{

}


void MainWindow::on_widget_4_windowIconChanged(const QIcon &icon)
{

}

