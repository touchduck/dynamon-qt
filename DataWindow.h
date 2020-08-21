#ifndef DATAWINDOW_H
#define DATAWINDOW_H

#include "Common.h"
#include "CDynamo.h"

#include <QMessageBox>
#include <QLabel>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QLayout>

#include <QMainWindow>

namespace Ui {
class DataWindow;
}

class DataWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DataWindow(QWidget *parent = 0);
    ~DataWindow();

private slots:
    void on_btnScan_clicked();

private:
    Ui::DataWindow *ui;

    bool isConvertDisp;
    QStandardItemModel *model;
    QLabel* statusBarMsg;
    CDynamo *dynamo;

    void setStatusBarMsg(QString message);
};

#endif // DATAWINDOW_H
