#pragma once

#include <QMainWindow>

#include "IMainView.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public IMainView
{
    Q_OBJECT
    Q_INTERFACES(IMainView)
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void setNumber(const QString& number) override;

    void setCount(int rightCount, int wrongCount) override;

signals:
    void startButtonClicked(bool checked);
    void stopButtonClicked(bool checked);
    void mousClicked();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void connectSignalSlots();
    void setStyle();

private:
    Ui::MainWindow* _ui;
};
