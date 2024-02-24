#ifndef AUDIO_H
#define AUDIO_H

#include <QPixmap>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaMetaData>
#include <QObject>

class Audio : public QObject
{
    Q_OBJECT
public:
    Audio();
    void init();
    void start();
    void pause();
    QString title;
    QString author;
    QString album;
    QImage cover;

    qint64 duration;
    qint64 position;

public slots:
    void getMediaInfo();
    void updatePosition();
signals:
    void mediaInfoChanged();
    void positionChanged();
private:

    QMediaPlayer *player;
    QAudioOutput *audioOutput;
};


#endif // AUDIO_H
