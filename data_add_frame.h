#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "controller.h"

enum class FrameType
{
    TYPE_ADD = 0,
    TYPE_EDIT = 1
};

template < class T >
class DataAddFrame: public wxFrame
{
public:

    virtual ~DataAddFrame() {}

    DataAddFrame( const wxString& title, const wxPoint& pos, const wxSize& size, 
                  const std::shared_ptr< Controller< T > >& controller, T* data = nullptr )
        : wxFrame(NULL, wxID_ANY, title, pos, size)
        , mController( controller )
        , mData( data )
        {
            mFrameType = data == nullptr ? FrameType::TYPE_ADD : FrameType::TYPE_EDIT;
        }

protected:
    void ArrangeItems( wxWindow* ctrl, wxBoxSizer* main_sizer, const std::string& label_text, bool top_border = false )
    {
        wxBoxSizer* sizer = new wxBoxSizer( wxHORIZONTAL );

        wxStaticText* text = new wxStaticText( this, wxID_ANY, label_text );
        text->SetMinSize( wxSize( 125, text->GetMinSize().y ) );
        sizer->Add( text );

        sizer->Add( ctrl, 1 );

        auto mask = wxLEFT | wxRIGHT | wxBOTTOM;
        if( top_border )
            mask = wxALL;

        main_sizer->Add( sizer, 1, wxEXPAND | wxALL, 10 );
    }

    virtual void OnOkClick( wxCommandEvent& event ) {}
    void OnCancelClick( wxCommandEvent& event ) { Close( true ); }

    std::shared_ptr< Controller< T > > mController;

    T* mData = nullptr;

    FrameType mFrameType = FrameType::TYPE_ADD;

    wxButton* mOkButton;
    wxButton* mCancelButton;
};