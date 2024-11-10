#include "openplaylist.h"


OpenPlaylist::OpenPlaylist(QObject *parent):QObject{parent}
{
    QSettings *settings = new QSettings("NaxiStudio", "NaxiStudio Player");
    this->pathDB = settings->value("db").toString();
}

QJsonArray OpenPlaylist::openPlaylist(QDate date, QString hour){
    if(date != currentDate){
        updatePlaylist(date);
    }

    QJsonArray hourPlaylist = this->currentPlaylist[hour].toArray();

    return hourPlaylist;
}

void OpenPlaylist::updatePlaylist(QDate date){
    this->currentDate = date;

    QFile playlist(this->pathDB + "/musical/grid/" + date.toString("yyyy-MM-dd") + ".json");

    if(playlist.open(QFile::ReadOnly | QFile::Text)){
        QTextStream dataPlaylist(&playlist);
        QString jsonString = dataPlaylist.readAll();
        playlist.close();

        this->currentPlaylist = QJsonDocument::fromJson(jsonString.toUtf8());

    }else if(playlist.open(QIODevice::WriteOnly | QIODevice::Text)){
        QFile standard(this->pathDB + "/musical/grid/standard.json");
        standard.open(QFile::ReadOnly | QFile::Text);
        QTextStream dataStandard(&standard);
        QTextStream out(&playlist);
        QString jsonString = dataStandard.readAll();
        out << jsonString;
        QJsonDocument currentPlaylist =  QJsonDocument::fromJson(jsonString.toUtf8());

        standard.close();
        playlist.close();

        this->currentPlaylist = currentPlaylist;
    }else{
        qWarning() << "Não foi possível abrir o arquivo.";
    }

}
