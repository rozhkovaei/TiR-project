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

void BulletFrame::OnAddClick( wxCommandEvent& event ) 
{
    BulletAddFrame* frame = new BulletAddFrame( "", wxPoint(200, 200), wxSize(300, 270), mController );
    frame->Show( true );
}

void BulletFrame::OnEditClick( wxCommandEvent& event )
{
    BulletData* data = mListView->GetSelectedItemData();

    if( data == nullptr)
    {
        wxLogMessage( "Данные не выбраны!" );
        return;
    }

    BulletAddFrame* frame = new BulletAddFrame( "", wxPoint( 200, 200 ), wxSize( 300, 270 ), mController, data );
    frame->Show( true );
}

BulletAddFrame::BulletAddFrame( const wxString& title, const wxPoint& pos, const wxSize& size,
                                const std::shared_ptr< Controller< BulletData > >& controller, BulletData* data )
        : DataAddFrame< BulletData >( title, pos, size, controller, data )
{
    AddItems();

    if( mFrameType == FrameType::TYPE_EDIT )
        SetValues();
}

void BulletAddFrame::AddItems()
{
    wxBoxSizer* main_sizer = new wxBoxSizer( wxVERTICAL );

    wxArrayString strings;
    strings.Add(wxT("Патрон"));

    mType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, strings, wxCB_DROPDOWN );
    mType->SetMinSize( wxSize( 200, mType->GetMinSize().y ) );
    ArrangeItems( mType, main_sizer, "Тип:", true );

    wxArrayString strings_caliber;
    strings_caliber.Add(wxT("9 x 19"));
    strings_caliber.Add(wxT("7,62 x 39"));

    mCaliber = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, strings_caliber, wxCB_DROPDOWN );
    mCaliber->SetMinSize( wxSize( 200, mCaliber->GetMinSize().y ) );
    ArrangeItems( mCaliber, main_sizer, "Калибр:" );

    mSerialNumber = new wxTextCtrl( this, wxID_ANY );
    mSerialNumber->SetMinSize( wxSize( 200, mSerialNumber->GetMinSize().y ) );
    ArrangeItems( mSerialNumber, main_sizer, "Номер партии:" );

    mIssueYear = new wxTextCtrl( this, wxID_ANY );
    mIssueYear->SetMinSize( wxSize( 200, mIssueYear->GetMinSize().y ) );
    ArrangeItems( mIssueYear, main_sizer, "Дата выпуска:" );

    wxBoxSizer* button_sizer = new wxBoxSizer( wxHORIZONTAL );

    mOkButton = mFrameType == FrameType::TYPE_ADD ? new wxButton(this, wxID_ANY, "Добавить") : 
        new wxButton(this, wxID_ANY, "Изменить");
    button_sizer->Add( mOkButton, 0, wxRIGHT, 10 );

    mCancelButton = new wxButton(this, wxID_ANY, "Отмена");
    button_sizer->Add( mCancelButton, 0 );

    mOkButton->Bind( wxEVT_COMMAND_BUTTON_CLICKED, &BulletAddFrame::OnOkClick, this );
    mCancelButton->Bind( wxEVT_COMMAND_BUTTON_CLICKED, &BulletAddFrame::OnCancelClick, this );

    main_sizer->Add( button_sizer, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM | wxTOP, 10 );

   // SetSizer( main_sizer );
   this->SetSizerAndFit( main_sizer );
}

void BulletAddFrame::SetValues()
{
    if( mData == nullptr )
        return;

    mSerialNumber->SetValue( mData->mSerialNumber );
    mIssueYear->SetValue( mData->mIssueYear );
    mType->SetSelection( mType->FindString( mData->mType ) );
    mCaliber->SetSelection( mCaliber->FindString( mData->mCaliber ) );
}

void BulletAddFrame::OnOkClick( wxCommandEvent& event )
{
    if( mFrameType == FrameType::TYPE_ADD )
    {
        BulletData data; 

        data.mType = mType->GetString( mType->GetCurrentSelection() );
        data.mCaliber = mCaliber->GetString( mCaliber->GetCurrentSelection() );
        data.mSerialNumber = mSerialNumber->GetValue().ToStdString();
        data.mIssueYear = mIssueYear->GetValue().ToStdString();

        if( mController )
        {
            mController->Notify( ControllerEvent::BUTTON_ADD_PRESSED, data );
        }
    }
    else if( mFrameType == FrameType::TYPE_EDIT )
    {
        mData->mSerialNumber = mSerialNumber->GetValue().ToStdString();
        mData->mType = mType->GetString( mType->GetCurrentSelection() );
        mData->mCaliber = mCaliber->GetString( mCaliber->GetCurrentSelection() );
        mData->mIssueYear = mIssueYear->GetValue().ToStdString();

        if( mController )
        {
            mController->Notify( ControllerEvent::BUTTON_EDIT_PRESSED, *mData );
        }
    }

    Close( true );
}
