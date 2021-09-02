#ifndef SKINMANAGER_H
#define SKINMANAGER_H

#include <QObject>
#include <QQuickView>
#include <QQmlContext>
#include <QResource>

class SkinManager : public QObject
{
    Q_PROPERTY(QString currentSkin READ currentSkin WRITE setCurrentSkin NOTIFY currentSkinChanged)
    Q_OBJECT
    Q_ENUMS(THEME_SETTING)
public:
    explicit SkinManager(QQuickView* view, QObject *parent = 0);

    QString currentSkin() const
    {
        return m_currentSkin;
    }

signals:

    void currentSkinChanged(QString currentSkin);

public slots:
void changeskin(int skin);
void setCurrentSkin(QString currentSkin)
{
    if (m_currentSkin == currentSkin)
        return;

    m_currentSkin = currentSkin;
    emit currentSkinChanged(currentSkin);
}

private:
QQuickView* _view;
QString m_currentSkin;
};

#endif // SKINMANAGER_H
