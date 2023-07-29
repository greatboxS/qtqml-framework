#include "../../include/app_view.h"
#include "../../include/app_engine.h"
#include <QQmlComponent>

namespace hmi
{
    ApplicationView::ApplicationView(ApplicationEngine *engine, qreal x, qreal y, qreal z,
                                     qreal width, qreal height, qreal opacity,
                                     bool enable, bool visible) :
        m_appEngine(engine),
        m_screenState(std::make_shared<ScreenState>(x, y, z, width, height, opacity, enable, visible)) {
    }

    ApplicationView::~ApplicationView() {
    }

    ScreenState *ApplicationView::getScreenState() { return m_screenState.get(); }

    QObject *ApplicationView::getViewObject(int id) {
        QQmlEngine *engine = m_appEngine->engine();
        const ViewProfile *profile = ViewFactory::getInstance()->getProfile(id);

        if (!engine || !profile) return NULL;

        QQmlComponent component(engine, QUrl(profile->url));
        if (component.isError()) {
            qWarning() << "Error loading QML file:" << component.errorString();
            return NULL;
        }
        return component.create();
    }

    void ApplicationView::show() {
    }
    void ApplicationView::hide() {
    }

} // namespace hmi
