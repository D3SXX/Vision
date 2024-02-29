#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <QObject>
#include <QImage>
#include <QAudioDecoder>
#include <QUrl>
#include <QPainter>
#include <QImageWriter>

class Waveform : public QObject
{
    Q_OBJECT
public:
    Waveform();
    void create(QString filepath);
    QAudioDecoder *decoder;
    QAudioFormat format;

public slots:

    void updateProgress();

    void bufferReady();




};

#endif // WAVEFORM_H
