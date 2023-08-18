#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>

#include <vector>
#include <numeric>
#include <unordered_map>

#include "common.h"

template < class T >
class VirtualListControl : public wxListCtrl
{
public:
    VirtualListControl( wxWindow *parent, const wxWindowID id, const wxPoint &pos, const wxSize &size )
        : wxListCtrl( parent, id, pos, size, wxLC_REPORT | wxLC_VIRTUAL )
    {
        this->Bind( wxEVT_LIST_COL_CLICK, [ this ]( wxListEvent &evt ) {
            auto selectedListIndex = getFirstSelectedIndex();
            long selectedDataIndex;

            if ( selectedListIndex != -1 )
            {
                selectedDataIndex = this->orderedIndices[ selectedListIndex ];

                // deselecting old index
                this->SetItemState( selectedListIndex, 0, wxLIST_STATE_SELECTED );
            }
 
            this->sortByColumn( evt.GetColumn() );
            this->RefreshAfterUpdate();

            if ( selectedListIndex != -1 )
            {
                auto listIndexToSelect = findIndexOfDataIndex( selectedDataIndex );
                this->SetItemState( listIndexToSelect, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
                this->EnsureVisible( listIndexToSelect );
            }

            this->sortAscending = !this->sortAscending;
        } );
    }

    virtual ~VirtualListControl() {}

    virtual wxString OnGetItemText( long index, long column ) const wxOVERRIDE
    {
        return L"";
    }

    void RefreshAfterUpdate()
    {
        SetItemCount( orderedIndices.size() );
        Refresh();
    }

    void setItem( T&& itemData )
    {
        auto index = itemData.mId;
        this->orderedIndices.push_back( index );
        items[ index ] = std::move( itemData );
        
        RefreshAfterUpdate();
    }

    void RemoveItem()
    {
        auto selectedListIndex = getFirstSelectedIndex();

        if( selectedListIndex == -1 || orderedIndices.size() == selectedListIndex )
            return;

        items.erase( orderedIndices[ selectedListIndex ] );
        orderedIndices.erase( orderedIndices.begin() + selectedListIndex );

        RefreshAfterUpdate();
    }

    int GetSelectedItemIndex()
    {
        auto selectedListIndex = getFirstSelectedIndex();

        if( selectedListIndex != -1 && orderedIndices.size() > selectedListIndex )
        {
            return orderedIndices[ selectedListIndex ];
        }

        return -1;
    }

    T* GetSelectedItemData()
    {
        auto selectedListIndex = getFirstSelectedIndex();

        if( selectedListIndex != -1 && orderedIndices.size() > selectedListIndex )
        {
            return &items[ orderedIndices[ selectedListIndex ] ];
        }

        return nullptr;
    }

protected:

    bool sortAscending = true;

    std::unordered_map< int, T > items;
    std::vector< int > orderedIndices;

    virtual void sortByColumn( int column )
    {
        // not implemented for base class
    }

    long getFirstSelectedIndex()
    {
        return GetNextItem( -1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED );
    }

    long findIndexOfDataIndex( long dataIndex )
    {
        return std::find( orderedIndices.begin(), orderedIndices.end(), dataIndex ) - orderedIndices.begin();
    }
};