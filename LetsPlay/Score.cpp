#include "Score.h"

#include <QFont>

Score::Score(int maxGoals, QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    //initializae the score to 0
    scoreTeam1 = 0;
    scoreTeam2 = 0;
    Max = maxGoals;

    //draw the text
    setPlainText(QString::number(scoreTeam1) + QString(" - ") + QString::number(scoreTeam2)); //Score: 0
    setFont(QFont("times", 18));
    setDefaultTextColor("white");
    setPos(275, 374);
}

bool Score::increaseTeam1()
{
    scoreTeam1++;
    setPlainText(QString::number(scoreTeam2) + QString(" - ") + QString::number(scoreTeam1)); //Score: +
    if (scoreTeam1 == Max){
        Winner();
        return true;
    }else{
        return false;
    }
}

bool Score::increaseTeam2()
{
    scoreTeam2++;
    setPlainText(QString::number(scoreTeam2) + QString(" - ") + QString::number(scoreTeam1)); //Score: +
    if (scoreTeam2 == Max){
        Winner();
        return true;
    }else{
        return false;
    }
}

int Score::getScoreTeam1()
{
    return scoreTeam1;
}

int Score::getScoreTeam2()
{
    return scoreTeam2;
}

void Score::Winner()
{
    setFont(QFont("times", 70));
    setPos(212, 118);
}
