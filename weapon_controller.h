#pragma once

#include <memory>

#include "common.h"
#include "controller.h"
#include "weapon_manager.h"

template< class T >
class WeaponController : public Controller< T >
{
public:
    WeaponController( const std::shared_ptr< IErrorObserver >& error_observer )
    {
        this->mDataManager = std::make_shared< WeaponManager >( error_observer );
    }
};