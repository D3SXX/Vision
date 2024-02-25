#ifndef MOUSETRACKINGSLIDER_H
#define MOUSETRACKINGSLIDER_H

#include <QSlider>
#include <QMouseEvent>
#include <QStyle>
#include <QStyleOption>

class MouseTrackingSlider : public QSlider
{
    Q_OBJECT
public:
    explicit MouseTrackingSlider(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // MOUSETRACKINGSLIDER_H
