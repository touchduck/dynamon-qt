#ifndef CDYNAMOITEMTYPE_H
#define CDYNAMOITEMTYPE_H

typedef enum {
    // custom data type
    CDynamoItemTypeNone,

    // A Binary data type.
    // Type: Blob
    // Required: No
    CDynamoItemTypeB,

    // A Boolean data type.
    // Type: Boolean
    // Required: No
    CDynamoItemTypeBool,

    // A Binary Set data type.
    // Type: array of Blobs
    // Required: No
    CDynamoItemTypeBS,

    // A List of attribute values.
    // Type: array of AttributeValue objects
    // Required: No
    CDynamoItemTypeL,

    // A Map of attribute values.
    // Type: String to AttributeValue object map
    // Required: No
    CDynamoItemTypeM,

    // A Number data type.
    // Type: String
    // Required: No
    CDynamoItemTypeN,

    // A Number Set data type.
    // Type: array of Strings
    // Required: No
    CDynamoItemTypeNS,

    // A Null data type.
    // Type: Boolean
    // Required: No
    CDynamoItemTypeNull,

    // A String data type.
    // Type: String
    // Required: No
    CDynamoItemTypeS,

    // A String Set data type.
    // Type: array of Strings
    // Required: No
    CDynamoItemTypeSS,

} CDynamoItemType;

#endif // CDYNAMOITEMTYPE_H
