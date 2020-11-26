#ifndef PETTYCASHTEST_CONTROLMANAGER_H
#define PETTYCASHTEST_CONTROLMANAGER_H
#include "IWin32Control.h"
#include <vector>
#include <string>

class ControlManager
{
public:
    void Append(IWin32Control& control)
    {
        controls.emplace_back(&control);
    }

    void SetChildrenFont(HFONT font)
    {
        for(const auto& c : controls)
        {
            //operator HWND() implicit type conversion
            SendMessage(*c, WM_SETFONT, (WPARAM)font, FALSE);
        }
    }

    void SetChildrenText(const std::string& text, const CtlType type = CtlType::All)
    {
        for(const auto& c : controls)
        {
            if(c->GetType() == type)
            {
                c->SetText(text);
            }
        }
    }

    bool CheckEmptyText()
    {
        for(const auto& c : controls)
        {
            if(c->GetType() == CtlType::Edit || c->GetType() == CtlType::Combo)
            {
                if(c->GetText() == "")
                {
                    //operator HWND() implicit type conversion
                    SetFocus(*c);
                    return false;
                }
            }
        }

        return true;
    }

private:
    std::vector<IWin32Control*> controls;
};

#endif //PETTYCASHTEST_CONTROLMANAGER_H
