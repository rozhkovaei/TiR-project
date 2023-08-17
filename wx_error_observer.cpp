#include "wx_error_observer.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

void WxErrorObserver::Notify( const std::string& message )
{
    wxLogMessage( message.data() );
}