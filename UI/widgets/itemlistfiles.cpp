#include "itemlistfiles.h"

#include <QDebug>

itemlistfiles::itemlistfiles(QWidget *parent) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setStyleSheet("background:red;");
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setFixedHeight(50);

    QLabel *duration = new QLabel("00:00:00");
    duration->setFixedWidth(50);

    QLabel *title = new QLabel("título da música");

    layout->addWidget(duration);
    layout->addWidget(title);

}

void itemlistfiles::mousePressEvent(QMouseEvent *event){
    qInfo() << event->button();
}

void itemlistfiles::mouseReleaseEvent(QMouseEvent *event){
    qInfo() << event->button();
}
