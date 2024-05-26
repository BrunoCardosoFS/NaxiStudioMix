#include "itemlistfiles.h"

#include <QDebug>

QString pathFile;
QLabel *titleFileLabel;

itemlistfiles::itemlistfiles(QWidget *parent) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setStyleSheet("background:red;");
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setFixedHeight(50);

    QLabel *durationFileLabel = new QLabel("00:00:00");
    durationFileLabel->setFixedWidth(50);

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
    qInfo() << pathFile;
}

void itemlistfiles::mouseReleaseEvent(QMouseEvent *event){
    //qInfo() << event->button();
    qInfo() << titleFile;
}
