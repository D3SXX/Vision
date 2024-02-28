#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QForeach>
#include <QGraphicsBlurEffect>
#include "mousetrackingslider.h"
#include "audio.h"
#include "source.h"

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

    void togglePlayback(bool forcePlay);

    void updatePosition();

    void updateVolumeElements();

    void on_progresslSlider_valueChanged(int value);

    void on_SelectFileButton_clicked();

    void on_SelectLibraryButton_clicked();

    void updateLibraryElements();

    void on_LibraryListWidget_itemClicked(QListWidgetItem *item);

    void updateLibrarySelectedItem();

    void on_SeekForwardButton_clicked();

    void on_SeekBackwardButton_clicked();

    void on_VolumeLevelSlider_valueChanged(int value);


    void on_AddFileButton_clicked();

    void on_AddDirectoryButton_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
