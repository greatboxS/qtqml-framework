#ifndef __APP_VIEW_H__
#define __APP_VIEW_H__

#include <QObject>
#include <QSize>
#include <QPoint>
#include <map>
#include <unordered_map>
#include <deque>
#include "app_base.h"

#define HMI_APP_VIEW_MODULE    "hmi.AppView"
#define HMI_APP_VIEW_VER_MAJOR 1
#define HMI_APP_VIEW_VER_MINOR 0
#define HMI_APP_VIEW_OBJ       "AppView"
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

        Q_PROPERTY(QObject *headerContainer READ getHeaderContainer WRITE setHeaderContainer NOTIFY headerContainerChanged)
        Q_PROPERTY(QObject *footerContainer READ getFooterContainer WRITE setFooterContainer NOTIFY footerContainerChanged)
        Q_PROPERTY(QObject *leftContainer READ getLeftContainer WRITE setLeftContainer NOTIFY leftContainerChanged)
        Q_PROPERTY(QObject *rightContainer READ getRightContainer WRITE setRightContainer NOTIFY rightContainerChanged)
        Q_PROPERTY(QObject *centerContainer READ getCenterContainer WRITE setCenterContainer NOTIFY centerContainerChanged)

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
            QObject *header;
            QObject *footer;
            QObject *left;
            QObject *right;
            QObject *center;
        } m_containerSource;

    public:
        explicit ScreenState(qreal x, qreal y, qreal z,
                             qreal width, qreal height, qreal opacity = 1.0,
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
        void setHeaderContainer(QObject *value);
        void setFooterContainer(QObject *value);
        void setLeftContainer(QObject *value);
        void setRightContainer(QObject *value);
        void setCenterContainer(QObject *value);

        qreal x() const;
        qreal y() const;
        qreal z() const;
        qreal width() const;
        qreal height() const;
        qreal opacity() const;
        bool isEnabled() const;
        bool isVisible() const;
        QObject *getHeaderContainer();
        QObject *getFooterContainer();
        QObject *getRightContainer();
        QObject *getLeftContainer();
        QObject *getCenterContainer();

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
        void centerContainerChanged();
    };

    class ApplicationView : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(ScreenState *screenState READ getScreenState NOTIFY screenStateChanged)

        std::deque<int> m_viewQueue;
        std::unordered_map<int, QObject *> m_viewObjects;
        ViewState m_viewState;
        int m_currentViewId;
        std::shared_ptr<ScreenState> m_screenState;
        ApplicationEngine *m_appEngine;

    public:
        explicit ApplicationView(ApplicationEngine *engine, qreal x, qreal y, qreal z,
                                 qreal width, qreal height, qreal opacity = 1.0,
                                 bool enable = true, bool visible = true);
        ~ApplicationView();

        int setHeaderContainer(int id);
        int setFooterContainer(int id);
        int setRightContainer(int id);
        int setLeftContainer(int id);
        int setCenterContainer(int id);

        ScreenState *getScreenState();
        QObject *getViewObject(int id);

        int requestSwitchView(int id);
        int requestSetViewState(ViewState state);
        int requestShow();
        int requestHide();

        int currentViewId() const;

    signals:
        void screenStateChanged();
        void componentLoaded();
        void viewStateChanged();
        void switchViewChanged(int oState, int nState);
    };
} // namespace hmi

#endif // __APP_VIEW_H__