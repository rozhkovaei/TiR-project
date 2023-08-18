#pragma once

#include "virtual_list.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

template < class T >
class DataListView: public IUpdateObserver< T >
{
public:

    virtual ~DataListView() {}
    void Clear() { mListView->DeleteAllItems(); }

    virtual void Notify( T&& data ) override { mListView->setItem( std::move( data ) ); }

    wxBoxSizer* GetSizer() { return mListViewSizer; }

    void RemoveSelectedItem() { mListView->RemoveItem(); }
    int GetSelectedItemIndex() { return mListView->GetSelectedItemIndex(); }
    T* GetSelectedItemData() { return mListView->GetSelectedItemData(); }

protected:

    wxBoxSizer* mListViewSizer;
    VirtualListControl< T >* mListView;
};