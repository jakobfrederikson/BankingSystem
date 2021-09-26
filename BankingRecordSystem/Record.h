#pragma once
#include <vector>
#include <string>

// Macros
#define CLEAR system("cls")
#define PAUSE system("pause")

class Record
{
public:
	void AddRecordToFile();
	void ShowRecordsInFile();
	void SearchRecordInFile();
	void UpdateExistingRecord();
	void DeleteExistingRecord();
	void DeleteRecordFile();
	std::vector<std::string> GetRecordsData();

	Record()
	{
		account_number_ = "Unknown";
		first_name_ = "Unknown";
		last_name_ = "Unknown";
		account_balance_ = "Unknown";
	}

	~Record() {};

private:
	// using std::string for everything so that user input doesn't crash the entire program
	std::string account_number_;
	std::string first_name_;
	std::string last_name_;
	std::string account_balance_;

	static void Search(std::string);
};

