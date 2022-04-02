#include <iostream>
#include <fstream>
#include <sstream>
#include "Record.h"

// Gets user input for bank account and adds it to records.csv
void Record::AddRecordToFile()
{
	std::cin.ignore();
	std::cout << "***Add record to file***\n\n";

	std::cout << "Enter account number:  ";
	std::getline(std::cin, account_number_);

	std::cout << "Enter first name(s):   ";
	std::getline(std::cin, first_name_);

	std::cout << "Enter last name:       ";
	std::getline(std::cin, last_name_);

	std::cout << "Enter account balance\n";
	std::cout << "Don't include commas:  ";
	std::getline(std::cin, account_balance_);

	// output to records.csv
	std::ofstream outfile;
	outfile.open("records.csv", std::ios::app);
	outfile << account_number_ << "," << first_name_ << "," << last_name_ << "," << account_balance_ << std::endl;
	outfile.close();
}

// Display every record in records.csv
void Record::ShowRecordsInFile()
{
	std::vector<AccountRecord> records_data = GetRecordsData();

	std::cout << "***All records in file***\n";
	
	for (int i = 0; i < records_data.size();)
	{
		std::cout << "Account number:  " << records_data[i] << "\n";
		std::cout << "First name:      " << records_data[i + 1] << "\n";
		std::cout << "Last name:       " << records_data[i + 2] << "\n";
		std::cout << "Account balance: " << records_data[i + 3] << "\n";
		std::cout << "\n";

		i = i + 4;
	}

	std::cout << "\n";
	PAUSE;
}

void Record::SearchRecordInFile()
{
	std::string user_input = "";

	do
	{
		CLEAR;
		std::cout << "***Search a for Record in File***\n";
		std::cout << "[ Search by Account Number, First Name or Last Name ]\n";
		std::cout << "[ Enter 0 to return to main menu ]\n\n";

		std::cout << "\n--------------------------------------------------------------\n";
		std::cout << "SEARCH FOR ACCOUNT HERE:  ";

		try
		{
			std::cin >> user_input;

			if (!std::cin) throw 6;
			else
			{
				Record::Search(user_input);
			}
				
		}
		catch (...)
		{
			std::cout << "\nError: Please enter an integer between 1-6.\n\n";

			// Clear the input stream
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			PAUSE;
		}

	} while (user_input != "0");
}

void Record::UpdateExistingRecord()
{
	std::cout << "***Update Existing Record***\n\n";
	std::cout << "There are ___ records in the file\n";
	// show records
	std::cout << "Enter account number to edit: ";
	// std::cin account_num_?

	// [1] Account number: #;
	// [2] First name: "asdf";
	// [3] Last name: "asdf";
	// [4] Current balance: #;
	
	std::cout << "Enter a line's number to edit: ";
	// std::cin >> num;
}

void Record::DeleteExistingRecord()
{
	std::cout << "delete\n";
	PAUSE;
}

std::vector<Record::AccountRecord> Record::GetRecordsData()
{
	std::ifstream records;
	std::string line, temp_string;
	std::vector<std::string>* v_ptr = new std::vector<std::string>;
	int column = 0;

	records.open("records.csv");

	if (records.good())
	{
		while (std::getline(records, line))
		{
			std::stringstream ss(line);
			while (!ss.eof())
			{
				std::getline(ss, temp_string, ',');

				// We say if 'column' is above 3 so it skips the first line of the csv file
				if (column > 3)
					(*v_ptr).push_back(temp_string);

				column++;
			}
		}
	}
	else
		std::cout << "\nError opening records.csv, check file is not already open.\n";
	
	records.close();
	return *v_ptr;
}

void Record::DeleteRecordFile()
{
	std::remove("records.csv");
}

void Record::Search(std::string user_data)
{
	std::ifstream records;
	std::string line, temp_string;
	std::string acc_details[4];
	bool flag = false;
	int count = 0;
	records.open("records.csv", std::ios::in);

	if (records.good())
	{
		while (std::getline(records, line))
		{
			std::stringstream ss(line);
			while (!ss.eof())
			{
				std::getline(ss, temp_string, ',');

				if (count == 4)
					break;

				if (temp_string == user_data)
				{
					flag = true;

					// We need to get the entire line again because names are in the middle of the row in a csv file
					std::stringstream ss(line);
					while (std::getline(ss, temp_string, ','))
					{
						acc_details[count] = temp_string;
						count++;
					}
				}
			}
		}
	}
	else
		std::cout << "\nError opening records.csv, check file is not already open.\n";

	records.close();

	if (flag == true)
	{
		std::cout << "\n\n***ACCOUNT FOUND***\n";
		std::cout << "Account number:  " << acc_details[0] << "\n";
		std::cout << "First name:      " << acc_details[1] << "\n";
		std::cout << "Last name:       " << acc_details[2] << "\n";
		std::cout << "Account balance: " << acc_details[3] << "\n\n";
	}
	else
		std::cout << "\nCould not find account details.\n\n";

	PAUSE;
}