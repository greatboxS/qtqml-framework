#include "../../include/app_engine.h"
#include <QQmlApplicationEngine>

namespace hmi
{
    ApplicationEngine::ApplicationEngine(QObject *p) {
        m_qmlEngine = new QQmlApplicationEngine(p);
        m_qmlContext = m_qmlEngine->rootContext();
    }

    ApplicationEngine::~ApplicationEngine() {
        delete m_qmlEngine;
    }
} // namespace hmi
