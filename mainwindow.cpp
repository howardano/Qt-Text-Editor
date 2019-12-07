#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_file.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeView->setMaximumSize(400, 541);
    ui->dockWidget_3->setMinimumSize(1359, 129);
    ui->dockWidget_3->setMaximumWidth(1359);
    ui->dockWidget_3->setVisible(false);
    ui->dockWidget->setMinimumSize(400, 541);
    ui->dockWidget->setMaximumSize(400, 700);
    ui->dockWidget->setVisible(false);
    editor1 = new QPlainTextEdit();
    ui->tabWidget->setMaximumSize(1195, 541);
    ui->tabWidget->clear();
    on_actionNew_triggered();
    setCentralWidget(ui->tabWidget);
    setWindowTitle("Text Editor");
    setupEditor(editor1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    QPlainTextEdit * helper = new QPlainTextEdit;
    setupEditor(helper);
    ui->tabWidget->addTab(helper, QString("default %0").arg(ui->tabWidget->count() + 1));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    currentFile.clear();
    if (ui->listView->isVisible() == true) {
        on_actionShow_second_thing_triggered();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open");
    setFile(fileName);
}

void MainWindow::setFile(QString &fileName) {
    ui->tabWidget->addTab(new QPlainTextEdit(), fileName);
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    QPlainTextEdit * pTextEdit = qobject_cast<QPlainTextEdit *>(ui->tabWidget->currentWidget());
    setupEditor(pTextEdit);
    pTextEdit->setPlainText(text);
    file.close();
    if (ui->listView->isVisible() == true) {
        on_actionShow_second_thing_triggered();
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }
    currentFile = fileName;
    QTextStream out(&file);
    QPlainTextEdit * pTextEdit = qobject_cast<QPlainTextEdit *>(ui->tabWidget->currentWidget());
    QString text = pTextEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog pDialog(&printer, this);
    if (pDialog.exec() == QDialog::Rejected) {
        QMessageBox::warning(this, "Warning", "Cannot Access printer");
        return;
    }
    QPlainTextEdit * pTextEdit = qobject_cast<QPlainTextEdit *>(ui->tabWidget->currentWidget());
    pTextEdit->print(&printer);
}

void MainWindow::on_actionExit_triggered()
{
    QPlainTextEdit * pTextEdit;
    for (int i = 0; i < ui->tabWidget->count(); ++i) {
        pTextEdit = qobject_cast<QPlainTextEdit *>(ui->tabWidget->widget(i));
        QString str = pTextEdit->document()->toPlainText();
        QFile file(ui->tabWidget->tabText(i));
        if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QApplication::quit();
        }
        QTextStream in(&file);
        QString ty = in.readAll();
        if (str.isEmpty() == false && str != ty) {
                QMessageBox msgBox;
                msgBox.setText("The document " + ui->tabWidget->tabText(i) + " has been modified.");
                msgBox.setInformativeText("Do you want to save your changes?");
                msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
                msgBox.setDefaultButton(QMessageBox::Save);
                int ret = msgBox.exec();
                switch (ret) {
                  case QMessageBox::Save:
                      on_actionSave_triggered();
                      break;
                  case QMessageBox::Discard:
                      break;
                  case QMessageBox::Cancel:
                      break;
                  default:
                      break;
            }
         }
      }
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    QPlainTextEdit * pTextEdit = qobject_cast<QPlainTextEdit *>(ui->tabWidget->currentWidget());
    pTextEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    QPlainTextEdit * pTextEdit = qobject_cast<QPlainTextEdit *>(ui->tabWidget->currentWidget());
    pTextEdit->paste();
}


void MainWindow::on_actionCut_triggered()
{
    QPlainTextEdit * pTextEdit = qobject_cast<QPlainTextEdit *>(ui->tabWidget->currentWidget());
    pTextEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    QPlainTextEdit * pTextEdit = qobject_cast<QPlainTextEdit *>(ui->tabWidget->currentWidget());
    pTextEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    QPlainTextEdit * pTextEdit = qobject_cast<QPlainTextEdit *>(ui->tabWidget->currentWidget());
    pTextEdit->redo();
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    QFile file(ui->tabWidget->tabText(index));
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        ui->tabWidget->removeTab(index);
        if (ui->listView->isVisible() == true) {
            on_actionShow_second_thing_triggered();
        }
        return;
    }
    QTextStream in(&file);
    QString ty = in.readAll();
    QPlainTextEdit * pTextEdit = qobject_cast<QPlainTextEdit *>(ui->tabWidget->widget(index));
    QString str = pTextEdit->document()->toPlainText();
    if (str.isEmpty() != true && str != ty) {
           QMessageBox msgBox;
           msgBox.setText("The document has been modified.");
           msgBox.setInformativeText("Do you want to save your changes?");
           msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
           msgBox.setDefaultButton(QMessageBox::Save);
           int ret = msgBox.exec();
            switch (ret) {
              case QMessageBox::Save:
                  on_actionSave_triggered();
                  ui->tabWidget->removeTab(index);
                  if (ui->listView->isVisible() == true) {
                      on_actionShow_second_thing_triggered();
                  }
                  break;
              case QMessageBox::Discard:
                  break;
              default:
                  break;
            }
         }
    ui->tabWidget->removeTab(index);
    if (ui->listView->isVisible() == true) {
        on_actionShow_second_thing_triggered();
    }
}

