#include "Settings.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>
//#include "resource.h" // settings dialog
#include "json.h"


void Settings::Load()
{
	std::ifstream is;
	is.open(fileName);
	
	if (is)
	{
		nlohmann::json j;
		is >> j;

		owner = j["owner"].get<std::string>();
		amount = j["amount"].get<double>();

		//std::string tmp;
		//while (std::getline(is, tmp) && is.good())
		//{
		//	if (tmp == "[owner]")
		//	{
		//		std::getline(is, owner);
		//	}
		//	else if (tmp == "[amount]")
		//	{
		//		is >> amount;
		//	}
		//	else if (tmp.empty())
		//	{
		//	}
		//	else
		//	{
		//		throw std::exception("Bad settings file in open");
		//	}
		//}
	}
	else
	{
		Save();
		//std::ofstream os(fileName, std::ios_base::trunc);

		//if (!os)
		//{
		//	throw std::exception("Can't create config file");
		//}
	}
}

void Settings::Save()
{
	std::ofstream os;
	os.open(fileName, std::ios_base::trunc);

	if (os)
	{
		nlohmann::json j;
		j["owner"] = owner;
		j["amount"] = amount;
		os << j;
		//os << "[owner]" << "\n" << owner << "\n";
		//os << "[amount]" << "\n" << amount << "\n";
	}
	else
	{
		throw std::exception("Bad settings file in save");
	}
}

std::string Settings::GetStringAmount()
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << std::fixed << amount;

	return ss.str();
}
//
//BOOL CALLBACK Settings::StaticConfigDlgProc(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//	Settings* pThis = nullptr;
//
//	if (msg == WM_INITDIALOG)
//	{
//		pThis = (Settings*)lparam;
//		SetWindowLongPtr(wndDlg, DWLP_USER, (LONG_PTR)pThis);
//	}
//	else
//	{
//		pThis = (Settings*)GetWindowLongPtr(wndDlg, DWLP_USER);
//	}
//
//	if (pThis)
//	{
//		return pThis->ConfigDlgProcedure(wndDlg, msg, wparam, lparam);
//	}
//
//	return FALSE;
//}
//
//BOOL Settings::ConfigDlgProcedure(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//	switch (msg)
//	{
//	case WM_INITDIALOG:
//	{
//		Load();
//		std::wstring tmp = GetStringAmount();
//		SetDlgItemText(wndDlg, IDC_TOTAL, tmp.c_str());
//		SetDlgItemText(wndDlg, IDC_CUSTODY, owner.c_str());
//	}
//	break;
//
//	case WM_COMMAND:
//		switch (LOWORD(wparam))
//		{
//		case IDOK:
//		{
//			wchar_t buffer[MAX_PATH] = { 0 };
//			GetDlgItemText(wndDlg, IDC_CUSTODY, buffer, MAX_PATH);
//			owner = buffer;
//
//			int len = GetWindowTextLength(GetDlgItem(wndDlg, IDC_TOTAL));
//			GetDlgItemText(wndDlg, IDC_TOTAL, buffer, len + 1);
//			amount = std::stod(buffer);
//			Save();
//		}
//		case IDCANCEL:
//			EndDialog(wndDlg, LOWORD(wparam));
//			return TRUE;
//		}
//		break;
//	}
//
//	return FALSE;
//}