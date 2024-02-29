#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QMediaFormat>
#include <QFileDialog>
#include <QTableView>
#include <QStandardItemModel>

Audio audio;
Source source;
Waveform waveform;

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
    QObject::connect(&source, &Source::libraryChanged, this, &MainWindow::updateLibraryElements);
    QObject::connect(&audio, &Audio::playlistItemChanged, this, &MainWindow::updateLibrarySelectedItem);
    QObject::connect(&audio, &Audio::requestNextPlaylist, this, &MainWindow::playNextPlaylist);
    if(!audio.volume){ // If the volume value is absent set it
        audio.setVolumeLevel(0.5);
    }
    ui->LibraryEmptyFrame->setVisible(source.libraryPaths.isEmpty()); // Enable/Disable pop-up frame for getting source
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
    ui->BitrateLabel->setText(QString("%1 kpbs").arg(audio.bitrate/1000));
    ui->CodecLabel->setText(audio.codec);
    ui->TypeLabel->setText(audio.type);
    ui->CentralBackgroundLabel->setPixmap(audio.cover.isNull() ? QPixmap("") : QPixmap::fromImage(audio.cover));
    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect;
    blurEffect->setBlurRadius(20);
    ui->CentralBackgroundLabel->setGraphicsEffect(blurEffect);
    QString debugCoverMsg = audio.cover.isNull() ? "Cover Art was not found or is empty!" : "Cover Art was found and set";
    qDebug() << debugCoverMsg;
}

void  MainWindow::updateVolumeElements(){
    /*When the global variable for volume changes make sure that the GUI displays it correctly*/
    qint8 audioInt = round(audio.volume * 100);
    if(ui->VolumeLevelSlider->value() != audioInt){
        ui->VolumeLevelSlider->setValue(audioInt);
    }
    ui->AudioVolumeLabel->setText(QString("%1%2")
                           .arg(audioInt)
                           .arg("%"));
}

void MainWindow::updateLibraryElements(){
    ui->LibraryEmptyFrame->setVisible(false);
    ui->LibraryPathsAmountLabel->setText(QString("Dir(s): %1").arg(source.libraryPathsAmount));
    ui->LibraryFilesAmountLabel->setText(QString("File(s): %1").arg(source.libraryFilesAmount));
    ui->LibraryListWidget->clear();
    quint16 position = 0;
    foreach(QString path, source.libraryPaths){
        QListWidgetItem* pathItem = new QListWidgetItem(path, ui->LibraryListWidget);
        pathItem->font().bold();
        pathItem->setFlags(Qt::NoItemFlags);
        pathItem->setToolTip(path);
        pathItem->setWhatsThis("Directory");
        uiLibraryPositions[path] = position;
        position += source.libraryFiles[path].size() + 1;
        foreach(QString file,source.libraryFiles[path]){
            QListWidgetItem* item = new QListWidgetItem(file, ui->LibraryListWidget);
            item->setToolTip(path);
            item->setWhatsThis("Audio file");

        }
    }
}

void MainWindow::updateLibrarySelectedItem(){
    ui->LibraryListWidget->item(this->uiLibraryPositions[audio.playlistPath] + audio.playlistPosition+1)->setSelected(true);
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
void MainWindow::togglePlayback(bool forceStart){
    audio.onPlay = !audio.onPlay;
    if(forceStart){
        audio.onPlay = true;
    }
    if(audio.onPlay){
        ui->PlayPauseButton->setIcon(QIcon::fromTheme("media-playback-pause"));
        if(audio.isPaused && !forceStart){
            audio.resume();
        }
        else{
            audio.start();
        }

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

void MainWindow::on_SelectFileButton_clicked()
{
    QString audioFileName = QFileDialog::getOpenFileName(this,
                                                         tr("Open Audio File"),
                                                         QDir::homePath(),
                                                         tr("Audio Files (*.mp3 *.flac *.wav)"));
    source.addFile(audioFileName);
    this->togglePlayback(true); // Start playing right after discovering new path
}


void MainWindow::on_SelectLibraryButton_clicked()
{
    QString audioDirectory = QFileDialog::getExistingDirectory(this,
                                                         tr("Select library location"),
                                                        QDir::homePath(),
                                                         QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    source.HandlePath(audioDirectory);
}


void MainWindow::on_LibraryListWidget_itemClicked(QListWidgetItem *item)
{
    if(item->whatsThis() != "Audio file"){ // One way to check if the item is an actual audio file
        return;
    }
    audio.setAudioPath(item->toolTip() + "/" +  item->text());
    audio.setPlaylist(source.libraryFiles[item->toolTip()],item->toolTip(), source.getIndexOfItem(item->text(),item->toolTip()));
    this->togglePlayback(true);
}


void MainWindow::on_SeekForwardButton_clicked()
{
    audio.playNextItem();
}


void MainWindow::on_SeekBackwardButton_clicked()
{
    audio.playPastItem();
}



void MainWindow::on_VolumeLevelSlider_valueChanged(int value)
{
    audio.setVolumeLevel((float)value / 100);
}


void MainWindow::on_AddFileButton_clicked()
{
    QString audioFileName = QFileDialog::getOpenFileName(this,
                                                         tr("Open Audio File"),
                                                         QDir::homePath(),
                                                         tr("Audio Files (*.mp3 *.flac *.wav)"));
    source.addFile(audioFileName);
    waveform.create(audioFileName); // For testing
}


void MainWindow::on_AddDirectoryButton_clicked()
{
    QString audioDirectory = QFileDialog::getExistingDirectory(this,
                                                               tr("Select library location"),
                                                               QDir::homePath(),
                                                               QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    source.HandlePath(audioDirectory);
}


void MainWindow::on_RepeatPlaylistButton_clicked()
{
    QString iconColor = "white"; // later just change icon
    audio.changePlaylistRepeat();
    if(audio.everythingRepeat){
        iconColor = "green";
    }
    else if(audio.playlistRepeat){
        iconColor = "blue";
    }
    else if(audio.songRepeat){
        iconColor = "red";
    }


    QString styleSheet = "QPushButton {"
                         "    background-color: " + iconColor + ";"
                                       "}";
    ui->RepeatPlaylistButton->setStyleSheet(styleSheet);

}

void MainWindow::playNextPlaylist(){
    /*This function is used for helping Audio class to figure out the next playlist available (only when Repeat: Everything is selected)*/
    QListWidgetItem *nextItem = ui->LibraryListWidget->item(this->uiLibraryPositions[audio.playlistPath] + audio.playlistPosition+3); // Check if the next element for the next playlist (entry) exists in ListLibraryWidget
    QListWidgetItem *pastItem = ui->LibraryListWidget->item(1); // In case it doesnt start from the start
    if(nextItem){
        audio.setPlaylist(source.libraryFiles[nextItem->toolTip()],nextItem->toolTip(), source.getIndexOfItem(nextItem->text(),nextItem->toolTip()));
        audio.setAudioPath(nextItem->toolTip() + "/" +  nextItem->text());
    }
    else{
        audio.setPlaylist(source.libraryFiles[pastItem->toolTip()],pastItem->toolTip(), source.getIndexOfItem(pastItem->text(),pastItem->toolTip()));
        audio.setAudioPath(pastItem->toolTip() + "/" +  pastItem->text());
    }
    this->updateLibrarySelectedItem();
    audio.start();
}
