#ifndef __APP_POPUP_H__
#define __APP_POPUP_H__

namespace hmi
{
    class ApplicationPopup
    {
    public:
        ApplicationPopup();
        ~ApplicationPopup();
        int requestShowPopup(int id);
        int requestClosePopup(int id);
    };
} // namespace hmi

#endif // __APP_POPUP_H__