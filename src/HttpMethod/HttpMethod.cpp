#include "HttpMethod.h"
#include <QTextCodec>

const int nHTTP_TIME = 10000; //10秒

HttpMethod::HttpMethod(QObject *parent) :
    QObject(parent)
{
//    m_pNetworkReply = NULL;
    m_pTimer = new QTimer;
    connect(m_pTimer,SIGNAL(timeout()),
            SLOT(slot_requestTimeout()));//超时信号

//    m_pNetRequest.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
//    m_pNetRequest.setHeader(QNetworkRequest::ContentLengthHeader, bytePost.length());
}

//发起请求
void HttpMethod::sendRequest(const QString &strUrl)
{
    m_strUrl = strUrl;

    m_pNetRequest.setUrl(QUrl(strUrl)); //地址信息
    m_pNetRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

//    m_pNetRequest.setRawHeader("Content-Type", "application/json");
//    m_pNetRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    m_pNetRequest.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
//    m_pNetRequest.setRawHeader("Referer","https://passport.bilibili.com/login");
    m_pNetRequest.setRawHeader("Accept-Language","zh-CN,zh;q=0.8");
    m_pNetRequest.setRawHeader("X-Requested-With","XMLHttpRequest");
    m_pNetRequest.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36");
//    m_pNetRequest.setRawHeader("Content-Type","application/x-www-form-urlencoded");
//    m_pNetRequest.setRawHeader("Accept-Encoding","gzip, deflate");//"gzip,deflate"
//    m_pNetRequest.setRawHeader("Host","localhost:8888");
//    m_pNetRequest.setRawHeader("Content-Length","18");
//    m_pNetRequest.setRawHeader("Connection","Keep-Alive");
//    m_pNetRequest.setRawHeader("Cache-Control","no-cache");
    if(strUrl.toLower().startsWith("https")){//https请求，需ssl支持(下载openssl拷贝libeay32.dll和ssleay32.dll文件至Qt bin目录或程序运行目录)
        QSslConfiguration sslConfig;
        sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
        sslConfig.setProtocol(QSsl::TlsV1_1);
        m_pNetRequest.setSslConfiguration(sslConfig);
    }
    m_pNetworkManager = new QNetworkAccessManager;
    m_pNetworkReply = m_pNetworkManager->get(m_pNetRequest);
    connect(m_pNetworkReply,SIGNAL(finished()),
            SLOT(slot_requestFinished())); //请求完成信号

    m_pTimer->start(nHTTP_TIME);

}

//请求结束
void HttpMethod::slot_requestFinished()
{
    m_pTimer->stop();//关闭定时器
    QByteArray resultContent = m_pNetworkReply->readAll();
    QString strResult = QString::fromUtf8(resultContent);
    int statusCode = m_pNetworkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//http返回码
    qDebug()<<"statusCode"<<statusCode;
    if(statusCode == 200){
//        qDebug()<<"replyData:"<<resultContent;
//        emit signal_requestFinished(true,strResult);//请求成功
    }
//    else{
//        emit signal_requestFinished(false,strResult);//请求失败
//    }
    m_pNetworkReply->deleteLater();
    this->deleteLater(); //释放内存
}

//请求超时
void HttpMethod::slot_requestTimeout()
{
    qDebug()<<"请求超时";
//    emit signal_requestFinished(false,"timeout");//请求失败
    m_pNetworkReply->deleteLater();
    this->deleteLater();//释放内存
}
