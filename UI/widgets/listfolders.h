#ifndef LISTFOLDERS_H
#define LISTFOLDERS_H

#include <QtWidgets>


class listFolders : public QWidget
{
    Q_OBJECT
public:
    listFolders(QMainWindow *parent = nullptr);

    void call(QMainWindow *w);

    QJsonArray folders;
    QList<QWidget*> *typesWidgets;

public slots:
    void testeMessage(const QString &path);

signals:
    void loadPlayer(const QString &path);

private:
    QGridLayout *jinglesLayout;
    QGridLayout *musicsLayout;
    QGridLayout *othersLayout;
    QGridLayout *commercialsLayout;

    QWidget *foldersList;
    QWidget *filesList;

    void openCatalog(QString path);
    void loadFilesList(QString path);
};

#endif // LISTFOLDERS_H
