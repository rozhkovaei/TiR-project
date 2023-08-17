#pragma once

struct IDBManager
{
    virtual ~IDBManager() {}

    virtual void ExecuteQuery( const std::string& db_name, const std::string& query, void* observer,
                               int ( *callback )( void*, int, char**, char** ) = 0 ) = 0;
};