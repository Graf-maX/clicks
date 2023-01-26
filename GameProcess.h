#pragma once

#include <memory>

#include <chrono>
#include <thread>

class GameDataManager;

class GameProcess
{
public:
    GameProcess();
    ~GameProcess();

    void startGame();
    void stopGame();

    void mouseClicked();

    const GameDataManager* gameData() const;

private:
    static void loopGameProcess(GameDataManager* gameData, int roundPeriod, int waitPeriod);

private:
    std::unique_ptr<GameDataManager> _gameData;

    std::thread* _gameProcess = nullptr;

    const int _roundPeriodMilsec = 2000;
    const int _waitPeriodMilsec  = 1000;
};
