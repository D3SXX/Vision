#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QMediaFormat>
#include <QFileDialog>
#include <QTableView>
#include <QStandardItemModel>

Audio audio;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap cover(":/V-Cover-Art-dev.png"); // Setting up image file that will be used as cover art
    ui->labelCover->setPixmap(cover.scaled(400,400,Qt::KeepAspectRatio)); // Putting it into label
    audio.init();
    QObject::connect(&audio, &Audio::mediaInfoChanged, this, &MainWindow::updateData); // Get media data right after the initialization is finished
    QObject::connect(&audio, &Audio::positionChanged, this, &MainWindow::updatePosition); // Update progress bar and labels
    QObject::connect(&audio, &Audio::volumeChanged, this, &MainWindow::updateVolumeElements); // Update UI Elements if the volume value was changed
    if(!audio.volume){ // If the volume value is absent set it
        audio.setVolumeLevel(0.5);
    }
    this->setWindowTitle("Vision (dev)"); // Window Title
    /*W.I.P. make QSlider that would go to the place where user has pressed*/
    //MouseTrackingSlider *progresslSlider;
    //ui->progresslSlider = new MouseTrackingSlider();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PlayPauseButton_clicked()
{
    this->togglePlayback(false);
}

void MainWindow::updateData(){
    ui->TitleLabel->setText(audio.title);
    ui->ArtistLabel->setText(audio.author);
    ui->AlbumTitleLabel->setText(audio.album);
    ui->labelCover->setPixmap(audio.cover.isNull() ? QPixmap(":/V-Cover-Art-dev.png") : QPixmap::fromImage(audio.cover));
    QString debugCoverMsg = audio.cover.isNull() ? "Cover Art was not found or is empty!" : "Cover Art was found and set";
    qDebug() << debugCoverMsg;
}

void MainWindow::on_comboBox_activated(int index)
{
    if(index==0){

        QString audioFileName = QFileDialog::getOpenFileName(this,
                                                tr("Open Audio File"), "/home/sergiu/Music", tr("Audio Files (*.mp3 *.flac)"));
        if (audioFileName == ""){
            qDebug("File path is empty, nothing to do..");
            return;
        }
        audio.setAudioPath(audioFileName);
        this->togglePlayback(true); // Start playing right after discovering new path
    }
}

void MainWindow::on_VolumeLevelScrollBar_valueChanged(int value)
{
    audio.setVolumeLevel((float)value / 100);
}

void  MainWindow::updateVolumeElements(){
    /*When the global variable for volume changes make sure that the GUI displays it correctly*/
    qint8 audioInt = round(audio.volume * 100);
    if(ui->VolumeLevelScrollBar->value() != audioInt){
        ui->VolumeLevelScrollBar->setValue(audioInt);
    }
    ui->AudioVolumeLabel->setText(QString("%1%2")
                           .arg(audioInt)
                           .arg("%"));
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
    ui->progresslSlider->setMaximum(audio.duration);
    ui->progresslSlider->setPageStep(audio.duration*0.10);
    ui->progresslSlider->setValue(audio.position);
}
void MainWindow::togglePlayback(bool forcePlay){
    audio.onPlay = !audio.onPlay;
    if(forcePlay){
        audio.onPlay = true;
    }
    if(audio.onPlay){
        ui->PlayPauseButton->setIcon(QIcon::fromTheme("media-playback-pause"));
        audio.start();

    }else {
        ui->PlayPauseButton->setIcon(QIcon::fromTheme("media-playback-start"));
        audio.pause();
    }
    qDebug() << "Play is set to" << (audio.onPlay ? "True (Playing)" : "False (Not playing)");

}

void MainWindow::on_progresslSlider_valueChanged(int value)
{
    if(value == audio.position){ // When we change the value for it using setValue(audio.position) the signal triggers this function as well, this helps to reduce this recursion
        return;
    }
    qDebug() << value;
    audio.setPosition(value);
}
