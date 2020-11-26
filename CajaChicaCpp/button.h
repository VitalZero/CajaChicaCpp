#ifndef PETTYCASHTEST_BUTTON_H
#define PETTYCASHTEST_BUTTON_H
#include <string>
#include <vector>
#include "IWin32Control.h"
#include "includes.h"

class Button : public IWin32Control
{
public:
    Button()
    {
        exStyle = 0;
        type = CtlType::Button;
    }
    Button(const Button&) = delete;
    Button& operator=(const Button&) = delete;

    explicit Button(DWORD style)
    {
        exStyle = 0;
        type = CtlType::Button;
        this->style = style;
    }

    explicit Button(HWND wndParent, int id)
    {
        exStyle = 0;
        type = CtlType::Button;
        this->wndParent = wndParent;
        this->id = id;
        wnd = GetDlgItem(wndParent, id);
        style = (int)GetWindowLong(wnd, GWL_STYLE);
    }

    virtual std::string GetText() const override
    {
        int len = GetLength();
        std::vector<char> tmp(len);

        if ( GetWindowText(wnd, tmp.data(), len) > 0 )
        {
            return std::string(tmp.data());
        }

        return std::string("0");
    }

    virtual void SetText(const std::string& text) override
    {
        SetWindowText(wnd, text.c_str());
    }

    void Create(const std::string& text, HWND parent, int id, int x, int y, int width, int height)
    {
        if ( wnd )
        {
            throw std::runtime_error("Button already created.");
        }

        type = CtlType::Button;
        wndParent = parent;
        this->id = id;

        wnd = CreateWindowEx(
                exStyle,
                "BUTTON",
                text.c_str(),
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
            throw std::runtime_error("Button could not be created.");
        }
    }
};

#endif //PETTYCASHTEST_BUTTON_H
