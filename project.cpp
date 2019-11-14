#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::find;
using std::ifstream;
using std::vector;
using std::map;

int check_diff(string temp, string password) {
    int diff_check = 0;
    if (static_cast<int>(password.size()) < static_cast<int>(temp.size())) {
        for (int i = 0; i < static_cast<int>(password.size()); i++) {
            if (password[i] != temp[i]) {
                diff_check++;
            }
        }
        diff_check += temp.size()-password.size();
    }
    else {
        for (int i = 0; i < static_cast<int>(temp.size()); i++) {
            if (temp[i] != password[i]) {
                diff_check++;
            }
        }
        diff_check += password.size()-temp.size();
    }
    return diff_check;
}
int main() {
    ifstream common_pwrds("common_passwords.txt");
    string password;
    string temp;
    int diff = 0;
    map<int,vector<string>> sim_passwords;
    cout << "Give me a password: ";
    cin >> password;
    cout << endl;
    cout << "You provided a password of " << password << endl;
    cout << "The most similar passwords to " << password << " are: " << endl;
    while (!common_pwrds.eof()){
        if(common_pwrds >> temp) {;
            diff = check_diff(temp,password); 
            if (sim_passwords.find(diff) == sim_passwords.end()) {
                vector<string> cmn_pwrd;
                cmn_pwrd.push_back(temp);
                sim_passwords.insert({diff, cmn_pwrd});
            }
            else {
                sim_passwords[diff].push_back(temp);
            }
        }
    }
    vector <string> sorted_pwds;
    for (auto v : sim_passwords.begin()->second) {
        sorted_pwds.push_back(v);
    }
    sort(sorted_pwds.begin(), sorted_pwds.end());
    for (auto elem : sorted_pwds) {
        cout << elem << ", " ;
    }
    cout << endl;
    cout << "All of which are " << sim_passwords.begin()->first  << " character(s) different." << endl;
} 