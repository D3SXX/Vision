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
    filters << "*.mp3" << "*.wav";
    directory.setNameFilters(filters);
    QStringList audioFiles = directory.entryList();
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
