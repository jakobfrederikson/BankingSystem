// -------------------------
// This file includes main()
// -------------------------
// Program by Jakob Frederikson 
// Github: https://github.com/jakobfrederikson
// 
// This is my first attempt at following a style guide: https://google.github.io/styleguide/cppguide.html
//
// --------------------------------------------------------------------------------------------------------

// Standard include
#include <iostream>
#include <fstream>
#include <filesystem>
#include "Record.h"

void MainScreen();
void CreateFile();

int main()
{    
    CreateFile();
    MainScreen();
}

void MainScreen()
{
    int choice = 0;
    Record r;
    do
    {
        std::cout << "**Banking Account Information System**\n";
        std::cout << "Select an option below:\n";
        std::cout << "\t\t[1] Add record to file\n";
        std::cout << "\t\t[2] Show all records from file\n";
        std::cout << "\t\t[3] Search for a record\n";
        std::cout << "\t\t[4] Update a record\n";
        std::cout << "\t\t[5] Delete a record\n";
        std::cout << "\t\t[6] Wipe record.csv [REMOVE WHEN FINISHED WITH PROGRAM]\n";
        std::cout << "\t\t[7] Quit\n";
        std::cout << "Enter your choice: ";

        try
        {
            std::cin >> choice;

            if (!std::cin) throw std::string("Error");
            else
                switch (choice)
                {
                case 1:
                    CLEAR;
                    r.AddRecordToFile();
                    break;
                case 2:
                    CLEAR;
                    r.ShowRecordsInFile();
                    break;
                case 3:
                    CLEAR;
                    r.SearchRecordInFile();
                    break;
                case 4:
                    CLEAR;
                    r.UpdateExistingRecord();
                    break;
                case 5:
                    CLEAR;
                    r.DeleteExistingRecord();
                    break;
                case 6:
                    r.DeleteRecordFile();
                    break;
                case 7:
                    break;
                default:
                    std::cout << "\nError: Please enter a value between 1-6.\n\n";
                    PAUSE;
                    break;
                }
        }
        catch (std::string e)
        {
            std::cout << "\nError: Please enter an integer between 1-6.\n\n";

            // Clear the input stream
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            PAUSE;
        }
       
        // clear screen regardless of user choice
        CLEAR;
    } while (choice != 7);
}

// If the project does not already contain 'record.csv', then create it with the file headers.
void CreateFile()
{
    if (!std::filesystem::exists("records.csv"))
    {
        std::fstream records_file("records.csv");

        if (!records_file.good())
        {
            std::ofstream outfile("records.csv", std::ios::out);

            // csv file headers
            outfile << "ACCOUNT_NUMBER" << "," << "F_NAME" << "," << "L_NAME" << "," << "ACCOUNT_BALANCE" << std::endl;
            outfile.close();
        }
        records_file.close();
    }
}