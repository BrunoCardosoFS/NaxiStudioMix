#include "filewidget.h"

FileWidget::FileWidget(QWidget *parent):QWidget{parent}
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(10,7,10,7);
    this->setLayout(layout);
    this->setObjectName("item_list");
    this->setFixedHeight(30);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    this->setCursor(Qt::PointingHandCursor);
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setStyleSheet("FileWidget{background-color: #232731; border-radius: 7px} FileWidget:hover{background-color: #2D3340;} QLabel{font-weight:  bold; color: #fff;}");

    this->TimeLabel = new QLabel(this);
    this->TimeLabel->setText("00:00:00");
    this->TimeLabel->setFixedWidth(60);
    this->TimeLabel->setAlignment(Qt::AlignHCenter);

    this->TitleLabel = new QLabel(this);

    layout->addWidget(this->TimeLabel);
    layout->addWidget(this->TitleLabel);
}

void FileWidget::setInfo(QString title, QString path, QString duration){
    this->TimeLabel->setText(duration);
    this->TitleLabel->setText(title);
    this->path = path;
    this->setToolTip(title);
}

void FileWidget::mousePressEvent(QMouseEvent *event){

}

void FileWidget::mouseReleaseEvent(QMouseEvent *event){
    switch (event->button()) {
    case Qt::LeftButton:
        emit clicked(this->path);
        break;
    case Qt::MiddleButton:
        break;
    case Qt::RightButton:
        break;
    default:
        break;
    }
}
