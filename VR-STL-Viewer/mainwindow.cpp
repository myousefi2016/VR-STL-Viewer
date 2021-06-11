#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileDialog>
#include <QVBoxLayout>
#include "VR-STL-Viewer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    win = new QWidget;
    btn = new QPushButton("Choose STL File",this);
    layout = new QVBoxLayout;
    cl = new QHBoxLayout;
    line = new QLineEdit(this);
    label = new QLabel("File Path",this);
    txt = new QTextEdit;
    mesh = new Mesh();

    line->show();
    btn->show();
    txt->show();

    layout->addWidget(btn);
    layout->addLayout(cl);
    cl->addWidget(label);
    cl->addWidget(line);
    layout->addWidget(txt);
    win->setLayout(layout);
    MainWindow::setCentralWidget(win);

    setFixedHeight(sizeHint().height());
    MainWindow::setWindowTitle("3D Surface Mesh Cleaner");

    QObject::connect(btn, SIGNAL(clicked()), this, SLOT(open()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("*.stl");
    dialog.setDefaultSuffix("*.stl");
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();
   fname = fileNames[0];
   QFile openFile(fname);
   openFile.open(QIODevice::ReadOnly);
   line->insert(fname);
   std::string fnameString = QString(fname).toLocal8Bit().constData();
   mesh->SetFilePath(fnameString.c_str());
   mesh->readSTLFile();
   QTextCursor prev_cursor = txt->textCursor();
   if (mesh->findDuplicateTriangles())
   {
       txt->moveCursor(QTextCursor::End);
       txt->insertPlainText(QString("Duplicate Triangle Found!\n"));
       txt->setTextCursor(prev_cursor);
   }
   else
   {
       txt->moveCursor(QTextCursor::End);
       txt->insertPlainText(QString("Duplicate Triangle Not Found!\n"));
       txt->setTextCursor(prev_cursor);
   }

   if (mesh->findNonManifoldEdges())
   {
       txt->moveCursor(QTextCursor::End);
       txt->insertPlainText(QString("Non-Manifold Edges Found!\n"));
       txt->setTextCursor(prev_cursor);
   }
   else
   {
       txt->moveCursor(QTextCursor::End);
       txt->insertPlainText(QString("Non-Manifold Edges Not Found!\n"));
       txt->setTextCursor(prev_cursor);
   }

   if (mesh->findFlippedTriangles())
   {
       txt->moveCursor(QTextCursor::End);
       txt->insertPlainText(QString("Flipped Normals Found!\n"));
       txt->setTextCursor(prev_cursor);
   }
   else
   {
       txt->moveCursor(QTextCursor::End);
       txt->insertPlainText(QString("Flipped Normals Not Found!\n"));
       txt->setTextCursor(prev_cursor);
   }
   vrRendering(fnameString.c_str());
}
