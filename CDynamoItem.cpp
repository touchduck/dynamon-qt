#include "CDynamoItem.h"

using namespace Aws::DynamoDB;
using namespace Aws::DynamoDB::Model;


CDynamoItem CDynamoItem::parsing(AttributeValue &attributeValue, Aws::String columnName) {

    CDynamoItem dynamoItem;

    dynamoItem.columnName = columnName;
    Aws::String typeName = "";

    auto mapJson = attributeValue.Jsonize().GetAllObjects();

    for(auto json: mapJson) {
        auto name = json.first.c_str();
        typeName = name;
    }

    if (typeName == "B") {
        dynamoItem.columnName.append(" [B]");
        dynamoItem.itemType = CDynamoItemTypeB;
        dynamoItem.itemValue = "byte data";
        return dynamoItem;
    }

    if (typeName == "BOOL") {
        dynamoItem.columnName.append(" [BOOL]");
        dynamoItem.itemType = CDynamoItemTypeBool;
        if (attributeValue.GetBool()) {
            dynamoItem.itemValue = "True";
        } else {
            dynamoItem.itemValue = "False";
        }
        return dynamoItem;
    }

    if (typeName == "BS") {
        dynamoItem.columnName.append(" [BS]");
        dynamoItem.itemType = CDynamoItemTypeBS;
        dynamoItem.itemValue = "[byte data]";
        return dynamoItem;
    }

    if (typeName == "L") {
        dynamoItem.columnName.append(" [L]");
        dynamoItem.itemType = CDynamoItemTypeL;
        auto lData = attributeValue.GetL();

        Aws::String buffer;
        buffer.append("[");

        for (size_t i = 0; i < lData.size(); i++) {
            auto attrData = *lData.at(i);

            CDynamoItem childDynamoItem = parsing(attrData, columnName);

            if (i == 0) {
                buffer.append(childDynamoItem.itemValue.c_str());
            } else {
                buffer.append(", ");
                buffer.append(childDynamoItem.itemValue.c_str());
            }
        }

        buffer.append("]");
        dynamoItem.itemValue = buffer;
        return dynamoItem;
    }

    if (typeName == "M") {
        dynamoItem.columnName.append(" [M]");
        dynamoItem.itemType = CDynamoItemTypeM;
        auto mData = attributeValue.GetM();
        return dynamoItem;
    }

    if (typeName == "N") {
        dynamoItem.columnName.append(" [N]");
        dynamoItem.itemType = CDynamoItemTypeN;
        auto data = attributeValue.GetN();
        dynamoItem.itemValue = data.c_str();
        return dynamoItem;
    }

    if (typeName == "NS") {
        dynamoItem.columnName.append(" [NS]");
        dynamoItem.itemType = CDynamoItemTypeNS;
        auto data = attributeValue.GetNS();

        Aws::String buffer;
        buffer.append("[");

        for (size_t i = 0; i < data.size(); i++) {
            auto strData = data.at(i);
            if (i == 0) {
                buffer.append(strData.c_str());
            } else {
                buffer.append(", ");
                buffer.append(strData.c_str());
            }
        }
        buffer.append("]");
        dynamoItem.itemValue = buffer;
        return dynamoItem;
    }

    if (typeName == "NULL") {
        dynamoItem.columnName.append(" [NULL]");
        dynamoItem.itemType = CDynamoItemTypeNull;
        if (attributeValue.GetNull()) {
            dynamoItem.itemValue = "Null";
        } else {
            dynamoItem.itemValue = "Not Null";
        }
        return dynamoItem;
    }

    if (typeName == "S") {
        dynamoItem.columnName.append(" [S]");
        dynamoItem.itemType = CDynamoItemTypeS;
        auto data = attributeValue.GetS();
        dynamoItem.itemValue = data.c_str();
        return dynamoItem;
    }

    if (typeName == "SS") {
        dynamoItem.columnName.append(" [SS]");
        dynamoItem.itemType = CDynamoItemTypeSS;
        auto data = attributeValue.GetSS();
        Aws::String buffer;
        buffer.append("[");
        for (size_t i = 0; i < data.size(); i++) {
            auto strData = data.at(i);
            if (i == 0) {
                buffer.append(strData.c_str());
            } else {
                buffer.append(", ");
                buffer.append(strData.c_str());
            }
        }
        buffer.append("]");
        dynamoItem.itemValue = buffer;
        return dynamoItem;
    }

    return dynamoItem;
}
