#ifndef __APP_FACTORY_H__
#define __APP_FACTORY_H__

#include "app_base.h"
#include <map>

namespace hmi
{
    class ViewFactory
    {
    private:
        ViewFactory() = default;
        ~ViewFactory() = default;
        ViewFactory(const ViewFactory &) = delete;
        ViewFactory &operator=(const ViewFactory &) = delete;

        static std::map<int, ViewProfile> getViews() {
            static std::map<int, ViewProfile> sViewProfiles;
            return sViewProfiles;
        }

    public:
        static ViewFactory *getInstance() {
            static ViewFactory instance;
            return &instance;
        }

        const ViewProfile *getProfile(int id) const {
            auto profiles = ViewFactory::getViews();
            if (profiles.find(id) != profiles.end()) return NULL;
            return &profiles.at(id);
        }

        int registerView(const ViewProfile &profile) {
            auto profiles = ViewFactory::getViews();
            if (profiles.find(profile.id) != profiles.end()) return -1;
            profiles[profile.id] = profile;
            return 0;
        }
    };
} // namespace hmi

#endif // __APP_FACTORY_H__