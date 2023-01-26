#pragma once

#include <QObject>

#include <memory>

#include "IMainView.h"
#include "GameProcess.h"

class MainWindow;

class MainWindowPresenter : public QObject
{
    Q_OBJECT
public:
    explicit MainWindowPresenter(MainWindow* view, QObject* parent = nullptr);
    ~MainWindowPresenter();

private slots:
    void onStartButtonClicked(bool checked);
    void onStopButtonClicked(bool checked);
    void onMouseClicked();

    void onDisplayedDataChanged();

private:
    IMainView*  _view = nullptr;

    std::unique_ptr<GameProcess> _gameProcess;
    const GameDataManager*       _gameData = nullptr;
};
