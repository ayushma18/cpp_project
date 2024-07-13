
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
        int emp_id, sal, group_id, attendance;
        std::vector<int> dailyAttendance; // Vector to store daily attendance
        ofstream offile;
        ifstream iffile;
        RSA::PublicKey publicKey;
        
    
    public:
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
        emp search_record(int id);
        void view_monthly_attendance(int month);
        void view_yearly_attendance();
        void view_monthly_salary(int month);
        void view_yearly_salary();
        void disableEcho(bool enable);


    void writeToFile() const {
        RSA::PublicKey publickey;
        LoadPublicKey("key/"+to_string(this->emp_id)+"public.key", publickey);
        // Serialize data
        string serializedData = to_string(emp_id) + ' ' + name + ' ' + to_string(sal) + ' ' + to_string(group_id) + ' ' + to_string(attendance);

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

        // Deserialize decrypted data
        istringstream iss(decryptedData);
        iss >> emp_id >> name >> sal >> group_id >> attendance;
    }

        void print_details() {
            cout << "Name: " << name << endl;
            cout << "Employee ID: " << emp_id << endl;
            cout << "Salary: " << sal << endl;
            cout << "Group ID: " << group_id << endl;
            cout << "Attendance: " << attendance << endl;
            cout << "monthly_attendance(int month): "<<endl;
            cout << "yearly_attendance: "<<endl;
            cout << "monthly_salary(int month): "<<endl;
            cout << "yearly_salary: "<<endl;
           
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