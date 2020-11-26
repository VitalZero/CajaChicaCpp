#include "controller.h"

LRESULT Controller::OnCreate(WPARAM wparam, LPARAM lparam)
{
    NONCLIENTMETRICS ncm = {};
    ncm.cbSize = sizeof(NONCLIENTMETRICS);
    SystemParametersInfo(SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0);
    guiFont = CreateFontIndirect(&ncm.lfMessageFont);

    CreateMainMenu();
    toolBar.InsertButton("Archivo", 3000);
    toolBar.InsertButton("Editar", 3010);
    toolBar.Create(wnd, 0);

    startDate.Create(wnd, 1100, 12, 42, 100, 23);
    endDate.Create(wnd, 1110, 118, 42, 100, 23);
    week.Create(wnd, 1120, 224, 42, 80, 23);
    captureInvoices.Create("Facturas", wnd, 1130, 310, 41, 75, 23);

    Label line{WS_CHILD | WS_VISIBLE | WS_BORDER};
    //line.SetExStyle(WS_EX_CLIENTEDGE);
    line.Create(wnd, -1, 12, 75, 986, 1);

    records.Create(wnd, 1140, 12, 86, 986, 290);

    {
        records.InsertColumn("Proveedor", 200, 0);
        records.InsertColumn("RFC", 100, 1);
        records.InsertColumn("Concepto", 120, 2);
        records.InsertColumn("Fecha", 80, 3);

        int index;
        index = records.InsertItem("Caricachupas");
        records.SetItem("presenta", index, 1);
        records.SetItem("nombres de", index, 2);
        records.SetItem("puchonas", index, 3);

        index = records.InsertItem("dos");
        index = records.InsertItem("tres");
        index = records.AppendItem("Este es otro pedo");
    }

    totalReq.Create(wnd, 1150, 141, 382, 100, 23);
    refundPend.Create(wnd, 1160, 141, 411, 100, 23);
    cashRemain.Create(wnd, 1170, 141, 440, 100, 23);
    receipts.Create(wnd, 1180, 141, 469, 100, 23);
    sum.Create(wnd, 1190, 141, 498, 100, 23);
    loans.Create(wnd, 1200, 377, 382, 100, 23);
    totalAsigned.Create(wnd, 1210, 377, 411, 100, 23);
    difference.Create(wnd, 1220, 377, 440, 100, 23);

    ctlMan.Append(startDate);
    ctlMan.Append(endDate);
    ctlMan.Append(week);
    ctlMan.Append(captureInvoices);
    ctlMan.Append(records);
    ctlMan.Append(totalReq);
    ctlMan.Append(refundPend);
    ctlMan.Append(cashRemain);
    ctlMan.Append(receipts);
    ctlMan.Append(sum);
    //ctlMan.Append(toolBar);
    ctlMan.Append(rebar);
    ctlMan.Append(loans);
    ctlMan.Append(totalAsigned);
    ctlMan.Append(difference);

    ctlMan.SetChildrenFont(guiFont);

    SetFocus(startDate.Window());

    return 0;
}

LRESULT Controller::OnPaint(WPARAM wparam, LPARAM lparam) {
    PAINTSTRUCT ps = {};
    HDC hdc = BeginPaint(wnd, &ps);

    HFONT oldFont = (HFONT)SelectObject(hdc, guiFont);

    SetBkMode(hdc, TRANSPARENT);
    TextOut(hdc, 12, 24, "Fecha inicio", 12);
    TextOut(hdc, 118, 24, "Fecha fin", 9);
    TextOut(hdc, 224, 24, "Semana num", 10);
    TextOut(hdc, 13, 385, "Total solicitado", 16);
    TextOut(hdc, 13, 414, "Reembolso pendiente", 19);
    TextOut(hdc, 13, 443, "Efectivo en caja", 16);
    TextOut(hdc, 13, 472, "Comprobantes", 12);
    TextOut(hdc, 13, 501, "Suma", 4);
    TextOut(hdc, 249, 385, "Prestamos", 9);
    TextOut(hdc, 249, 414, "Total fondo asignado", 20);
    TextOut(hdc, 249, 443, "Diferencia", 10);
    SetBkMode(hdc, OPAQUE);

    SelectObject(hdc, oldFont);

    EndPaint(wnd, &ps);

    return 0;
}

