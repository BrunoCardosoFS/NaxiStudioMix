#include "playlistitemwidget.h"

PlaylistItemWidget::PlaylistItemWidget(QWidget *parent, QString time, QString title, QString path, int id):QWidget{parent}
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setFixedHeight(30);
    this->setCursor(Qt::PointingHandCursor);
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setStyleSheet("PlaylistItemWidget{background-color: #232731; border-radius: 7px} PlaylistItemWidget:hover{background-color: #2D3340;} QLabel{font-weight:  bold; color: #fff;}");


    this->id = id;
    this->time = time;
    this->title = title;
    this->path = path;

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(10,0,10,0);
    this->setLayout(layout);

    QLabel *timeLabel = new QLabel(this);
    timeLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    timeLabel->setText(time);

    QLabel *titleLabel = new QLabel(this);
    titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    titleLabel->setText(title);

    this->setToolTip(title);

    layout->addWidget(timeLabel);
    layout->addWidget(titleLabel);
}
