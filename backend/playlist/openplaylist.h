#ifndef OPENPLAYLIST_H
#define OPENPLAYLIST_H

#include <QtWidgets>

class OpenPlaylist : public QObject
{
    Q_OBJECT
public:
    explicit OpenPlaylist(QObject *parent = nullptr);

private:
    QString pathDB;
    QJsonDocument currentPlaylist;
    QDate currentDate;

public slots:
    QJsonArray openPlaylist(QDate date, QString hour);
    void updatePlaylist(QDate date);

signals:
    void savedPlaylist(bool saved);
};

#endif // OPENPLAYLIST_H
