#ifndef SCOREKEEPER_H
#define SCOREKEEPER_H

#include <QObject>

class ScoreKeeper : public QObject
{
    Q_OBJECT

public:
    explicit ScoreKeeper(QObject *parent = 0);

    struct Score {
        int numberCorrect;
        int totalGuesses;
    };

    enum Guesses {
        Correct,
        Incorrect
    };


    Score getCurrentScore() const;
    void setCurrentScore(const Score &value);

    Score getExpectedScore() const;
    void setExpectedScore(const Score &value);

signals:
    void scoreUpdated(ScoreKeeper::Score currentScore, ScoreKeeper::Score expectedScore);

public slots:
    void guessMade(ScoreKeeper::Guesses guess);

private:
    Score currentScore;
    Score expectedScore;

};

#endif // SCOREKEEPER_H
