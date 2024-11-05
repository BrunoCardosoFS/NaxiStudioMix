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

#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QtWidgets>
#include <QSettings>

#include "./widgets/playerwidget.h"
#include "./widgets/folderswidget.h"
#include "./widgets/fileslistwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Player;
}
QT_END_NAMESPACE

class Player : public QMainWindow
{
    Q_OBJECT

public:
    Player(QWidget *parent = nullptr);
    ~Player();

private slots:
    void updateClock();

    void loadMediaInPlayers(QString path);
    void playerLoaded(bool loaded);
    void loadFiles(QString folder, QString search);

    void on_search_button_clicked();
    void on_search_clear_clicked();
    void on_search_line_returnPressed();

private:
    Ui::Player *ui;
    QSettings *settings;

    QString currentFolder;

    PlayerWidget *Player1;
    PlayerWidget *Player2;
    PlayerWidget *Player3;

    FoldersWidget *Folders;
    FilesListWidget *Files;

};
#endif // PLAYER_H
