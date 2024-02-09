#include "tictactoe.h"
#include "./ui_tictactoe.h"

#include "gamelogic.h"

TicTacToe::TicTacToe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TicTacToe)
{
    ui->setupUi(this);

    Init();
    ResetBoard();

}

TicTacToe::~TicTacToe()
{
    delete ui;
    delete m_gameLogic;
}

bool TicTacToe::Init()
{
    bool bSuccess = true;

    m_gameLogic = new GameLogic();

    for (int column =0; column < m_gameLogic->GetColumns(); column++)
    {
        for (int row =0; row < m_gameLogic->GetRows(); row++)
        {
            QPushButton* button = dynamic_cast<QPushButton*>(ui->ticTacToeLayout->itemAtPosition(row, column)->widget());
            Q_ASSERT(button != nullptr);
            m_TTTButtons[row][column] = button;

            connect(button, &QPushButton::clicked, this, [this, button, row, column] {TicTacToe::TicTacToeButtonPress(button, row, column);});
        }
    }

    connect(ui->resetButton, &QPushButton::clicked, this, &TicTacToe::ResetBoard);
    connect(ui->computerStarts, &QRadioButton::clicked, this, &TicTacToe::SettingsChanged);

    return bSuccess;
}

// Slots
//==================================================================================

void TicTacToe::TicTacToeButtonPress(QPushButton* i_button, int i_row, int i_column)
{
    Q_ASSERT(i_button);
    i_button->setText("X");


    QPoint userSquareIndex {i_row, i_column};
    GameState state = m_gameLogic->UserPlay(userSquareIndex);
    if(state == GameState::WIN)
    {
        ui->gameOutput->setText("You win!");
        return;
    }
    else if(state == GameState::DRAW)
    {
        ui->gameOutput->setText("Game Draw");
        return;
    }

    ComputerPlay();
}

void TicTacToe::ResetBoard()
{
    for (int i =0; i < m_gameLogic->GetColumns(); i++)
    {
        for (int j =0; j < m_gameLogic->GetRows(); j++)
        {
            m_TTTButtons[j][i]->setText("");
        }
    }
    ui->gameOutput->setText("");

    m_gameLogic->ResetGame();

    if (ui->computerStarts->isChecked())
        ComputerPlay();
}

void TicTacToe::SettingsChanged()
{
    ui->gameOutput->setText("Click ResetGame for settings to take effect.");
}

void TicTacToe::ComputerPlay()
{
    QPoint comSquareIndex;
    GameState state = m_gameLogic->ComputerPlay(comSquareIndex);
    if(state == GameState::WIN)
    {
        ui->gameOutput->setText("Computer win!");
    }
    else if(state == GameState::DRAW)
    {
        ui->gameOutput->setText("Game Draw");
        return;
    }

    QPushButton* comButtonSelected = dynamic_cast<QPushButton*>(ui->ticTacToeLayout->itemAtPosition(comSquareIndex.x(), comSquareIndex.y())->widget());
    comButtonSelected->setText("O");
}
