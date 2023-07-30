#include "../../include/app_abstract.h"

namespace hmi
{
    AbstractApplication::AbstractApplication(qreal width, qreal height) :
        m_app(NULL), m_appEngine(NULL), m_appView(NULL),
        m_width(width), m_height(height) {
    }

    AbstractApplication::~AbstractApplication() noexcept {
        delete m_appView;
        delete m_appEngine;
        delete m_app;
    }

    QGuiApplication *AbstractApplication::create(int argc, char *argv[]) {
        if (m_app) return m_app;

        m_app = new QGuiApplication(argc, argv);
        m_appEngine = new ApplicationEngine(this);
        m_appView = new ApplicationView(m_appEngine, 0.0, 0.0, 0.0, m_width, m_height, 1.0, true, true);

        /* Add resource prefix path*/
        m_appEngine->engine()->addImportPath(":/modules/qml");
        qmlRegisterSingletonInstance(HMI_APP_VIEW_MODULE, HMI_APP_VIEW_VER_MAJOR, HMI_APP_VIEW_VER_MINOR, HMI_APP_VIEW_OBJ, m_appView);

        onViewRegister(m_appView);

        onApplicationRegisterContext(m_appEngine);
        return m_app;
    }

    int AbstractApplication::destroy() {
        delete m_appView;
        delete m_appEngine;
        delete m_app;
        m_appView = NULL;
        m_appEngine = NULL;
        m_app = NULL;
        return 0;
    }

    int AbstractApplication::quit() {
        QCoreApplication::quit();
        return 0;
    }

    int AbstractApplication::exit(int retCode) {
        QCoreApplication::exit(retCode);
        return 0;
    }

    ApplicationEngine *AbstractApplication::appEnngine() {
        return m_appEngine;
    }

    ApplicationView *AbstractApplication::appView() {
        return m_appView;
    }
} // namespace hmi