LRESULT Controller::OnTbnDropDown(WPARAM wparam, LPARAM lparam)
{
    NMTOOLBAR* lpnmtb = (NMTOOLBAR*)lparam;
    RECT* menuRect = &lpnmtb->rcButton;
    RECT rc;
    GetWindowRect(toolBar, &rc);
    HMENU currMenu = nullptr;

    switch(lpnmtb->iItem)
    {
        case 3000:
            currMenu = fileMenu;
            break;

        case 3010:
            currMenu = editMenu;
            break;
    }

    TrackPopupMenu(currMenu, TPM_LEFTALIGN | TPM_TOPALIGN,
                   rc.left + menuRect->left, rc.top + menuRect->bottom, 0, wnd, nullptr);

    return TBDDRET_DEFAULT;
}

void Controller::CreateMainMenu()
{
    mainMenu = CreateMenu();

    // file menu
    fileMenu = CreatePopupMenu();
    AppendMenu(fileMenu, MF_STRING, 2000, "&Nuevo");
    AppendMenu(fileMenu, MF_STRING, 2010, "&Abrir");
    AppendMenu(fileMenu, MF_STRING, 2020, "&Guardar");
    AppendMenu(fileMenu, MF_STRING, 2030, "Guardar como...");
    AppendMenu(fileMenu, MF_SEPARATOR, -1, "-");
    AppendMenu(fileMenu, MF_STRING, 2040, "Im&primir");
    AppendMenu(fileMenu, MF_SEPARATOR, -1, "-");
    AppendMenu(fileMenu, MF_STRING, 2050, "&Salir");

    // edit menu
    editMenu = CreatePopupMenu();
    AppendMenu(editMenu, MF_STRING, 2060, "Agregar &Departamento");
    AppendMenu(editMenu, MF_STRING, 2070, "Agregar C&uenta");
    AppendMenu(editMenu, MF_STRING, 2080, "&Configuracion");

    // help menu

    // main menu
    AppendMenu(mainMenu, MF_POPUP | MF_STRING, (UINT_PTR)fileMenu, "Archivo");
    AppendMenu(mainMenu, MF_POPUP | MF_STRING, (UINT_PTR)editMenu, "Editar");
    SetMenu(wnd, mainMenu);
}

LRESULT Controller::OnNmCustomDraw(WPARAM wparam, LPARAM lparam)
{
    NMHDR* nmhdr = (NMHDR*)lparam;
    if(nmhdr->hwndFrom != toolBar)
    {
        return CDRF_DODEFAULT;
    }

    NMTBCUSTOMDRAW* nmtbcustomdraw = (NMTBCUSTOMDRAW*)lparam;

    if(nmtbcustomdraw->nmcd.dwDrawStage == CDDS_PREERASE)
    {
        TRIVERTEX vertex[2] ;
        vertex[0].x     = 0;
        vertex[0].y     = 0;
        vertex[0].Red   = 0xf000;
        vertex[0].Green = 0xf000;
        vertex[0].Blue  = 0xf000;
        vertex[0].Alpha = 0x0000;

        vertex[1].x     = nmtbcustomdraw->nmcd.rc.right;
        vertex[1].y     = nmtbcustomdraw->nmcd.rc.bottom;
        vertex[1].Red   = 0xfc00;
        vertex[1].Green = 0xfc00;
        vertex[1].Blue  = 0xfc00;
        vertex[1].Alpha = 0x0000;
        // Create a GRADIENT_RECT structure that
        // references the TRIVERTEX vertices.
        GRADIENT_RECT gRect;
        gRect.UpperLeft  = 0;
        gRect.LowerRight = 1;

        // Draw a shaded rectangle.
        GradientFill(nmtbcustomdraw->nmcd.hdc, vertex, 2, &gRect, 1, GRADIENT_FILL_RECT_H);

        return CDRF_SKIPDEFAULT;
    }

    return CDRF_DODEFAULT;
}
