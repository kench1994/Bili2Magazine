#include "src/GeetTest/geettest.h"
#include "src/QJsonParsing/qjsonparsing.h"
#include <QStateMachine>
static const QString sc_getGT = "https://passport.bilibili.com/captcha/gc?cType=2&vcType=2&_=";
static const QString sc_sendGT = "https://api.geetest.com/gettype.php?gt=";
static const QString sc_getPIC = "https://api.geetest.com/get.php?gt=";
QString str_gt,str_challenge,str_path,str_staticServer,
        str_bg,str_fullbg,str_slice;


//typedef struct s_gtChal{
//    QString str_gt;
//    QString str_challenge;
//}gtChal;

extern int StateMachine;

GeetTest::GeetTest()
{
    m_pNetworkReply = NULL;
    m_pTimer = new QTimer;
    connect(m_pTimer,SIGNAL(timeout()),
            SLOT(slot_requestTimeout()));//超时信号

    m_pNetRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
//    QStateMachine machine;
//    auto prepareGT = new QState();
//    machine.setInitialState(prepareGT);
//    machine.start();

}

//获取GeetTest相关参数
void GeetTest::CaptchaGc(){
    qint64 n_UnixStampTime = QDateTime::currentSecsSinceEpoch();
    sendRequest(sc_getGT+n_UnixStampTime*1000);
}
void GeetTest::SendGt(){
//    qDebug()<<sc_sendGT+str_gt;
    QString ss = sc_sendGT+str_gt+"&callback=cb";
    sendRequest(ss);
}
void GeetTest::GetPic(){
    //"https://api.geetest.com/get.php?gt={0}&challenge={1}&width=100%&product=float&offline=false&protocol=&path={2}&type=slide&callback=cb"
    QString ss = sc_getPIC+str_gt+"&challenge="+str_challenge+"&width=100%&product=float&offline=false&protocol=&path=/static/js/geetest.5.10.10.js&type=slide&callback=cb";
    qDebug()<<ss;
    sendRequest(ss);

//    sendRequest(sc_getPIC+str_gt+"&challenge="+str_challenge+\
//    "&width=100%&product=float&offline=false&protocol=&path="+\
//    str_path+"type=slide&callback=cb");//type参数后面要补充
}

//void GeetTest::GetPic(){

//}
void GeetTest::slot_requestFinished(){
//    qDebug()<<"进入无参数槽函数";
    m_pTimer->stop();//关闭定时器
    QByteArray resultContent = m_pNetworkReply->readAll();
//    qDebug()<<"resultContent"<<resultContent;

    QString strResult = QString::fromUtf8(resultContent);
//    qDebug()<<"resultContent"<<strResult;
    int statusCode = m_pNetworkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//http返回码
    qDebug()<<"statusCode:"<<statusCode<<"状态码:"<<StateMachine;
    if(statusCode == 200){
        QJsonObject jsonObj_Data;
//        qDebug()<<"now:"<<GetJsonObjectFromByteArray(resultContent);
        if(!StateMachine){
            StateMachine = 0x11;//解析第1个包
            jsonObj_Data = GetJsonObjectFromByteArray(resultContent).value("data").toObject();
            str_gt = jsonObj_Data.value("gt").toString();
            str_challenge = jsonObj_Data.value("challenge").toString();
        }else if(StateMachine == 0x02){
            qDebug()<<"正在解析第2个包";
//            qDebug()<<resultContent.mid(3,resultContent.length()-4);
            jsonObj_Data = GetJsonObjectFromByteArray(resultContent.mid(3,resultContent.length()-4)).value("data").toObject();

            str_path = jsonObj_Data.value("path").toString();
            str_staticServer = jsonObj_Data.value("static_servers").toString();
//            qDebug()<<"path:"<<str_path<<str_staticServer;
            StateMachine = 0x12;//解析第2个包
        }else if(StateMachine == 0x03){
            StateMachine = 0x13;//解析第3个包
            qDebug()<<"正在解析第3个包";
            jsonObj_Data = GetJsonObjectFromByteArray(resultContent.mid(3,resultContent.length()-4));
            str_bg = jsonObj_Data.value("bg").toString();
            str_fullbg = jsonObj_Data.value("fullbg").toString();
            str_slice =  jsonObj_Data.value("slice").toString();

        }
        emit GeetTest::signal_requestFinished(true,StateMachine,strResult);//请求成功

    }else{
        emit GeetTest::signal_requestFinished(false,0,strResult);//请求失败
    }

    m_pNetworkReply->deleteLater();
    this->deleteLater(); //释放内存
}

//QString GeetTest::setVauleGT(QString &s){
//    this->str_gt = s;
//}

//QString GeetTest::showVauleGT(){
//    return this->str_gt;
//}
//QString GeetTest::showVauleCL(){
//    return str_challenge;
//}
