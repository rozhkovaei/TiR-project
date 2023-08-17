#pragma once
 
#include "data_list_view.h"
#include "clients_virtual_list.h"

class ClientsListView: public DataListView< ClientData >
{
public:
    ClientsListView( wxWindow* parent )
    {
        // wxPanel* panel = new wxPanel( parent, wxID_ANY );
        this->mListView = new ClientsVirtualListControl( parent, wxID_ANY, wxDefaultPosition, wxSize( 600, 400 ) );

        this->mListViewSizer= new wxBoxSizer( wxVERTICAL );
        this->mListViewSizer->Add( this->mListView, 1, wxALL | wxEXPAND, 10 );

        // panel->SetSizerAndFit( mListViewSizer );
    }

};