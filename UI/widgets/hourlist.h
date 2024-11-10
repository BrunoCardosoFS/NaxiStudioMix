#ifndef HOURLIST_H
#define HOURLIST_H

#include <QtWidgets>

class HourList : public QObject
{
    Q_OBJECT
public:
    explicit HourList(QWidget *parent = nullptr);

private:
    QWidget *parent;

signals:
    void clicked(QString hour);

private slots:
    void loadHour(QString hour);
};

#endif // HOURLIST_H
