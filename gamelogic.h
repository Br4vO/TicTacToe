#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
 #include <QPoint>

enum GameState{RUNNING=0, WIN, DRAW};

class GameLogic : public QObject
{
    Q_OBJECT
private:
    enum Marking {NOTMARKED=0, O, X};
public:
    // Constructor
    explicit GameLogic(QObject *parent = nullptr);

    GameState UserPlay(QPoint i_index);
    GameState ComputerPlay(QPoint &o_index);

    void ResetGame();

    inline const int GetColumns() const { return COLUMNCOUNT;}
    inline const int GetRows() const { return ROWCOUNT;}

signals:

private:
    inline bool isChecked(QPoint i_index) const { return m_ticTacToeGrid[i_index.x()][i_index.y()] != Marking::NOTMARKED;}


    GameState MarkSquare(QPoint i_index, Marking i_marking);
    bool CheckForWin(QPoint i_index, Marking i_mark);

    const int COLUMNCOUNT = 3, ROWCOUNT = 3;
    const int m_totalTiles;

    Marking m_ticTacToeGrid[3][3];
    int m_moveCounter = 0;
};

#endif // GAMELOGIC_H
