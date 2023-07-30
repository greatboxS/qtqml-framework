#ifndef __APP_BASE_H__
#define __APP_BASE_H__

#include <cstdint>
#include <QString>

namespace hmi
{
    enum class ViewType {
        eScreen,
        ePopup,
    };

    enum class ViewState {
        eViewNormal = 0,
        eViewMimimum,
        eViewMaximum,
        eViewHide,
    };

    struct ViewProfile {
        int id;
        QString url;
        bool singleton;
        ViewType type;
        ViewState state;
        qreal x, y, z;
        qreal width, height;
        qreal opacity;
    };

    struct PopupProfile {
        int id;
        QString url;
        bool singleton;
        ViewType type;
        ViewState state;
        int64_t timeout;
        qreal x, y, z;
        qreal width, height;
        qreal opacity;
    };

    enum class ViewIdOffset {
        eAppSystem = 0,
        eAppUserView = 1000,
        eAppUserPopup = 100000,
    };
} // namespace hmi

#endif // __APP_BASE_H__