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
    ifstream file("spain_data.csv"); // Replace with the actual filename

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
        if (iss >> sno >> comma >> financialData[numDataEntries].year >> comma >> financialData[numDataEntries].interestRate >> comma >> financialData[numDataEntries].inflationRate) {
            numDataEntries++;
        } else {
            cout << "Error reading line: " << line << "\n";
        }
    }

    // Take user input for investment amount and year of investment
    double investmentAmount;
    int investedYear;

    cout << "Enter investment amount (in Peseta): ";
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

    // Calculate received money and value in invested year (Peseta)
    double effectiveRate = 1 + interestRate - inflationRate;
    double receivedMoneyPeseta = investmentAmount * effectiveRate;

    // Calculate investment growth considering interest rates and inflation rates
    for (int i = index; i < numDataEntries; i++) {
        investmentAmount *= (1.0 + financialData[i].interestRate / 100.0);
    }

    // Calculate value at invested year considering inflation rates
    for (int i = numDataEntries - 1; i >= index; i--) {
        investmentAmount *= (1.0 - financialData[i].inflationRate / 100.0);
    }

    // Convert investment amount to Euro after 2002 (1 Euro = 166 Peseta)
    if (investedYear <= 2002) {
        investmentAmount /= 166.0;
    }

    // Compare the growth rates during dictatorial and republican eras
    double valueGrowthDictatorial = receivedMoneyPeseta;
    double valueGrowthRepublican = receivedMoneyPeseta;

    for (int i = 0; i < numDataEntries; i++) {
        if (financialData[i].year <= 1975) {
            valueGrowthDictatorial *= (1.0 + financialData[i].interestRate / 100.0);
        } else {
            valueGrowthRepublican *= (1.0 + financialData[i].interestRate / 100.0);
        }
    }

    if (valueGrowthDictatorial > valueGrowthRepublican) {
        cout << "Value of money grew faster during the dictatorial era.\n";
    } else if (valueGrowthDictatorial < valueGrowthRepublican) {
        cout << "Value of money grew faster during the republican era.\n";
    } else {
        cout << "Value of money grew at the same rate during both eras.\n";
    }

    // Print the calculated values
    cout << "Investment Value: " << investmentAmount << " Euro (or currency)\n";

    return 0;
}