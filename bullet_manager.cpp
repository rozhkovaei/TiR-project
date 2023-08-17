#include "common.h"
#include "bullet_manager.h"
#include "db_manager_sqlite.h"

#include <sstream>
#include <memory>

int add_bullet_results( void* observer, int columns, char **data, char ** names )
{    
    if( observer )
    {
        BulletData cl_data;

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
            if( column_name == "type" )
            {
                std::string str ( data[i]); 
                cl_data.mType = std::move( str );
                continue;
            }
            if( column_name == "caliber" )
            {
                cl_data.mCaliber = data[i];
                continue;
            }
            if( column_name == "serial_number" )
            {
                cl_data.mSerialNumber = data[i];
                continue;
            }
            if( column_name == "issue_year" )
            {
                cl_data.mIssueYear = data[i];
                continue;
            }
        }

        reinterpret_cast < IUpdateObserver< BulletData >* >( observer )->Notify( std::move( cl_data ) );
    }

    return 0;
}

BulletManager::BulletManager( const std::shared_ptr< IErrorObserver >& error_observer )
    : mDBManager( std::make_shared< DBManagerSQlite >( error_observer ) )
{
  //  std::string query1 = "DROP TABLE BULLET";

  // if( mDBManager )
   //     mDBManager->ExecuteQuery( DB_NAME, query1.data(), mUpdateObserver.get() );

    std::string query = "CREATE TABLE IF NOT EXISTS BULLET ("
        "id INTEGER PRIMARY KEY,"
        "type VARCHAR(255) NOT NULL ,"
        "caliber VARCHAR(255) NOT NULL ,"
        "serial_number VARCHAR(255),"
        "issue_year VARCHAR(255))";

    if( mDBManager )
        mDBManager->ExecuteQuery( DB_NAME, query.data(), mUpdateObserver.get() );
}

void BulletManager::AddData( const BulletData& data )
{
    std::stringstream query_ss;

    query_ss << "INSERT INTO BULLET (id, type, caliber, serial_number, issue_year) VALUES (\"" <<
        data.mId << "\", \"" << data.mType << "\", \"" << data.mCaliber << "\", \"" <<
        data.mSerialNumber << "\", \"" << data.mIssueYear << "\") RETURNING *";

    if( mDBManager )
        mDBManager->ExecuteQuery( DB_NAME, query_ss.str(), mUpdateObserver.get(), add_bullet_results );
}

void BulletManager::DeleteData( const BulletData& data )
{
    std::stringstream query_ss;

    query_ss << "DELETE FROM BULLET where id = " << data.mId;

    if( mDBManager )
        mDBManager->ExecuteQuery( DB_NAME, query_ss.str(), mUpdateObserver.get() );
}

void BulletManager::ShowAllData()
{
    std::stringstream query_ss;

    query_ss << "SELECT * FROM BULLET";

    std::cout << mUpdateObserver.get() << std::endl;

    if( mDBManager )
        mDBManager->ExecuteQuery( DB_NAME, query_ss.str(), mUpdateObserver.get(), add_bullet_results );
}

void BulletManager::SetClientsObserver( const std::shared_ptr< IUpdateObserver< BulletData > >& observer )
{
    mUpdateObserver = observer;
}