#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QApplication>
#include <QGridLayout>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QLCDNumber>
#include <QPrintDialog>
#include <QListView>
#include "file.h"
#include "ui_file.h"
#include "widgetchanger.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void setFile(QString &file);

    void closeEvent(QCloseEvent *event);

    friend class WidgetChanger;

private slots:

    void on_plainTextEdit_cursorPositionChanged();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_tabWidget_tabCloseRequested(int index);

    void on_actionSave_2_triggered();

    void on_actionSave_all_triggered();

    void on_actionClose_all_triggered();

    void on_plainTextEdit_textChanged();

    void on_actionSelect_all_triggered();

    void on_actionShow_folder_triggered();

    void text_in_tab_edited(int index);

    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_actionShow_second_thing_triggered();

    void on_listView_clicked(const QModelIndex &index);

    void on_actionShow_status_bar_triggered();

    void on_tabWidget_tabBarClicked(int index);

private:
    int numberOfSigns = 0;
    void setupEditor(QPlainTextEdit * editor);
    QFileSystemModel * fileMdl;
    QPlainTextEdit * editor1;
    Highlighter * highlighter;
    Ui::MainWindow * ui;
    QString currentFile = "";
};

#endif // MAINWINDOW_H
