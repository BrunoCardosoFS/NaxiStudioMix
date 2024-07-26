/******************************************************************************
    Copyright (C) 2024 by Bruno Cardoso <contato@brunocardosofm.com.br>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/



#include "player.h"
#include "./ui_player.h"

#include <QFileInfo>
#include <QFile>
#include <QDateTime>
#include <QSettings>

#include "./widgets/files/listfolders.h"
#include "./widgets/components/playlist.h"

#include <QDir>

#include<QDebug>

QSettings settings("NaxiStudio", "NaxiStudio Player");

QString currentFolder;
QString pathDB;
QString pathLoadMusic;

Playlist *playlist;

Player::Player(QWidget *parent):QMainWindow(parent), ui(new Ui::player)
{
    ui->setupUi(this);

    initApp();

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

Player::~Player()
{
    delete ui;
}

void Player::initApp(){

    if(!settings.contains("db")){
        settings.setValue("db", QCoreApplication::applicationDirPath() + "/../DB");
    }

    pathDB = settings.value("db").toString();

    listFolders *folders = new listFolders(this);
    folders->setObjectName("Folders");
    folders->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(folders, &listFolders::loadPlayer, this, &Player::receivePath);

    QScrollArea *scroll = new QScrollArea(this);
    scroll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scroll->setWidgetResizable(true);
    scroll->setWidget(folders);
    ui->catalog->layout()->addWidget(scroll);

    playlist = new Playlist(this);
    playlist->setObjectName("scrollPlaylistWidget");
    ui->scrollPlaylist->setWidget(playlist);


    ui->loadMediaPlayer1->hide();
    ui->loadMediaPlayer2->hide();
    ui->loadMediaPlayer3->hide();
}

// Updating clock
void Player::updateClock(){
    QDateTime currentTime = QDateTime::currentDateTime();
    ui->dateTime->setText(currentTime.toString("dd/MM/yyyy  hh:mm:ss"));
}

void Player::receivePath(const QString &path){
    pathLoadMusic = path;

    ui->player1Controls->hide();
    ui->player2Controls->hide();
    ui->player3Controls->hide();

    ui->loadMediaPlayer1->show();
    ui->loadMediaPlayer2->show();
    ui->loadMediaPlayer3->show();
}


// Updating player times

void Player::updateDuration(qint64 duration, qint8 player)
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

void Player::updateProgress(qint64 progress, qint8 player){
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


// Loading media in player

void Player::loadPlayer(qint8 player, QString path)
{
    QList players = {MPlayer1, MPlayer2, MPlayer3};
    QList playersTitle = {ui->player1Title, ui->player2Title, ui->player3Title};

    if(path != ""){
        players[player]->setSource(QUrl::fromLocalFile(path));

        QFileInfo fileInfo(path);
        playersTitle[player]->setText(fileInfo.fileName());
    }
}


//Load Media Player

void Player::on_loadMediaPlayer1_clicked()
{
    loadPlayer(0, pathLoadMusic);

    ui->player1Controls->show();
    ui->player2Controls->show();
    ui->player3Controls->show();

    ui->loadMediaPlayer1->hide();
    ui->loadMediaPlayer2->hide();
    ui->loadMediaPlayer3->hide();
}

void Player::on_loadMediaPlayer2_clicked()
{
    loadPlayer(1, pathLoadMusic);

    ui->player1Controls->show();
    ui->player2Controls->show();
    ui->player3Controls->show();

    ui->loadMediaPlayer1->hide();
    ui->loadMediaPlayer2->hide();
    ui->loadMediaPlayer3->hide();
}

void Player::on_loadMediaPlayer3_clicked()
{
    loadPlayer(2, pathLoadMusic);

    ui->player1Controls->show();
    ui->player2Controls->show();
    ui->player3Controls->show();

    ui->loadMediaPlayer1->hide();
    ui->loadMediaPlayer2->hide();
    ui->loadMediaPlayer3->hide();
}


// Player 1 controls

void Player::on_player1Play_clicked()
{MPlayer1->play();}

void Player::on_player1Pause_clicked()
{MPlayer1->pause();}

void Player::on_player1Stop_clicked()
{MPlayer1->stop();MPlayer1->setPosition(0);}

void Player::on_player1Slider_sliderMoved(int position)
{MPlayer1->setPosition(position * 100);}


// Player 2 controls

void Player::on_player2Play_clicked()
{MPlayer2->play();}

void Player::on_player2Pause_clicked()
{MPlayer2->pause();}

void Player::on_player2Stop_clicked()
{MPlayer2->stop();MPlayer2->setPosition(0);}

void Player::on_player2Slider_sliderMoved(int position)
{MPlayer2->setPosition(position * 100);}


// Player 3 controls

void Player::on_player3Play_clicked()
{MPlayer3->play();}

void Player::on_player3Pause_clicked()
{MPlayer3->pause();}

void Player::on_player3Stop_clicked()
{MPlayer3->stop();MPlayer3->setPosition(0);}

void Player::on_player3Slider_sliderMoved(int position)
{MPlayer3->setPosition(position * 100);}



void Player::on_openConfig_clicked()
{
    windowConfig = new Configurations;
    windowConfig->show();
}

void Player::on_playlistOpen_clicked()
{
    if(!(playlist->loadPlaylist(ui->playlistDate->date().toString("yyyy-MM-dd")))){
        // ui->playlistDate->setStyleSheet("QDateEdit{background-color : #C70909;}");
        qInfo() << "O arquivo não existe";
    }
}


void Player::on_hour00_clicked()
{
    playlist->loadHour("00");
}

