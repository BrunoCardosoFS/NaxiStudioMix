#include "fileslistwidget.h"

#include "filewidget.h"

FilesListWidget::FilesListWidget(QWidget *parent):QWidget{parent}
{
    this->parent = parent;

    this->setFixedWidth(0);
    this->setFixedHeight(0);

    this->FilesListThread = new FilesList(this);
    connect(this->FilesListThread, &FilesList::finish, this, &FilesListWidget::finishedLoad);
}

void FilesListWidget::loadFiles(QString path, QString search){
    this->FilesListThread->init(path, search);

    // Deleting all widgets from the file list
    QLayoutItem *item;
    while ((item = this->parent->layout()->takeAt(0)) != nullptr) {
        delete item->widget();
    }

    QLabel *loading = new QLabel(this->parent);
    loading->setText("Carregando...");
    loading->setAlignment(Qt::AlignHCenter);

    this->parent->layout()->addWidget(loading);
}

void FilesListWidget::finishedLoad(const QJsonArray list){
    delete this->parent->layout()->takeAt(0)->widget();

    foreach (QJsonValue item, list) {
        QJsonArray itemArray = item.toArray();

        FileWidget *itemList = new FileWidget(this);
        itemList->setInfo(itemArray[0].toString(), itemArray[1].toString(), itemArray[2].toString());
        connect(itemList, &FileWidget::clicked, this, &FilesListWidget::loadPlayer);

        this->parent->layout()->addWidget(itemList);
    }

    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->parent->layout()->addItem(spacer);
}

void FilesListWidget::loadPlayer(QString path){
    emit loadPlayerSignal(path);
}
