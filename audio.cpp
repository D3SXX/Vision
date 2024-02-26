#include "audio.h"
#include "mainwindow.h"
Audio::Audio() {
}

void Audio::init(){
    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    QObject::connect(player, &QMediaPlayer::metaDataChanged, this, &Audio::getMediaInfo);
    QObject::connect(player, &QMediaPlayer::positionChanged, this, &Audio::updatePosition); // For progress bar/slider
    QObject::connect(player, &QMediaPlayer::playingChanged, this, &Audio::playNextItem);
}
void Audio::start(){
    qDebug ()<< this->audioPath;
    player->setSource(QUrl::fromLocalFile(this->audioPath));
    audioOutput->setVolume(this->volume);
    player->play();
}

void Audio::resume(){
    player->play();
    this->isPaused = false;
}

void Audio::pause(){
    player->pause();
    this->isPaused = true;
}

void Audio::getMediaInfo(){
    QMediaMetaData metaDataMap = player->metaData();
    this->title = player->metaData().stringValue(QMediaMetaData::Title).isEmpty() ? this->audioName : player->metaData().stringValue(QMediaMetaData::Title);
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
void Audio::setAudioPath(QString path){
    this->audioPath = path;
    /*Safe way of getting filename from filepath, maybe change it later for something more efficient*/
    QFileInfo fileInfo(path);
    QString filename = fileInfo.fileName();
    this->audioName = filename;
}
void Audio::setVolumeLevel(qfloat16 volume){
    this->volume = volume;
    audioOutput->setVolume(volume);
    qDebug()<<volume;
    emit volumeChanged();
}

void Audio::setPlaylist(QStringList playlist,QString path, qint16 startFromPosition){
    this->playlist = playlist;
    this->playlistPath = path;
    this->playlistPosition = startFromPosition;
    qDebug("New playlist was loaded");
    foreach(QString item, playlist){
        qDebug() << item;
    }
    qDebug() << "Starting position is set to" << startFromPosition;
}

void Audio::updatePosition(){
    this->position = player->position();
    emit positionChanged();
}

void Audio::setPosition(qint64 position){
    player->setPosition(position);
}

void Audio::playNextItem(){
    if(!player->isPlaying() && this->position == this->duration){ // Checking if it is not the start and the pause was not triggered by user
        this->playlistPosition++;
        this->setAudioPath(this->playlistPath + "/" + this->playlist[this->playlistPosition]); // Get the next audiopath
        this->start();
        emit playlistItemChanged();
    }
}
