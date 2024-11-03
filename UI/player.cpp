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

Player::Player(QWidget *parent):QMainWindow(parent), ui(new Ui::Player)
{
    ui->setupUi(this);

    this->settings = new QSettings("NaxiStudio", "NaxiStudio Player");

    if(!settings->contains("db")){
        settings->setValue("db", QCoreApplication::applicationDirPath() + "/../DB");
    }

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

    connect(this->Player1, &PlayerWidget::loaded, this, &Player::playerLoaded);
    connect(this->Player2, &PlayerWidget::loaded, this, &Player::playerLoaded);
    connect(this->Player3, &PlayerWidget::loaded, this, &Player::playerLoaded);

    ui->players_area->layout()->addWidget(this->Player1);
    ui->players_area->layout()->addWidget(this->Player2);
    ui->players_area->layout()->addWidget(this->Player3);

    this->Folders = new FoldersWidget(ui->folders_scroll_widget);
}

Player::~Player()
{
    delete ui;
}

void Player::on_buttonTeste_clicked()
{
    this->Player1->loadPlayer("D:/MEDIA/MÚSICAS/Hits Sertanejo/Luan Santana, Luísa Sonza - Coração Cigano.mp3");
    this->Player2->loadPlayer("D:/MEDIA/MÚSICAS/Hits Sertanejo/Marília Mendonça - Morango do Nordeste.mp3");
    this->Player3->loadPlayer("D:/MEDIA/MÚSICAS/Hits Sertanejo/Maiara & Maraisa - Ai, Que Vontade (Ao Vivo).webm");
}

void Player::playerLoaded(bool loaded){
    this->Player1->unloadPlayer();
    this->Player2->unloadPlayer();
    this->Player3->unloadPlayer();
}

