#ifndef __APP_VIEW_H__
#define __APP_VIEW_H__

#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlEngine>

namespace hmi
{
    class ApplicationState
    {
    private:
    public:
        ApplicationState();
        ~ApplicationState();
    };

    class ApplicationView
    {
    protected:
        explicit ApplicationView();
        virtual ~ApplicationView();

        void show();
        void hide();
    };
} // namespace hmi

#endif // __APP_VIEW_H__