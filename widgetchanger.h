#ifndef WIDGETCHANGER_H
#define WIDGETCHANGER_H

#include <QWidget>
#include <QDockWidget>
#include <QFileSystemModel>
#include <QtCore>
#include <QtGui>
#include <QTabWidget>
#include "mainwindow.h"

namespace Ui {
class WidgetChanger;
}

class WidgetChanger : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetChanger(QWidget *parent = nullptr);
    ~WidgetChanger();

    void help(QStringList &list, QMainWindow ino);
private slots:

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::WidgetChanger * ui;
    QStringListModel * mdl;
    QStringList list;
    QMainWindow * in;
};

#endif // WIDGETCHANGER_H
