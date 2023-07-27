#ifndef __APP_ABSTRACT_H__
#define __APP_ABSTRACT_H__

#include "app_engine.h"
#include "app_view.h"
#include <memory>

namespace hmi
{
    class AbstractApplication : QObject
    {
    private:
    protected:
        std::unique_ptr<ApplicationEngine> m_appEngine;
        std::unique_ptr<ApplicationView> m_appView;

    public:
        explicit AbstractApplication();
        virtual ~AbstractApplication();

        virtual int onInitialize() = 0;
        virtual int onFinalized() = 0;
        virtual int onWindowShowPreparing() = 0;
        virtual int onWindowHidePreparing() = 0;
        virtual int onWindowShow() = 0;
        virtual int onWindowHide() = 0;
        virtual int onApplicationRegisterContext(QQmlContext *context) = 0;

        int initialize();
        int unInitialzie();
    };
} // namespace hmi

#endif // __APP_ABSTRACT_H__