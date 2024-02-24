#include "audio.h"
#include "mainwindow.h"

Audio::Audio() {
}

void Audio::init(){
    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    QObject::connect(player, &QMediaPlayer::metaDataChanged, this, &Audio::getMediaInfo);
    QObject::connect(player, &QMediaPlayer::positionChanged, this, &Audio::updatePosition);
}
void Audio::start(){
    player->setSource(QUrl("qrc:/Vision.mp3"));
    audioOutput->setVolume(50);
    player->play();

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
    this->duration = player->duration();
    qDebug() << "Title:" << this->title;
    qDebug() << "Author:" << this->author;
    qDebug() << "Album:" << this->album;
    qDebug() << "Cover Art:" << this->cover.width() <<"x"<< this->cover.height();
    emit mediaInfoChanged();
}

void Audio::updatePosition(){
    this->position = player->position();
    emit positionChanged();
}
