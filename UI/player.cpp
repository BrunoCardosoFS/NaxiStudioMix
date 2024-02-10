#include "player.h"
#include "./ui_player.h"

#include <QFileInfo>
#include <QDateTime>
#include<QDebug>

player::player(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::player)
{
    ui->setupUi(this);


    // Creating date and time

    dateTime = new QTimer(this);
    updateClock();
    connect(dateTime, SIGNAL(timeout()), this, SLOT(updateClock()));
    dateTime->start(1000);


    // Creating and configuring players

    MPlayer1 = new QMediaPlayer();
    MPlayer1AudioOutput = new QAudioOutput();
    MPlayer1AudioOutput->setVolume(100);
    MPlayer1->setAudioOutput(MPlayer1AudioOutput);

    MPlayer2 = new QMediaPlayer();
    MPlayer2AudioOutput = new QAudioOutput();
    MPlayer2AudioOutput->setVolume(100);
    MPlayer2->setAudioOutput(MPlayer2AudioOutput);

    MPlayer3 = new QMediaPlayer();
    MPlayer3AudioOutput = new QAudioOutput();
    MPlayer3AudioOutput->setVolume(100);
    MPlayer3->setAudioOutput(MPlayer3AudioOutput);


    // Connect players

    connect(MPlayer1, &QMediaPlayer::durationChanged, this, [=](qint64 duration){updateDuration(duration, 0);});
    connect(MPlayer1, &QMediaPlayer::positionChanged, this, [=](qint64 progress){updateProgress(progress, 0);});

    connect(MPlayer2, &QMediaPlayer::durationChanged, this, [=](qint64 duration){updateDuration(duration, 1);});
    connect(MPlayer2, &QMediaPlayer::positionChanged, this, [=](qint64 progress){updateProgress(progress, 1);});

    connect(MPlayer3, &QMediaPlayer::durationChanged, this, [=](qint64 duration){updateDuration(duration, 2);});
    connect(MPlayer3, &QMediaPlayer::positionChanged, this, [=](qint64 progress){updateProgress(progress, 2);});
}

player::~player()
{
    delete ui;
}

// Updating clock
void player::updateClock(){
    QDateTime currentTime = QDateTime::currentDateTime();
    ui->dateTime->setText(currentTime.toString("dd/MM/yyyy  hh:mm:ss"));
}


// Updating player times

void player::updateDuration(qint64 duration, qint8 player)
{
    QList playerSlider = {ui->player1Slider, ui->player2Slider, ui->player3Slider};
    QList playerDuration = {ui->player1Duration, ui->player2Duration, ui->player3Duration};

    QTime totalTime((duration / 3600000) % 60, (duration / 60000) % 60, (duration / 1000) % 60, (duration) % 1000);

    QString timeMediaFormat = "mm:ss:zzz";
    if(duration > 3600000){
        timeMediaFormat = "hh:mm:ss";
    }

    playerSlider[player]->setRange(0, duration / 100);
    playerDuration[player]->setText(totalTime.toString(timeMediaFormat));
}

void player::updateProgress(qint64 progress, qint8 player){
    QList playerTime = {ui->player1Time, ui->player2Time, ui->player3Time};
    QList playerSlider = {ui->player1Slider, ui->player2Slider, ui->player3Slider};

    QTime CurrentTime((progress / 3600000) % 60, (progress / 60000) % 60, (progress / 1000) % 60, (progress) % 1000);

    QString timeMediaFormat = "mm:ss:zzz";
    if(progress > 3600000){
        timeMediaFormat = "hh:mm:ss";
    }

    playerSlider[player]->setValue(progress / 100);
    playerTime[player]->setText(CurrentTime.toString(timeMediaFormat));
}


// Temporary buttons

void player::on_openMusic_clicked()
{
    QString FileName = QFileDialog::getOpenFileName(this, tr("Selecionar Audio"), "", tr("MP3 Files (*.mp3)"));
    loadPlayer(0, FileName);
}

void player::on_openMusic1_clicked()
{
    QString FileName = QFileDialog::getOpenFileName(this, tr("Selecionar Audio"), "", tr("MP3 Files (*.mp3)"));
    loadPlayer(1, FileName);
}

void player::on_openMusic2_clicked()
{
    QString FileName = QFileDialog::getOpenFileName(this, tr("Selecionar Audio"), "", tr("MP3 Files (*.mp3)"));
    loadPlayer(2, FileName);
}


// Loading media in player

void player::loadPlayer(qint8 player, QString path)
{
    QList players = {MPlayer1, MPlayer2, MPlayer3};
    QList playersTitle = {ui->player1Title, ui->player2Title, ui->player3Title};

    if(path != ""){
        players[player]->setSource(QUrl::fromLocalFile(path));

        QFileInfo fileInfo(path);
        playersTitle[player]->setText(fileInfo.fileName());
    }
}


// Player 1 controls

void player::on_player1Play_clicked()
{MPlayer1->play();}

void player::on_player1Pause_clicked()
{MPlayer1->pause();}

void player::on_player1Stop_clicked()
{MPlayer1->stop();MPlayer1->setPosition(0);}

void player::on_player1Slider_sliderMoved(int position)
{MPlayer1->setPosition(position * 100);}


// Player 2 controls

void player::on_player2Play_clicked()
{MPlayer2->play();}

void player::on_player2Pause_clicked()
{MPlayer2->pause();}

void player::on_player2Stop_clicked()
{MPlayer2->stop();MPlayer2->setPosition(0);}

void player::on_player2Slider_sliderMoved(int position)
{MPlayer2->setPosition(position * 100);}


// Player 3 controls

void player::on_player3Play_clicked()
{MPlayer3->play();}

void player::on_player3Pause_clicked()
{MPlayer3->pause();}

void player::on_player3Stop_clicked()
{MPlayer3->stop();MPlayer3->setPosition(0);}

void player::on_player3Slider_sliderMoved(int position)
{MPlayer3->setPosition(position * 100);}

