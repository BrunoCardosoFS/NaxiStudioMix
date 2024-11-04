#include "folderswidget.h"

FoldersWidget::FoldersWidget(QWidget *parent):QWidget{parent}
{
    this->parent = parent;
}

void FoldersWidget::loadFolders(){
    this->folders = new FoldersList(this);

    QList<QWidget*> typeWidgets;
    QList mediaTypes = {"Vinhetas", "Músicas", "Outros", "Comerciais"};

    foreach (QString type, mediaTypes) {
        QWidget *typeWidget = new QWidget(this->parent);
        typeWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        QVBoxLayout *typeLayout = new QVBoxLayout(typeWidget);
        typeLayout->setContentsMargins(0, 0, 0, 0);

        QLabel *typeLabel = new QLabel((type + ":"), typeWidget);
        typeLabel->setAlignment(Qt::AlignCenter);

        typeLayout->addWidget(typeLabel);

        this->parent->layout()->addWidget(typeWidget);
        typeWidgets.append(typeWidget);
    }

    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->parent->layout()->addItem(spacer);

    foreach (QJsonValue jsonValue, this->folders->foldersArray) {
        QJsonObject jsonObject = jsonValue.toObject();

        QPushButton *item = new QPushButton(jsonObject.value("title").toString());
        item->setToolTip(jsonObject.value("title").toString());
        item->setIconSize(QSize(20, 20));
        item->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        item->setCursor(Qt::PointingHandCursor);

        item->setText(jsonObject.value("title").toString());
        item->setProperty("id", jsonObject.value("id").toString());

        connect(item, &QPushButton::clicked, [this, jsonObject](){
            emit loadFiles(jsonObject.value("path").toString(), "");
        });

        int type = jsonObject.value("type").toInt();

        if(type == 0){
            item->setProperty("type", "jingle");
            item->setIcon(QIcon(":/catalog/jingle.svg"));
            typeWidgets.at(0)->layout()->addWidget(item);
        }else if(type == 1){
            item->setProperty("type", "music");
            item->setIcon(QIcon(":/catalog/music.svg"));
            typeWidgets.at(1)->layout()->addWidget(item);
        }else if(type == 2){
            item->setProperty("type", "commercial");
            item->setIcon(QIcon(":/catalog/commercial.svg"));
            typeWidgets.at(3)->layout()->addWidget(item);
        }else{
            item->setProperty("type", "other");
            item->setIcon(QIcon(":/catalog/other.svg"));
            typeWidgets.at(2)->layout()->addWidget(item);
        }
    }
}
