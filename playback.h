#ifndef PLAYBACK_H
#define PLAYBACK_H

#include <QWidget>

#include "player.h"


namespace Ui {
class Playback;
}

class Playback : public QWidget
{
    Q_OBJECT

public:
    explicit Playback(QWidget *parent = 0);
    ~Playback();

    QUrl getUrlA();
    QUrl getUrlB();
    QUrl getUrlX();

public slots:
    void startNewTrial();


    void durationChanged(qint64 len);
    void positionChanged(qint64 pos);
    //    void setPlaybackPosition(qint64 pos);
    void setPlaybackPosition(qint64 pos);

    void handlePlayerError(QMediaPlayer::Error error);
private slots:

    void on_pushButton_play_pressed();

    void on_radioButton_A_pressed();

    void on_radioButton_B_pressed();

    void on_radioButton_X_pressed();

    void on_pushButton_pause_pressed();

    void on_pushButton_stop_pressed();

    void loadSounds(QUrl sound_1, QUrl sound_2);



signals:
    void playbackModeChanged(bool checked);

private:
    Ui::Playback *ui;

    Player *player_A;
    Player *player_B;
    Player *player_X;

    QThread *thread_A;\
    QThread *thread_B;
    QThread *thread_X;

    Player *last_player;
    Player *current_player;

    QUrl sound_1;
    QUrl sound_2;

//    bool soundsPlaying();

    bool switchToPlayer(Player *p);
};

#endif // PLAYBACK_H
