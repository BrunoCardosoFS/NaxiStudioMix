#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QtWidgets>
#include "../../backend/audio/audioplayer.h"

namespace Ui {
class PlayerWidget;
}

class PlayerWidget : public QGroupBox
{
    Q_OBJECT

public:
    explicit PlayerWidget(QWidget *parent = nullptr);
    ~PlayerWidget();

private:
    Ui::PlayerWidget *ui;

    AudioPlayer *Player;

    QString loadPath;

signals:
    void loaded(bool loaded);

public slots:
    void updateDuration(qint64 durationms, QString duration);
    void updatePosition(qint64 positionms, QString position);

    void setPlayShortcut(QString key);
    void setPauseShortcut(QString key);
    void setStopShortcut(QString key);

    void loadPlayer(QString path);
    void unloadPlayer();

private slots:
    void updateTitle(QString title);
    void on_play_clicked();
    void on_pause_clicked();
    void on_stop_clicked();
    void on_slider_sliderMoved(int position);
    void on_load_media_clicked();
};

#endif // PLAYERWIDGET_H
