#include "CDynamo.h"

#include <QMessageBox>

static const char* ALLOCATION_TAG = "DynaMon";

Aws::Vector<GetItemOutcome> getItemResultsFromCallbackTest;
Aws::Vector<PutItemOutcome> putItemResultsFromCallbackTest;
Aws::Vector<DeleteItemOutcome> deleteItemResultsFromCallbackTest;
Aws::Vector<UpdateItemOutcome> updateItemResultsFromCallbackTest;

std::mutex getItemResultMutex;
std::condition_variable getItemResultSemaphore;

std::mutex putItemResultMutex;
std::condition_variable putItemResultSemaphore;

std::mutex deleteItemResultMutex;
std::condition_variable deleteItemResultSemaphore;

std::mutex updateItemResultMutex;
std::condition_variable updateItemResultSemaphore;

void CDynamo::showMsg(Aws::String text) {

    QString qStr = QString::fromUtf8(text.c_str());

    QMessageBox msgBox;

    msgBox.setText(qStr);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    msgBox.exec();
}

void CDynamo::Configuration() {

    Aws::Client::ClientConfiguration config;

    config.connectTimeoutMs = 30000;
    config.requestTimeoutMs = 30000;

    config.readRateLimiter = Aws::MakeShared<Aws::Utils::RateLimits::DefaultRateLimiter<>>(ALLOCATION_TAG, 200000);
    config.writeRateLimiter = Aws::MakeShared<Aws::Utils::RateLimits::DefaultRateLimiter<>>(ALLOCATION_TAG, 200000);

    config.httpLibOverride = Aws::Http::TransferLibType::DEFAULT_CLIENT;

    config.region = Aws::Region::US_EAST_1;
    config.scheme = Scheme::HTTP;

    config.proxyHost = "127.0.0.1";
    config.proxyPort = 8000;

    Aws::String accessKeyId = "willow";
    Aws::String secretKey = "ditto";

    AWSCredentials credentials = AWSCredentials(accessKeyId, secretKey);
    m_client = Aws::MakeShared<DynamoDBClient>(ALLOCATION_TAG, credentials, config);
}

Aws::Vector<Aws::String> CDynamo::getTableList() {

    Aws::Vector<Aws::String> vec;

    ListTablesRequest request;
    ListTablesOutcome outcome = m_client->ListTables(request);

    if (!outcome.IsSuccess()) {
        auto error = outcome.GetError();
        showMsg(error.GetExceptionName());
        return vec;
    }

    auto result = outcome.GetResult();

    for (auto tableName: result.GetTableNames()) {
        vec.push_back(tableName.c_str());
    }

    return vec;

}

void CDynamo::Scan(Aws::String tableName) {

    fieldMap.clear();
    collection.clear();

    ScanRequest request;
    request.WithTableName(tableName);
    request.SetLimit(100);

    while (true) {

        ScanOutcome outcome = m_client->Scan(request);

        if (!outcome.IsSuccess()) {
            auto error = outcome.GetError();
            showMsg(error.GetExceptionName());
            return;
        }

        auto result = outcome.GetResult();
        auto items = result.GetItems();

        for(auto item: items) {

            CDynamoColumns dataColumns;

            for(auto col: item) {
                Aws::String columnNmae = col.first.c_str();
                CDynamoItem dynamoItem = CDynamoItem::parsing(col.second, columnNmae);
                dataColumns.push_back(CDynamoColumns::value_type(dynamoItem));
                fieldMap.insert(FieldMap::value_type(dynamoItem.columnName.c_str(), dynamoItem.itemType));
            }

            this->collection.push_back(CDynamoRows::value_type(dataColumns));
        }

        if (result.GetLastEvaluatedKey().size() == 0) {
            break;
        }

        request.SetExclusiveStartKey(result.GetLastEvaluatedKey());
    }

}


