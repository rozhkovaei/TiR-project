#include "common.h"
#include "weapon_manager.h"
#include "db_manager_sqlite.h"

#include <sstream>
#include <memory>

int add_weapon_results( void* observer, int columns, char **data, char ** names )
{    
    if( observer )
    {
        WeaponData cl_data;

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
            if( column_name == "serial_number" )
            {
                std::string str ( data[i] ); 
                cl_data.mSerialNumber = str.c_str();
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
            if( column_name == "mark" )
            {
                cl_data.mMark = data[i];
                continue;
            }
            if( column_name == "issue_year" )
            {
                cl_data.mIssueYear = data[i];
                continue;
            }
        }

        reinterpret_cast < IUpdateObserver< WeaponData >* >( observer )->Notify( std::move( cl_data ) );
    }

    return 0;
}

WeaponManager::WeaponManager( const std::shared_ptr< IErrorObserver >& error_observer )
    : mDBManager( std::make_shared< DBManagerSQlite >( error_observer ) )
{
  //  std::string query1 = "DROP TABLE WEAPON";

//   if( mDBManager )
  //      mDBManager->ExecuteQuery( DB_NAME, query1.data(), mUpdateObserver.get() );

    std::string query = "CREATE TABLE IF NOT EXISTS WEAPON ("
        "id INTEGER PRIMARY KEY,"
        "serial_number VARCHAR NOT NULL,"
        "type VARCHAR NOT NULL,"
        "caliber VARCHAR NOT NULL,"
        "mark VARCHAR NOT NULL,"
        "issue_year VARCHAR)";

    if( mDBManager )
        mDBManager->ExecuteQuery( DB_NAME, query.data(), mUpdateObserver.get() );
}

void WeaponManager::AddData( const WeaponData& data )
{
    std::stringstream query_ss;

    query_ss << "INSERT INTO WEAPON (serial_number, type, caliber, mark, issue_year) VALUES (\"" <<
        data.mSerialNumber << "\", \"" << data.mType << "\", \"" << data.mCaliber << "\", \"" <<
        data.mMark << "\", \"" << data.mIssueYear << "\") RETURNING *";

    if( mDBManager )
        mDBManager->ExecuteQuery( DB_NAME, query_ss.str(), mUpdateObserver.get(), add_weapon_results );
}

void WeaponManager::EditData( const WeaponData& data )
{
    std::stringstream query_ss;

    query_ss << "UPDATE WEAPON SET serial_number = \"" << data.mSerialNumber <<
        "\", type = \"" << data.mType << "\", caliber = \"" << data.mCaliber << "\", mark = \"" << 
        data.mMark << "\", issue_year = \"" << data.mIssueYear << "\" WHERE id = " << data.mId;

    if( mDBManager )
        mDBManager->ExecuteQuery( DB_NAME, query_ss.str(), mUpdateObserver.get(), add_weapon_results );
}

void WeaponManager::DeleteData( const WeaponData& data )
{
    std::stringstream query_ss;

    query_ss << "DELETE FROM WEAPON where id = " << data.mId;

    if( mDBManager )
        mDBManager->ExecuteQuery( DB_NAME, query_ss.str(), mUpdateObserver.get() );
}

void WeaponManager::ShowAllData()
{
    std::stringstream query_ss;

    query_ss << "SELECT * FROM WEAPON";

    std::cout << mUpdateObserver.get() << std::endl;

    if( mDBManager )
        mDBManager->ExecuteQuery( DB_NAME, query_ss.str(), mUpdateObserver.get(), add_weapon_results );
}

void WeaponManager::SetClientsObserver( const std::shared_ptr< IUpdateObserver< WeaponData > >& observer )
{
    mUpdateObserver = observer;
}