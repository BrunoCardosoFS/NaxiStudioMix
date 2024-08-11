#ifndef MINIPLAYER_H
#define MINIPLAYER_H

#include <QWidget>
#include <QtMultimedia>

namespace Ui {
class MiniPlayer;
}

class MiniPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit MiniPlayer(QWidget *parent = nullptr, QString path = nullptr);
    ~MiniPlayer();

    QString int2time(qint64 time);

    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);

private slots:

    void on_AudioSlider_sliderMoved(int position);
    void on_AudioSlider_sliderPressed();
    void on_AudioSlider_sliderReleased();

    void on_Play_clicked();
    void on_Pause_clicked();
    void on_Stop_clicked();

    void on_Repeat_clicked();

private:
    Ui::MiniPlayer *ui;

    QMediaPlayer *player;
    QAudioOutput *output;

    bool isReapeat;
    qint64 audioDuration;
};

#endif // MINIPLAYER_H
