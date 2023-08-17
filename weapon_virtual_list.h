#pragma once

#include "virtual_list.h"

class WeaponVirtualListControl : public VirtualListControl< WeaponData >
{
public:
    WeaponVirtualListControl( wxWindow *parent, const wxWindowID id, const wxPoint &pos, const wxSize &size )
        : VirtualListControl< WeaponData >( parent, id, pos, size )
    {
        this->AppendColumn( "№" );
       // this->SetColumnWidth( 0, 30 );

        this->AppendColumn( "Тип" );
        this->SetColumnWidth( 0, 120 );

        this->AppendColumn( "Калибр" );
        this->SetColumnWidth( 1, 120 );

        this->AppendColumn( "Марка" );
        this->SetColumnWidth( 2, 120 );

        this->AppendColumn( "Год выпуска" );
        ///this->SetColumnWidth( 3, 110 );
    }

    virtual wxString OnGetItemText( long index, long column ) const override
    {
        const auto& item = this->items.at( this->orderedIndices[ index ] );

        switch ( column )
        {
        case 0:
            return wxString::Format( "%d", item.mId );
        case 1:
            return item.mType;
        case 2:
            return item.mCaliber;
        case 3:
            return item.mMark;
        case 4:
            return item.mIssueYear;
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
                return genericCompare( i1.mType, i2.mType, ascending );
            case 2:
                return genericCompare( i1.mCaliber, i2.mCaliber, ascending );
            case 3:
                return genericCompare( i1.mMark, i2.mMark, ascending );
            case 4:
                return genericCompare( i1.mIssueYear, i2.mIssueYear, ascending );
            default:
                return false;
            }
        } );
    }
};