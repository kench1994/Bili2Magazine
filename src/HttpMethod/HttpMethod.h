#ifndef HTTPMETHOD_H
#define HTTPMETHOD_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QTimer>
#include <QSslConfiguration>
#include <QString>
#include <QByteArray>

//http请求类
class HttpMethod : public QObject
{
    Q_OBJECT
public:
    explicit HttpMethod(QObject *parent = 0);
    void sendRequest(const QString& strUrl);//根据url发起http请求

public slots:
    virtual void slot_requestFinished(); //http请求结束
    void slot_requestTimeout();  //请求超时

//    void slot_requestFinished(bool bSuccess, const QString& strResult); //http请求结束


//protected:
//    virtual void requestFinished(QNetworkReply *reply, const QByteArray data, const int statusCode) = 0;

private:
    QNetworkAccessManager *m_pNetworkManager;//网络管理类
protected:
    QTimer* m_pTimer; //请求超时计时器
    QNetworkRequest m_pNetRequest;
    QNetworkReply* m_pNetworkReply; //封装请求返回信息
    QString m_strUrl; //记录当前请求的url

signals:
    void signal_requestFinished(bool bSuccess,int iStateMachine,const QString& strResult); //http请求结束
};

#endif // HTTPMETHOD_H
