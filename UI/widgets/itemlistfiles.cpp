#include "itemlistfiles.h"

#include <QDebug>

QString pathFile;
QLabel *titleFileLabel;

itemlistfiles::itemlistfiles(QWidget *parent):QGroupBox(parent) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 7, 10, 7);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    this->setObjectName("itemList");
    this->setCursor(Qt::PointingHandCursor);

    this->setStyleSheet("QGroupBox{background: #232731; border-radius: 7px} QGroupBox:hover{background: #2D3340;} QLabel{font-weight:  bold; color: #fff;}");

    QLabel *durationFileLabel = new QLabel("TODO");
    durationFileLabel->setFixedWidth(60);

    titleFileLabel = new QLabel();

    layout->addWidget(durationFileLabel);
    layout->addWidget(titleFileLabel);
}

void itemlistfiles::setPathFile(QString path){
    pathFile = path;
}

void itemlistfiles::setTitleFile(QString title){
    titleFile = title;
    titleFileLabel->setText(title);
}


void itemlistfiles::mousePressEvent(QMouseEvent *event){
    emit loadPlayer(pathFile);
    //qInfo() << pathFile;
}

void itemlistfiles::mouseReleaseEvent(QMouseEvent *event){
    //qInfo() << event->button();
    //qInfo() << titleFile;
}
