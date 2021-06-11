#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QPushButton>
#include <QString>
#include <QFileDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <string>
#include <iostream>
#include "mesh.h"
#include "vrviewer.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPushButton * btn;
    QLineEdit * line;
    QVBoxLayout * layout;
    QHBoxLayout * cl;
    QString fname;
    QWidget * win;
    QLabel * label;
    QTextEdit * txt;
    Mesh* mesh;
	Renderer* renderer;
private slots:
    void open();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
