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

#include <QDebug>

Player::Player(QWidget *parent):QMainWindow(parent), ui(new Ui::Player)
{
    ui->setupUi(this);

    this->settings = new QSettings("NaxiStudio", "NaxiStudio Player");
    if(!settings->contains("db")){
        settings->setValue("db", QCoreApplication::applicationDirPath() + "/../db");
    }

    QTimer *clockTimer = new QTimer(this);
    updateClock();
    connect(clockTimer, &QTimer::timeout, this, &Player::updateClock);
    clockTimer->start(1000);

    this->Player1 = new PlayerWidget(this);
    this->Player2 = new PlayerWidget(this);
    this->Player3 = new PlayerWidget(this);

    this->Player1->setObjectName("Player1");
    this->Player2->setObjectName("Player2");
    this->Player3->setObjectName("Player3");

    this->Player1->setPlayShortcut("F1");
    this->Player2->setPlayShortcut("F5");
    this->Player3->setPlayShortcut("F9");

    this->Player1->setPauseShortcut("F2");
    this->Player2->setPauseShortcut("F6");
    this->Player3->setPauseShortcut("F10");

    this->Player1->setStopShortcut("F3");
    this->Player2->setStopShortcut("F7");
    this->Player3->setStopShortcut("F11");

    if(settings->contains("OutputDevicePlayer1") || settings->contains("OutputDevicePlayer2") || settings->contains("OutputDevicePlayer3")){
        this->Player1->setDevice(settings->value("OutputDevicePlayer1").toString());
        this->Player2->setDevice(settings->value("OutputDevicePlayer2").toString());
        this->Player3->setDevice(settings->value("OutputDevicePlayer3").toString());
    }

    connect(this->Player1, &PlayerWidget::loaded, this, &Player::playerLoaded);
    connect(this->Player2, &PlayerWidget::loaded, this, &Player::playerLoaded);
    connect(this->Player3, &PlayerWidget::loaded, this, &Player::playerLoaded);

    ui->players_area->layout()->addWidget(this->Player1);
    ui->players_area->layout()->addWidget(this->Player2);
    ui->players_area->layout()->addWidget(this->Player3);

    this->Folders = new FoldersWidget(ui->folders_scroll_widget);
    connect(this->Folders, &FoldersWidget::loadFiles, this, &Player::loadFiles);
    this->Folders->loadFolders();

    this->Files = new FilesListWidget(ui->fileslist_scroll_widget);
    connect(this->Files, &FilesListWidget::loadPlayerSignal, this, &Player::loadMediaInPlayers);

    this->Hours = new HourList(ui->playlist_hours);
    connect(this->Hours, &HourList::clicked, this, &Player::loadHour);

    this->Playlist = new PlaylistList(ui->playlist_scroll_widget);
    connect(this->Playlist, &PlaylistList::clicked, this, &Player::loadMediaInPlayers);

    ui->openplaylist_date->setDate(QDate::currentDate());
    this->loadHour(QTime::currentTime().toString("hh"));
}

Player::~Player()
{
    delete ui;
}

void Player::updateClock(){
    QDateTime currentTime = QDateTime::currentDateTime();
    ui->clock_label->setText(currentTime.toString("dd/MM/yyyy  hh:mm:ss"));
}

void Player::loadMediaInPlayers(QString path){
    if(this->Player1->readyLoad || this->Player2->readyLoad || this->Player3->readyLoad){
        playerLoaded();
    }else{
        this->Player1->loadPlayer(path);
        this->Player2->loadPlayer(path);
        this->Player3->loadPlayer(path);
    }
}

void Player::playerLoaded(){
    this->Player1->unloadPlayer();
    this->Player2->unloadPlayer();
    this->Player3->unloadPlayer();
}

void Player::loadFiles(QString folder, QString search){
    this->currentFolder = folder;
    this->Files->loadFiles(folder, search);
}

void Player::loadHour(QString hour){
    this->Playlist->openPlaylist(ui->openplaylist_date->date(), hour);
    this->Hours->updateCurrentHour(hour);
}

void Player::on_openplaylist_button_clicked()
{
    this->Playlist->updatePlaylist(ui->openplaylist_date->date());
    this->loadHour(QTime::currentTime().toString("hh"));
}

void Player::on_search_button_clicked()
{
    loadFiles(this->currentFolder, ui->search_line->text());
}

void Player::on_search_clear_clicked()
{
    ui->search_line->clear();
    loadFiles(this->currentFolder, "");
}

void Player::on_search_line_returnPressed()
{
    loadFiles(this->currentFolder, ui->search_line->text());
}

