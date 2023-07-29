#ifndef __APP_VIEW_H__
#define __APP_VIEW_H__

#include "app_factory.h"
#include <QObject>
#include <QSize>
#include <QPoint>

namespace hmi
{
    class ApplicationEngine;

    class ScreenState : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
        Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
        Q_PROPERTY(qreal z READ z WRITE setZ NOTIFY zChanged)
        Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
        Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)
        Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
        Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
        Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)

        Q_PROPERTY(QString headerContainer READ getHeaderContainer WRITE setHeaderContainer NOTIFY headerContainerChanged)
        Q_PROPERTY(QString footerContainer READ getFooterContainer WRITE setFooterContainer NOTIFY footerContainerChanged)
        Q_PROPERTY(QString leftContainer READ getLeftContainer WRITE setLeftContainer NOTIFY leftContainerChanged)
        Q_PROPERTY(QString rightContainer READ getRightContainer WRITE setRightContainer NOTIFY rightContainerChanged)

    private:
        qreal m_x;
        qreal m_y;
        qreal m_z;
        qreal m_width;
        qreal m_height;
        qreal m_opacity;
        bool m_enabled;
        bool m_visible;
        struct ContainerSource {
            QString header;
            QString footer;
            QString left;
            QString right;
        } m_containerSource;

    public:
        explicit ScreenState(qreal x, qreal y, qreal z,
                             qreal width, qreal height, bool opacity = 1.0,
                             bool enable = true, bool visible = true);
        ~ScreenState();

        void setX(qreal value);
        void setY(qreal value);
        void setZ(qreal value);
        void setWidth(qreal value);
        void setHeight(qreal value);
        void setOpacity(qreal value);
        void setEnabled(bool value);
        void setVisible(bool value);
        void setHeaderContainer(const QString &value);
        void setFooterContainer(const QString &value);
        void setLeftContainer(const QString &value);
        void setRightContainer(const QString &value);

        qreal x() const;
        qreal y() const;
        qreal z() const;
        qreal width() const;
        qreal height() const;
        qreal opacity() const;
        bool isEnabled() const;
        bool isVisible() const;
        QString getHeaderContainer() const;
        QString getFooterContainer() const;
        QString getRightContainer() const;
        QString getLeftContainer() const;

    signals:
        void xChanged();
        void yChanged();
        void widthChanged();
        void heightChanged();
        void zChanged();
        void opacityChanged();
        void enabledChanged();
        void visibleChanged();
        void headerContainerChanged();
        void footerContainerChanged();
        void leftContainerChanged();
        void rightContainerChanged();
    };

    class ApplicationView : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(ScreenState *screenState READ getScreenState NOTIFY screenStateChanged)

        std::shared_ptr<ScreenState> m_screenState;
        ApplicationEngine *m_appEngine;

    public:
        explicit ApplicationView(ApplicationEngine *engine, qreal x, qreal y, qreal z,
                                 qreal width, qreal height, qreal opacity = 1.0,
                                 bool enable = true, bool visible = true);
        ~ApplicationView();

        ScreenState *getScreenState();
        QObject *getViewObject(int id);

        void show();
        void hide();

    signals:
        void screenStateChanged();
    };
} // namespace hmi

#endif // __APP_VIEW_H__