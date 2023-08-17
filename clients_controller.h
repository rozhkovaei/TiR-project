#pragma once

#include <memory>

#include "common.h"
#include "controller.h"
#include "client_manager.h"

template< class T >
class ClientsController : public Controller< T >
{
public:
    ClientsController( const std::shared_ptr< IErrorObserver >& error_observer )
    {
        this->mDataManager = std::make_shared< ClientManager >( error_observer );
    }
};