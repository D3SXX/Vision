#ifndef CUSTOMLISTITEM_H
#define CUSTOMLISTITEM_H

#include <QListWidgetItem>

class CustomListItem : public QListWidgetItem {
public:
    CustomListItem(const QString& text, const QString& absolutePath)
        : QListWidgetItem(text), m_absolutePath(absolutePath) {}

    QString absolutePath() const { return m_absolutePath; }

private:
    QString m_absolutePath;
};


#endif // CUSTOMLISTITEM_H
