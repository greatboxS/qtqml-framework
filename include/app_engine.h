#ifndef __APP_ENGINE_H__
#define __APP_ENGINE_H__

#include <QQmlContext>
#include <QQmlEngine>

namespace hmi
{
    class ApplicationEngine
    {
        QQmlEngine *m_qmlEngine;
        QQmlContext *m_qmlContext;

    public:
        explicit ApplicationEngine(QObject *p = nullptr);
        ~ApplicationEngine();

        QQmlEngine *engine() { return m_qmlEngine; }
        QQmlContext *context() { return m_qmlContext; }
    };
} // namespace hmi

#endif // __APP_ENGINE_H__