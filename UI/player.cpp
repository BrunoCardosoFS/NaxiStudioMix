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
#include "./widgets/playlist/playlist.h"

#include <QDir>

#include<QDebug>

QSettings settings("NaxiStudio", "NaxiStudio Player");

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

    this->MPlayer1 = new QMediaPlayer();
    this->MPlayer1AudioOutput = new QAudioOutput();
    this->MPlayer1AudioOutput->setVolume(100);
    this->MPlayer1->setAudioOutput(this->MPlayer1AudioOutput);

    this->MPlayer2 = new QMediaPlayer();
    this->MPlayer2AudioOutput = new QAudioOutput();
    this->MPlayer2AudioOutput->setVolume(100);
    this->MPlayer2->setAudioOutput(this->MPlayer2AudioOutput);

    this->MPlayer3 = new QMediaPlayer();
    this->MPlayer3AudioOutput = new QAudioOutput();
    this->MPlayer3AudioOutput->setVolume(100);
    this->MPlayer3->setAudioOutput(this->MPlayer3AudioOutput);


    // Connect players
    connect(this->MPlayer1, &QMediaPlayer::durationChanged, this, [=](qint64 duration){updateDuration(duration, 0);});
    connect(this->MPlayer1, &QMediaPlayer::positionChanged, this, [=](qint64 progress){updateProgress(progress, 0);});

    connect(this->MPlayer2, &QMediaPlayer::durationChanged, this, [=](qint64 duration){updateDuration(duration, 1);});
    connect(this->MPlayer2, &QMediaPlayer::positionChanged, this, [=](qint64 progress){updateProgress(progress, 1);});

    connect(this->MPlayer3, &QMediaPlayer::durationChanged, this, [=](qint64 duration){updateDuration(duration, 2);});
    connect(this->MPlayer3, &QMediaPlayer::positionChanged, this, [=](qint64 progress){updateProgress(progress, 2);});
}

Player::~Player()
{
    delete ui;
}

void Player::initApp(){

    if(!settings.contains("db")){
        settings.setValue("db", QCoreApplication::applicationDirPath() + "/../DB");
    }

    this->pathDB = settings.value("db").toString();

    listFolders *folders = new listFolders(this);
    folders->setObjectName("Folders");
    folders->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(folders, &listFolders::loadPlayer, this, &Player::receivePath);

    QScrollArea *scroll = new QScrollArea(this);
    scroll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scroll->setWidgetResizable(true);
    scroll->setWidget(folders);
    ui->catalog->layout()->addWidget(scroll);

    this->playlist = new Playlist(this);
    this->playlist->setObjectName("scrollPlaylistWidget");
    ui->scrollPlaylist->setWidget(this->playlist);


    ui->loadMediaPlayer1->hide();
    ui->loadMediaPlayer2->hide();
    ui->loadMediaPlayer3->hide();

    windowConfig = new Configurations;
}

// Updating clock
void Player::updateClock(){
    QDateTime currentTime = QDateTime::currentDateTime();
    ui->dateTime->setText(currentTime.toString("dd/MM/yyyy  hh:mm:ss"));
}

void Player::receivePath(const QString &path){
    this->pathLoadMusic = path;

    preLoad();
}

void Player::preLoad(){
    ui->player1Controls->hide();
    ui->loadMediaPlayer1->show();

    ui->player2Controls->hide();
    ui->loadMediaPlayer2->show();

    ui->player3Controls->hide();
    ui->loadMediaPlayer3->show();

    if(this->MPlayer1->isPlaying()){
        ui->loadMediaPlayer1->hide();
        ui->player1Controls->show();
    }
    if(this->MPlayer2->isPlaying()){
        ui->loadMediaPlayer2->hide();
        ui->player2Controls->show();
    }
    if(this->MPlayer3->isPlaying()){
        ui->loadMediaPlayer3->hide();
        ui->player3Controls->show();
    }
}

void Player::posLoad(){
    ui->loadMediaPlayer1->hide();
    ui->player1Controls->show();

    ui->loadMediaPlayer2->hide();
    ui->player2Controls->show();

    ui->loadMediaPlayer3->hide();
    ui->player3Controls->show();
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
    QList players = {this->MPlayer1, this->MPlayer2, this->MPlayer3};
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
    loadPlayer(0, this->pathLoadMusic);

    posLoad();
}

void Player::on_loadMediaPlayer2_clicked()
{
    loadPlayer(1, this->pathLoadMusic);

    posLoad();
}

void Player::on_loadMediaPlayer3_clicked()
{
    loadPlayer(2, this->pathLoadMusic);

    posLoad();
}


// Player 1 controls

void Player::on_player1Play_clicked()
{this->MPlayer1->play();}

void Player::on_player1Pause_clicked()
{this->MPlayer1->pause();}

void Player::on_player1Stop_clicked()
{this->MPlayer1->stop();this->MPlayer1->setPosition(0);}

void Player::on_player1Slider_sliderMoved(int position)
{this->MPlayer1->setPosition(position * 100);}

void Player::on_player1Slider_sliderPressed()
{/*this->MPlayer1->pause();*/}

void Player::on_player1Slider_sliderReleased()
{/*this->MPlayer1->play();*/}



// Player 2 controls

void Player::on_player2Play_clicked()
{this->MPlayer2->play();}

