#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controls.h"
#include <QMediaPlayer>
#include <QAudioOutput>

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

private slots:

    void on_PlayPauseButton_clicked();

    void on_widget_4_windowIconChanged(const QIcon &icon);

    void on_widget_4_windowIconTextChanged(const QString &iconText);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
};
#endif // MAINWINDOW_H
