#include "DataWindow.h"
#include "ui_DataWindow.h"
#include <QDateTime>
#include <QTimeZone>
#include <QDesktopWidget>
#include <aws/core/Aws.h>

//#include "LibXL/libxl.h"

typedef std::map<Aws::String, int> FieldNumMap;
Aws::SDKOptions options;

DataWindow::DataWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DataWindow)
{
    ui->setupUi(this);

    Aws::InitAPI(options);

    this->model = new QStandardItemModel();
    this->statusBarMsg  = new QLabel;
    this->statusBarMsg->setAlignment(Qt::AlignRight);
    this->statusBarMsg->setMinimumSize(this->statusBarMsg->sizeHint());
    ui->statusbar->addWidget(this->statusBarMsg, 1);

    this->setWindowTitle("dynamon");

    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 12pt; }");
    ui->tableView->setSortingEnabled(true);

    ui->tableView->horizontalHeader()->setDefaultSectionSize(150);
    ui->tableView->verticalHeader()->setDefaultSectionSize(26);

    this->isConvertDisp = true;

    dynamo = new CDynamo();
    dynamo->Configuration();

    for (auto tableName : dynamo->getTableList())
    {
        QString qStr = QString::fromUtf8(tableName.c_str());
        ui->comboBox->addItem(qStr);
    }
}

DataWindow::~DataWindow()
{
    Aws::ShutdownAPI(options);
    delete ui;
}


void DataWindow::setStatusBarMsg(QString message) {
    this->statusBarMsg->setText(message);
}


void DataWindow::on_btnScan_clicked()
{
    this->model->clear();

    FieldNumMap fieldNumMap;

    QString tableName = ui->comboBox->currentText();

    dynamo->Scan(tableName.toUtf8().constData());

    if (dynamo->collection.size() == 0) {
        setStatusBarMsg(QString("データがありません"));
        return;
    }

    int i = 0;
    for (auto field : dynamo->fieldMap) {
        QString qStr = QString::fromUtf8(field.first.c_str());
        model->setHorizontalHeaderItem(i++, new QStandardItem(qStr));
        fieldNumMap.insert(FieldNumMap::value_type(field.first, i));
    }

    QFont* font = new QFont("Lucida Grande");
    font->setPixelSize(11);

    int j = 0;
    for (auto items : dynamo->collection) {
        for (auto item : items) {

            int fNo = fieldNumMap.at(item.columnName);
            QString qStr = QString::fromUtf8(item.itemValue.c_str());
            QStandardItem *qItem = new QStandardItem(qStr);
            qItem->setFont(*font);
            qItem->setData(Qt::AlignCenter, Qt::TextAlignmentRole);

            model->setItem(j, fNo - 1,qItem);
        }
        j++;

    }

    ui->tableView->setModel(model);
    delete font;

    QString msg = QString("[ %1 ]件のデータを取得しました").arg(dynamo->collection.size());
    setStatusBarMsg(msg);
}
