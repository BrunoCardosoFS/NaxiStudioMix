#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QtCore>
#include <QtWidgets>
#include <QtMultimedia>
#include <QTimer>

#include "configurations.h"
#include "./widgets/listfolders.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class player;
}
QT_END_NAMESPACE

class Player : public QMainWindow
{
    Q_OBJECT

public:
    Player(QWidget *parent = nullptr);

    QString teste;

    ~Player();

public slots:
    void updateClock();

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

    void on_openConfig_clicked();

    void on_openPlaylist_clicked();

private:
    void initApp();

    void openCatalog(QString path);

    void updateDuration(qint64 duration, qint8 player);
    void updateProgress(qint64 progress, qint8 player);

    void loadFoldersCatalog();
    void loadMediasCatalog(QListWidgetItem *item);

    Ui::player *ui;

    QTimer *dateTime;

    QMediaPlayer *MPlayer1;
    QMediaPlayer *MPlayer2;
    QMediaPlayer *MPlayer3;

    QAudioOutput *MPlayer1AudioOutput;
    QAudioOutput *MPlayer2AudioOutput;
    QAudioOutput *MPlayer3AudioOutput;

    QJsonArray foldersMusic;
    QJsonArray foldersJingle;
    QJsonArray foldersOther;
    QJsonArray foldersCommercial;

    listFolders *folders;

    Configurations *windowConfig;


};
#endif // PLAYER_H
