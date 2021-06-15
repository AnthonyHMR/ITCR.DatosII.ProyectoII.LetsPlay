#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score : public QGraphicsTextItem
{
public:
    Score(int, QGraphicsItem *parent=0);
    bool increaseTeam1();
    bool increaseTeam2();
    int getScoreTeam1();
    int getScoreTeam2();
private:
    int scoreTeam1;
    int scoreTeam2;
    int Max;
    void Winner();
};

#endif // SCORE_H
