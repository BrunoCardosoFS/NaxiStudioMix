#ifndef PLAYLISTITEM_H
#define PLAYLISTITEM_H

#include <QtWidgets>

class PlaylistItem : public QGroupBox
{
    Q_OBJECT
public:
    explicit PlaylistItem(QWidget *parent = nullptr);

    void setDuration(qint64 duration);
    void setTitle(QString title);
    void setPath(QString path);

private:
    QHBoxLayout *layout;
    QString pathFile;
    QLabel *played;
    QLabel *duration;
    QLabel *titleFile;

signals:
};

#endif // PLAYLISTITEM_H
