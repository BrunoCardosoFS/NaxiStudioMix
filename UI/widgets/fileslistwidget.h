#ifndef FILESLISTWIDGET_H
#define FILESLISTWIDGET_H

#include <QtWidgets>
#include "../../backend/files/fileslist.h"

class FilesListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FilesListWidget(QWidget *parent = nullptr);

private:
    FilesList *FilesListThread;

    QWidget *parent;

signals:
    void loadPlayerSignal(QString path);

public slots:
    void loadFiles(QString path, QString search);

private slots:
    void finishedLoad(const QJsonArray list);
    void loadPlayer(QString path);
};

#endif // FILESLISTWIDGET_H
