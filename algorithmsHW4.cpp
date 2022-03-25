#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
using namespace std;

class Match {
    public:
        Match(int numPeople) {
            _listLength = numPeople + 1;

            initializeAllArrays();
            getNames();
            getPref();
            printPreferences();
            
            stableMatching();
            printIsMatched();
        }

    protected:

    #pragma region MainFunctions
        
        void initializeAllArrays() {
            boys = new string[_listLength];
            girls = new string[_listLength];
            isMatchedB = new int[_listLength];
            isMatchedG = new int[_listLength];
            fillIsMatchedWithZero();
        }

        void getNames() {
            string userInput;
            cout << "Begin entering boys names, then girls names. \n";
            for (int i = 0; i < 2; i++) {
                for (int j = 1; j < _listLength; j++) {
                    cout << takeNumReturnGender(i) << " " << j << ") ";
                    cin >> userInput;
                    if (i == 0) { boys[j] = userInput; }
                    else { girls[j] = userInput; }
                }
            }
        }

        void getPref() {
            for (int i = 0; i < 2; i++) {
                for (int j = 1; j < _listLength; j++) {
                    if (i == 0) {
                        cout << "What is " << boys[j] << "'s preferences? (enter 1 to n). \n";
                        bPref.insert(pair<int, int*>(j, fillPrefList(i)));
                    }
                    else {
                        cout << "What is " << girls[j] << "'s preferences? (enter 1 to n). \n";
                        gPref.insert(pair<int, int*>(j, fillPrefList(i)));
                    }
                }
            }
        }

        void stableMatching() {
            for (int i = 1; i < _listLength; i++) { // Choose which man is selected
                while (isMatchedB[i] == 0) { // While my man is single
                    int girl = i;
                    if (isMatchedG[girl]) {
                        isMatchedB[i];
                    }

                    //if (isMatchedG[bPref[i][j]] == 0) { // If w is single, then...
                    //    isMatchedB[i] = bPref[i][j];
                    //    isMatchedG[bPref[i][j]] = i;
                    //    break;
                    //}
                    //else { // If w is not single, then...
                    //    if (findMatchIndex(isMatchedB[i],0, j) < findMatchIndex(isMatchedG[bPref[i][j]],1,j)) { // If w is engaged with someone she prefers less than m, then engage these 2 and set old m to single
                    //        int hold = isMatchedB[i]; // guy who is divorced now
                    //        isMatchedB[i] = bPref[i][j]; // 
                    //        isMatchedG[bPref[i][j]] = i;
                    //    }
                    //    else { // If w is engaged with someone whom she prefers more than m, leave m single
                    //        continue;
                    //    }
                    //}
                }
            }
        }

        //check list of girls to see if matched
        //if matched, check gPref to see if current boy has smaller index
        //if the index is smaller, match current boy with girl (add to output array) then repeat the process with the boy who got replaced
        //if index is larger, go to the next girl in the current boys list

    #pragma endregion

    #pragma region HelperFunctions

        int findMatchIndex(int match, int gender, int person) {
            if (gender == 0) {
                for (int i = 1; i < _listLength; i++) {
                    if (bPref[person][i] == match) return i;
                }
            }
            else {
                for (int i = 1; i < _listLength; i++) {
                    if (gPref[person][i] == match) return i;
                }
            }
        }

        void fillIsMatchedWithZero() {
            for (int i = 0; i < 2; i++) {
                for (int j = 1; j < _listLength; j++) {
                    (i == 0) ? isMatchedB[j] = 0 : isMatchedG[j] = 0;
                }
            }
        }

        int* fillPrefList(int gender) {
            int userInput;
            int* currentPreferenceList = new int[_listLength];
            for (int prefCounter = 1; prefCounter < _listLength; prefCounter++) {
                cout << prefCounter << ") ";
                cin >> userInput;
                userInput = loopUntilNumValidated(userInput, prefCounter);
                currentPreferenceList[prefCounter] = userInput;
            }
            return currentPreferenceList;
        }

        string takeNumReturnGender(int gender) { return (gender == 0) ? "Boy" : "Girl"; }

        string takeNumAndGender_ReturnOppositeGenderName(int gender, int num) { return (gender == 0) ? girls[num] : boys[num]; }

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
                cout << endl;
                for (int j = 1; j < _listLength; j++) {
                    (i == 0) ? cout << boys[j] : cout << girls[j];
                }
            }
        }

        void printPreferences() {
            for (int i = 0; i < 2; i++) {
                cout << endl;
                for (int j = 1; j < _listLength; j++) {
                    if (i == 0) {
                        cout << boys[j] << "\t \t";
                        for (int count = 1; count < _listLength; count++) {
                            cout << takeNumAndGender_ReturnOppositeGenderName(i, bPref[j][count]) << "\t";
                        }
                    }
                    else {
                        cout << girls[j] << "\t \t";
                        for (int count = 1; count < _listLength; count++) {
                            cout << takeNumAndGender_ReturnOppositeGenderName(i, gPref[j][count]) << "\t";
                        }
                    }
                    cout << endl;
                }
            }
        }

        void printIsMatched() {
            for (int i = 0; i < 2; i++) {
                cout << endl;
                for (int j = 1; j < _listLength; j++) {
                    if (i == 0) { cout << isMatchedB[j] << "\t"; }
                    else { cout << isMatchedG[j] << "\t"; }
                }
            }
        }

    #pragma endregion

    private:
        int _listLength;

        string* boys;
        string* girls;

        int* manNextProposal;

        int* isMatchedB;
        int* isMatchedG;

        map<int, int*> bPref;
        map<int, int*> gPref;
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