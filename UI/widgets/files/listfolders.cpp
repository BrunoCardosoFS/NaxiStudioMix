#include "listfolders.h"

#include "itemlistfiles.h"


#include <QSettings>
#include <QAudioDecoder>
#include <QDebug>
#include <QDir>


listFolders::listFolders(QMainWindow *parent):QWidget(parent) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    QSettings settings("NaxiStudio", "NaxiStudio Player");
    QString pathDB = settings.value("db").toString();

    //Creating the widget where folders will be listed
    QWidget *foldersList = new QWidget(this);
    foldersList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    foldersList->setStyleSheet("QLabel{font-weight: bold; margin-top: 10px;}");
    foldersList->setObjectName("foldersList");

    QVBoxLayout *foldersListLayout = new QVBoxLayout(foldersList);
    foldersListLayout->setContentsMargins(0, 0, 0, 0);

    QScrollArea *scrollFolders = new QScrollArea(this);
    scrollFolders->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    scrollFolders->setWidgetResizable(true);
    scrollFolders->setFixedWidth(155);
    scrollFolders->setWidget(foldersList);

    this->typesWidgets = new QList<QWidget*>();
    QList mediaTypes = {"Vinhetas", "Músicas", "Outros", "Comerciais"};

    foreach (QString type, mediaTypes) {
        QLabel *typeLabel = new QLabel((type + ":"), this);
        typeLabel->setAlignment(Qt::AlignCenter);

        QWidget *typeWidget = new QWidget(this);
        QVBoxLayout *typeLayout = new QVBoxLayout(typeWidget);
        typeLayout->setContentsMargins(0, 0, 0, 0);
        typeLayout->addWidget(typeLabel);

        foldersListLayout->addWidget(typeWidget);

        this->typesWidgets->append(typeWidget);
    }


    // Creating the files area

    QGroupBox *filesArea = new QGroupBox(this);
    filesArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    filesArea->setObjectName("filesArea");

    QVBoxLayout *filesAreaLayout = new QVBoxLayout(filesArea);
    filesAreaLayout->setContentsMargins(0, 0, 0, 0);


    // Creating the file search area

    QWidget *searchBar = new QWidget(this);
    searchBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    searchBar->setFixedHeight(30);

    QHBoxLayout *searchBarLayout = new QHBoxLayout(searchBar);
    searchBarLayout->setContentsMargins(0, 0, 0, 0);

    QLineEdit *searchInput = new QLineEdit(searchBar);
    searchInput->setPlaceholderText("Pesquisar");
    searchInput->setObjectName("searchInput");
    searchInput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    searchInput->setFixedHeight(30);

    QPushButton *clearSearch = new QPushButton(searchBar);
    clearSearch->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    clearSearch->setFixedWidth(30);
    clearSearch->setFixedHeight(30);
    clearSearch->setIcon(QIcon(":/images/icons/close.svg"));
    clearSearch->setCursor(Qt::PointingHandCursor);

    QPushButton *searchButton = new QPushButton(searchBar);
    searchButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    searchButton->setFixedWidth(30);
    searchButton->setFixedHeight(30);
    searchButton->setIcon(QIcon(":/images/icons/search.svg"));
    searchButton->setCursor(Qt::PointingHandCursor);

    searchBarLayout->addWidget(searchInput);
    searchBarLayout->addWidget(clearSearch);
    searchBarLayout->addWidget(searchButton);

    connect(clearSearch, &QPushButton::clicked, [this, searchInput](){
        searchInput->clear();
        searchFilesList("");
    });

    connect(searchButton, &QPushButton::clicked, [this, searchInput](){
        searchFilesList(searchInput->text());
    });

    connect(searchInput, &QLineEdit::returnPressed, [this, searchInput](){
        searchFilesList(searchInput->text());
    });

    filesAreaLayout->addWidget(searchBar);


    //Creating the widget where the files will be listed

    this->filesList = new QWidget(this);
    this->filesList->setObjectName("filesList");
    this->filesList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    QVBoxLayout *filesListLayout = new QVBoxLayout(this->filesList);
    filesListLayout->setContentsMargins(0, 0, 0, 0);

    QScrollArea *scrollFiles = new QScrollArea(filesArea);
    scrollFiles->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollFiles->setWidgetResizable(true);
    scrollFiles->setWidget(this->filesList);

    filesAreaLayout->addWidget(scrollFiles);

    this->thread = new itemListThread(this->filesList);
    connect(this->thread, &itemListThread::finishedLoad, this, &listFolders::finishedLoad);


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
            this->typesWidgets->at(0)->layout()->addWidget(item);
        }else if(type == 1){
            item->setProperty("type", "music");
            item->setIcon(QIcon(":/images/iconsCatalog/music.svg"));
            this->typesWidgets->at(1)->layout()->addWidget(item);
        }else if(type == 2){
            item->setProperty("type", "commercial");
            item->setIcon(QIcon(":/images/iconsCatalog/commercial.svg"));
            this->typesWidgets->at(3)->layout()->addWidget(item);
        }else{
            item->setProperty("type", "other");
            item->setIcon(QIcon(":/images/iconsCatalog/other.svg"));
            this->typesWidgets->at(2)->layout()->addWidget(item);
        }
    }
}

void listFolders::emitLoadPlayer(const QString &path){
    emit loadPlayer(path);
}

void listFolders::finishedLoad(const QJsonArray list){
    QLayoutItem *item;
    while ((item = this->filesList->layout()->takeAt(0)) != nullptr) {
        QWidget *widget = item->widget();
        delete widget;
    }

    foreach (QJsonValue item, list) {
        QJsonArray itemArray = item.toArray();

        itemlistfiles *itemList = new itemlistfiles(this);
        itemList->setFixedHeight(30);
        itemList->setTitleFile(itemArray[0].toString());
        itemList->setPathFile(itemArray[1].toString());
        itemList->setDuration(itemArray[2].toInt());

        connect(itemList, &itemlistfiles::loadPlayer, this,
                &listFolders::emitLoadPlayer);

        this->filesList->layout()->addWidget(itemList);
    }

    QSpacerItem *spacer =
        new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->filesList->layout()->addItem(spacer);
}

void listFolders::loadFilesList(QString path){
    QLayoutItem *item;
    while((item = this->filesList->layout()->takeAt(0)) != nullptr){
        QWidget *widget = item->widget();
        delete widget;
    }

    QLabel *loading = new QLabel("Carregando...");
    loading->setAlignment(Qt::AlignCenter);
    this->filesList->layout()->addWidget(loading);

    this->thread->init(path, "");
    this->currentPath = path;
}

void listFolders::searchFilesList(QString search){
    QLayoutItem *item;
    while((item = this->filesList->layout()->takeAt(0)) != nullptr){
        QWidget *widget = item->widget();
        delete widget;
    }

    QLabel *loading = new QLabel("Carregando...");
    loading->setAlignment(Qt::AlignCenter);
    this->filesList->layout()->addWidget(loading);
    this->thread->init(this->currentPath, search);
}


