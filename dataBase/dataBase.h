#pragma once

#include <iostream>
#include <fstream>

using namespace std;


void saveDataBase(int score, int& save) {
    ifstream inFile("dataBase/dataBase.txt");

    int record;
    inFile >> record;

    save = record;

    inFile.close();

    if (score > record) {
        record = score;
    }

    ofstream outFile("dataBase/dataBase.txt");

    outFile << record;
    outFile.close();

}