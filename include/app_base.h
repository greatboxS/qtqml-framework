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
        ViewType type;
        ViewState state;
        qreal x, y, z;
        qreal width, height;
        qreal opacity;
    };
} // namespace hmi

#endif // __APP_BASE_H__