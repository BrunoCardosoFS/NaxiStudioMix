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

#include "./widgets/playerwidget.h"

Player::Player(QWidget *parent):QMainWindow(parent), ui(new Ui::Player)
{
    ui->setupUi(this);

    PlayerWidget *Player1 = new PlayerWidget(this);
    PlayerWidget *Player2 = new PlayerWidget(this);
    PlayerWidget *Player3 = new PlayerWidget(this);

    Player1->setObjectName("Player1");
    Player2->setObjectName("Player2");
    Player3->setObjectName("Player3");

    ui->players_area->layout()->addWidget(Player1);
    ui->players_area->layout()->addWidget(Player2);
    ui->players_area->layout()->addWidget(Player3);



}

Player::~Player()
{
    delete ui;
}
