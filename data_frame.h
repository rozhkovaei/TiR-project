#pragma once

#include "controller.h"
#include "data_list_view.h"
#include "clients_controller.h"

template< class T >
class DataFrame: public wxFrame
{
public:

    DataFrame( const wxString& title, const wxPoint& pos, const wxSize& size )
        : wxFrame( NULL, wxID_ANY, title, pos, size )
    {}

protected:

    void AddElements()
    {
        wxBoxSizer* main_sizer = mListView->GetSizer();

        wxBoxSizer* button_sizer = new wxBoxSizer( wxHORIZONTAL );

        wxButton* add_btn = new wxButton( this, wxID_ANY, "Добавить" );
        button_sizer->Add( add_btn, 0, wxRIGHT, 10 );

        wxButton* delete_btn = new wxButton(this, wxID_ANY, "Удалить");
        button_sizer->Add( delete_btn, 0, wxRIGHT, 10 );

        wxButton* cancel_btn = new wxButton(this, wxID_ANY, "Закрыть");
        button_sizer->Add( cancel_btn, 0 );

        add_btn->Bind( wxEVT_COMMAND_BUTTON_CLICKED, &DataFrame::OnClientAddClick, this );
        delete_btn->Bind( wxEVT_COMMAND_BUTTON_CLICKED, &DataFrame::OnClientDeleteClick, this );
        cancel_btn->Bind( wxEVT_COMMAND_BUTTON_CLICKED, &DataFrame::OnCancelClick, this );

        if( mController )
        {
            mController->SetClientsObserver( mListView );
            mController->Notify( ControllerEvent::BUTTON_CLIENTS_PRESSED );
        }
        
        main_sizer->Add( button_sizer, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM | wxTOP, 10 );

        // SetSizer( main_sizer );
        this->SetSizerAndFit( main_sizer );
    }

    virtual void OnClientAddClick( wxCommandEvent& event ) {}

    void OnClientDeleteClick( wxCommandEvent& event )
    {
        T data;
        data.mId = mListView->GetSelectedItemIndex();

        if( mController && data.mId != -1 )
            mController->Notify( ControllerEvent::BUTTON_DELETE_PRESSED, data );
        
        mListView->RemoveSelectedItem();
    }

    void OnCancelClick( wxCommandEvent& event ) { Close( true ); }

    std::shared_ptr< Controller< T > > mController;
    std::shared_ptr< DataListView< T > > mListView;
};
