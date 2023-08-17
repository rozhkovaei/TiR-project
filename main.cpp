#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "wx_error_observer.h"

#include "clients_frame.h"
#include "weapon_frame.h"
#include "bullet_frame.h"

class MyFrame;

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame: public wxFrame
{
public:
    MyFrame( const wxString& title, const wxPoint& pos, const wxSize& size );
private:
    void OnHello( wxCommandEvent& event );
    void OnExit( wxCommandEvent& event );
    void OnAbout( wxCommandEvent& event );

    void OnClientsClick( wxCommandEvent& event );
    void OnWeaponClick( wxCommandEvent& event );
    void OnBulletClick( wxCommandEvent& event );

    wxDECLARE_EVENT_TABLE();

    wxButton* mClientsButton;
    wxButton* mWeaponButton;
    wxButton* mBulletButton;

    std::shared_ptr< IErrorObserver > mErrorObserver;
};

enum
{
    ID_Hello = 1,
    BUTTON_CLIENTS = 2,
    BUTTON_WEAPON = 3,
    BUTTON_BULLET = 4,
};

wxBEGIN_EVENT_TABLE( MyFrame, wxFrame )
    EVT_MENU( ID_Hello,   MyFrame::OnHello )
    EVT_MENU( wxID_EXIT,  MyFrame::OnExit )
    EVT_MENU( wxID_ABOUT, MyFrame::OnAbout )
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP( MyApp );

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame( "", wxPoint( 50, 50 ), wxSize( 450, 340 ) );
    frame->Show( true );
    return true;
}

MyFrame::MyFrame( const wxString& title, const wxPoint& pos, const wxSize& size )
        : wxFrame( NULL, wxID_ANY, title, pos, size )
{
  /*  wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );*/
    CreateStatusBar();
    SetStatusText( "Спортивно-стрелковый клуб Звезда" );

    mClientsButton = 
                new wxButton( this, BUTTON_CLIENTS, "Клиенты клуба", wxPoint( 5, 10 ), wxSize( 120, 20), 0 );

    mWeaponButton = new wxButton( this, BUTTON_WEAPON, "Арсенал", wxPoint( 5, 50 ), wxSize( 120, 20 ), 0 );

    mBulletButton = new wxButton( this, BUTTON_BULLET, "Патроны", wxPoint( 5, 90 ), wxSize( 120, 20 ), 0 );

    mClientsButton->Bind( wxEVT_COMMAND_BUTTON_CLICKED, &MyFrame::OnClientsClick, this );
    mWeaponButton->Bind( wxEVT_COMMAND_BUTTON_CLICKED, &MyFrame::OnWeaponClick, this );
    mBulletButton->Bind( wxEVT_COMMAND_BUTTON_CLICKED, &MyFrame::OnBulletClick, this );

    mErrorObserver = std::make_shared< WxErrorObserver>();
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
}

void MyFrame::OnHello(wxCommandEvent& event)
{
}

void MyFrame::OnClientsClick( wxCommandEvent& event )
{
    ClientsFrame* frame = new ClientsFrame( "", wxPoint( 150, 150 ), wxSize( 450, 340 ), mErrorObserver );
    frame->Show( true );
}

void MyFrame::OnWeaponClick( wxCommandEvent& event )
{
    WeaponFrame* frame = new WeaponFrame( "", wxPoint( 150, 150 ), wxSize( 450, 340 ), mErrorObserver );
    frame->Show( true );
}

void MyFrame::OnBulletClick( wxCommandEvent& event )
{
    //wxLogMessage("Button ammo clicked!");

    BulletFrame* frame = new BulletFrame( "", wxPoint( 150, 150 ), wxSize( 450, 340 ), mErrorObserver );
    frame->Show( true );
}