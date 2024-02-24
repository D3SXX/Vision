#ifndef AUDIO_H
#define AUDIO_H

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
public slots:
    void getMediaInfo();
signals:
    void mediaInfoChanged();
private:

    QMediaPlayer *player;
    QAudioOutput *audioOutput;
};


#endif // AUDIO_H
