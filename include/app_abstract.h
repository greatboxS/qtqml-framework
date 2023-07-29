#ifndef __APP_ABSTRACT_H__
#define __APP_ABSTRACT_H__

#include "app_engine.h"
#include "app_view.h"
#include <memory>
#include <QGuiApplication>

#define DEFAULT_WINDOW_HEIGHT 720
#define DEFAULT_WINDOW_WIDTH  1280
namespace hmi
{
    class AbstractApplication : public QObject
    {
    private:
    protected:
        std::unique_ptr<ApplicationEngine> m_appEngine;
        std::unique_ptr<ApplicationView> m_appView;
        QGuiApplication *m_guiApp;

    public:
        explicit AbstractApplication(QGuiApplication *app,
                                     qreal width = DEFAULT_WINDOW_WIDTH, qreal height = DEFAULT_WINDOW_HEIGHT);
        virtual ~AbstractApplication();

        virtual int onInitialize() = 0;
        virtual int onFinalized() = 0;
        virtual int onWindowShowPreparing() = 0;
        virtual int onWindowHidePreparing() = 0;
        virtual int onWindowShow() = 0;
        virtual int onWindowHide() = 0;
        virtual int onApplicationRegisterContext(ApplicationEngine *engine) = 0;
        virtual int onViewRegister(ApplicationView *view) = 0;

        int initialize();
        int unInitialzie();
    };

} // namespace hmi

#endif // __APP_ABSTRACT_H__