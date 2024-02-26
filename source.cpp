#include "source.h"

Source::Source() {}


void Source::HandlePath(QString path){
    if (path.isNull()){
        qDebug("File path is empty, nothing to do..");
        return;
    }
    qDebug() << "Got folder" << path;
    QDir directory(path);
    QStringList filters;
    filters << "*.mp3" << "*.flac" << "*.wav"; // Add more filetypes later
    directory.setNameFilters(filters);
    QStringList audioFiles = directory.entryList(); // Get every audio file
    if(audioFiles.isEmpty()){
        qDebug("No Audio files were found, nothing to do..");
        return;
    }
    foreach(QString filename, audioFiles) {
        qDebug() << filename;
    }
    this->libraryPaths.append(path);
    this->libraryFiles[path] = audioFiles;
    emit libraryChanged();
}

void Source::addFile(QString path){

}

qint16 Source::getIndexOfItem(QString filename,QString directory){
    QStringList files = this->libraryFiles[directory];
    qint16 k = files.indexOf(filename);
    return files.indexOf(filename);
}
