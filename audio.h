#ifndef AUDIO_H
#define AUDIO_H

#include <QPixmap>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaMetaData>
#include <QFloat16>
#include <QObject>

class Audio : public QObject
{
    Q_OBJECT
public:
    Audio();
    void init();
    void start();
    void pause();
    bool onPlay;
    bool isPaused;

    QString title;
    QString author;
    QString album;
    QImage cover;
    qint64 duration;
    qint64 position;
    QString audioPath;
    QString audioName;
    qfloat16 volume;

    QStringList playlist;
    QString playlistPath;
    qint8 playlistPosition;
    bool playlistRepeat = false;

public slots:
    void getMediaInfo();
    void setAudioPath(QString path);
    void setVolumeLevel(qfloat16 volume);
    void updatePosition();
    void setPosition(qint64 position);
    void resume();
    void autoPlayNextItem();
    void playNextItem();
    void playPastItem();
    void setPlaylist(QStringList playlist,QString path, qint16 startFromPosition);
    bool decreasePlaylistPosition();
    bool increasePlaylistPosition();
signals:
    void mediaInfoChanged();
    void positionChanged();
    void volumeChanged();
    void playlistItemChanged();
private:

    QMediaPlayer *player;
    QAudioOutput *audioOutput;
};


#endif // AUDIO_H
