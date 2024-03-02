#include "../player.h"
#include "listfolders.h"

#include <QSettings>
#include <QDebug>

listFolders::listFolders(QMainWindow *parent):QWidget() {
    call(parent);

    QVBoxLayout *layout = new QVBoxLayout(this);
    this->setFixedWidth(150);

    layout->setContentsMargins(0, 0, 0, 10);

    QSettings settings("NaxiStudio", "NaxiStudio Player");
    QString pathDB = settings.value("db").toString();

    QLabel *jinglesLabel = new QLabel("Vinhetas:", this);
    jinglesLabel->setAlignment(Qt::AlignCenter);
    QWidget *jingles = new QWidget(this);
    jinglesLayout = new QGridLayout(jingles);
    jinglesLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *musicsLabel = new QLabel("Músicas:", this);
    musicsLabel->setAlignment(Qt::AlignCenter);
    QWidget *musics = new QWidget(this);
    musicsLayout = new QGridLayout(musics);
    musicsLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *othersLabel = new QLabel("Outros:", this);
    othersLabel->setAlignment(Qt::AlignCenter);
    QWidget *others = new QWidget(this);
    othersLayout = new QGridLayout(others);
    othersLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *commercialsLabel = new QLabel("Comerciais:", this);
    commercialsLabel->setAlignment(Qt::AlignCenter);
    QWidget *commercials = new QWidget(this);
    commercialsLayout = new QGridLayout(commercials);
    commercialsLayout->setContentsMargins(0, 0, 0, 0);

    openCatalog(pathDB + "/catalog.json");

    layout->addWidget(jinglesLabel);
    layout->addWidget(jingles);

    layout->addWidget(musicsLabel);
    layout->addWidget(musics);

    layout->addWidget(othersLabel);
    layout->addWidget(others);

    layout->addWidget(commercialsLabel);
    layout->addWidget(commercials);
}

void listFolders::call(QMainWindow *w){
    Player *player = qobject_cast<Player*>(w);
    qInfo() << player->teste;
}

void listFolders::openCatalog(QString path){
    QFile catalog(path);
    catalog.open(QFile::ReadOnly | QFile::Text);
    QTextStream dataCatalog(&catalog);
    QString jsonString = dataCatalog.readAll();
    catalog.close();

    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonArray jsonArray = jsonDocument.array();

    foreach (QJsonValue jsonValue, jsonArray) {
        QJsonObject jsonObject = jsonValue.toObject();

        QPushButton *item = new QPushButton(jsonObject.value("title").toString());
        item->setToolTip(jsonObject.value("title").toString());
        item->setIconSize(QSize(20, 20));
        item->setMaximumWidth(120);

        item->setText(jsonObject.value("title").toString());
        item->setProperty("path", jsonObject.value("path").toString());
        item->setProperty("id", jsonObject.value("id").toString());

        switch (jsonObject.value("type").toInt()) {
        case 0:
            item->setProperty("type", "jingle");
            item->setIcon(QIcon(":/images/iconsCatalog/jingle.svg"));
            jinglesLayout->addWidget(item);
            break;
        case 1:
            item->setProperty("type", "music");
            item->setIcon(QIcon(":/images/iconsCatalog/music.svg"));
            musicsLayout->addWidget(item);
            break;
        case 2:
            item->setProperty("type", "commercial");
            item->setIcon(QIcon(":/images/iconsCatalog/commercial.svg"));
            commercialsLayout->addWidget(item);
            break;
        default:
            item->setProperty("type", "other");
            item->setIcon(QIcon(":/images/iconsCatalog/other.svg"));
            othersLayout->addWidget(item);
            break;
        }
    }
}
