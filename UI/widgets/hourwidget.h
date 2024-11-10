#ifndef HOURWIDGET_H
#define HOURWIDGET_H

#include <QtWidgets>

class HourWidget : public QPushButton
{
    Q_OBJECT
public:
    explicit HourWidget(QWidget *parent = nullptr, qint8 hour = 0);

private:
    QString hour;
    QLabel *label;

public slots:


signals:
    void loadClick(QString hour);
};

#endif // HOURWIDGET_H
