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

    // User Play function
    // Handles the user input
    // @param i_index: index of button pressed
    // @returns: Result of Tic Tac Toe play
    GameState UserPlay(QPoint i_index);

    // Computer Play function
    // Finds a random free spot on the board and passes it on
    // @param o_index: output index of button chosen. Is being used by the UI
    // @returns: Result of Tic Tac Toe play
    GameState ComputerPlay(QPoint &o_index);

    // Reset Game function
    // Resets all game variables
    void ResetGame();

    inline const int GetColumns() const { return COLUMNCOUNT;}
    inline const int GetRows() const { return ROWCOUNT;}

signals:

private:
    // Is Checked function
    // Function checks if a tile on the board is checked
    // @param i_index: index of tile to check
    // @returns: if tile is checked
    inline bool isChecked(QPoint i_index) const { return m_ticTacToeGrid[i_index.x()][i_index.y()] != Marking::NOTMARKED;}

    // Mark Square function
    // Marks square based on input index and marking
    // @param i_index: index of tile to mark
    // @param i_marking: type of mark to set at index
    GameState MarkSquare(QPoint i_index, Marking i_marking);

    // Check For Win function
    // Checks if previous play causes a win state. Checks rows, columns and diagonal conditions
    // @param i_index: square index from last play
    // @param i_mark: mark to compare with
    bool CheckForWin(QPoint i_index, Marking i_mark);

    const int COLUMNCOUNT = 3, ROWCOUNT = 3;
    const int m_totalSquares;

    // Stores mark data for the Tic Tac Toe
    Marking m_ticTacToeGrid[3][3];
    // Keeping a counter of how many marks have been placed
    int m_moveCounter = 0;
};

#endif // GAMELOGIC_H
