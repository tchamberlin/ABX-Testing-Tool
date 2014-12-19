#ifndef PLAYER_H
#define PLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QThread>

class Player : public QMediaPlayer
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0, Flags flags = 0);

    void changeSound(QUrl url);

    QUrl getUrl();

public slots:
    void setLooping(bool doLoop);

    void playbackModeChanged(bool checked);

signals:
    void error(QString err);
    void soundChanged();

private slots:
    void waitForBuffer(QMediaPlayer::MediaStatus status);

private:
    QMediaPlaylist *playlist;
    void delay(int millisecondsToWait);
};

#endif // PLAYER_H
