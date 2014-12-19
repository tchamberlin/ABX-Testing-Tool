#include "player.h"

#include <QTest>

Player::Player(QObject *parent, Flags flags) :
    QMediaPlayer(parent, flags)
{
    playlist = new QMediaPlaylist;
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    setPlaylist(playlist);

    this->setNotifyInterval(50);

    connect(this, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(waitForBuffer(QMediaPlayer::MediaStatus)));
}

void Player::setLooping(bool doLoop)
{
    if (doLoop)
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    else
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
}

void Player::playbackModeChanged(bool checked)
{
    if (checked)
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    else
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);

//    qDebug() << "playback mode changed" << endl;
}


void Player::changeSound(QUrl url)
{
    stop();

    playlist->clear();
    playlist->addMedia(url);

//    nanosleep()

    setMuted(true);
    play();
    QTest::qSleep(200);
//    while (mediaStatus() != QMediaPlayer::BufferedMedia && mediaStatus() != QMediaPlayer::LoadedMedia);
    stop();
    setMuted(false);

//    pause();

    qDebug() << "Duration: " << this->duration() << endl;

    qDebug() << "Status: " << mediaStatus() << endl;


}

void Player::waitForBuffer(QMediaPlayer::MediaStatus status)
{
//    qDebug() << "Status: " << status << endl;

//    if (status == QMediaPlayer::LoadedMedia ||
//            status == QMediaPlayer::BufferedMedia)
//    {
//        stop();
//        setMuted(false);
//        emit soundChanged();
//        qDebug() << "Sound changed; safe to continue." << endl;
//    }
}

QUrl Player::getUrl()
{
    return playlist->currentMedia().canonicalUrl();
}
