#ifndef PETTYCASHTEST_LISTVIEW_H
#define PETTYCASHTEST_LISTVIEW_H
#include <string>
#include <vector>
#include "IWin32Control.h"
#include "includes.h"

class Listview : public IWin32Control
{
public:
    Listview()
    {
        exStyle = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;
        type = CtlType::Listview;
    }
    Listview(const Listview&) = delete;
    Listview& operator=(const Listview&) = delete;

    explicit Listview(DWORD style)
    {
        exStyle = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;;
        type = CtlType::Listview;
        this->style = style;
    }

    explicit Listview(HWND wndParent, int id)
    {
        exStyle = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;;
        type = CtlType::Listview;
        this->wndParent = wndParent;
        this->id = id;
        wnd = GetDlgItem(wndParent, id);
        style = (int)GetWindowLong(wnd, GWL_STYLE);
    }

    void Create(HWND parent, int id, int x, int y, int width, int height)
    {
        if ( wnd )
        {
            throw std::runtime_error("Editbox already created.");
        }

        INITCOMMONCONTROLSEX icex = {};
        icex.dwSize = sizeof(icex);
        icex.dwICC = ICC_LISTVIEW_CLASSES;
        InitCommonControlsEx(&icex);

        type = CtlType::Listview;
        wndParent = parent;
        this->id = id;

        wnd = CreateWindowEx(
                0,
                WC_LISTVIEW,
                "",
                style,
                x,
                y,
                width,
                height,
                wndParent,
                (HMENU)this->id,
                GetModuleHandle(nullptr),
                nullptr);

        if ( !wnd )
        {
            throw std::runtime_error("Editbox could not be created.");
        }

        SendMessage(wnd, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, exStyle);
    }

public:
    void InsertColumn(const std::string& text, int size, int index = 0)
    {
        LVCOLUMN lvCol = {};
        std::vector<char> buffer(text.length() + 1);
        buffer.assign(text.begin(), text.end());
        lvCol.pszText = buffer.data();
        lvCol.cchTextMax = 255;
        lvCol.cx = size;
        lvCol.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

        ListView_InsertColumn(wnd, index, &lvCol);
    }

    int InsertItem(const std::string& text)
    {
        LVITEM lvItem = {};
        lvItem.mask = LVIF_TEXT;
        lvItem.cchTextMax = 255;
        std::vector<char> buffer(text.length() + 1);
        buffer.assign(text.begin(), text.end());
        lvItem.pszText = buffer.data();
        lvItem.iItem = 0;

        return ListView_InsertItem(wnd, &lvItem);
    }

    int AppendItem(const std::string& text)
    {
        LVITEM lvItem = {};
        lvItem.mask = LVIF_TEXT;
        lvItem.cchTextMax = 255;
        std::vector<char> buffer(text.length() + 1);
        buffer.assign(text.begin(), text.end());
        lvItem.pszText = buffer.data();
        lvItem.iItem = ListView_GetItemCount(wnd);

        return ListView_InsertItem(wnd, &lvItem);
    }

    void SetItem(const std::string& text, int row, int col)
    {
        std::vector<char> buffer(text.length() + 1);
        buffer.assign(text.begin(), text.end());

        ListView_SetItemText(wnd, row, col, buffer.data());
    }

private:
    virtual std::string GetText() const override { return ""; }
    virtual void SetText(const std::string& text) override {}
};

#endif //PETTYCASHTEST_LISTVIEW_H
