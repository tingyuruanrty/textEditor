#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QFile>
#include <QByteArray>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* k);
    void mousePressEvent(QMouseEvent* m);

private slots:
    void newTriggered();
    void openTriggered();
    void saveAsTriggered();
    void saveTriggered();
private:
    Ui::MainWindow *ui;
    QString filePath;
    QString fileName;
};
#endif // MAINWINDOW_H