void Player::on_player2Pause_clicked()
{this->MPlayer2->pause();}

void Player::on_player2Stop_clicked()
{this->MPlayer2->stop();this->MPlayer2->setPosition(0);}

void Player::on_player2Slider_sliderMoved(int position)
{this->MPlayer2->setPosition(position * 100);}

void Player::on_player2Slider_sliderPressed()
{/*this->MPlayer2->pause();*/}

void Player::on_player2Slider_sliderReleased()
{/*this->MPlayer2->play();*/}


// Player 3 controls

void Player::on_player3Play_clicked()
{this->MPlayer3->play();}

void Player::on_player3Pause_clicked()
{this->MPlayer3->pause();}

void Player::on_player3Stop_clicked()
{this->MPlayer3->stop();this->MPlayer3->setPosition(0);}

void Player::on_player3Slider_sliderMoved(int position)
{this->MPlayer3->setPosition(position * 100);}

void Player::on_player3Slider_sliderPressed()
{/*this->MPlayer3->pause();*/}

void Player::on_player3Slider_sliderReleased()
{/*this->MPlayer3->play();*/}



void Player::on_openConfig_clicked()
{
    windowConfig->show();
}

void Player::on_playlistOpen_clicked()
{
    if(!(this->playlist->loadPlaylist(ui->playlistDate->date().toString("yyyy-MM-dd")))){
        // ui->playlistDate->setStyleSheet("QDateEdit{background-color : #C70909;}");
        qInfo() << "O arquivo não existe";
    }
}

void Player::clearHours(){
    QString style = "QPushButton{background-color: #2b303d;}";

    ui->hour00->setStyleSheet(style);
    ui->hour01->setStyleSheet(style);
    ui->hour02->setStyleSheet(style);
    ui->hour03->setStyleSheet(style);
    ui->hour04->setStyleSheet(style);
    ui->hour05->setStyleSheet(style);
    ui->hour06->setStyleSheet(style);
    ui->hour07->setStyleSheet(style);
    ui->hour08->setStyleSheet(style);
    ui->hour09->setStyleSheet(style);
    ui->hour10->setStyleSheet(style);
    ui->hour11->setStyleSheet(style);
    ui->hour12->setStyleSheet(style);
    ui->hour13->setStyleSheet(style);
    ui->hour14->setStyleSheet(style);
    ui->hour15->setStyleSheet(style);
    ui->hour16->setStyleSheet(style);
    ui->hour17->setStyleSheet(style);
    ui->hour18->setStyleSheet(style);
    ui->hour19->setStyleSheet(style);
    ui->hour20->setStyleSheet(style);
    ui->hour21->setStyleSheet(style);
    ui->hour22->setStyleSheet(style);
    ui->hour23->setStyleSheet(style);
}


void Player::on_hour00_clicked()
{
    this->playlist->loadHour("00");
    clearHours();
    ui->hour00->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}


void Player::on_hour01_clicked()
{
    this->playlist->loadHour("01");
    clearHours();
    ui->hour01->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour02_clicked()
{
    this->playlist->loadHour("02");
    clearHours();
    ui->hour02->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour03_clicked()
{
    this->playlist->loadHour("03");
    clearHours();
    ui->hour03->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour04_clicked()
{
    this->playlist->loadHour("04");
    clearHours();
    ui->hour04->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour05_clicked()
{
    this->playlist->loadHour("05");
    clearHours();
    ui->hour05->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour06_clicked()
{
    this->playlist->loadHour("06");
    clearHours();
    ui->hour06->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour07_clicked()
{
    this->playlist->loadHour("07");
    clearHours();
    ui->hour07->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour08_clicked()
{
    this->playlist->loadHour("08");
    clearHours();
    ui->hour08->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour09_clicked()
{
    this->playlist->loadHour("09");
    clearHours();
    ui->hour09->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour10_clicked()
{
    this->playlist->loadHour("10");
    clearHours();
    ui->hour10->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour11_clicked()
{
    this->playlist->loadHour("11");
    clearHours();
    ui->hour11->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour12_clicked()
{
    this->playlist->loadHour("12");
    clearHours();
    ui->hour12->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour13_clicked()
{
    this->playlist->loadHour("13");
    clearHours();
    ui->hour13->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour14_clicked()
{
    this->playlist->loadHour("14");
    clearHours();
    ui->hour14->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour15_clicked()
{
    this->playlist->loadHour("15");
    clearHours();
    ui->hour15->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour16_clicked()
{
    this->playlist->loadHour("16");
    clearHours();
    ui->hour16->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour17_clicked()
{
    this->playlist->loadHour("17");
    clearHours();
    ui->hour17->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour18_clicked()
{
    this->playlist->loadHour("18");
    clearHours();
    ui->hour18->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour19_clicked()
{
    this->playlist->loadHour("19");
    clearHours();
    ui->hour19->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour20_clicked()
{
    this->playlist->loadHour("20");
    clearHours();
    ui->hour20->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour21_clicked()
{
    this->playlist->loadHour("21");
    clearHours();
    ui->hour21->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour22_clicked()
{
    this->playlist->loadHour("22");
    clearHours();
    ui->hour22->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

void Player::on_hour23_clicked()
{
    this->playlist->loadHour("23");
    clearHours();
    ui->hour23->setStyleSheet("QPushButton{background-color: #FFA60A;}");
}

