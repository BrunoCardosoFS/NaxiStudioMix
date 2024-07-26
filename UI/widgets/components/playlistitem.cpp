#include "playlistitem.h"

PlaylistItem::PlaylistItem(QWidget *parent):QGroupBox{parent}{

    this->layout = new QHBoxLayout(this);
    this->layout->setContentsMargins(0, 0, 0, 3);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setFixedHeight(30);
    this->setCursor(Qt::PointingHandCursor);

    this->setStyleSheet("QWidget{background: #232731; border-radius: 7px} QLabel{font-weight:  bold; color: #fff;}");

    this->pathFile = "";

   this->played = new QLabel(this);

    this->played->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->played->setFixedWidth(30);
    this->played->setFixedHeight(30);
    this->played->setText("x");

    this->titleFile = new QLabel(this);
    this->titleFile->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    this->layout->addWidget(this->played);
    this->layout->addWidget(this->titleFile);
}

void PlaylistItem::setTitle(QString title){
    this->titleFile->setText(title);
}

void PlaylistItem::setPath(QString path){
    this->pathFile = path;
}
