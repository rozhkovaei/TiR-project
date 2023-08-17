#include "i_error_observer.h"

class WxErrorObserver : public IErrorObserver
{
public:
    virtual void Notify( const std::string& message ) override;
};