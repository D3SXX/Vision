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
    QString title;
    QString author;
    QString album;
    QImage cover;
    qint64 duration;
    qint64 position;
    QString audioPath;
    qfloat16 volume;


public slots:
    void getMediaInfo();
    void setAudioPath(QString path);
    void setVolumeLevel(qfloat16 volume);
    void updatePosition();
    void setPosition(qint64 position);
signals:
    void mediaInfoChanged();
    void positionChanged();
    void volumeChanged();
private:

    QMediaPlayer *player;
    QAudioOutput *audioOutput;
};


#endif // AUDIO_H
