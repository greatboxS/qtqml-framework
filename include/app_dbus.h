#ifndef __APP_DBUS_H__
#define __APP_DBUS_H__

#include <string>

namespace hmi
{
    class ApplicationDbusProxy
    {
    private:
    public:
        explicit ApplicationDbusProxy(const std::string &service);
        ~ApplicationDbusProxy();

        void requestOpenScreen();
    };
} // namespace hmi

#endif // __APP_DBUS_H__