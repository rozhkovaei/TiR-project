#pragma once

#include <memory>

#include "common.h"
#include "i_data_manager.h"
#include "i_error_observer.h"
#include "i_update_observer.h"

template< class T >
class Controller
{
public:
    Controller() {}

    virtual ~Controller() {}

    virtual void Notify( ControllerEvent event )
    {
        switch( event )
        {
            case ControllerEvent::BUTTON_CLIENTS_PRESSED:
            {
                if( mDataManager )
                    mDataManager->ShowAllData();
            }
            break;

            default:
            break;
        }
    }

    virtual void Notify( ControllerEvent event, const T& data )
    {
        switch( event )
        {
            case ControllerEvent::BUTTON_ADD_PRESSED:
            {
                if( mDataManager )
                    mDataManager->AddData( data );
            }
            break;

            case ControllerEvent::BUTTON_DELETE_PRESSED:
            {
                if( mDataManager )
                    mDataManager->DeleteData( data );
            }
            break;

            case ControllerEvent::BUTTON_EDIT_PRESSED:
            {
                if( mDataManager )
                    mDataManager->EditData( data );
            }
            break;

            default:
            break;
        }
    }

    virtual void SetClientsObserver( const std::shared_ptr< IUpdateObserver< T > >& observer )
    {
        mDataManager->SetClientsObserver( observer );
    }

protected:

    std::shared_ptr< IDataManager< T > > mDataManager;
};