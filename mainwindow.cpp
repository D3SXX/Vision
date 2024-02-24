#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QMediaFormat>

Controls control;
Audio audio;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap cover(":/V-Cover-Art-dev.png"); // Setting up image file that will be used as cover art
    ui->labelCover->setPixmap(cover.scaled(400,400,Qt::KeepAspectRatio)); // Putting it into label
    audio.init();
    QObject::connect(&audio, &Audio::mediaInfoChanged, this, &MainWindow::updateData);
    QObject::connect(&audio, &Audio::positionChanged, this, &MainWindow::updatePosition);
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
        audio.start();

    }else {
        ui->PlayPauseButton->setIcon(QIcon::fromTheme("media-playback-start"));
        audio.pause();
    }
    qDebug() << "Play is set to" << (control.onPlay ? "True (Playing)" : "False (Not playing)");
}

void MainWindow::updateData(){
    ui->TitleLabel->setText(audio.title);
    ui->ArtistLabel->setText(audio.author);
    ui->AlbumTitleLabel->setText(audio.album);
    ui->labelCover->setPixmap(audio.cover.isNull() ? QPixmap(":/V-Cover-Art-dev.png") : QPixmap::fromImage(audio.cover));
}

void  MainWindow::updatePosition(){
    ui->progressBar->setMaximum(audio.duration);
    ui->progressBar->setValue(audio.position);
    QString position =  QString("%1:%2:%3/%4:%5:%6")
                           .arg((audio.position / (1000*60*60)) % 24, 2, 10, QChar('0'))
                           .arg((audio.position / (1000 * 60)) % 60, 2, 10, QChar('0'))
                           .arg((audio.position / 1000) % 60, 2, 10, QChar('0'))
                           .arg((audio.duration / (1000*60*60)) % 24, 2, 10, QChar('0'))
                           .arg((audio.duration / (1000 * 60)) % 60, 2, 10, QChar('0'))
                           .arg((audio.duration / 1000) % 60, 2, 10, QChar('0'));
    ui->mediaPositionLabel->setText(position);
}

void MainWindow::on_widget_4_windowIconTextChanged(const QString &iconText)
{

}


void MainWindow::on_widget_4_windowIconChanged(const QIcon &icon)
{

}

