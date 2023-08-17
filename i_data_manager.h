#pragma once

#include "i_update_observer.h"

template < class T >
struct IDataManager
{
    virtual ~IDataManager() {}

    virtual void AddData( const T& ) = 0;
    virtual void DeleteData( const T& ) = 0;
    virtual void ShowAllData() = 0;

    virtual void SetClientsObserver( const std::shared_ptr< IUpdateObserver< T > >& ) = 0;
};