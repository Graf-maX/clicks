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
}

void GameProcess::startGame()
{
    _gameData->setGameStatus(GameDataManager::GAME_START);
    if (_gameProcess != nullptr)
        return;

    _gameProcess = new std::thread(loopGameProcess, _gameData.get(), _roundPeriodMilsec, _waitPeriodMilsec);
    _gameProcess->detach();
}

void GameProcess::stopGame()
{
    delete _gameProcess;
    _gameProcess = nullptr;

    _gameData->setGameStatus(GameDataManager::GAME_STOP);
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

        gameData->setRoundStatus(GameDataManager::ROUND_STOP);
        std::this_thread::sleep_for(std::chrono::milliseconds(waitPeriod));
    }
}
