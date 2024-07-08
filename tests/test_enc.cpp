#include "../headers/emp.h"
#include "../headers/crypto.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    emp obj;
    obj.set_id(1);
    obj.readFromFile();
    obj.print_details();
}