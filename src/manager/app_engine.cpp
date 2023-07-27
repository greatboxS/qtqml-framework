#include "../../include/app_engine.h"

namespace hmi
{
    ApplicationEngine::ApplicationEngine(QObject *p) {
        m_qmlEngine = new QQmlEngine(p);
        m_qmlContext = m_qmlEngine->rootContext();
    }

    ApplicationEngine::~ApplicationEngine() {
        delete m_qmlEngine;
    }
} // namespace hmi
