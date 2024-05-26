#include "../player.h"
#include "listfolders.h"

#include "itemlistfiles.h"

#include <QSettings>
#include <QDebug>
#include <QDir>

QList<QWidget*> *typesWidgets;
QWidget *filesList;

listFolders::listFolders(QMainWindow *parent):QWidget() {
    call(parent);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    QSettings settings("NaxiStudio", "NaxiStudio Player");
    QString pathDB = settings.value("db").toString();

    //Criando o widget onde vão ser listadas as pastas
    QWidget *foldersList = new QWidget(this);
    QVBoxLayout *foldersListLayout = new QVBoxLayout(foldersList);

    QScrollArea *scrollFolders = new QScrollArea(this);
    scrollFolders->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    scrollFolders->setWidgetResizable(true);
    scrollFolders->setFixedWidth(155);
    scrollFolders->setWidget(foldersList);

    typesWidgets = new QList<QWidget*>();
    QList mediaTypes = {"Vinhetas", "Músicas", "Outros", "Comerciais"};

    foreach (QString type, mediaTypes) {
        QLabel *typeLabel = new QLabel((type + ":"), this);
        typeLabel->setAlignment(Qt::AlignCenter);

        QWidget *typeWidget = new QWidget(this);
        QVBoxLayout *typeLayout = new QVBoxLayout(typeWidget);
        typeLayout->setContentsMargins(0, 0, 0, 0);
        typeLayout->addWidget(typeLabel);

        foldersListLayout->addWidget(typeWidget);

        typesWidgets->append(typeWidget);
    }

    // Criando o widget onde vão ser listados os arquivos
    filesList = new QWidget(this);
    QVBoxLayout *filesListLayout = new QVBoxLayout(filesList);

    QScrollArea *scrollFiles = new QScrollArea(this);
    scrollFiles->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollFiles->setWidgetResizable(true);
    scrollFiles->setWidget(filesList);

    //loadFilesList("D:/MEDIA/MÚSICAS/Dance");


    openCatalog((pathDB + "/catalog.json"));


    layout->addWidget(scrollFolders);
    layout->addWidget(scrollFiles);
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

    qInfo() << typesWidgets->at(0);

    foreach (QJsonValue jsonValue, jsonArray) {
        QJsonObject jsonObject = jsonValue.toObject();

        QPushButton *item = new QPushButton(jsonObject.value("title").toString());
        item->setToolTip(jsonObject.value("title").toString());
        item->setIconSize(QSize(20, 20));
        item->setMaximumWidth(120);
        item->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        item->setText(jsonObject.value("title").toString());
        item->setProperty("id", jsonObject.value("id").toString());

        connect(item, &QPushButton::clicked, [this, jsonObject](){
            loadFilesList(jsonObject.value("path").toString());
        });


        int type = jsonObject.value("type").toInt();


        if(type == 0){
            item->setProperty("type", "jingle");
            item->setIcon(QIcon(":/images/iconsCatalog/jingle.svg"));
            typesWidgets->at(0)->layout()->addWidget(item);
        }else if(type == 1){
            item->setProperty("type", "music");
            item->setIcon(QIcon(":/images/iconsCatalog/music.svg"));
            typesWidgets->at(1)->layout()->addWidget(item);
        }else if(type == 2){
            item->setProperty("type", "commercial");
            item->setIcon(QIcon(":/images/iconsCatalog/commercial.svg"));
            typesWidgets->at(3)->layout()->addWidget(item);
        }else{
            item->setProperty("type", "other");
            item->setIcon(QIcon(":/images/iconsCatalog/other.svg"));
            typesWidgets->at(2)->layout()->addWidget(item);
        }
    }
}


void listFolders::loadFilesList(QString path){
    QDir files(path);

    QLayoutItem *item;
    while((item = filesList->layout()->takeAt(0)) != nullptr){
        QWidget *widget = item->widget();
        delete widget;
    }

    foreach (QFileInfo qfi, files.entryInfoList()) {
        QString suffix = qfi.completeSuffix();
        if(qfi.isFile() && (suffix == "mp3" || suffix == "wav" || suffix == "opus" || suffix == "aac" || suffix == "flac" || suffix == "webm")){
            itemlistfiles *itemList = new itemlistfiles(this);
            itemList->setPathFile(qfi.absoluteFilePath());
            itemList->setTitleFile(qfi.fileName());

            filesList->layout()->addWidget(itemList);
        }
    }
}








