#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QPoint>
#include <QPen>
#include <QColor>
#include <QScrollBar>
#include <QFileDialog>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentSelection1(NULL)
    , currentSelection2(NULL)
{
    ui->setupUi(this);
    ui->graphicsView->installEventFilter(this);
    ui->graphicsView_2->installEventFilter(this);
    QGraphicsScene *scene1 = new QGraphicsScene();
    QGraphicsScene *scene2 = new QGraphicsScene();

    QPixmap pic1("/home/ashima/Desktop/hidden_camera/kantara/frames/2754.jpg");

    ui->graphicsView->setScene(scene1);
    scene1->addPixmap(pic1);

    QPixmap pic2("/home/ashima/Desktop/hidden_camera/kantara/frames/2755.jpg");
    scene2->addPixmap(pic2);
    ui->graphicsView_2->setScene(scene2);

    ui->label->setText("Selected pixel coordinates will appear here.");
    ui->label_2->setText("Selected pixel coordinates will appear here");
}

MainWindow::~MainWindow()
{
    delete ui;
}


//Get position with scroll and top margin in consideration
bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if ( object == ui->graphicsView && (event->type() == QEvent::MouseButtonPress)) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        point1 = ui->graphicsView->mapToScene(mouseEvent->pos());

        ui->label->setText(QStringLiteral("%1, %2").arg(point1.x()).arg(point1.y()));
        // Check if selection's scene is not null or matches with this scene
        if(currentSelection1 != NULL) {
            ui->graphicsView->scene()->removeItem(currentSelection1);
            delete currentSelection1;
        }
        currentSelection1 = new QGraphicsEllipseItem(point1.x(), point1.y(), 3, 3);
        currentSelection1->setBrush(QBrush(QColor("red")));
        currentSelection1->setPen(QPen(QColor("red")));
        ui->graphicsView->scene()->addItem(currentSelection1);
    }
    if ( object == ui->graphicsView_2 && (event->type() == QEvent::MouseButtonPress)) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        point2 = ui->graphicsView_2->mapToScene(mouseEvent->pos());

        ui->label_2->setText(QStringLiteral("%1, %2").arg(point2.x()).arg(point2.y()));
        if(currentSelection2 != NULL) {
            ui->graphicsView_2->scene()->removeItem(currentSelection2);
            delete currentSelection2;
        }
        currentSelection2 = new QGraphicsEllipseItem(point2.x(), point2.y(), 3, 3);
        currentSelection2->setBrush(QBrush(QColor("red")));
        currentSelection2->setPen(QPen(QColor("red")));
        ui->graphicsView_2->scene()->addItem(currentSelection2);
    }
    return false;
}

void MainWindow::on_pushButton_clicked()
{
    matches.push_back(qMakePair(point1, point2));
    ui->graphicsView->scene()->removeItem(currentSelection1);
    ui->graphicsView_2->scene()->removeItem(currentSelection2);
    QGraphicsEllipseItem *match1 = new QGraphicsEllipseItem(point1.x(), point1.y(), 3, 3);
    QGraphicsEllipseItem *match2 = new QGraphicsEllipseItem(point2.x(), point2.y(), 3, 3);
    match1->setBrush(QBrush(QColor("#CCCCCC")));
    match2->setBrush(QBrush(QColor("#CCCCCC")));
    match1->setPen(QPen(QColor("#CCCCCC")));
    match2->setPen(QPen(QColor("#CCCCCC")));
    ui->graphicsView->scene()->addItem(match1);
    ui->graphicsView_2->scene()->addItem(match2);
    selectedMatches.push_back(qMakePair(match1, match2));
}


void MainWindow::on_pushButton_2_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "DialogTitle", "matches.csv");

    QFile data(filename);
    if(data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream output(&data);
        foreach(auto match, matches) {
            output << match.first.x() << "," << match.first.y() << "," << match.second.x() << "," << match.second.y() << Qt::endl;
        }
        qInfo() << "Saved matches to csv" << filename;
    }
}

