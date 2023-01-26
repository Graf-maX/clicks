#pragma once

#include <QLabel>
#include <QWidget>

class Label : public QLabel
{
    Q_OBJECT
public:
    explicit Label(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~Label();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override;
};
