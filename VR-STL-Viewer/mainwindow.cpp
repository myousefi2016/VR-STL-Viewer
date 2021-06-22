#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileDialog>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    win = new QWidget;
    btn = new QPushButton("Choose STL File",this);
    clck = new QPushButton("Send 3D Mesh to VR",this);
    layout = new QVBoxLayout;
    cl = new QHBoxLayout;
    line = new QLineEdit(this);
    label = new QLabel("File Path",this);
    txt = new QTextEdit;
    mesh = new Mesh();
    renderer = new Renderer();

    line->show();
    btn->show();
    clck->show();
    txt->show();

    layout->addWidget(btn);
    layout->addWidget(clck);
    layout->addLayout(cl);
    cl->addWidget(label);
    cl->addWidget(line);
    layout->addWidget(txt);
    win->setLayout(layout);
    MainWindow::setCentralWidget(win);

    setFixedHeight(sizeHint().height());
    MainWindow::setWindowTitle("3D Surface Mesh Cleaner");

    QObject::connect(btn, SIGNAL(clicked()), this, SLOT(open()));
    QObject::connect(clck, SIGNAL(clicked()), this, SLOT(click()));
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

   mesh->writeSTLFile();
   const char* filepathcleaned = mesh->GetFilePathCleaned();
   fnamecleaned = QString(filepathcleaned);
}

void MainWindow::click()
{
    std::string fnameString = QString(fnamecleaned).toLocal8Bit().constData();
    renderer->SetFilePath(fnameString.c_str());
    renderer->Render();
}
