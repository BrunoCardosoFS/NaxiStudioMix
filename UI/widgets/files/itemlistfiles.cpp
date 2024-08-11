#include "itemlistfiles.h"

#include <QDebug>

QLabel *titleFileLabel;

itemlistfiles::itemlistfiles(QWidget *parent):QGroupBox(parent) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 7, 10, 7);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    this->setObjectName("itemList");
    this->setCursor(Qt::PointingHandCursor);

    this->setStyleSheet("QGroupBox{background: #232731; border-radius: 7px} QGroupBox:hover{background: #2D3340;} QLabel{font-weight:  bold; color: #fff;}");

    this->durationFileLabel = new QLabel("--");
    this->durationFileLabel->setFixedWidth(60);
    this->durationFileLabel->setAlignment(Qt::AlignHCenter);

    this->titleFileLabel = new QLabel();

    layout->addWidget(this->durationFileLabel);
    layout->addWidget(this->titleFileLabel);
}

void itemlistfiles::setPathFile(QString path){
    this->pathFile = path;
}

void itemlistfiles::setTitleFile(QString title){
    titleFile = title;
    this->titleFileLabel->setText(title);
}

void itemlistfiles::setDuration(qint64 duration){
    QTime CurrentTime((duration / 3600000) % 60, (duration / 60000) % 60, (duration / 1000) % 60, (duration) % 1000);

    QString timeMediaFormat = "mm:ss:zzz";
    if(duration > 3600000){
        timeMediaFormat = "hh:mm:ss";
    }
    this->durationFileLabel->setText(CurrentTime.toString(timeMediaFormat));
}


void itemlistfiles::mousePressEvent(QMouseEvent *event){

}

void itemlistfiles::mouseReleaseEvent(QMouseEvent *event){
    switch (event->button()) {
    case Qt::LeftButton:
        emit loadPlayer(this->pathFile);
        break;
    case Qt::MiddleButton:
        break;
    case Qt::RightButton:
        player = new MiniPlayer(nullptr, this->pathFile);
        player->show();

        break;
    default:
        break;
    }
}
