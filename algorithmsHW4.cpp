#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
using namespace std;

class Match {
    public:
        Match(int numPeople) {
            _listLength = numPeople;

            initializeAllArrays();
            getNames();
            getPref();
            printPreferences();
        }

    protected:

    #pragma region MainFunctions
        
        void initializeAllArrays() {
            boys = new string[_listLength];
            girls = new string[_listLength];
        }

        void getNames() {
            string userInput;
            cout << "Begin entering boys names, then girls names. \n";
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < _listLength; j++) {
                    cout << takeNumReturnGender(i) << " " << j + 1 << ") ";
                    cin >> userInput;
                    if (i == 0) { boys[j] = userInput; }
                    else { girls[j] = userInput; }
                }
            }
        }

        void getPref() {
            int userInput;
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < _listLength; j++) {
                    string* tempArr = new string[_listLength];
                    if (i == 0) {
                        cout << "What is " << boys[j] << "'s preferences? (enter 1 to n). \n";
                        for (int prefCounter = 0; prefCounter < _listLength; prefCounter++) {
                            cout << prefCounter + 1 << ") ";
                            cin >> userInput;
                            userInput = loopUntilNumValidated(userInput, prefCounter);
                            tempArr[prefCounter] = takeNumReturnName(i, userInput);
                        }
                        bPref.insert(pair<int, string*>(j, tempArr));
                    }
                    else {
                        cout << "What is " << girls[j] << "'s preferences? (enter 1 to n). \n";
                        for (int prefCounter = 0; prefCounter < _listLength; prefCounter++) {
                            cout << prefCounter + 1 << ") ";
                            cin >> userInput;
                            userInput = loopUntilNumValidated(userInput, prefCounter);
                            tempArr[prefCounter] = takeNumReturnName(i, userInput);
                        }
                        gPref.insert(pair<int, string*>(j, tempArr));
                    }
                }
            }
        }

    #pragma endregion

    #pragma region HelperFunctions

        string takeNumReturnGender(int gender) { return (gender == 0) ? "Boy" : "Girl"; }

        string takeNumReturnName(int gender, int num) { return (gender == 0) ? girls[num - 1] : boys[num - 1]; }

        bool isNumValid(int input) { return (input > 0 && input <= _listLength); } // If true, num is valid.

        int loopUntilNumValidated(int input, int count) {
            while (!isNumValid(input)) {
                cout << "Input is invalid, input a number from 1 to n. \n" << count + 1 << ") ";
                cin >> input;
            }
            return input;
        }

    #pragma endregion

    #pragma region PrintFunctions
        
        void printNames() {
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < _listLength; j++) {
                    (i == 0) ? cout << boys[j] : cout << girls[j];
                }
            }
        }

        void printPreferences() {
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < _listLength; j++) {
                    if (i == 0) {
                        cout << boys[j] << "\t \t";
                        for (int count = 0; count < _listLength; count++) {
                            cout << bPref[j][count] << "\t";
                        }
                    }
                    else {
                        cout << girls[j] << "\t \t";
                        for (int count = 0; count < _listLength; count++) {
                            cout << gPref[j][count] << "\t";
                        }
                    }
                    cout << endl;
                }
            }
        }

    #pragma endregion

    private:
        int _listLength;

        string* boys;
        string* girls;

        map<int, string*> bPref;
        map<int, string*> gPref;
};

int main() {
    int numberPeople;
    cout << "Enter the number of people: ";
    cin >> numberPeople;

    Match newMatch = Match(numberPeople);
}

// Write a C++ program that inputs the preference lists for a set of n boys and n girls and implements the 
// Gale-Shapely algorithm to output a stable matching.

// Have the user enter the names of the boys and girls.Then ask the user to enter the preference list for each boy and each girl. 

// When giving the preference lists for the boys(girls) have the user enter a permutation of the numbers 1, 2, ..., n, where i represents
// the ith girl(boy) who was entered by the user.

// Have your program output two tables with the boy and girl preferences and the set of (boy, girl) pairs of the stable matching for these preferences.

// In addition to submitting your source code, run your program for an example with n=5 and submit the output from this run.