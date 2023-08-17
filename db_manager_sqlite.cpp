
#include <sstream>
#include "db_manager_sqlite.h"

sqlite3* DBManagerSQlite::Connect( const std::string& db_name )
{
    sqlite3* handle;
    if ( sqlite3_open( db_name.c_str(), &handle ) )
    {
       if( mErrorObserver ) 
       {
            std::stringstream ss;
            ss << "Ошибка доступа к БД " << sqlite3_errmsg( handle );
            mErrorObserver->Notify( ss.str() ); 
       }

        sqlite3_close( handle );
        return nullptr;
    }
    return handle;
}

void DBManagerSQlite::ExecuteQuery( const std::string& db_name, const std::string& query, void* observer,
                                    int ( *callback )( void*, int, char**, char** ) )
{
    sqlite3* handle = Connect( db_name );
    if( handle == nullptr )
        return;
    
    char *errmsg;
    int rc = sqlite3_exec( handle, query.data(), callback, observer, &errmsg );
    if ( rc != SQLITE_OK )
    {
        if( mErrorObserver ) 
        {
            std::stringstream ss;
            ss << "Ошибка выполнения SQL запроса " << sqlite3_errmsg( handle );
            mErrorObserver->Notify( ss.str() ); 
        }
        
        sqlite3_free( errmsg );
    }
}