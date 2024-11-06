#include "audioplayer.h"

#include <QDebug>

AudioPlayer::AudioPlayer(QWidget *parent):QObject{parent}
{
    this->Player = new QMediaPlayer(this);
    this->AudioOutput = new QAudioOutput(this->Player);
    this->AudioOutput->setVolume(100);
    this->Player->setAudioOutput(this->AudioOutput);
    this->isPlaying = false;

    connect(this->Player, &QMediaPlayer::durationChanged, this, &AudioPlayer::updateDuration);
    connect(this->Player, &QMediaPlayer::positionChanged, this, &AudioPlayer::updatePosition);
    connect(this->Player, &QMediaPlayer::playingChanged, this, &AudioPlayer::updatePlaying);
}

bool AudioPlayer::setDevice(QString id){
    const QList<QAudioDevice> audioDevices = QMediaDevices::audioOutputs();

    for (const QAudioDevice &device : audioDevices){
        if(device.id() == id){
            this->AudioOutput->setDevice(device);
            return true;
        }
    }
    return false;
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

void AudioPlayer::updatePlaying(bool playing){
    this->isPlaying = playing;
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
