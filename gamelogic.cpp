#include "gamelogic.h"
#include <QRandomGenerator>

GameLogic::GameLogic(QObject *parent)
    : QObject{parent}, m_totalTiles(ROWCOUNT*COLUMNCOUNT)
{}

GameState GameLogic::UserPlay(QPoint i_index)
{
    return MarkSquare(i_index, Marking::X);
}

GameState GameLogic::ComputerPlay(QPoint &o_index)
{
    Q_ASSERT(m_moveCounter < m_totalTiles);

    QPoint playPos {QRandomGenerator::global()->bounded(ROWCOUNT), QRandomGenerator::global()->bounded(COLUMNCOUNT)};
    while (isChecked(playPos))
    {
        if (playPos.y() < (COLUMNCOUNT-1))
        {
            playPos.setY(playPos.y()+1);
        }
        else
        {
            if (playPos.x() < (ROWCOUNT-1))
            {
                playPos.setX(playPos.x()+1);
            }
            else
            {
                playPos.setX(0);
            }
            playPos.setY(0);
        }
    }

    // Returning square index computer selected
    o_index.setX(playPos.x());
    o_index.setY(playPos.y());

    return MarkSquare(playPos, Marking::O);
}

GameState GameLogic::MarkSquare(QPoint i_index, Marking i_marking)
{
    GameState bState = GameState::RUNNING;

    Q_ASSERT(i_index.x() < ROWCOUNT && i_index.y() < COLUMNCOUNT);
    m_ticTacToeGrid[i_index.x()][i_index.y()] = i_marking;
    qInfo("Marked square at row = %d & coloumn = %d!", i_index.x(), i_index.y());

    // Nobody can win before 5 moves have been played
    m_moveCounter++;
    if (m_moveCounter >= (ROWCOUNT + COLUMNCOUNT - 1))
    {
        bState = (CheckForWin(i_index, i_marking)) ? GameState::WIN : GameState::RUNNING;
        if (bState != GameState::WIN && m_moveCounter >= m_totalTiles)
            bState = GameState::DRAW;
    }

    return bState;
}

bool GameLogic::CheckForWin(QPoint i_index, Marking i_marking)
{
    int rowIndex = 0;

    while(rowIndex < ROWCOUNT && m_ticTacToeGrid[rowIndex][i_index.y()] == i_marking)
    {
        rowIndex++;
    }
    if (rowIndex == ROWCOUNT)
        return true;

    // Check coloumn
    int columnIndex = 0;
    while(columnIndex < COLUMNCOUNT && m_ticTacToeGrid[i_index.x()][columnIndex] == i_marking)
    {
        columnIndex++;
    }
    if (columnIndex == COLUMNCOUNT)
        return true;

    // Check downward diagonal
    if (i_index.x() == i_index.y())
    {
        rowIndex = 0;
        columnIndex = 0;

        while(columnIndex < COLUMNCOUNT && m_ticTacToeGrid[rowIndex][columnIndex] == i_marking)
        {
            rowIndex++;
            columnIndex++;
        }
        if (columnIndex == COLUMNCOUNT)
            return true;
    }

    if ((i_index.x() + i_index.y()) == (ROWCOUNT-1))
    {
        rowIndex = (ROWCOUNT-1);
        columnIndex = 0;

        while(columnIndex < COLUMNCOUNT && m_ticTacToeGrid[rowIndex][columnIndex] == i_marking)
        {
            rowIndex--;
            columnIndex++;
        }
        if (columnIndex == COLUMNCOUNT)
            return true;
    }

    return false;
}

void GameLogic::ResetGame()
{
    for(int row = 0; row < ROWCOUNT; row++)
    {
        for(int coloumn = 0; coloumn < COLUMNCOUNT; coloumn++)
        {
            m_ticTacToeGrid[row][coloumn] = Marking::NOTMARKED;
        }
    }
    m_moveCounter =0;
}
