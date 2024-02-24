#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QMediaFormat>
#include <QFileDialog>

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
    ui->labelCover->setPixmap(audio.cover.size().isNull() ? QPixmap(":/V-Cover-Art-dev.png") : QPixmap::fromImage(audio.cover));
    qDebug() << audio.cover.isNull();
}


void MainWindow::on_widget_4_windowIconTextChanged(const QString &iconText)
{

}


void MainWindow::on_widget_4_windowIconChanged(const QIcon &icon)
{

}


void MainWindow::on_comboBox_activated(int index)
{
    if(index==0){

        QString audioFileName = QFileDialog::getOpenFileName(this,
                                                tr("Open Image"), "/home/sergiu/Music", tr("Audio Files (*.mp3 *.flac)"));
        audio.setAudioPath(audioFileName);


    }
}


void MainWindow::on_horizontalSlider_actionTriggered(int action)
{
    //audio.setVolumeLevel(action);
}


void MainWindow::on_horizontalSlider_rangeChanged(int min, int max)
{

}


void MainWindow::on_horizontalScrollBar_actionTriggered(int action)
{
    //audio.setVolumeLevel(action);

}


void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    float tempValue = ((float)value)/100;
    audio.setVolumeLevel(tempValue);

}

