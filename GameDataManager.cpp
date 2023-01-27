#include "GameDataManager.h"

#include <cstdlib>
#include <time.h>

GameDataManager::GameDataManager(QObject* parent)
    : QObject(parent)
{
}

GameDataManager::~GameDataManager()
{
}

void GameDataManager::resetData()
{
    _correctAnswers = 0;
    _wrongAnswers   = 0;
    _requiredClicks = 0;
    _currentClicks  = 0;
}

int GameDataManager::correctAnswers() const
{
    return _correctAnswers;
}

int GameDataManager::wrongAnswers() const
{
    return _wrongAnswers;
}

int GameDataManager::requiredClicks() const
{
    return _requiredClicks;
}

int GameDataManager::currentClicks() const
{
    return _currentClicks;
}

void GameDataManager::addCurrentClicks()
{
    if (_roundStatus == ROUND_STOP || _gameStatus == GAME_STOP)
        return;

    ++_currentClicks;
}

GameDataManager::GameStatus GameDataManager::gameStatus() const
{
    return _gameStatus;
}

void GameDataManager::setGameStatus(GameStatus status)
{
    _gameStatus = status;
    if (_gameStatus == GAME_START)
        resetData();

    emit displayedDataChanged();
}

GameDataManager::RoundStatus GameDataManager::roundStatus() const
{
    return _roundStatus;
}

void GameDataManager::setRoundStatus(RoundStatus status)
{
    if (_gameStatus == GAME_STOP && _roundStatus == status)
        return;

    _roundStatus = status;
    switch (_roundStatus) {
        case ROUND_START:
        {
            setLastRoundResult(RESULT_UNDEFINED);
            srand(time(NULL));
            _requiredClicks = _minCount + rand() % (_maxCount - _minCount + 1);
            break;
        }
        case ROUND_STOP:
        {
            setLastRoundResult(_requiredClicks == _currentClicks ? RESULT_SUCCESS : RESULT_FAIL);
            _requiredClicks = 0;
            _currentClicks  = 0;
            break;
        }
        default:
            break;
    }

    emit displayedDataChanged();
}

GameDataManager::RoundResult GameDataManager::lastRoundResult() const
{
    return _lastRoundResult;
}

void GameDataManager::setLastRoundResult(RoundResult result)
{
    if (_gameStatus == GAME_STOP)
        return;

    _lastRoundResult = result;
    switch (_lastRoundResult)
    {
        case RESULT_UNDEFINED:
            break;

        case RESULT_SUCCESS:
            ++_correctAnswers;
            break;

        case RESULT_FAIL:
            ++_wrongAnswers;
            break;
    }
}
