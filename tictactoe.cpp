#include "tictactoe.h"
#include "./ui_tictactoe.h"

#include "gamelogic.h"

TicTacToe::TicTacToe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TicTacToe)
{
    ui->setupUi(this);

    Init();
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

    // Connects each button on the board with the TicTacToeButtonPress
    for (int column =0; column < m_gameLogic->GetColumns(); column++)
    {
        for (int row =0; row < m_gameLogic->GetRows(); row++)
        {
            QPushButton* button = dynamic_cast<QPushButton*>(ui->ticTacToeLayout->itemAtPosition(row, column)->widget());
            Q_ASSERT(button != nullptr);
            m_TTTButtons[row][column] = button;

            connect(button, &QPushButton::clicked, this, [this, button, row, column] {TicTacToe::TicTacToeButtonPress(row, column);});
        }
    }

    connect(ui->resetButton, &QPushButton::clicked, this, &TicTacToe::ResetBoard);
    connect(ui->computerStarts, &QRadioButton::clicked, this, &TicTacToe::SettingsChanged);

    return bSuccess;
}

void TicTacToe::ComputerPlay()
{
    QPoint comSquareIndex;
    // Execute computer move. Returns index of square computer chose. Need it to change button
    GameState state = m_gameLogic->ComputerPlay(comSquareIndex);
    if(state == GameState::WIN)
    {
        ui->gameOutput->setText("Computer win!");
    }
    else if(state == GameState::DRAW)
    {
        ui->gameOutput->setText("Game Draw");
    }

    Q_ASSERT(comSquareIndex.x() >= 0 && comSquareIndex.x() < m_gameLogic->GetRows());
    Q_ASSERT(comSquareIndex.y() >= 0 && comSquareIndex.y() < m_gameLogic->GetColumns());

    m_TTTButtons[comSquareIndex.x()][comSquareIndex.y()]->setText("O");
    m_TTTButtons[comSquareIndex.x()][comSquareIndex.y()]->setEnabled(false);
}

// Slots
//==================================================================================

void TicTacToe::TicTacToeButtonPress(int i_row, int i_column)
{

    m_TTTButtons[i_row][i_column]->setText("X");
    m_TTTButtons[i_row][i_column]->setEnabled(false);

    QPoint userSquareIndex {i_row, i_column};
    GameState state = m_gameLogic->UserPlay(userSquareIndex);
    if(state == GameState::WIN)
    {
        ui->gameOutput->setText("You win!");
    }
    else if(state == GameState::DRAW)
    {
        ui->gameOutput->setText("Game Draw");
    }
    else
    {
        ComputerPlay();
    }

}

void TicTacToe::ResetBoard()
{
    for (int i =0; i < m_gameLogic->GetColumns(); i++)
    {
        for (int j =0; j < m_gameLogic->GetRows(); j++)
        {
            m_TTTButtons[j][i]->setText("");
            m_TTTButtons[j][i]->setEnabled(true);
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
