#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

struct FinancialData {
    int year;
    double interestRate;
    double inflationRate;
};

int main() {
    ifstream file("india_data.csv");

    if (!file.is_open()) {
        cout << "Error opening file\n";
        return 1;
    }

    FinancialData financialData[100]; // Assuming a maximum of 100 data entries
    int numDataEntries = 0;

    string line;
    // reading header file
    getline(file,line);
    while (getline(file, line) && numDataEntries < 100) {
        istringstream iss(line);
        char comma;
        int sno;
        if (iss >>sno>>comma>> financialData[numDataEntries].year >> comma>>financialData[numDataEntries].interestRate >> comma>>financialData[numDataEntries].inflationRate) {
            numDataEntries++;
        } else {
            cout << "Error reading line: " << line << "\n";
        }
    }

    // Take user input for investment amount and year of investment
    double investmentAmount;
    int investedYear;

    cout << "Enter investment amount: ";
    cin >> investmentAmount;

    cout << "Enter year of investment: ";
    cin >> investedYear;

    // Search for data corresponding to the invested year
    double interestRate = 0.0;
    double inflationRate = 0.0;
    int index;
    for (int i = 0; i < numDataEntries; ++i) {
        if (financialData[i].year == investedYear) {
            index = i;
            interestRate = financialData[i].interestRate;
            inflationRate = financialData[i].inflationRate;
            break;
        }
    }

    // Calculate received money and value in invested year
    double effectiveRate = 1 + interestRate - inflationRate;
    double receivedMoney = investmentAmount * effectiveRate;

    for(int i=index;i<numDataEntries;i++)
    {
        investmentAmount = investmentAmount*(1.0 + financialData[i].interestRate/100.0);
    }
    
    cout<<investmentAmount<<"\n";

    for(int i=numDataEntries-1;i>=index;i--)
    {
        investmentAmount = investmentAmount*(1.0 - financialData[i].inflationRate/100.0);
    }
    cout<<investmentAmount<<"\n";
    return 0;
}