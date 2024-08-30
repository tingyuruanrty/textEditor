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
    //open dialog show up
    QString fileName=QFileDialog::getOpenFileName(this,"Open File",QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),"*.txt");

    if(fileName.isEmpty()){
        //MessageBox Dialog
        QMessageBox::warning(this,"waring","please select a file");
    }else{
        //after chosen the file
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);
        QByteArray ba = file.readAll();
        file.close();

        QString a(ba);
        ui->textEdit->setText(a);
    }
}

void MainWindow::saveAsTriggered(){
    //save dialog show up
    QString fileName = QFileDialog::getSaveFileName(this,"Save File as",QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),"*.txt");

    if(fileName.isEmpty()){
        QMessageBox::warning(this,"waring","please enter a name");
    }else{
        QByteArray ba;
        ba.append(ui->textEdit->toPlainText().toUtf8());

        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        file.write(ba);
        file.close();
    }
}

void MainWindow::keyPressEvent(QKeyEvent* k){
    if(k->modifiers()==Qt::ControlModifier && k->key()==Qt::Key_S){
        saveAsTriggered();
    }
}

void MainWindow::mousePressEvent(QMouseEvent* m){
    QPoint p=m->pos();
    if(m->button()==Qt::LeftButton || m->button()==Qt::RightButton){
        qDebug()<< p;
    }
}
