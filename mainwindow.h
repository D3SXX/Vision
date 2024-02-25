#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mousetrackingslider.h"
#include "audio.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateData();

private slots:

    void on_PlayPauseButton_clicked();

    void on_comboBox_activated(int index);

    void on_VolumeLevelScrollBar_valueChanged(int value);

    void togglePlayback(bool forcePlay);

    void updatePosition();

    void updateVolumeElements();

    void on_progresslSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
