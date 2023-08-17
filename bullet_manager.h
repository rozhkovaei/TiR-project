#pragma once

#include "i_error_observer.h"

#include "i_db_manager.h"
#include "i_update_observer.h"
#include "i_data_manager.h"

struct BulletData;

class BulletManager : public IDataManager< BulletData >
{
public:

    BulletManager( const std::shared_ptr< IErrorObserver >& error_observer );

    virtual void AddData( const BulletData& data ) override;
    virtual void DeleteData( const BulletData& data ) override;
    virtual void ShowAllData() override;

    virtual void SetClientsObserver( const std::shared_ptr< IUpdateObserver< BulletData > >& observer ) override;

private:

    std::shared_ptr< IDBManager > mDBManager;
    std::shared_ptr< IUpdateObserver< BulletData > > mUpdateObserver;
};