#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QSharedPointer>
#include <QVector>
#include <QPointF>
#include <QPair>
#include <QMenu>
#include <QAction>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsEllipseItem *currentSelection1;
    QGraphicsEllipseItem *currentSelection2;
    QVector<QPair<QPointF, QPointF>> matches;
    QVector<QPair<QGraphicsEllipseItem*, QGraphicsEllipseItem*>> selectedMatches;
    QPointF point1;
    QPointF point2;
    QMenu *imageMenu;
    QAction *chooseLeftImage;
    QAction *chooseRightImage;
    bool eventFilter(QObject *object, QEvent *event);
    void createMenus();
    void createActions();
    void loadLeftImage();
    void loadRightImage();
};
#endif // MAINWINDOW_H
