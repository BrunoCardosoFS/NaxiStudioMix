#ifndef FILESLIST_H
#define FILESLIST_H

#include <QtWidgets>

class FilesList : public QThread
{
    Q_OBJECT
public:
    explicit FilesList(QObject *parent = nullptr);
    void init(QString path, QString search);

private:
    void run();

    QString path;
    QString search;

signals:
    void finish(const QJsonArray list);
};

#endif // FILESLIST_H
