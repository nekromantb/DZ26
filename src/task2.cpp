#include "task2.h"
#include <iostream>
#include <map>
#include <cassert>
#include <fstream>
#include <vector>

bool stringIsNumber(std::string input)
{
    for (int i = 0; i<input.length();++i)
    {
        if (input[i] < '0' || input [i] > '9')
        {
            return false;
        }
    }
    return true;
}

class Number
{
    std::string number;
    std::string firstDigit = "+7";

public:

    std::string getFullNumber()
    {
        return (firstDigit+number);
    }

    std::string getNumber()
    {
        return (number);
    }

    void setNumber (std::string input)
    {
        assert(input.length() == 10 || stringIsNumber(input));
        number = input;
    }
};

class Record
{
    std::string name;
    Number number;

public:

    void newRecord()
    {
        std::string inNumber;
        std::string inName;
        std::cout << "Enter number of new contact. (10 numbers after +7 without space)" << std::endl;
        std::cin >> inNumber;
        std::cout << "Enter name of record:"<< std::endl;
        std::cin >> inName;
        name = inName;
        number.setNumber(inNumber);
        std::ofstream contacts ("G:\\work\\Prog\\progs\\DZ26\\contacts.txt", std::ios::app);
        contacts << inNumber << " " << inName << std::endl;
        contacts.close();
    }

    void loadRecord(std::string inName, Number inNumber)
    {
        name = inName;
        number = inNumber;
    }

    std::string getRecordName()
    {
        return name;
    }

    Number getRecordNumber()
    {
        return number;
    }


};

class ContactsApp
{
    std::map <std::string, Record> contactListName;
    std::map <std::string, Record> contactListNumber;

    Record findRecord()
    {
        std::string input;
        while(true)
        {
            std::cout << "Enter name or number(without +7) of subscriber:" << std::endl;
            std::cin >> input;
            if (stringIsNumber(input))
            {
                auto itr = contactListNumber.find(input);
                if (itr == contactListNumber.end())
                    std::cout << "No such record" << std::endl;
                else
                    return itr->second;
            }
            else
            {
                auto itrN = contactListName.find(input);
                if (itrN == contactListName.end())
                    std::cout << "No such record" << std::endl;
                else
                    return itrN->second;
            }
        }
    }

public:

    void initialisation()
    {
        std::ifstream contacts ("G:\\work\\Prog\\progs\\DZ26\\contacts.txt");
        std::string num,name;
        Number inNum;
        Record inRec;
        while (!contacts.eof())
        {
            contacts >> num >> name;
            inNum.setNumber(num);
            inRec.loadRecord(name, inNum);
            contactListName.insert(std::make_pair(name, inRec));
            contactListNumber.insert(std::make_pair(num, inRec));
        }
        contacts.close();
    }

    void recordAdd()
    {
        Record newRec;
        newRec.newRecord();
        contactListName.insert(std::make_pair(newRec.getRecordName(), newRec));
        contactListNumber.insert(std::make_pair(newRec.getRecordNumber().getNumber(), newRec));
    }

    void recordCall()
    {
        Record destination;
        destination = findRecord();
        std::cout << "CALL on number: " << destination.getRecordNumber().getFullNumber() << std::endl;
    }

    void recordSMS()
    {
        Record destination;
        destination = findRecord();
        std::string sms;
        std::cout << "Enter a message:" <<std::endl;
        std::cin.ignore();
        std::getline(std::cin, sms);
        std::cout << "SMS on number " << destination.getRecordNumber().getFullNumber() << " text is: " << sms <<std::endl;
    }

};

void task2()
{
    std::cout << "Telephone welcomes you!" <<std::endl;
    std::cout << "Commands are \"add\", \"call\", \"sms\", \"exit\"" << std::endl;
    ContactsApp* application = new ContactsApp();
    application->initialisation();
    while (1)
    {
        std::string command;
        std::cin >> command;
        if (command == "add")
            application->recordAdd();
        else if (command == "call")
            application->recordCall();
        else if (command == "sms")
            application->recordSMS();
        else if (command == "exit")
            break;
        std::cout << "Command:" <<std::endl;
    }
    delete application;
    application = nullptr;
    delete application;
}
