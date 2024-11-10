#ifndef PLAYLISTITEMWIDGET_H
#define PLAYLISTITEMWIDGET_H

#include <QtWidgets>

class PlaylistItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlaylistItemWidget(QWidget *parent = nullptr, QString time = "00:00:00", QString title = "--", QString path = "", int id = 0);
    int id;
    QString time;
    QString title;
    QString path;

signals:
};

#endif // PLAYLISTITEMWIDGET_H
