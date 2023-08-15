#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGeoCoordinate>
#include <QGeoLocation>

class InputHandler;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void connectWindowElements(const InputHandler* _inputHdl);
    void connectInputs(const InputHandler *_inputHdl);
    void setMapViewContextProperty(const QString &_name, QObject *_value);

public slots:
    void displayCurrentPos(QGeoCoordinate _coord);
    void displayAdress(QGeoLocation _loc);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
