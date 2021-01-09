#pragma once
#include <string>
#include <fstream>
#include <windows.h>

// Singleton
class Settings
{
public:
	static Settings& GetInstance();
	void Load();
	void Save();
	double GetAmount() const { return amount; }
	std::string GetStringAmount();
	std::string GetOwner() const { return owner; }
	void SetAmount(double amount) { this->amount = amount; }
	void SetOwner(const std::string& owner) { this->owner = owner; }
	//static BOOL CALLBACK StaticConfigDlgProc(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam);
	//BOOL ConfigDlgProcedure(HWND wndDlg, UINT msg, WPARAM wparam, LPARAM lparam);

private:
	Settings(std::string fileName = "cfg.txt")
		: fileName(fileName), amount(0), owner("N/A")	{}
	Settings(Settings const&) = delete;
	Settings& operator=(Settings const&) = delete;
	~Settings() {}
private:
	std::string owner;
	double amount;
	std::string fileName;
};