#ifndef HOURLIST_H
#define HOURLIST_H

#include <QtWidgets>

#include "./hourwidget.h"

class HourList : public QObject
{
    Q_OBJECT
public:
    explicit HourList(QWidget *parent = nullptr);

private:
    QWidget *parent;
    QList<HourWidget*> HourItems;

signals:
    void clicked(QString hour);

public slots:
    void updateCurrentHour(QString hour);

private slots:
    void loadHour(QString hour);
};

#endif // HOURLIST_H
