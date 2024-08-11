#include "playlist.h"

#include <QSettings>
#include <QDir>
#include <QAudioDecoder>

#include "./playlistitem.h"

#include<QDebug>

Playlist::Playlist(QWidget *parent):QWidget{parent}{
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    Playlist::boxLayout = new QVBoxLayout(this);

    this->boxLayout->setContentsMargins(10, 10, 5, 10);
    this->boxLayout->setSpacing(5);

    QSettings settings("NaxiStudio", "NaxiStudio Player");
    this->playlistDB = (settings.value("db").toString() + "/musical/grid/");
}

bool Playlist::loadPlaylist(QString date){
    QString path = (this->playlistDB + date + ".json");

    QFile catalog(path);
    if(!catalog.open(QFile::ReadOnly | QFile::Text)){
        return false;
    }

    QTextStream dataCatalog(&catalog);
    QString jsonString = dataCatalog.readAll();
    catalog.close();

    this->jsonPlaylist = QJsonDocument::fromJson(jsonString.toUtf8());

    QDateTime currentTime = QDateTime::currentDateTime();

    if(currentTime.toString("yyyy-MM-dd") == date){
        loadHour(currentTime.toString("hh"));
    }else {
        loadHour("00");
    }

    return true;
}

bool Playlist::loadHour(QString hour){
    if(this->jsonPlaylist.isNull()){
        return false;
    }

    QLayoutItem *item;
    while((item = this->boxLayout->takeAt(0)) != nullptr){
        QWidget *widget = item->widget();
        delete widget;
    }

    QJsonArray jsonArray = this->jsonPlaylist[hour].toArray();

    if(jsonArray.isEmpty()){
        QLabel *clean = new QLabel("Nenhum arquivo encontrado");
        clean->setAlignment(Qt::AlignCenter);
        this->boxLayout->addWidget(clean);
        return true;
    }

    QAudioDecoder decoder;

    foreach (QJsonValue value, jsonArray) {
        QJsonArray valueArray = value.toArray();

        decoder.setSource(QUrl::fromLocalFile(valueArray[1].toString()));
        decoder.start();

        PlaylistItem *item = new PlaylistItem(this);

        item->setDuration(decoder.duration());
        item->setPath(valueArray[1].toString());
        item->setTitle(valueArray[0].toString());

        this->boxLayout->addWidget(item);
    }

    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->boxLayout->addItem(spacer);

    return true;
}

