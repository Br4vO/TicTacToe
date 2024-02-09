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
    void TicTacToeButtonPress(QPushButton* i_button, int row, int coloumn);
    void ResetBoard();
    void SettingsChanged();

private:

    bool Init();
    void ComputerPlay();

    Ui::TicTacToe *ui;
    QStandardItemModel* m_model;
    QPushButton* m_TTTButtons[3][3];

    GameLogic* m_gameLogic;
};
#endif // TICTACTOE_H
