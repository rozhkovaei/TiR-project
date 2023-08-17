#pragma once
 
#include "data_list_view.h"
#include "weapon_virtual_list.h"

class WeaponListView: public DataListView< WeaponData >
{
public:
    WeaponListView( wxWindow* parent )
    {
        // wxPanel* panel = new wxPanel( parent, wxID_ANY );
        this->mListView = new WeaponVirtualListControl( parent, wxID_ANY, wxDefaultPosition, wxSize( 600, 400 ) );

        this->mListViewSizer= new wxBoxSizer( wxVERTICAL );
        this->mListViewSizer->Add( this->mListView, 1, wxALL | wxEXPAND, 10 );

        // panel->SetSizerAndFit( mListViewSizer );
    }

};