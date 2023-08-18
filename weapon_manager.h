#pragma once

#include "i_error_observer.h"
#include "i_update_observer.h"

#include "i_db_manager.h"
#include "i_data_manager.h"

struct WeaponData;

class WeaponManager : public IDataManager< WeaponData >
{

public:

    WeaponManager( const std::shared_ptr< IErrorObserver >& error_observer );

    virtual void AddData( const WeaponData& data ) override;
    virtual void DeleteData( const WeaponData& data ) override;
    virtual void EditData( const WeaponData& data ) override;
    virtual void ShowAllData() override;

    virtual void SetClientsObserver( const std::shared_ptr< IUpdateObserver< WeaponData > >& observer ) override;

private:

    std::shared_ptr< IDBManager > mDBManager;
    std::shared_ptr< IUpdateObserver< WeaponData > > mUpdateObserver;
};