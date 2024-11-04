#ifndef FOLDERSWIDGET_H
#define FOLDERSWIDGET_H

#include <QtWidgets>
#include <QJsonArray>
#include <QJsonObject>

#include "../../backend/files/folderslist.h"

class FoldersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FoldersWidget(QWidget *parent = nullptr);

    void loadFolders();

private:
    QWidget *parent;
    FoldersList *folders;

signals:
    void loadFiles(QString folder, QString search);
};

#endif // FOLDERSWIDGET_H