void MainWindow::on_actionSave_2_triggered()
{
    QFile file(currentFile);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }
    QTextStream out(&file);
    QPlainTextEdit * pTextEdit = qobject_cast<QPlainTextEdit *>(ui->tabWidget->currentWidget());
    QString text = pTextEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::on_actionSave_all_triggered()
{
    ui->tabWidget->setCurrentIndex(0);
    for (int i = 0; i < ui->tabWidget->count(); ++i) {
        currentFile = ui->tabWidget->tabText(i);
        if (currentFile == "default") {
            on_actionSave_triggered();
            return;
        }
        QFile file(currentFile);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
            return;
        }
        QTextStream out(&file);
        QPlainTextEdit * pTextEdit = qobject_cast<QPlainTextEdit *>(ui->tabWidget->widget(i));
        QString text = pTextEdit->toPlainText();
        out << text;
        file.close();
    }
}

void MainWindow::on_actionClose_all_triggered()
{
    QPlainTextEdit * pTextEdit;
    for (int i = 0; i < ui->tabWidget->count(); ++i) {
        pTextEdit = qobject_cast<QPlainTextEdit *>(ui->tabWidget->widget(i));
        QString str = pTextEdit->document()->toPlainText();
        if (str.isEmpty() == false) {
                QMessageBox msgBox;
                msgBox.setText("The document " + ui->tabWidget->tabText(i) + " has been modified.");
                msgBox.setInformativeText("Do you want to save your changes?");
                msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
                msgBox.setDefaultButton(QMessageBox::Save);
                int ret = msgBox.exec();
                switch (ret) {
                  case QMessageBox::Save:
                      on_actionSave_triggered();
                      break;
                  case QMessageBox::Discard:
                      break;
                  case QMessageBox::Cancel:
                      break;
                  default:
                      break;
            }
         }
      }
    ui->tabWidget->setCurrentIndex(0);
    for (int i = ui->tabWidget->count(); i != -1; i--) {
        ui->tabWidget->removeTab(i);
    }
    on_actionNew_triggered();
    if (ui->listView->isVisible() == true) {
        on_actionShow_second_thing_triggered();
    }
}


void MainWindow::on_actionSelect_all_triggered()
{
    QPlainTextEdit * pTextEdit = qobject_cast<QPlainTextEdit *>(ui->tabWidget->currentWidget());
    pTextEdit->selectAll();
}

void MainWindow::setupEditor(QPlainTextEdit * editor)
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    editor->setFont(font);

    highlighter = new Highlighter(editor->document());

    QFile file("mainwindow.h");
    if (file.open(QFile::ReadOnly | QFile::Text))
        editor->setPlainText(file.readAll());
}

void MainWindow::on_actionShow_folder_triggered()
{
    QString sPath = "C:/";

    fileMdl = new QFileSystemModel(this);
    fileMdl->setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);
    fileMdl->setRootPath(sPath);
    ui->treeView->setModel(fileMdl);
    ui->tabWidget->resize(1100, 570);
    ui->dockWidget->setVisible(true);
    ui->treeView->resize(400, 512);
    ui->dockWidget->resize(400, 512);
    //resize(1100, 570);
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QString fileName = fileMdl->fileInfo(index).absoluteFilePath();
    setFile(fileName);
}

void MainWindow::on_actionShow_second_thing_triggered()
{
    ui->dockWidget_3->setVisible(true);
    setMinimumSize(1195, 747);
    setMaximumSize(1195, 747);
    resize(1195, 747);
    QStringList list;
    for (int i = 0; i < ui->tabWidget->count(); ++i) {
        list << ui->tabWidget->tabText(i);
    }
    QStringListModel * mdl = new QStringListModel();
    mdl->setStringList(list);
    ui->listView->setModel(mdl);
}

void MainWindow::on_dockWidget_3_visibilityChanged(bool visible)
{
    setMinimumSize(1195, 610);
    setMaximumSize(1195, 610);
    resize(1195, 560);
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    for (int i = 0; i < ui->tabWidget->count(); ++i) {
        if (index.data().toString() == ui->tabWidget->tabText(i)) {
            ui->tabWidget->setCurrentIndex(i);
            break;
        }
    }
}
