#include "waveform.h"

Waveform::Waveform() {
    decoder = new QAudioDecoder;
    QObject::connect(decoder, &QAudioDecoder::positionChanged, this, &Waveform::updateProgress);
    QObject::connect(decoder, &QAudioDecoder::durationChanged, this, &Waveform::updateProgress);
    QObject::connect(decoder, &QAudioDecoder::bufferReady, this, &Waveform::bufferReady);
}

void Waveform::create(QString filepath){
    if(decoder->isDecoding()){
        decoder->stop();
    }
    decoder->setSource(QUrl::fromLocalFile(filepath));
    decoder->start();
}


void Waveform::updateProgress()
{
   // qDebug() << QString("Decoding progress: %1 - %2 (%3)").arg(decoder->position()).arg(decoder->duration()).arg(decoder->isDecoding() ? "Ongoing" : "Paused");
}

void Waveform::bufferReady(){
    QString outputPath = "/home/d3sx/repositories/C++/Vision/image.png";
    //qDebug() << "Buffer is ready";
    QAudioBuffer buffer = decoder->read();
    this->format = buffer.format();
    const int width = buffer.frameCount(); // Width of the waveform image
    const int height = 500; // Height of the waveform image
    QImage waveformImage(width, height, QImage::Format_RGB32);
    waveformImage.fill(Qt::white);

    QPainter painter(&waveformImage);
    painter.setPen(Qt::black);

    const qint64 duration = decoder->duration();
    const int sampleRate = format.sampleRate();

    const int numSamples = duration * sampleRate;
    const int samplesPerPixel = numSamples / width;

    const qint64 numBufferSamples = buffer.frameCount();
    //qDebug() << QString("image: %1 duration: %2 | sampleRate: %3 | numSamples: ‰4 SamplePerPixel: ‰5").arg(QString("%1x%2").arg(width).arg(height)).arg(duration).arg(sampleRate).arg(numSamples).arg(samplesPerPixel);
    qint64 xPosition = 1;
    QVector<qreal> peaks;
    qint16 pastValue = 0;
    for (int i = 0; i < numBufferSamples; i++) {
        const qint16 value = buffer.data<qint16>()[i] / 50;
        //painter.drawLine(xPosition/samplesPerPixel,pastValue,xPosition / samplesPerPixel,value);
        painter.drawLine(i, 0, i+1, value);
        pastValue = value;
        xPosition++;
    }

    painter.end();

    QImageWriter writer(outputPath);
    if (!writer.write(waveformImage)) {
        qDebug() << "Error writing waveform image:" << writer.errorString();
        return;
    }

    //qDebug() << "Waveform image saved to:" << outputPath;

}
