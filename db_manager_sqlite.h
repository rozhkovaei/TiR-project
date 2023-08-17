#pragma once

#include "db_manager.h"
#include "sqlite3.h"

class DBManagerSQlite : public DBManager
{
public:
    DBManagerSQlite( const std::shared_ptr< IErrorObserver >& error_observer )
        : DBManager( error_observer )
    {}

    virtual void ExecuteQuery( const std::string& db_name, const std::string& query, void* observer,
                                int ( *callback )( void*, int, char**, char** ) = 0 ) override;

private:

    sqlite3* Connect( const std::string& db_name );
};