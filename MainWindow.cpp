#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QCloseEvent>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    connectSignalSlots();
    setStyle();
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::setNumber(const QString& number)
{
    _ui->numberLabel->setText(number);
}

void MainWindow::setCount(int rightCount, int wrongCount)
{
    _ui->rightCountLabel->setText(QString::number(rightCount));
    _ui->wrongCountLabel->setText(QString::number(wrongCount));
}

void MainWindow::closeEvent(QCloseEvent* /*event*/)
{
    emit stopButtonClicked(true);

    QMessageBox messageBox;
    messageBox.setText(tr("Приходите еще."));
    messageBox.setButtonText(QMessageBox::Ok, tr("Обязательно приду"));
    messageBox.exec();
}

void MainWindow::connectSignalSlots()
{
    connect(_ui->startButton, &QPushButton::clicked, this, &MainWindow::startButtonClicked);
    connect(_ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopButtonClicked);
    connect(_ui->numberLabel, &Label::clicked, this, &MainWindow::mousClicked);
}

void MainWindow::setStyle()
{
    const QString styleNumberLabel =
            "QLabel {\n"
            "   font: bold;\n"
            "   font-size: 32px;\n"
            "}";
    _ui->numberLabel->setStyleSheet(styleNumberLabel);
}
