#include "common.h"
#include "client_manager.h"
#include "db_manager_sqlite.h"

#include <sstream>
#include <memory>

int add_client_results( void* observer, int columns, char **data, char ** names )
{    
    if( observer )
    {
        ClientData cl_data;

        for ( int i = 0; i < columns; ++i )
        {
            std::string column_name( names[i] );
           // std::string data_str( data[i] );
           //std::cout << column_name << " " << data_str << std::endl;

            if( column_name == "id" )
            {
                std::string str ( data[i] ); 
                cl_data.mId = std::atoi( str.c_str() );
                continue;
            }
            if( column_name == "first_name" )
            {
                std::string str ( data[i]); 
                cl_data.mFirstName = std::move( str );
                continue;
            }
            if( column_name == "last_name" )
            {
                cl_data.mLastName = data[i];
                continue;
            }
            if( column_name == "patronymic" )
            {
                cl_data.mPatronymic = data[i];
                continue;
            }
            if( column_name == "passport" )
            {
                cl_data.mPassport = data[i];
                continue;
            }
            if( column_name == "phone" )
            {
                cl_data.mPhone = data[i];
                continue;
            }
        }

        reinterpret_cast < IUpdateObserver< ClientData >* >( observer )->Notify( std::move( cl_data ) );
    }

    return 0;
}

ClientManager::ClientManager( const std::shared_ptr< IErrorObserver >& error_observer )
    : mDBManager( std::make_shared< DBManagerSQlite >( error_observer ) )
{
  //  std::string query1 = "DROP TABLE CLIENTS";

  // if( mDBManager )
    //    mDBManager->ExecuteQuery( DB_NAME, query1.data(), mUpdateObserver.get() );

    std::string query = "CREATE TABLE IF NOT EXISTS CLIENTS ("
        "id INTEGER PRIMARY KEY,"
        "last_name VARCHAR NOT NULL,"
        "first_name VARCHAR NOT NULL,"
        "patronymic VARCHAR,"
        "passport VARCHAR,"
        "phone VARCHAR)";

    if( mDBManager )
        mDBManager->ExecuteQuery( DB_NAME, query.data(), mUpdateObserver.get() );
}

void ClientManager::AddData( const ClientData& data )
{
    std::stringstream query_ss;

    query_ss << "INSERT INTO CLIENTS (last_name, first_name, patronymic, passport, phone) VALUES (\"" <<
        data.mLastName << "\", \"" << data.mFirstName << "\", \"" << data.mPatronymic << "\", \"" <<
        data.mPassport << "\", \"" << data.mPhone << "\") RETURNING *";

    if( mDBManager )
        mDBManager->ExecuteQuery( DB_NAME, query_ss.str(), mUpdateObserver.get(), add_client_results );
}

void ClientManager::EditData( const ClientData& data )
{
    std::stringstream query_ss;

    query_ss << "UPDATE CLIENTS SET last_name = \"" << data.mLastName <<
        "\", first_name = \"" << data.mFirstName << "\", patronymic = \"" << data.mPatronymic << "\", passport = \"" << 
        data.mPassport << "\", phone = \"" << data.mPhone << "\" WHERE id = " << data.mId;

    if( mDBManager )
        mDBManager->ExecuteQuery( DB_NAME, query_ss.str(), mUpdateObserver.get(), add_client_results );
}

void ClientManager::DeleteData( const ClientData& data )
{
    std::stringstream query_ss;

    query_ss << "DELETE FROM CLIENTS where id = " << data.mId;

    if( mDBManager )
        mDBManager->ExecuteQuery( DB_NAME, query_ss.str(), mUpdateObserver.get() );
}

void ClientManager::ShowAllData()
{
    std::stringstream query_ss;

    query_ss << "SELECT * FROM CLIENTS";

    std::cout << mUpdateObserver.get() << std::endl;

    if( mDBManager )
        mDBManager->ExecuteQuery( DB_NAME, query_ss.str(), mUpdateObserver.get(), add_client_results );
}

void ClientManager::SetClientsObserver( const std::shared_ptr< IUpdateObserver< ClientData > >& observer )
{
    mUpdateObserver = observer;
}