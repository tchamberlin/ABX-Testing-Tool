#include "scorekeeper.h"

ScoreKeeper::ScoreKeeper(QObject *parent) :
    QObject(parent)
{
    currentScore.numberCorrect = 0;
    currentScore.totalGuesses = 0;

    expectedScore.numberCorrect = 0;
    expectedScore.totalGuesses= 0;
}


void ScoreKeeper::guessMade(ScoreKeeper::Guesses guess)
{
    if (guess == Correct)
        currentScore.numberCorrect++;

    currentScore.totalGuesses++;


    expectedScore.totalGuesses++;
    expectedScore.numberCorrect = expectedScore.totalGuesses / 2;

    emit scoreUpdated(currentScore, expectedScore);
}
ScoreKeeper::Score ScoreKeeper::getExpectedScore() const
{
    return expectedScore;
}

void ScoreKeeper::setExpectedScore(const Score &value)
{
    expectedScore = value;
}

ScoreKeeper::Score ScoreKeeper::getCurrentScore() const
{
    return currentScore;
}

void ScoreKeeper::setCurrentScore(const Score &value)
{
    currentScore = value;
}


