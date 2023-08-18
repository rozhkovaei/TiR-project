#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "data_add_frame.h"
#include "data_frame.h"

class BulletFrame: public DataFrame< BulletData >
{
public:

    BulletFrame( const wxString& title, const wxPoint& pos, const wxSize& size, 
                 const std::shared_ptr< IErrorObserver >& error_observer );

private:

   virtual void OnAddClick( wxCommandEvent& event ) override;
   virtual void OnEditClick( wxCommandEvent& event ) override;
};

class BulletAddFrame: public DataAddFrame< BulletData >
{
public:

    BulletAddFrame( const wxString& title, const wxPoint& pos, const wxSize& size,
                    const std::shared_ptr< Controller< BulletData > >& controller,
                    BulletData* data = nullptr );

private:

    virtual void OnOkClick( wxCommandEvent& event ) override;

    void AddItems();
    void SetValues();

    wxChoice* mType;
    wxChoice* mCaliber;
    wxTextCtrl* mSerialNumber;
    wxTextCtrl* mIssueYear;
};

