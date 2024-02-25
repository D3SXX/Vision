#ifndef CONTROLS_H
#define CONTROLS_H
#include <QFloat16>
#include <QObject>

class Controls : public QObject
{
    Q_OBJECT
public:
    Controls();
    bool onPlay;
    qfloat16 audioVolume;

public slots:
    void updateVolumeFromScrollBar(int);
signals:
    void volumeChanged();
};



#endif // CONTROLS_H
