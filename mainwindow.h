#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGeoCoordinate>
#include <QGeoLocation>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void displayCurrentPos(QGeoCoordinate _coord);
    void displayAdress(QGeoLocation _loc);

private:
    void connectWindowElements();

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
