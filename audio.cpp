#include "audio.h"
#include "mainwindow.h"
Audio::Audio() {
}

void Audio::init(){
    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
}
void Audio::start(){
    player->setSource(QUrl::fromLocalFile(this->audioPath));
    qDebug ()<< this->audioPath;
    audioOutput->setVolume(0.5);
    player->play();
    QObject::connect(player, &QMediaPlayer::metaDataChanged, this, &Audio::getMediaInfo);
}
void Audio::pause(){
    player->pause();
}

void Audio::getMediaInfo(){
    QMediaMetaData metaDataMap = player->metaData();
    this->title = player->metaData().stringValue(QMediaMetaData::Title);
    this->author = player->metaData().stringValue(QMediaMetaData::Author);
    if(this->author == ""){ // Change this if structure for something better in the future
        this->author = player->metaData().stringValue(QMediaMetaData::Composer);
    }
    if(this->author == ""){
        this->author = player->metaData().stringValue(QMediaMetaData::AlbumArtist);
    }
    if(this->author == ""){
        this->author = player->metaData().stringValue(QMediaMetaData::ContributingArtist);
    }
    this->album = player->metaData().stringValue(QMediaMetaData::AlbumTitle);
    QVariant variant = player->metaData().value(QMediaMetaData::CoverArtImage);
    if(variant.isNull()){
        variant = player->metaData().value(QMediaMetaData::ThumbnailImage);
    }
    QImage image = variant.value<QImage>();
    this->cover = image;
    qDebug() << "Title:" << this->title;
    qDebug() << "Author:" << this->author;
    qDebug() << "Album:" << this->album;
    qDebug() << "Cover Art:" << this->cover.width() <<"x"<< this->cover.height();
    emit mediaInfoChanged();
}
void Audio::setAudioPath(QString path){

    this->audioPath = path;
}
void Audio::setVolumeLevel(float volume){
    audioOutput->setVolume(volume);
    qDebug()<<volume;
}
