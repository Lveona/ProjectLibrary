#include "langugeManage.h"

LangugeManage::LangugeManage(QObject *parent) : QObject(parent),
    m_langugeChengeSW("CN")
{
    m_translator = new QTranslator(this);
    m_translator->load(":/translations/translations/qnote_"+m_langugeChengeSW+".qm");
    qApp->installTranslator(m_translator);
}

LangugeManage::~LangugeManage()
{
    // Nothing
}

void LangugeManage::setLangugeChengeSW(QString currentLanguge)
{
    if ( m_langugeChengeSW != currentLanguge ) {
        m_langugeChengeSW = currentLanguge;
        emit langugeChengeSWChanged();
    }
}

void LangugeManage::setLang(QString setLanguge)
{
    if ( m_langugeChengeSW == setLanguge ) {
        return;
    }
    // 语言变更
    qApp->removeTranslator(m_translator);

    bool loadTrue = m_translator->load(QString(":/translations/translations/qnote_"+setLanguge+".qm"));

    qWarning()<<"chen-LangugeManage::langugeChenged---------"<<loadTrue;
    if(loadTrue)
    {
        qApp->installTranslator(m_translator);
    }
    else{
        qWarning()<<"load multiLanguage "<<"qnote_"+setLanguge+".qm " << "error!!!";
    }

    setLangugeChengeSW(setLanguge);
}
