#include "audioplayer.h"

AudioPlayer::AudioPlayer(QWidget *parent):QWidget{parent}
{
    this->Player = new QMediaPlayer(this);
    this->AudioOutput = new QAudioOutput(this->Player);
    this->AudioOutput->setVolume(100);
    this->Player->setAudioOutput(this->AudioOutput);

    connect(this->Player, &QMediaPlayer::durationChanged, this, &AudioPlayer::updateDuration);
    connect(this->Player, &QMediaPlayer::positionChanged, this, &AudioPlayer::updatePosition);
}

void AudioPlayer::updateDuration(qint64 duration){
    QTime time = QTime(0, 0).addMSecs(duration);

    QString format = "mm:ss:zzz";
    if(duration > 3600000){
        format = "hh:mm:ss";
    }

    emit durationChanged(duration, time.toString(format));
}

void AudioPlayer::updatePosition(qint64 position){
    QTime time = QTime(0, 0).addMSecs(position);

    QString format = "mm:ss:zzz";
    if(position > 3600000){
        format = "hh:mm:ss";
    }

    emit positionChanged(position, time.toString(format));
}

void AudioPlayer::setSource(QString path){
    this->Player->setSource(QUrl::fromLocalFile(path));

    QFileInfo fileInfo(path);
    emit titleChanged(fileInfo.fileName());
}

void AudioPlayer::setPosition(qint64 position){
    this->Player->setPosition(position);
}

void AudioPlayer::play(){
    this->Player->play();
}

void AudioPlayer::pause(){
    this->Player->pause();
}

void AudioPlayer::stop(){
    this->Player->pause();
    this->Player->setPosition(0);
}
