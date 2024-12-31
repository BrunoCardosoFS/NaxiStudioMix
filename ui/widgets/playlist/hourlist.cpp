#include "hourlist.h"

HourList::HourList(QWidget *parent):QObject{parent}
{
    this->parent = parent;

    for (qint8 i=0; i<=24; ++i) {
        HourWidget *hour = new HourWidget(this->parent, i);
        connect(hour, &HourWidget::loadClick, this, &HourList::loadHour);
        this->parent->layout()->addWidget(hour);

        this->HourItems.append(hour);

        if(i != 24){
            QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
            this->parent->layout()->addItem(spacer);
        }
    }
}

void HourList::updateCurrentHour(QString hour){
    for (int i=0; i<=24; ++i) {
        this->HourItems[i]->setStyleSheet("");
    }

    this->HourItems[hour.toInt()]->setStyleSheet("background-color:#FFA60A;");
}

void HourList::loadHour(QString hour){
    emit clicked(hour);
}
