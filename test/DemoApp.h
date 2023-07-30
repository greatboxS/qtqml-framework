#include "../include/app_abstract.h"

namespace hmi
{
    class DemoApp : public AbstractApplication
    {
    public:
        DemoApp() :
            AbstractApplication(1280, 720) {}
        virtual ~DemoApp() {}

        virtual int onInitialize() {
            return 0;
        }
        virtual int onFinalized() {
            return 0;
        }
        virtual int onWindowShowPreparing() {
            return 0;
        }
        virtual int onWindowHidePreparing() {
            return 0;
        }
        virtual int onWindowShow() {
            return 0;
        }
        virtual int onWindowHide() {
            return 0;
        }
        virtual int onApplicationRegisterContext(ApplicationEngine *engine) {
            return 0;
        }
        virtual int onViewRegister(ApplicationView *view) {
            return 0;
        }
    };
} // namespace hmi