#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QtCore>
#include <QtWidgets>
#include <QtMultimedia>

QT_BEGIN_NAMESPACE
namespace Ui {
class player;
}
QT_END_NAMESPACE

class player : public QMainWindow
{
    Q_OBJECT

public:
    player(QWidget *parent = nullptr);
    ~player();

private slots:
    void loadPlayer(qint8 player, QString path);

    void on_player1Play_clicked();
    void on_player1Pause_clicked();
    void on_player1Stop_clicked();
    void on_player1Slider_sliderMoved(int position);

    void on_player2Play_clicked();
    void on_player2Pause_clicked();
    void on_player2Stop_clicked();
    void on_player2Slider_sliderMoved(int position);

    void on_player3Play_clicked();
    void on_player3Pause_clicked();
    void on_player3Stop_clicked();
    void on_player3Slider_sliderMoved(int position);

    void on_openMusic_clicked();
    void on_openMusic1_clicked();
    void on_openMusic2_clicked();

private:
    void updateDuration(qint64 duration, qint8 player);
    void updateProgress(qint64 progress, qint8 player);

    Ui::player *ui;
    QMediaPlayer *MPlayer1;
    QMediaPlayer *MPlayer2;
    QMediaPlayer *MPlayer3;

    QAudioOutput *MPlayer1AudioOutput;
    QAudioOutput *MPlayer2AudioOutput;
    QAudioOutput *MPlayer3AudioOutput;

    qint64 M1Duration;
    qint64 M2Duration;
    qint64 M3Duration;

};
#endif // PLAYER_H
