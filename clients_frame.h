#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "data_add_frame.h"
#include "data_frame.h"

class ClientsFrame: public DataFrame< ClientData >
{
public:

    ClientsFrame( const wxString& title, const wxPoint& pos, const wxSize& size, 
                  const std::shared_ptr< IErrorObserver >& error_observer );

private:

   virtual void OnClientAddClick( wxCommandEvent& event ) override;
};

class ClientAddFrame: public DataAddFrame< ClientData >
{
public:

    ClientAddFrame( const wxString& title, const wxPoint& pos, const wxSize& size,
                    const std::shared_ptr< Controller< ClientData > >& controller );

private:

    virtual void OnOkClick( wxCommandEvent& event ) override;

    wxTextCtrl* mEditName;
    wxTextCtrl* mEditSurName;
    wxTextCtrl* mEditPatronymicName;
    wxTextCtrl* mEditPassport;
    wxTextCtrl* mEditPhone;
};

