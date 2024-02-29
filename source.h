#ifndef SOURCE_H
#define SOURCE_H

#include <QObject>
#include <QList>
#include <QDir>

class Source : public QObject
{
    Q_OBJECT
public:
    Source();

    QList <QString>libraryPaths;

    QMap<QString, QStringList> libraryFiles;

    quint16 libraryFilesAmount;
    quint16 libraryPathsAmount;

public slots:

    void HandlePath(QString path);

    void addFile(QString path);

    void updateAmountOfAllItems();

    qint16 getIndexOfItem(QString filename,QString directory);

signals:

    void libraryChanged();
};

#endif // SOURCE_H
