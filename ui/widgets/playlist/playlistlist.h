#ifndef PLAYLISTLIST_H
#define PLAYLISTLIST_H

#include <QtWidgets>

#include "../../../backend/playlist/openplaylist.h"

class PlaylistList : public QObject
{
    Q_OBJECT
public:
    explicit PlaylistList(QWidget *parent = nullptr);

private:
    QWidget *parent;
    OpenPlaylist *OpenPlaylistBackend;

public slots:
    void openPlaylist(QDate date, QString hour);
    void updatePlaylist(QDate date);

private slots:
    void loadPlayer(QString path);

signals:
    void clicked(QString path);
};

#endif // PLAYLISTLIST_H
