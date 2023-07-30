#include "../app_factory.h"
#include "../../include/app_view.h"
#include "../../include/app_engine.h"
#include <QQmlComponent>

namespace hmi
{
    ApplicationView::ApplicationView(ApplicationEngine *engine, qreal x, qreal y, qreal z,
                                     qreal width, qreal height, qreal opacity,
                                     bool enable, bool visible) :
        m_appEngine(engine),
        m_currentViewId(-1),
        m_screenState(std::shared_ptr<ScreenState>(new ScreenState(x, y, z, width, height, opacity, enable, visible))) {
    }

    ApplicationView::~ApplicationView() {
    }

    int ApplicationView::setHeaderContainer(int id) {
        auto obj = getViewObject(id);
        if (!obj) return -1;
        m_screenState->setHeaderContainer(obj);
        return 0;
    }

    int ApplicationView::setFooterContainer(int id) {
        auto obj = getViewObject(id);
        if (!obj) return -1;
        m_screenState->setFooterContainer(obj);
        return 0;
    }

    int ApplicationView::setRightContainer(int id) {
        auto obj = getViewObject(id);
        if (!obj) return -1;
        m_screenState->setRightContainer(obj);
        return 0;
    }

    int ApplicationView::setLeftContainer(int id) {
        auto obj = getViewObject(id);
        if (!obj) return -1;
        m_screenState->setLeftContainer(obj);
        return 0;
    }

    int ApplicationView::setCenterContainer(int id) {
        auto obj = getViewObject(id);
        if (!obj) return -1;
        m_screenState->setCenterContainer(obj);
        return 0;
    }

    ScreenState *ApplicationView::getScreenState() { return m_screenState.get(); }

    QObject *ApplicationView::getViewObject(int id) {
        QObject *obj = nullptr;
        QQmlEngine *engine = m_appEngine->engine();
        const ViewProfile *profile = ViewFactory::getInstance()->getProfile(id);
        if (!engine || !profile) return NULL;

        if (profile->singleton) {
            auto f = m_viewObjects.find(id);
            if (f != m_viewObjects.end()) return f->second;
        }

        QQmlComponent component(engine, QUrl(profile->url));
        if (component.isError()) {
            qWarning() << "Error loading QML file:" << component.errorString();
            return NULL;
        }
        obj = component.create();
        if (profile->singleton) {
            m_viewObjects[id] = obj;
        }
        return obj;
    }

    int ApplicationView::requestSwitchView(int id) {
        if (id < 0 || id == m_currentViewId) return -1;

        auto obj = getViewObject(id);

        if (!obj) return -1;

        m_currentViewId = id;
        m_viewQueue.push_back(id);
        return 0;
    }

    int ApplicationView::requestSetViewState(ViewState state) {
        if (m_viewState == state) return -1;
        m_viewState = state;
        emit viewStateChanged();
        return 0;
    }

    int ApplicationView::requestShow() {
        return requestSetViewState(ViewState::eViewNormal);
    }

    int ApplicationView::requestHide() {
        return requestSetViewState(ViewState::eViewHide);
    }

    int ApplicationView::currentViewId() const {
        return m_viewQueue.back();
    }

} // namespace hmi
