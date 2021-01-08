#pragma once
#include <string>
#include <fstream>
#include <windows.h>
class Settings
{
public:
	Settings(std::string fileName = "cfg.txt")
		: fileName(fileName), amount(8000.00), owner("JONATHAN MICHEL")
	{}
	void Load();
	void Save();
	double GetAmount() const { return amount; }
	std::string GetStringAmount();
	std::string GetOwner() const { return owner; }
	void SetAmount(double amount) { this->amount = amount; }
	void SetOwner(std::string& owner) { this->owner = owner; }
	//static BOOL CALLBACK StaticConfigDlgProc(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam);
	//BOOL ConfigDlgProcedure(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam);

private:
	std::string owner;
	double amount;
	std::string fileName;
};