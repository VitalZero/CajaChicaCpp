#ifndef PETTYCASHTEST_IWIN32CONTROL_H
#define PETTYCASHTEST_IWIN32CONTROL_H
#include "includes.h"
#include <stdexcept>

enum class CtlType
{
    All, Edit, Static, Combo, Listbox, Button, Check, Radio,
    Listview, Treeview, Toolbar, Statusbar, Rebar
};

class IWin32Control {
protected:
    IWin32Control()
            : wnd(nullptr), style(WS_TABSTOP | WS_CHILD | WS_VISIBLE), wndParent(nullptr) {}

public:
    virtual void SetText(const std::string &text) = 0;
    virtual std::string GetText() const = 0;
    HWND Window() const { return wnd; }
    operator HWND() const { return wnd; }
    size_t GetLength() const { return GetWindowTextLength(wnd) + 1; }
    void Disable() const { EnableWindow(wnd, FALSE); }
    void Enable() const { EnableWindow(wnd, TRUE); }
    CtlType GetType() const { return type; }

    void SetStyle(DWORD style)
    {
        if (wnd)
        {
            throw std::runtime_error("SetStyle should be called before creating the controller");
        }

        this->style = style;
    }

    void SetExStyle(DWORD exStyle)
    {
        if (wnd)
        {
            throw std::runtime_error("SetExStyle should be called before creating the controller");
        }

        this->exStyle = exStyle;
    }

protected:
    HWND wndParent;
    int id = 0;
    DWORD style;
    DWORD exStyle = 0;
    HWND wnd;
    CtlType type = CtlType::All;
};

#endif //PETTYCASHTEST_IWIN32CONTROL_H
