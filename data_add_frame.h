#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "controller.h"

template < class T >
class DataAddFrame: public wxFrame
{
public:

    virtual ~DataAddFrame() {}

    DataAddFrame( const wxString& title, const wxPoint& pos, const wxSize& size, const std::shared_ptr< Controller< T > >& controller )
        : wxFrame(NULL, wxID_ANY, title, pos, size)
        , mController( controller )
        {}

protected:
    void ArrangeItems( wxTextCtrl* ctrl, wxBoxSizer* main_sizer, const std::string& label_text, bool top_border = false )
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

    wxButton* mOkButton;
    wxButton* mCancelButton;
};