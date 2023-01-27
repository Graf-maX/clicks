#include "MainWindowPresenter.h"

#include <thread>

#include "GameDataManager.h"
#include "GameProcess.h"
#include "MainWindow.h"

MainWindowPresenter::MainWindowPresenter(MainWindow* view, QObject* parent)
    : QObject(parent)
    , _view(view)
    , _gameProcess(new GameProcess)
{
    connect(view, &MainWindow::startButtonClicked, this, &MainWindowPresenter::onStartButtonClicked);
    connect(view, &MainWindow::stopButtonClicked, this, &MainWindowPresenter::onStopButtonClicked);
    connect(view, &MainWindow::mousClicked, this, &MainWindowPresenter::onMouseClicked);

    _gameData = _gameProcess->gameData();

    connect(_gameData, &GameDataManager::displayedDataChanged, this, &MainWindowPresenter::onDisplayedDataChanged);
    onDisplayedDataChanged();
}

MainWindowPresenter::~MainWindowPresenter()
{
}

void MainWindowPresenter::onStartButtonClicked(bool /*checked*/)
{
    _gameProcess->startGame();
}

void MainWindowPresenter::onStopButtonClicked(bool /*checked*/)
{
    _gameProcess->stopGame();
}

void MainWindowPresenter::onMouseClicked()
{
    _gameProcess->mouseClicked();
}

void MainWindowPresenter::onDisplayedDataChanged()
{
    if (_gameData->gameStatus() == GameDataManager::GAME_STOP)
    {
        _view->setNumber({});
        return;
    }
    else if (_gameData->roundStatus() == GameDataManager::ROUND_PRESTART)
    {
        _view->setNumber(tr("Начали!"));
        return;
    }

    _view->setCount(_gameData->correctAnswers(), _gameData->wrongAnswers());
    const QString textLable = _gameData->roundStatus() == GameDataManager::ROUND_START
                    ? QString::number(_gameData->requiredClicks())
                    : _gameData->lastRoundResult() == GameDataManager::RESULT_SUCCESS
                        ? QString(tr("Верно!"))
                        : QString(tr("Неверно"));

    _view->setNumber(textLable);
}
