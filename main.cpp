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

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "./UI/player.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QApplication::setStyle(QStyleFactory::create("Fusion"));

    QApplication::setWindowIcon(QIcon(":/icons/images/icons/icon.ico"));

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "NaxiStudio_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    Player w;
    w.show();
    return a.exec();
}
