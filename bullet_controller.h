#pragma once

#include <memory>

#include "common.h"
#include "controller.h"
#include "bullet_manager.h"

template< class T >
class BulletController : public Controller< T >
{
public:
    BulletController( const std::shared_ptr< IErrorObserver >& error_observer )
    {
        this->mDataManager = std::make_shared< BulletManager >( error_observer );
    }
};