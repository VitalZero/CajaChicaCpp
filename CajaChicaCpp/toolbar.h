#ifndef PETTYCASHTEST_TOOLBAR_H
#define PETTYCASHTEST_TOOLBAR_H
#include <string>
#include <vector>
#include "IWin32Control.h"
#include "includes.h"

class Toolbar : public IWin32Control
{
public:
    Toolbar(BYTE style)
        : btnStyles(style), bmpSize(0), hasButtons(false)
    {
        // reserve vectors, so every insertion wont reallocate memory
        // thus won't change address, needed for TBBUTTON
        tbButtons.reserve(100);
        buttonLabels.reserve(100);
        type = CtlType::Toolbar;
    }

    void Create(HWND parent, int bmpSize )
    {
        if(!hasButtons)
        {
            throw std::runtime_error("Toolbar doesn't have any buttons");
        }

        btnStyles = (BYTE)style;
        this->bmpSize = bmpSize;

        if ( wnd )
        {
            throw std::runtime_error("Toolbar already created.");
        }

        type = CtlType::Toolbar;
        wndParent = parent;
        this->id = id;

        RECT rc;
        GetClientRect(wndParent, &rc);

        wnd = CreateWindowEx(
                0,
                TOOLBARCLASSNAME,
                nullptr,
                WS_CHILD | TBSTYLE_FLAT | TBSTYLE_LIST | CCS_NORESIZE |
                CCS_NODIVIDER | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | TBSTYLE_CUSTOMERASE,
                12, rc.top, rc.right, 24,
                wndParent,
                nullptr,
                GetModuleHandle(nullptr),
                nullptr);

        if ( !wnd )
        {
            throw std::runtime_error("Toolbar could not be created.");
        }

        SendMessage(wnd, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
        SendMessage(wnd, TB_ADDBUTTONS, (WPARAM)tbButtons.size(), (LPARAM)tbButtons.data());

        SendMessage(wnd, TB_AUTOSIZE, 0, 0);
        ShowWindow(wnd, SW_SHOW);
    }

    void InsertButton(const std::string& text, int cmdId)
    {
        if(wnd)
        {
            throw std::runtime_error("Insertion must happen before toolbar creation");
        }

        // Labels must be on it's own vector due to address change every insertion
        // TBBUTTON takes an address of the string, doesn't copy the value
        // so it must point to a static location
        buttonLabels.emplace_back(text);

        TBBUTTON tmp =
        {
            I_IMAGENONE, cmdId, TBSTATE_ENABLED, btnStyles,
            {0}, 0, (INT_PTR)buttonLabels.back().c_str()
        };

        tbButtons.push_back(tmp);

        if(!hasButtons)
        {
            hasButtons = true;
        }
    }

    int NumButtons() const { return tbButtons.size(); }

private:
    BYTE btnStyles;
    std::vector<TBBUTTON> tbButtons;
    std::vector<std::string> buttonLabels;
    int bmpSize;
    bool hasButtons;
    virtual std::string GetText() const override { return ""; }
    virtual void SetText(const std::string& text) override {}
};

#endif //PETTYCASHTEST_TOOLBAR_H
