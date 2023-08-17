#include "clients_frame.h"
#include "clients_controller.h"
#include "clients_list_view.h"

ClientsFrame::ClientsFrame( const wxString& title, const wxPoint& pos, const wxSize& size,
                            const std::shared_ptr< IErrorObserver >& error_observer )
        : DataFrame< ClientData >( title, pos, size ) 
{
    this->mController = std::make_shared< ClientsController< ClientData > >( error_observer );
    this->mListView = std::make_shared< ClientsListView >( this );
    AddElements();    
}

void ClientsFrame::OnClientAddClick(wxCommandEvent& event)
{
    ClientAddFrame* clients_frame = new ClientAddFrame( "", wxPoint(200, 200), wxSize(300, 270), mController );
    clients_frame->Show( true );
}

ClientAddFrame::ClientAddFrame( const wxString& title, const wxPoint& pos, const wxSize& size,
                                const std::shared_ptr< Controller< ClientData > >& controller )
        : DataAddFrame< ClientData >( title, pos, size, controller )
{
    wxBoxSizer* main_sizer = new wxBoxSizer( wxVERTICAL );

    mEditSurName = new wxTextCtrl( this, wxID_ANY );
    mEditSurName->SetMinSize( wxSize( 200, mEditSurName->GetMinSize().y ) );

    ArrangeItems( mEditSurName, main_sizer, "Фамилия:", true );

    mEditName = new wxTextCtrl( this, wxID_ANY );
    mEditName->SetMinSize( wxSize( 200, mEditSurName->GetMinSize().y ) );
    ArrangeItems( mEditName, main_sizer, "Имя:" );

    mEditPatronymicName = new wxTextCtrl( this, wxID_ANY );
    mEditPatronymicName->SetMinSize( wxSize( 200, mEditSurName->GetMinSize().y ) );
    ArrangeItems( mEditPatronymicName, main_sizer, "Отчество:" );

    mEditPassport = new wxTextCtrl( this, wxID_ANY );
    mEditPassport->SetMinSize( wxSize( 200, mEditSurName->GetMinSize().y ) );
    ArrangeItems( mEditPassport, main_sizer, "Паспорт:" );

    mEditPhone = new wxTextCtrl( this, wxID_ANY );
    mEditPhone->SetMinSize( wxSize( 200, mEditSurName->GetMinSize().y ) );
    ArrangeItems( mEditPhone, main_sizer, "Телефон:" );

    wxBoxSizer* button_sizer = new wxBoxSizer( wxHORIZONTAL );

    mOkButton = new wxButton(this, wxID_ANY, "Добавить");
    button_sizer->Add( mOkButton, 0, wxRIGHT, 10 );

    mCancelButton = new wxButton(this, wxID_ANY, "Отмена");
    button_sizer->Add( mCancelButton, 0 );

    mOkButton->Bind( wxEVT_COMMAND_BUTTON_CLICKED, &ClientAddFrame::OnOkClick, this );
    mCancelButton->Bind( wxEVT_COMMAND_BUTTON_CLICKED, &ClientAddFrame::OnCancelClick, this );

    main_sizer->Add( button_sizer, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM | wxTOP, 10 );

   // SetSizer( main_sizer );
   this->SetSizerAndFit( main_sizer );
}

void ClientAddFrame::OnOkClick( wxCommandEvent& event )
{
    ClientData data; 

    data.mFirstName = mEditName->GetValue().ToStdString();
    data.mLastName = mEditSurName->GetValue().ToStdString();
    data.mPatronymic = mEditPatronymicName->GetValue().ToStdString();
    data.mPassport = mEditPassport->GetValue().ToStdString();
    data.mPhone = mEditPhone->GetValue().ToStdString();

    if( mController )
    {
        mController->Notify( ControllerEvent::BUTTON_ADD_PRESSED, data );
    }

    Close( true );
}
