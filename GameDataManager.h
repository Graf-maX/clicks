#pragma once

#include <QObject>

/// Класс управления данными игры
class GameDataManager : public QObject
{
    Q_OBJECT
public:
    enum GameStatus
    {
        GAME_START,
        GAME_STOP
    };

    enum RoundStatus
    {
        ROUND_PRESTART,
        ROUND_START,
        ROUND_STOP
    };

    enum RoundResult
    {
        RESULT_UNDEFINED,
        RESULT_SUCCESS,
        RESULT_FAIL
    };

    GameDataManager(QObject* parent = nullptr);
    ~GameDataManager();

    int  correctAnswers() const;
    int  wrongAnswers() const;
    int  requiredClicks() const;

    int  currentClicks() const;
    void addCurrentClicks();

    GameStatus gameStatus() const;
    void       setGameStatus(GameStatus status);

    RoundStatus roundStatus() const;
    void        setRoundStatus(RoundStatus status);

    RoundResult lastRoundResult() const;

signals:
    void displayedDataChanged();

private:
    void resetData();
    void setLastRoundResult(RoundResult result);

private:
    /// Данные счета в игре
    int _correctAnswers = 0;
    int _wrongAnswers   = 0;

    /// Данные счетчика кликов
    int _requiredClicks = 0;
    int _currentClicks  = 0;

    /// Текущий статус игры
    GameStatus _gameStatus = GAME_STOP;

    /// Cтатус раунда
    RoundStatus _roundStatus     = ROUND_PRESTART;
    RoundResult _lastRoundResult = RESULT_UNDEFINED;

    /// Границы формируюемых значений количества требуемых кликов
    const int _minCount = 1;
    const int _maxCount = 6;
};
