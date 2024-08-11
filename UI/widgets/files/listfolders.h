#ifndef LISTFOLDERS_H
#define LISTFOLDERS_H

#include <QtWidgets>

#include "itemlistthread.h"


class listFolders : public QWidget
{
    Q_OBJECT
public:
    listFolders(QMainWindow *parent = nullptr);
    void searchFilesList(QString search);

    QJsonArray folders;
    QList<QWidget*> *typesWidgets;

public slots:
    void emitLoadPlayer(const QString &path);
    void finishedLoad(const QJsonArray list);

signals:
    void loadPlayer(const QString &path);

private:
    QGridLayout *jinglesLayout;
    QGridLayout *musicsLayout;
    QGridLayout *othersLayout;
    QGridLayout *commercialsLayout;

    itemListThread *thread;

    QWidget *foldersList;
    QWidget *filesList;

    QString currentPath;

    void openCatalog(QString path);
    void loadFilesList(QString path);
};

#endif // LISTFOLDERS_H
