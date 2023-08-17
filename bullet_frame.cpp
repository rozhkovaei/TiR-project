#include "bullet_frame.h"
#include "bullet_controller.h"
#include "bullet_list_view.h"

BulletFrame::BulletFrame( const wxString& title, const wxPoint& pos, const wxSize& size,
                          const std::shared_ptr< IErrorObserver >& error_observer )
        : DataFrame< BulletData >( title, pos, size ) 
{
    this->mController = std::make_shared< BulletController< BulletData > >( error_observer );
    this->mListView = std::make_shared< BulletListView >( this );
    AddElements();    
}

void BulletFrame::OnClientAddClick( wxCommandEvent& event ) 
{
    BulletAddFrame* frame = new BulletAddFrame( "", wxPoint(200, 200), wxSize(300, 270), mController );
    frame->Show( true );
}

BulletAddFrame::BulletAddFrame( const wxString& title, const wxPoint& pos, const wxSize& size,
                                const std::shared_ptr< Controller< BulletData > >& controller )
        : DataAddFrame< BulletData >( title, pos, size, controller )
{
    wxBoxSizer* main_sizer = new wxBoxSizer( wxVERTICAL );

    mType = new wxTextCtrl( this, wxID_ANY );
    mType->SetMinSize( wxSize( 200, mType->GetMinSize().y ) );

    ArrangeItems( mType, main_sizer, "Тип:", true );

    mCaliber = new wxTextCtrl( this, wxID_ANY );
    mCaliber->SetMinSize( wxSize( 200, mCaliber->GetMinSize().y ) );
    ArrangeItems( mCaliber, main_sizer, "Калибр:" );

    mSerialNumber = new wxTextCtrl( this, wxID_ANY );
    mSerialNumber->SetMinSize( wxSize( 200, mSerialNumber->GetMinSize().y ) );
    ArrangeItems( mSerialNumber, main_sizer, "Номер партии:" );

    mIssueYear = new wxTextCtrl( this, wxID_ANY );
    mIssueYear->SetMinSize( wxSize( 200, mIssueYear->GetMinSize().y ) );
    ArrangeItems( mIssueYear, main_sizer, "Дата выпуска:" );

    wxBoxSizer* button_sizer = new wxBoxSizer( wxHORIZONTAL );

    mOkButton = new wxButton(this, wxID_ANY, "Добавить");
    button_sizer->Add( mOkButton, 0, wxRIGHT, 10 );

    mCancelButton = new wxButton(this, wxID_ANY, "Отмена");
    button_sizer->Add( mCancelButton, 0 );

    mOkButton->Bind( wxEVT_COMMAND_BUTTON_CLICKED, &BulletAddFrame::OnOkClick, this );
    mCancelButton->Bind( wxEVT_COMMAND_BUTTON_CLICKED, &BulletAddFrame::OnCancelClick, this );

    main_sizer->Add( button_sizer, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM | wxTOP, 10 );

   // SetSizer( main_sizer );
   this->SetSizerAndFit( main_sizer );
}

void BulletAddFrame::OnOkClick( wxCommandEvent& event )
{
    BulletData data; 

    data.mType = mType->GetValue().ToStdString();
    data.mCaliber = mCaliber->GetValue().ToStdString();
    data.mSerialNumber = mSerialNumber->GetValue().ToStdString();
    data.mIssueYear = mIssueYear->GetValue().ToStdString();

    if( mController )
    {
        mController->Notify( ControllerEvent::BUTTON_ADD_PRESSED, data );
    }

    Close( true );
}
