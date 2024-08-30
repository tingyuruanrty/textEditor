#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionNew_N,&QAction::triggered,this,&MainWindow::newTriggered);
    connect(ui->actionOpen_O,&QAction::triggered,this,&MainWindow::openTriggered);
    connect(ui->actionSave_as,&QAction::triggered,this,&MainWindow::saveAsTriggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newTriggered(){
    ui->textEdit->clear();
    this->setWindowTitle("newFile.txt");
}

void MainWindow::openTriggered(){
    QString fileName=QFileDialog::getOpenFileName(this,"Open File",QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),"*.txt");
    if(fileName.isEmpty()){
        QMessageBox::warning(this,"waring","please select a file");
    }else{
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);
        QByteArray ba = file.readAll();
        QString a(ba);
        ui->textEdit->setText(a);
        file.close();
    }
}

void MainWindow::saveAsTriggered(){
    QString fileName = QFileDialog::getSaveFileName(this,"Open File",QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),"*.txt");
    if(fileName.isEmpty()){
        QMessageBox::warning(this,"waring","please enter a name");
    }else{
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        QByteArray ba;
        ba.append(ui->textEdit->toPlainText().toUtf8());
        file.write(ba);
        file.close();
    }
}
