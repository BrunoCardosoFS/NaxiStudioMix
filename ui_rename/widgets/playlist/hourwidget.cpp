#include "hourwidget.h"

HourWidget::HourWidget(QWidget *parent, qint8 hour):QPushButton{parent}
{

    this->hour = QString::number(hour, 10).rightJustified(2, '0');

    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    this->setFixedWidth(31);
    this->setFixedHeight(31);
    this->setCursor(Qt::PointingHandCursor);

    this->setText(this->hour);

    connect(this, &HourWidget::clicked, this, [=]() {
        emit loadClick(this->hour);
    });
}
