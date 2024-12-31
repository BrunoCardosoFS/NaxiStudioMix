#include "fileslist.h"

#include <QDir>
#include <QAudioDecoder>

FilesList::FilesList(QObject *parent):QThread{parent}
{}

void FilesList::init(QString path, QString search){
    if(this->isRunning()){
        this->terminate();
    }

    this->path = path;
    this->search = search;

    this->start();
}

void FilesList::run(){
    QJsonArray jsonArray = {};
    QDir files(this->path);

    QString suffix;
    QString fileName;
    QAudioDecoder decoder;
    QJsonArray item;

    foreach (QFileInfo qfi, files.entryInfoList()) {
        suffix = qfi.completeSuffix().toLower();
        fileName = qfi.fileName();

        if(qfi.isFile() && (fileName.contains(search, Qt::CaseInsensitive)) && (suffix == "mp3" || suffix == "wav" || suffix == "opus" || suffix == "aac" || suffix == "flac" || suffix == "webm" || suffix == "m4a")){
            decoder.setSource(QUrl::fromLocalFile(qfi.absoluteFilePath()));
            decoder.start();

            QTime time = QTime(0, 0).addMSecs(decoder.duration());

            QString format = "mm:ss:zzz";
            if(decoder.duration() > 3600000){
                format = "hh:mm:ss";
            }

            item = {qfi.fileName(), qfi.absoluteFilePath(), time.toString(format)};
            jsonArray.append(item);
        }
    }

    emit finish(jsonArray);
}
