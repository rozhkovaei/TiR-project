#pragma once

#include "virtual_list.h"

class ClientsVirtualListControl : public VirtualListControl< ClientData >
{
public:

    ClientsVirtualListControl( wxWindow *parent, const wxWindowID id, const wxPoint &pos, const wxSize &size )
        : VirtualListControl< ClientData >( parent, id, pos, size )
    {
        this->AppendColumn( "ID" );
       // this->SetColumnWidth( 0, 30 );

        this->AppendColumn( "Фамилия" );
        this->SetColumnWidth( 0, 120 );

        this->AppendColumn( "Имя" );
        this->SetColumnWidth( 1, 120 );

        this->AppendColumn( "Отчество" );
        this->SetColumnWidth( 2, 120 );

        this->AppendColumn( "Паспорт" );
        ///this->SetColumnWidth( 3, 110 );

        this->AppendColumn( "Телефон" );
        //this->SetColumnWidth( 4, 120 );
    }

    virtual wxString OnGetItemText( long index, long column ) const override
    {
        const auto& item = this->items.at( this->orderedIndices[ index ] );

        switch ( column )
        {
        case 0:
            return wxString::Format( "%d", item.mId );
        case 1:
            return item.mLastName;
        case 2:
            return item.mFirstName;
        case 3:
            return item.mPatronymic;
        case 4:
            return item.mPassport;
        case 5:
            return item.mPhone;
        default:
            return "";
        }
    }

    virtual void sortByColumn( int column ) override 
    {
        // C++14 generic lambda
        static auto genericCompare = []( auto i1, auto i2, bool ascending ) {
            return ascending ? i1 < i2 : i1 > i2;
        };

        bool ascending = this->sortAscending;

        std::sort( this->orderedIndices.begin(), this->orderedIndices.end(), [ this, column, ascending ]( long index1, long index2 ) {
            auto& i1 = this->items[ index1 ];
            auto& i2 = this->items[ index2 ];

            switch ( column )
            {
            case 0:
                return genericCompare( i1.mId, i2.mId, ascending );
            case 1:
                return genericCompare( i1.mLastName, i2.mLastName, ascending );
            case 2:
                return genericCompare( i1.mFirstName, i2.mFirstName, ascending );
            case 3:
                return genericCompare( i1.mPatronymic, i2.mPatronymic, ascending );
            case 4:
                return genericCompare( i1.mPassport, i2.mPassport, ascending );
            case 5:
                return genericCompare( i1.mPhone, i2.mPhone, ascending );
            default:
                return false;
            }
        } );
    }
};