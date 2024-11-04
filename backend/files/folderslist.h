#ifndef FOLDERSLIST_H
#define FOLDERSLIST_H

#include <QObject>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class FoldersList : public QObject
{
    Q_OBJECT
public:
    explicit FoldersList(QObject *parent = nullptr);

    QJsonArray foldersArray;

private:
    QString pathDB;

signals:
};

#endif // FOLDERSLIST_H
