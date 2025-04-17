#include "playlistlist.h"
#include "playlistitemwidget.h"

#include <QAudioDecoder>

PlaylistList::PlaylistList(QWidget *parent):QObject{parent}
{
    this->parent = parent;
    this->OpenPlaylistBackend = new OpenPlaylist(this);
}

void PlaylistList::openPlaylist(QDate date, QString hour){
    QJsonArray hourList = this->OpenPlaylistBackend->openPlaylist(date, hour);

    QLayoutItem *item;
    while ((item = this->parent->layout()->takeAt(0)) != nullptr) {
        delete item->widget();
    }

    if(hourList.isEmpty()){
        QLabel *clean = new QLabel("Nenhum arquivo encontrado");
        clean->setAlignment(Qt::AlignCenter);

        this->parent->layout()->addWidget(clean);
    }

    QAudioDecoder decoder;

    for (int i=0; i<hourList.size(); ++i) {
        QJsonArray itemArray = hourList[i].toArray();

        decoder.setSource(QUrl::fromLocalFile(itemArray[1].toString()));
        decoder.start();
        QTime time = QTime(0, 0).addMSecs(decoder.duration());

        QString format = "mm:ss:zzz";
        if(decoder.duration() > 3600000){
            format = "hh:mm:ss";
        }

        PlaylistItemWidget *playlistItem = new PlaylistItemWidget(this->parent, time.toString(format), itemArray[0].toString(), itemArray[1].toString(), i);

        connect(playlistItem, &PlaylistItemWidget::clicked, this, &PlaylistList::loadPlayer);

        this->parent->layout()->addWidget(playlistItem);

    }

    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->parent->layout()->addItem(spacer);
}

void PlaylistList::updatePlaylist(QDate date){
    this->OpenPlaylistBackend->updatePlaylist(date);
}

void PlaylistList::loadPlayer(QString path){
    emit this->clicked(path);
}
