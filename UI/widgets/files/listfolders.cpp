#include "listfolders.h"

#include "itemlistfiles.h"

#include <QSettings>
#include <QDebug>
#include <QDir>

QList<QWidget*> *typesWidgets;
QWidget *filesList;

QString currentPath;

listFolders::listFolders(QMainWindow *parent):QWidget(parent) {
    //call(parent);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    QSettings settings("NaxiStudio", "NaxiStudio Player");
    QString pathDB = settings.value("db").toString();

    //Creating the widget where folders will be listed
    QWidget *foldersList = new QWidget(this);
    foldersList->setObjectName("foldersList");
    QVBoxLayout *foldersListLayout = new QVBoxLayout(foldersList);
    foldersList->setStyleSheet("QLabel{font-weight: bold; margin-top: 10px;}");

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

    QGroupBox *filesArea = new QGroupBox(this);
    filesArea->setObjectName("filesArea");

    QVBoxLayout *filesAreaLayout = new QVBoxLayout(filesArea);
    filesArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    // Creating the file search area

    QWidget *searchBar = new QWidget(this);
    searchBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    searchBar->setFixedHeight(30);

    QHBoxLayout *searchBarLayout = new QHBoxLayout(searchBar);
    searchBarLayout->setContentsMargins(0, 0, 0, 0);

    QLineEdit *searchInput = new QLineEdit(searchBar);
    searchInput->setObjectName("searchInput");
    searchInput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    searchInput->setFixedHeight(30);

    QPushButton *searchButton = new QPushButton(searchBar);
    searchButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    searchButton->setFixedWidth(40);
    searchButton->setFixedHeight(30);
    searchButton->setIcon(QIcon(":/images/icons/search.svg"));
    searchButton->setCursor(Qt::PointingHandCursor);

    searchBarLayout->addWidget(searchInput);
    searchBarLayout->addWidget(searchButton);

    connect(searchButton, &QPushButton::clicked, [this, searchInput](){
        searchFilesList(searchInput->text());
    });

    connect(searchInput, &QLineEdit::returnPressed, [this, searchInput](){
        searchFilesList(searchInput->text());
    });

    filesAreaLayout->addWidget(searchBar);



    //Creating the widget where the files will be listed

    filesList = new QWidget(this);
    filesList->setObjectName("filesList");
    QVBoxLayout *filesListLayout = new QVBoxLayout(filesList);
    filesList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    filesListLayout->setContentsMargins(0, 0, 0, 0);

    QScrollArea *scrollFiles = new QScrollArea(filesArea);
    scrollFiles->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollFiles->setWidgetResizable(true);
    scrollFiles->setWidget(filesList);

    filesAreaLayout->addWidget(scrollFiles);


    openCatalog((pathDB + "/catalog.json"));

    layout->addWidget(scrollFolders);
    layout->addWidget(filesArea);
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
        item->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        item->setCursor(Qt::PointingHandCursor);

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

void listFolders::emitLoadPlayer(const QString &path){
    emit loadPlayer(path);
}


void listFolders::loadFilesList(QString path){
    QDir files(path);
    currentPath = path;

    QLayoutItem *item;
    while((item = filesList->layout()->takeAt(0)) != nullptr){
        QWidget *widget = item->widget();
        delete widget;
    }


    foreach (QFileInfo qfi, files.entryInfoList()) {
        QString suffix = qfi.completeSuffix();
        suffix = suffix.toLower();
        if(qfi.isFile() && (suffix == "mp3" || suffix == "wav" || suffix == "opus" || suffix == "aac" || suffix == "flac" || suffix == "webm")){
            itemlistfiles *itemList = new itemlistfiles(this);
            itemList->setPathFile(qfi.absoluteFilePath());
            itemList->setTitleFile(qfi.fileName());

            connect(itemList, &itemlistfiles::loadPlayer, this, &listFolders::emitLoadPlayer);

            filesList->layout()->addWidget(itemList);
        }
    }
}

void listFolders::searchFilesList(QString search){
    QDir files(currentPath);

    QLayoutItem *item;
    while((item = filesList->layout()->takeAt(0)) != nullptr){
        QWidget *widget = item->widget();
        delete widget;
    }

    foreach (QFileInfo qfi, files.entryInfoList()) {
        QString suffix = qfi.completeSuffix();
        suffix = suffix.toLower();

        QString fileName = qfi.fileName();

        if(qfi.isFile() && (fileName.contains(search, Qt::CaseInsensitive)) && (suffix == "mp3" || suffix == "wav" || suffix == "opus" || suffix == "aac" || suffix == "flac" || suffix == "webm")){
            itemlistfiles *itemList = new itemlistfiles(this);
            itemList->setPathFile(qfi.absoluteFilePath());
            itemList->setTitleFile(qfi.fileName());

            connect(itemList, &itemlistfiles::loadPlayer, this, &listFolders::emitLoadPlayer);

            filesList->layout()->addWidget(itemList);
        }
    }
}








