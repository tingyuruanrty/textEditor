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
    connect(ui->actionSave,&QAction::triggered,this,&MainWindow::saveTriggered);
    this->setWindowTitle("tingyu text editor");
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
    filePath=QFileDialog::getOpenFileName(this,"Open File",QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),"*.txt");
    fileName=filePath.remove(0,filePath.lastIndexOf('/')+1);
    if(filePath.isEmpty()){
        //MessageBox Dialog
        QMessageBox::warning(this,"waring","please select a file");
    }else{
        //after chosen the file
        QFile file(filePath);
        file.open(QIODevice::ReadOnly);
        QByteArray ba = file.readAll();
        file.close();

        QString a(ba);
        ui->textEdit->setText(a);

        this->setWindowTitle(fileName);
    }
}

void MainWindow::saveAsTriggered(){
    //save dialog show up
    filePath = QFileDialog::getSaveFileName(this,"Save File as",QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),"*.txt");
    fileName=filePath.remove(0,filePath.lastIndexOf('/')+1);
    if(filePath.isEmpty()){
        QMessageBox::warning(this,"waring","please enter a name");
    }else{
        QByteArray ba;
        ba.append(ui->textEdit->toPlainText().toUtf8());

        QFile file(filePath);
        file.open(QIODevice::WriteOnly);
        file.write(ba);
        file.close();

        this->setWindowTitle(fileName);
    }
}

void MainWindow::saveTriggered(){
    QByteArray ba;
    ba.append(ui->textEdit->toPlainText().toUtf8());

    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    file.write(ba);
    file.close();
}

void MainWindow::keyPressEvent(QKeyEvent* k){
    if(k->modifiers()==Qt::ControlModifier && k->key()==Qt::Key_S){
        saveTriggered();
    }
}

void MainWindow::mousePressEvent(QMouseEvent* m){
    QPoint p=m->pos();
    if(m->button()==Qt::LeftButton || m->button()==Qt::RightButton){
        qDebug()<< p;
    }
}
