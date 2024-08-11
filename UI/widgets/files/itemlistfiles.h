#ifndef ITEMLISTFILES_H
#define ITEMLISTFILES_H

#include <QtWidgets>

#include "../miniplayer/miniplayer.h"

class itemlistfiles : public QGroupBox
{

    Q_OBJECT

public:
    itemlistfiles(QWidget *parent = nullptr);

    QString pathFile;
    QString titleFile;

    void setPathFile(QString path);
    void setDuration(qint64 duration);
    void setTitleFile(QString title);

    MiniPlayer *player;

private:
    QLabel *titleFileLabel;
    QLabel *durationFileLabel;

signals:
    void loadPlayer(const QString &path);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // ITEMLISTFILES_H
