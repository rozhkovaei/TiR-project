#pragma once
#include <iostream>

#include "i_db_manager.h"
#include "i_error_observer.h"

class DBManager : public IDBManager
{
public:
    DBManager( const std::shared_ptr< IErrorObserver >& error_observer )
        : mErrorObserver( error_observer )
    {}

    virtual void ExecuteQuery( const std::string& db_name, const std::string& query, void* observer,
                               int ( *callback )( void*, int, char**, char** ) = 0 ) override {}

protected:
    std::shared_ptr< IErrorObserver > mErrorObserver;
};