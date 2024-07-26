#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QtWidgets>


class Playlist : public QWidget
{
    Q_OBJECT
public:
    explicit Playlist(QWidget *parent = nullptr);

    bool loadPlaylist(QString date);
    bool loadHour(QString hour);

private:
    QVBoxLayout *boxLayout;
    QString playlistDB;

    QJsonDocument jsonPlaylist;

signals:
};

#endif // PLAYLIST_H
