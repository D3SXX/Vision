#include "source.h"

Source::Source() {}


void Source::HandlePath(QString path){
    if (path.isNull()){
        qDebug("Directory's path is empty, nothing to do..");
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
    this->updateAmountOfAllItems();
    emit libraryChanged();
}

void Source::addFile(QString path){
    if (path.isNull()){
        qDebug("File's path is empty, nothing to do..");
        return;
    }
    qDebug() << "Got file" << path;
    QFileInfo fileInfo(path);
    QString directoryPath = fileInfo.path();
    QString fileName = fileInfo.fileName();
    this->libraryPaths.append(directoryPath);
    QStringList filenameList = {fileName};
    this->libraryFiles[directoryPath] =  filenameList;
    this->updateAmountOfAllItems();
    emit libraryChanged();
}

qint16 Source::getIndexOfItem(QString filename,QString directory){
    QStringList files = this->libraryFiles[directory];
    qint16 k = files.indexOf(filename);
    return files.indexOf(filename);
}

void Source::updateAmountOfAllItems(){
    quint16 filesAmount = 0;
    foreach (QString path, this->libraryPaths) {
        filesAmount += this->libraryFiles[path].size();
    }
    this->libraryFilesAmount = filesAmount;
    this->libraryPathsAmount = this->libraryPaths.size();
}
