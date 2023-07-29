#include "../../include/app_abstract.h"

namespace hmi
{
    AbstractApplication::AbstractApplication(QGuiApplication *app,
                                             qreal width, qreal height) :
        m_guiApp(app) {
        m_appEngine = std::make_unique<ApplicationEngine>(this);
        m_appView = std::make_unique<ApplicationView>(m_appEngine.get(), 0.0, 0.0, 0.0, width, height);
    }

    AbstractApplication::~AbstractApplication() {
    }

    int AbstractApplication::initialize() {
        return 0;
    }

    int AbstractApplication::unInitialzie() {
        return 0;
    }
} // namespace hmi
