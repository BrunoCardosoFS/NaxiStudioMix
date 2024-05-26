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


private:
    QGridLayout *jinglesLayout;
    QGridLayout *musicsLayout;
    QGridLayout *othersLayout;
    QGridLayout *commercialsLayout;

    void openCatalog(QString path);
};

#endif // LISTFOLDERS_H
