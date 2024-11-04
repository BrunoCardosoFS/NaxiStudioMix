#include "folderslist.h"
#include <QDir>

FoldersList::FoldersList(QObject *parent):QObject{parent}
{
    QSettings *settings = new QSettings("NaxiStudio", "NaxiStudio Player");
    this->pathDB = settings->value("db").toString();

    QFile catalog(this->pathDB + "/catalog.json");
    catalog.open(QFile::ReadOnly | QFile::Text);
    QTextStream dataCatalog(&catalog);
    QString jsonString = dataCatalog.readAll();
    catalog.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
    this->foldersArray = jsonDocument.array();
}
