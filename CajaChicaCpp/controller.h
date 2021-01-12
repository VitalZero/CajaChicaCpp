#ifndef PETTYCASHTEST_CONTROLLER_H
#define PETTYCASHTEST_CONTROLLER_H
#include "includes.h"
#include "editbox.h"
#include "label.h"
#include "button.h"
#include "listview.h"
#include "toolbar.h"
#include "rebar.h"
#include "controlmanager.h"

class Controller
{
public:
    Controller(HWND wnd)
        : wnd(wnd), guiFont(nullptr), toolBar(BTNS_DROPDOWN | BTNS_AUTOSIZE),
        sum( WS_CHILD | WS_VISIBLE | WS_DISABLED),
        totalReq( WS_CHILD | WS_VISIBLE | WS_DISABLED),
        records(WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_ALIGNTOP | LVS_SHOWSELALWAYS | LVS_SINGLESEL),
        difference( WS_CHILD | WS_VISIBLE | WS_DISABLED)
    {}

public:
    LRESULT OnCreate(WPARAM wparam, LPARAM lparam);
    LRESULT OnPaint(WPARAM wparam, LPARAM lparam);
    LRESULT OnCommand(WPARAM wparam, LPARAM lparam);
    LRESULT OnTbnDropDown(WPARAM wparam, LPARAM lparam);
    LRESULT OnNmCustomDraw(WPARAM wparam, LPARAM lparam);
    void CreateMainMenu();

private:
    HWND wnd;
    HFONT guiFont;
    HMENU mainMenu;
    HMENU fileMenu;
    HMENU editMenu;

private:
    Editbox startDate;
    Editbox endDate;
    Editbox week;
    Button captureInvoices;
    Listview records;
    Editbox totalReq;
    Editbox refundPend;
    Editbox cashRemain;
    Editbox receipts;
    Editbox sum;
    Editbox loans;
    Editbox totalAsigned;
    Editbox difference;
    ControlManager ctlMan;
    Toolbar toolBar;
    Rebar rebar;
};

#endif //PETTYCASHTEST_CONTROLLER_H
