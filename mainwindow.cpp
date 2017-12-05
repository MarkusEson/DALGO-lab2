#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QActionGroup>
#include <assert.h>
#include <QThread>
#include <QApplication>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _pixels(_numberOfRows, std::vector<QColor>(_numberOfColumns, Qt::white)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->centralWidget->setDrawingParent(this);

    _colorGroup = new QActionGroup(this);
    _colorGroup->setObjectName("colors");
    _colorGroup->addAction(ui->actionBlack);
    _colorGroup->addAction(ui->actionWhite);
    _colorGroup->addAction(ui->actionRed);
    _colorGroup->addAction(ui->actionBlue);
    _colorGroup->addAction(ui->actionYellow);
    _colorGroup->addAction(ui->actionGreen);
    _colorGroup->addAction(ui->actionOrange);

    _penGroup = new QActionGroup(this);
    _penGroup->addAction(ui->actionPixelpenna);
    _penGroup->addAction(ui->actionFill);
    _penGroup->addAction(ui->actionFillNRFifo);
    _penGroup->addAction(ui->actionFillNRStack);


    _speedGroup = new QActionGroup(this);
    _speedGroup->addAction(ui->actionSlow);
    _speedGroup->addAction(ui->actionNormal);
    _speedGroup->addAction(ui->actionsFast);
    _speedGroup->addAction(ui->actionUltraFast);


    ui->actionBlack->setChecked(true);
    ui->actionPixelpenna->setChecked(true);

    connect(_speedGroup, &QActionGroup::triggered, this, &MainWindow::speedDidChange);
    connect(_penGroup, &QActionGroup::triggered, this, &MainWindow::penDidChange);

    ui->actionBlack->trigger();
    ui->actionNormal->trigger();
    ui->actionPixelpenna->trigger();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::speedDidChange(QAction *action){

    if (action==ui->actionSlow) _durationOfSetpixel = 200;
    else if (action==ui->actionNormal)  _durationOfSetpixel = 50;
    else if (action==ui->actionsFast)  _durationOfSetpixel = 1;
    else if (action==ui->actionUltraFast)  _durationOfSetpixel = 0;
    else assert(false);
}
void MainWindow::penDidChange(QAction *action){

    if (action==ui->actionPixelpenna){
        _doDelaySetpixel = false;
        ui->centralWidget->setCursor(QCursor(Qt::ArrowCursor));

    }
    else {
        _doDelaySetpixel =  true;
        ui->centralWidget->setCursor(QCursor(Qt::PointingHandCursor));


    }

}


void MainWindow::setPixel(int r, int k, QColor color)
{
    assert( isInside(r,k) );
    if (_pixels[r][k]!=color){
        _pixels[r][k] = color;

        emit pixelChanged(r,k);
        if (_doDelaySetpixel && _durationOfSetpixel>0){
            QThread::msleep(_durationOfSetpixel);
            QApplication::processEvents();
        }
    }
}

QColor MainWindow::colorSelected()
{
    QAction *selected = _colorGroup->checkedAction();
    if (selected==ui->actionBlack) return Qt::black;
    if (selected==ui->actionWhite) return Qt::white;
    if (selected==ui->actionRed)  return Qt::red;
    if (selected==ui->actionBlue) return QColor(0,128,255);
    if (selected==ui->actionYellow) return Qt::yellow;
    if (selected==ui->actionGreen) return Qt::green;
    if (selected==ui->actionOrange) return QColor(255,128,0);
    assert( false );
    return QColor();
}

bool MainWindow::isPentool()
{
    return ui->actionPixelpenna->isChecked();
}

bool MainWindow::isFilltool(){
    return ui->actionFill->isChecked();
}

bool MainWindow::isFilltoolNonRecursiveStack(){
    return ui->actionFillNRStack->isChecked();
}


bool MainWindow::isFilltoolNonRecursiveFifo(){
    return ui->actionFillNRFifo->isChecked();
}


void MainWindow::on_actionErase_triggered()
{
    for (int r=0;r<numberOfRows(); r+=1)
        for (int k=0; k<numberOfColumns(); k+=1){
            _pixels[r][k] = Qt::white;
        }
    ui->centralWidget->update();
}
