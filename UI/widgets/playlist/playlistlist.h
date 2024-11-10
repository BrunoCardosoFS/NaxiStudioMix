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

signals:
};

#endif // PLAYLISTLIST_H
