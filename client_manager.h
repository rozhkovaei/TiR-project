#pragma once

#include "i_error_observer.h"
#include "i_update_observer.h"

#include "i_db_manager.h"
#include "i_data_manager.h"

class ClientManager : public IDataManager< ClientData >
{

public:

    ClientManager( const std::shared_ptr< IErrorObserver >& error_observer );

    virtual void AddData( const ClientData& data ) override;
    virtual void DeleteData( const ClientData& data ) override;
    virtual void ShowAllData() override;

    virtual void SetClientsObserver( const std::shared_ptr< IUpdateObserver< ClientData > >& observer ) override;

private:

    std::shared_ptr< IDBManager > mDBManager;
    std::shared_ptr< IUpdateObserver< ClientData > > mUpdateObserver;
};