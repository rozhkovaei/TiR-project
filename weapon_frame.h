#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "data_add_frame.h"
#include "data_frame.h"

class WeaponFrame: public DataFrame< WeaponData >
{
public:

    WeaponFrame( const wxString& title, const wxPoint& pos, const wxSize& size, 
                  const std::shared_ptr< IErrorObserver >& error_observer );

private:

   virtual void OnClientAddClick( wxCommandEvent& event ) override;
};

class WeaponAddFrame: public DataAddFrame< WeaponData >
{
public:

    WeaponAddFrame( const wxString& title, const wxPoint& pos, const wxSize& size,
                    const std::shared_ptr< Controller< WeaponData > >& controller );

private:

    virtual void OnOkClick( wxCommandEvent& event ) override;

    wxTextCtrl* mType;
    wxTextCtrl* mCaliber;
    wxTextCtrl* mMark;
    wxTextCtrl* mIssueYear;
};

