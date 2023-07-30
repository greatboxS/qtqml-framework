#ifndef __APP_ABSTRACT_H__
#define __APP_ABSTRACT_H__

#include "app_engine.h"
#include "app_view.h"
#include <memory>
#include <QGuiApplication>

#define DEFAULT_WINDOW_HEIGHT 720.0
#define DEFAULT_WINDOW_WIDTH  1280.0
namespace hmi
{
    class AbstractApplication : public QObject
    {
    private:
        qreal m_width, m_height;

    protected:
        ApplicationEngine *m_appEngine;
        ApplicationView *m_appView;
        QGuiApplication *m_app;

    public:
        explicit AbstractApplication(qreal width = DEFAULT_WINDOW_WIDTH, qreal height = DEFAULT_WINDOW_HEIGHT);
        virtual ~AbstractApplication() noexcept;

        virtual int onWindowShowPreparing() = 0;
        virtual int onWindowHidePreparing() = 0;
        virtual int onWindowShow() = 0;
        virtual int onWindowHide() = 0;
        virtual int onApplicationRegisterContext(ApplicationEngine *engine) = 0;
        virtual int onViewRegister(ApplicationView *view) = 0;

        QGuiApplication *create(int argc, char *argv[]);
        int destroy();
        int quit();
        int exit(int retCode);

        ApplicationEngine *appEnngine();
        ApplicationView *appView();

    signals:
        void prepareShow();
        void prepareHide();
    };

} // namespace hmi

#endif // __APP_ABSTRACT_H__