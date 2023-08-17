#include "weapon_frame.h"
#include "weapon_controller.h"
#include "weapon_list_view.h"

WeaponFrame::WeaponFrame( const wxString& title, const wxPoint& pos, const wxSize& size,
                          const std::shared_ptr< IErrorObserver >& error_observer )
        : DataFrame< WeaponData >( title, pos, size ) 
{
    this->mController = std::make_shared< WeaponController< WeaponData > >( error_observer );
    this->mListView = std::make_shared< WeaponListView >( this );
    AddElements();    
}

void WeaponFrame::OnClientAddClick( wxCommandEvent& event )
{
    WeaponAddFrame* frame = new WeaponAddFrame( "", wxPoint( 200, 200 ), wxSize( 300, 270 ), mController );
    frame->Show( true );
}

WeaponAddFrame::WeaponAddFrame( const wxString& title, const wxPoint& pos, const wxSize& size,
                                const std::shared_ptr< Controller< WeaponData > >& controller )
        : DataAddFrame< WeaponData >( title, pos, size, controller )
{
    wxBoxSizer* main_sizer = new wxBoxSizer( wxVERTICAL );

    mType = new wxTextCtrl( this, wxID_ANY );
    mType->SetMinSize( wxSize( 200, mType->GetMinSize().y ) );

    ArrangeItems( mType, main_sizer, "Тип:", true );

    mCaliber = new wxTextCtrl( this, wxID_ANY );
    mCaliber->SetMinSize( wxSize( 200, mCaliber->GetMinSize().y ) );
    ArrangeItems( mCaliber, main_sizer, "Калибр:" );

    mMark = new wxTextCtrl( this, wxID_ANY );
    mMark->SetMinSize( wxSize( 200, mMark->GetMinSize().y ) );
    ArrangeItems( mMark, main_sizer, "Марка:" );

    mIssueYear = new wxTextCtrl( this, wxID_ANY );
    mIssueYear->SetMinSize( wxSize( 200, mIssueYear->GetMinSize().y ) );
    ArrangeItems( mIssueYear, main_sizer, "Дата выпуска:" );

    wxBoxSizer* button_sizer = new wxBoxSizer( wxHORIZONTAL );

    mOkButton = new wxButton(this, wxID_ANY, "Добавить");
    button_sizer->Add( mOkButton, 0, wxRIGHT, 10 );

    mCancelButton = new wxButton(this, wxID_ANY, "Отмена");
    button_sizer->Add( mCancelButton, 0 );

    mOkButton->Bind( wxEVT_COMMAND_BUTTON_CLICKED, &WeaponAddFrame::OnOkClick, this );
    mCancelButton->Bind( wxEVT_COMMAND_BUTTON_CLICKED, &WeaponAddFrame::OnCancelClick, this );

    main_sizer->Add( button_sizer, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM | wxTOP, 10 );

   // SetSizer( main_sizer );
   this->SetSizerAndFit( main_sizer );
}

void WeaponAddFrame::OnOkClick( wxCommandEvent& event )
{
    WeaponData data; 

    data.mType = mType->GetValue().ToStdString();
    data.mCaliber = mCaliber->GetValue().ToStdString();
    data.mMark = mMark->GetValue().ToStdString();
    data.mIssueYear = mIssueYear->GetValue().ToStdString();

    if( mController )
    {
        mController->Notify( ControllerEvent::BUTTON_ADD_PRESSED, data );
    }

    Close( true );
}
