#ifndef ITEMLISTTHREAD_H
#define ITEMLISTTHREAD_H


#include <QtWidgets>
#include <QThread>

class itemListThread : public QThread
{
    Q_OBJECT
public:
    itemListThread(QObject *parent = nullptr);

    void init(QString pathList, QString search);

private:
    void run();

    QString path;
    QString search;

signals:
    void finishedLoad(const QJsonArray list);

private slots:

};

#endif // ITEMLISTTHREAD_H
