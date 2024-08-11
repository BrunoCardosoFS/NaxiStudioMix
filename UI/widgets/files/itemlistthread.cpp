#include "itemlistthread.h"

#include <QDebug>

#include <QDir>
#include <QAudioDecoder>

itemListThread::itemListThread(QWidget *parent):QThread{parent}{

}

void itemListThread::init(QString pathList, QString search){
    this->path = pathList;
    this->search = search;

    if(this->isRunning()){
        this->terminate();
    }

    this->start();

    // qInfo() << (this->isRunning() ? "Executando" : "Não executando");
}

void itemListThread::run(){
    QJsonArray jsonArray = {};
    QDir files(path);

    QString suffix;
    QString fileName;
    QAudioDecoder decoder;
    QJsonArray item;

    foreach (QFileInfo qfi, files.entryInfoList()) {
        suffix = qfi.completeSuffix().toLower();

        fileName = qfi.fileName();

        if(qfi.isFile() && (fileName.contains(search, Qt::CaseInsensitive)) && (suffix == "mp3" || suffix == "wav" || suffix == "opus" || suffix == "aac" || suffix == "flac" || suffix == "webm")){
            decoder.setSource(QUrl::fromLocalFile(qfi.absoluteFilePath()));
            decoder.start();

            item = {qfi.fileName(), qfi.absoluteFilePath(), decoder.duration()};
            jsonArray.append(item);
        }
    }

    emit finishedLoad(jsonArray);
}
