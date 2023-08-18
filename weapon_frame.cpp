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

void WeaponFrame::OnAddClick( wxCommandEvent& event )
{
    WeaponAddFrame* frame = new WeaponAddFrame( "", wxPoint( 200, 200 ), wxSize( 300, 270 ), mController );
    frame->Show( true );
}

void WeaponFrame::OnEditClick( wxCommandEvent& event )
{
    WeaponData* data = mListView->GetSelectedItemData();

    if( data == nullptr)
    {
        wxLogMessage( "Данные не выбраны!" );
        return;
    }

    WeaponAddFrame* frame = new WeaponAddFrame( "", wxPoint( 200, 200 ), wxSize( 300, 270 ), mController, data );
    frame->Show( true );
}

WeaponAddFrame::WeaponAddFrame( const wxString& title, const wxPoint& pos, const wxSize& size,
                                const std::shared_ptr< Controller< WeaponData > >& controller,
                                WeaponData* data )
        : DataAddFrame< WeaponData >( title, pos, size, controller, data )
{
    AddItems();

    if( mFrameType == FrameType::TYPE_EDIT )
        SetValues();
}

void WeaponAddFrame::AddItems( )
{
    wxBoxSizer* main_sizer = new wxBoxSizer( wxVERTICAL );

    wxArrayString strings;
    strings.Add(wxT("Гражданское спортивное огнестрельное оружие с нарезным стволом"));
    strings.Add(wxT("Гражданское охотничье огнестрельное длинноствольное оружие с нарезным стволом"));
    strings.Add(wxT("Гражданское спортивное огнестрельное длинноствольное оружие с нарезным стволом"));
    strings.Add(wxT("Гражданское охотничье длинноствольное оружие"));
    strings.Add(wxT("Гражданское огнестрельное оружие ограниченного поражения"));

    mSerialNumber = new wxTextCtrl( this, wxID_ANY );
    mSerialNumber->SetMinSize( wxSize( 200, mSerialNumber->GetMinSize().y ) );
    ArrangeItems( mSerialNumber, main_sizer, "Серийный номер:", true );

    mType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, strings, wxCB_DROPDOWN );
    mType->SetMinSize( wxSize( 200, mType->GetMinSize().y ) );
    ArrangeItems( mType, main_sizer, "Тип:", true );

    wxArrayString strings_caliber;
    strings_caliber.Add(wxT("9 x 19"));
    strings_caliber.Add(wxT("7,62 x 39"));

    mCaliber = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, strings_caliber, wxCB_DROPDOWN );
    mCaliber->SetMinSize( wxSize( 200, mCaliber->GetMinSize().y ) );
    ArrangeItems( mCaliber, main_sizer, "Калибр:" );

    mMark = new wxTextCtrl( this, wxID_ANY );
    mMark->SetMinSize( wxSize( 200, mMark->GetMinSize().y ) );
    ArrangeItems( mMark, main_sizer, "Марка:" );

    mIssueYear = new wxTextCtrl( this, wxID_ANY );
    mIssueYear->SetMinSize( wxSize( 200, mIssueYear->GetMinSize().y ) );
    ArrangeItems( mIssueYear, main_sizer, "Дата выпуска:" );

    wxBoxSizer* button_sizer = new wxBoxSizer( wxHORIZONTAL );

    mOkButton = mFrameType == FrameType::TYPE_ADD ? new wxButton(this, wxID_ANY, "Добавить") : 
        new wxButton(this, wxID_ANY, "Изменить");
    button_sizer->Add( mOkButton, 0, wxRIGHT, 10 );

    mCancelButton = new wxButton(this, wxID_ANY, "Отмена");
    button_sizer->Add( mCancelButton, 0 );

    mOkButton->Bind( wxEVT_COMMAND_BUTTON_CLICKED, &WeaponAddFrame::OnOkClick, this );
    mCancelButton->Bind( wxEVT_COMMAND_BUTTON_CLICKED, &WeaponAddFrame::OnCancelClick, this );

    main_sizer->Add( button_sizer, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM | wxTOP, 10 );

   // SetSizer( main_sizer );
   this->SetSizerAndFit( main_sizer );
}

void WeaponAddFrame::SetValues()
{
    if( mData == nullptr )
        return;

    mType->SetSelection( mType->FindString( mData->mType ) );
    mCaliber->SetSelection( mCaliber->FindString( mData->mCaliber ) );
    mSerialNumber->SetValue( mData->mSerialNumber );
    mMark->SetValue( mData->mMark );
    mIssueYear->SetValue( mData->mIssueYear );
}

void WeaponAddFrame::OnOkClick( wxCommandEvent& event )
{
    if( mFrameType == FrameType::TYPE_ADD)
    {
        WeaponData data; 

        data.mSerialNumber = mSerialNumber->GetValue().ToStdString();
        data.mType = mType->GetString( mType->GetCurrentSelection() );
        data.mCaliber = mCaliber->GetString( mCaliber->GetCurrentSelection() );
        data.mMark = mMark->GetValue().ToStdString();
        data.mIssueYear = mIssueYear->GetValue().ToStdString();

        if( mController )
        {
            mController->Notify( ControllerEvent::BUTTON_ADD_PRESSED, data );
        }
    }
    else if( mFrameType == FrameType::TYPE_EDIT)
    {
        mData->mSerialNumber = mSerialNumber->GetValue().ToStdString();
        mData->mType = mType->GetString( mType->GetCurrentSelection() );
        mData->mCaliber = mCaliber->GetString( mCaliber->GetCurrentSelection() );
        mData->mMark = mMark->GetValue().ToStdString();
        mData->mIssueYear = mIssueYear->GetValue().ToStdString();

        if( mController )
        {
            mController->Notify( ControllerEvent::BUTTON_EDIT_PRESSED, *mData );
        }
    }

    Close( true );
}
