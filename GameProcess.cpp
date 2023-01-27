#include "GameProcess.h"

#include <iostream>

#include <functional>

#include "GameDataManager.h"

GameProcess::GameProcess()
    : _gameData(std::make_unique<GameDataManager>(new GameDataManager))
{
}

GameProcess::~GameProcess()
{
    delete _gameProcess;
}

void GameProcess::startGame()
{
    if (_gameData->gameStatus() == GameDataManager::GAME_START)
        stopGame();

    _gameData->setGameStatus(GameDataManager::GAME_START);
    _gameProcess = new std::thread(loopGameProcess, _gameData.get(), _roundPeriodMilsec, _waitPeriodMilsec);
}

void GameProcess::stopGame()
{
    _gameData->setGameStatus(GameDataManager::GAME_STOP);
    _gameProcess->join();
}

void GameProcess::mouseClicked()
{
    _gameData->addCurrentClicks();
}

const GameDataManager* GameProcess::gameData() const
{
    return _gameData.get();
}

void GameProcess::loopGameProcess(GameDataManager* gameData, int roundPeriod, int waitPeriod)
{
    while (gameData->gameStatus() != GameDataManager::GAME_STOP)
    {
        gameData->setRoundStatus(GameDataManager::ROUND_START);
        std::this_thread::sleep_for(std::chrono::milliseconds(roundPeriod));

        if (gameData->gameStatus() == GameDataManager::GAME_STOP)
            break;

        gameData->setRoundStatus(GameDataManager::ROUND_STOP);
        std::this_thread::sleep_for(std::chrono::milliseconds(waitPeriod));
    }
}
