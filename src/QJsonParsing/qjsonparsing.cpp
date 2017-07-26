#include "qjsonparsing.h"

//QJsonParsing::QJsonParsing()
//{

//}
QJsonObject GetJsonObjectFromByteArray(const QByteArray jsonByteArray){
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonByteArray);
//    if( jsonDocument.isNull() ){
//        qDebug()<< "===> please check the string "<< jsonString.toLocal8Bit().data();
//    }
    QJsonObject jsonObject = jsonDocument.object();
    return jsonObject;
}
