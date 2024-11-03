#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H
#include <QtWidgets>
#include <QtCore>
#include <QtMultimedia>

class AudioPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit AudioPlayer(QWidget *parent = nullptr);

private:
    QMediaPlayer *Player;
    QAudioOutput *AudioOutput;

signals:
    void durationChanged(qint64 durationms, QString duration);
    void positionChanged(qint64 positionms, QString position);
    void titleChanged(QString title);

public slots:
    void setSource(QString path);
    void setPosition(qint64 position);
    void play();
    void pause();
    void stop();

private slots:
    void updateDuration(qint64 duration);
    void updatePosition(qint64 position);
};

#endif // AUDIOPLAYER_H
