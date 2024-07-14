
#ifndef EMP_H
#define EMP_H
#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <cryptopp/rsa.h>
#include "crypto.h"
using namespace std;
using namespace CryptoPP;
void pressAnyKey(); 

class emp{
    protected: 
        string name;
        int emp_id, sal, group_id;
        std::vector<std::vector<bool>> attendance;

        bool in_office;
        ofstream offile;
        ifstream iffile;
        RSA::PublicKey publicKey;
        
    
    public:
        emp() : attendance(std::vector<std::vector<bool>>(12, std::vector<bool>(31, false))) {}
        
        void set_id(int id) {
            emp_id = id;
            try
            {
                /* code */
                this->readFromFile();

            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }            
        }

        virtual void login() ;
        virtual emp insert(int id);
        virtual  void menu();
        void check_attendance();
        void check_details();
        void check_in();
        void check_out();
        emp search_record(int id);
        void view_monthly_attendance(int month);
        void view_yearly_attendance();
        void view_monthly_salary(int month);
        void view_yearly_salary();
        void disableEcho(bool enable);

        const std::string serializeAttendance(const std::vector<std::vector<bool>>& attendance) {
            std::ostringstream oss;
            for (const auto& month : attendance) {
                for (bool day : month) {
                    oss << (day ? '1' : '0');
                }
                oss << '|'; // delimiter for months
            }
            return oss.str();
        }

        const std::vector<std::vector<bool>> deserializeAttendance(const std::string& data) {
            std::vector<std::vector<bool>> attendance;
            std::istringstream iss(data);
            std::string monthData;

            while (std::getline(iss, monthData, '|')) {
                std::vector<bool> month;
                for (char dayChar : monthData) {
                    month.push_back(dayChar == '1');
                }
                attendance.push_back(month);
            }

            return attendance;
        }
        // void test()
        // {
        //     cout << "this just for testing" <<endl;
        //     attendance[5][6]=0;
        //     cout << attendance[5][6]<<endl;
        //     cout << "Size of vector: " << attendance.size() << endl;
        //     cout << "Size of vector: " << attendance[0].size() << endl;

        // }



    void writeToFile() {
        RSA::PublicKey publickey;
        LoadPublicKey("key/"+to_string(this->emp_id)+"public.key", publickey);
        // Serialize data
        string serializedData = to_string(emp_id) + ' ' + name + ' ' + to_string(sal) + ' ' + to_string(group_id) + ' ' + serializeAttendance(attendance);

        // Encrypt serialized data
        string encryptedData = RSAEncryptString(publickey, serializedData);

        // Save encrypted data to file
        ofstream file("data/"+to_string(this->emp_id)+ ".txt", ios::binary);
        file << encryptedData;
    }

    void readFromFile( ) {
        RSA::PrivateKey privateKey;
        LoadPrivateKey("key/"+to_string(this->emp_id)+"private.key", privateKey);
        // Read encrypted data from file
        ifstream file("data/"+to_string(this->emp_id)+ ".txt", ios::binary);
        string encryptedData;
        file.seekg(0, ios::end);
        size_t size = file.tellg();
        encryptedData.resize(size);
        file.seekg(0);
        file.read(&encryptedData[0], size);


        // Decrypt data
        string decryptedData = RSADecryptString(privateKey, encryptedData);
        string serializedAttendance;
        // Deserialize decrypted data
        istringstream iss(decryptedData);
        iss >> emp_id >> name >> sal >> group_id >> serializedAttendance;
        attendance = deserializeAttendance(serializedAttendance);
        
    }

        void print_details() {
            cout << "Name: " << name << endl;
            cout << "Employee ID: " << emp_id << endl;
            cout << "Salary: " << sal << endl;
            cout << "Group ID: " << group_id << endl;
            cout << "Attendance: " << serializeAttendance(attendance) << endl;
            cout << "monthly_attendance(int month): "<<endl;
            cout << "yearly_attendance: "<<endl;
            cout << "monthly_salary(int month): "<<endl;
            cout << "yearly_salary: "<<endl;
           
        }
         void changeAttendance() {
            size_t month, day;
            char newAttendance;
            std::cout << "Enter the month (0-11): ";
            std::cin >> month;
            std::cout << "Enter the day (0-30): ";
            std::cin >> day;
            std::cout << "Enter new attendance (1 for present, 0 for absent): ";
            std::cin >> newAttendance;

            if (month < attendance.size() && day < attendance[month].size()) {
                attendance[month][day] = (newAttendance == '1');
            } else {
                std::cout << "Invalid input. Please enter valid month and day." << std::endl;
            }
        }
        friend class admin;
    };

class admin : public emp {
public:
    void login() override;
    void menu() override;
    void del();
    void modify();
    void search_group();
    void search_attendance();
    void show_group();
    void insert();
    void view_monthly_attendance(int month);
    void view_yearly_attendance();
    void view_monthly_salary(int month);
    void view_yearly_salary();
    emp create_emp();
    void delete_emp(int id);

};
void disableEcho(bool enable);
#endif 