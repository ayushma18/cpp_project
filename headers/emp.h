#pragma once


#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <termios.h>
#include <unistd.h>
using namespace std;

class emp{
    protected:
        string name;
        int emp_id, sal, group_id, attendance;
        static ofstream offile;
        static ifstream iffile;
        
    
    public:
        virtual void login() ;
        virtual  void menu();
        void check_attendance();
        void check_details();

        void writeToFile() const {
            this->offile << name << ' ' << emp_id << ' ' << sal << ' ' << group_id << ' ' << attendance << endl;
        }

        void readFromFile() {
            this->iffile >> name >> emp_id >> sal >> group_id >> attendance;
        }

        void setFilename(string filename) {
            this->offile.open(filename, ios::app);
            this->iffile.open(filename);
        }
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

    friend class emp;
};
void disableEcho(bool enable);
