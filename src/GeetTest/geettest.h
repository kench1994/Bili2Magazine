#ifndef GEETTEST_H
#define GEETTEST_H
#include "src/HttpMethod/HttpMethod.h"

const QString GET_GAME = QString("https://www.xxx.com").append("/apps");

enum{
    e_GET_GT = 0x02
}PACK_CPAT;

class GeetTest : public HttpMethod
{
public:
    GeetTest();
    void CaptchaGc();
    void SendGt();
    void SendPic();
    void GetPic();

//protected:
//        QString setVauleGT(QString &s);

//        friend QString showVauleCL();

//    void requestFinished(QNetworkReply *reply, const QByteArray data, const int statusCode) = 0;
public slots:
    void slot_requestFinished(); //http请求结束
//    void slot_requestFinished(bool bSuccess, const QString &strResult);

//signals:
//    void signal_requestFinished(bool bSuccess,const QString& strResult); //http请求结束
};

#endif // GEETTEST_H
