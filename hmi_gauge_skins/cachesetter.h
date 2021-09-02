#ifndef CACHESETTER_H
#define CACHESETTER_H

#include <QObject>
#include <QtQuick3D/qquick3d.h>
#include <QtQuick3D/private/qquick3dviewport_p.h>
#include <qtimer.h>
#include <QFile>

static QUrl s_shaderCacheFile = QUrl(":/shadercachefile1.dat");

class Q_DECL_EXPORT CacheSetter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuick3DViewport *myView READ myView WRITE setMyView)

public:
    CacheSetter(QObject *parent = nullptr) : QObject(parent) {}
    ~CacheSetter() {}
    QQuick3DViewport *myView() const
    {
        return m_view;
    }
    void setMyView(QQuick3DViewport *view)
    {
        m_view = view;
        m_view->setShaderCacheFile(s_shaderCacheFile);

//        QObject::connect(m_view, &QQuick3DViewport::shaderCacheLoadErrors, [](const QByteArray &errors){
//            qDebug () << "Shader cache load errors: " << errors;
//        });
//        QObject::connect(m_view, &QQuick3DViewport::shaderCacheExported, [](bool success){
//            qDebug () << "Shader cache exported: " << success;
//        });
//        QTimer::singleShot(3000, [&](){
//            m_view->update();
//            //第一次在车机中运行需要执行，检测根目录是否有这个文件
//            if(QFile::exists(":/shadercachefile1.dat") || QFile::exists("/shadercachefile1.dat")) return;
//            m_view->exportShaderCache(s_shaderCacheFile, true, -1);
//        });
    }
private:
    QQuick3DViewport *m_view;
};

#endif // CACHESETTER_H
