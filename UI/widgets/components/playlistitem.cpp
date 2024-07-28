#include "playlistitem.h"

PlaylistItem::PlaylistItem(QWidget *parent):QGroupBox{parent}{

    this->layout = new QHBoxLayout(this);
    this->layout->setContentsMargins(0, 0, 0, 0);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setFixedHeight(30);
    this->setCursor(Qt::PointingHandCursor);

    this->setStyleSheet("QWidget{background: #232731; border-radius: 7px} QLabel{font-weight:  bold; color: #fff;}");

    this->pathFile = "";

    this->played = new QLabel(this);
    this->played->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->played->setFixedWidth(30);
    this->played->setText("TD");
    this->played->setAlignment(Qt::AlignHCenter);

    this->duration = new QLabel(this);
    this->duration->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->duration->setFixedWidth(60);
    this->duration->setText("TODO");
    this->duration->setAlignment(Qt::AlignHCenter);

    this->titleFile = new QLabel(this);
    this->titleFile->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    this->layout->addWidget(this->played);
    this->layout->addWidget(this->duration);
    this->layout->addWidget(this->titleFile);
}

void PlaylistItem::setDuration(qint64 duration){
    QTime CurrentTime((duration / 3600000) % 60, (duration / 60000) % 60, (duration / 1000) % 60, (duration) % 1000);

    QString timeMediaFormat = "mm:ss:zzz";
    if(duration > 3600000){
        timeMediaFormat = "hh:mm:ss";
    }
    this->duration->setText(CurrentTime.toString(timeMediaFormat));
}

void PlaylistItem::setTitle(QString title){
    this->titleFile->setText(title);
}

void PlaylistItem::setPath(QString path){
    this->pathFile = path;
}
