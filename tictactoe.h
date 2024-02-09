#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QPushButton>

class GameLogic;

QT_BEGIN_NAMESPACE
namespace Ui {
class TicTacToe;
}
QT_END_NAMESPACE

class TicTacToe : public QMainWindow
{
    Q_OBJECT

public:
    TicTacToe(QWidget *parent = nullptr);
    ~TicTacToe();

private slots:
    // Tic Tac Toe Button Press
    // Handles whenever a button is presson on the Tic Tac Toe board
    // @param i_button: passes in the button pressed to mark it
    // @param i_row: row of button
    // @param i_column: column of button
    void TicTacToeButtonPress(int i_row, int i_column);

    // Reset Board
    // Resets all UI elements and game state
    void ResetBoard();

    // Settings Changed
    // Prints out a message whenever a setting is changed
    void SettingsChanged();

private:

    // Init
    // Initializes ui elements and creates GameLogic
    bool Init();
    // Computer Play
    // Sets off a computer move and set ui components depending on outcome
    void ComputerPlay();

    Ui::TicTacToe *ui;
    QPushButton* m_TTTButtons[3][3];

    GameLogic* m_gameLogic;
};
#endif // TICTACTOE_H
