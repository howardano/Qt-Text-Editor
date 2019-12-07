#include "widgetchanger.h"
#include "ui_widgetchanger.h"

WidgetChanger::WidgetChanger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetChanger)
{
    mdl = new QStringListModel();
    ui->setupUi(this);
}

void WidgetChanger::help(QStringList &list, QMainWindow ino) {
    in = &ino;
    mdl->setStringList(list);
    ui->listView->setModel(mdl);
    ui->dockWidget->show();
}

WidgetChanger::~WidgetChanger()
{
    delete ui;
}

void WidgetChanger::on_listView_clicked(const QModelIndex &index)
{
    QString fileName = index.data().toString();
}
