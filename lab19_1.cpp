#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream import(filename);
    string line;
    char format[] = "%[^:]: %d %d %d";
    while(getline(import,line)){
        char t[100];
        int score1, score2, score3;
        sscanf(line.c_str(), format, t, &score1, &score2, &score3);
        names.push_back(t);
        int total = score1 + score2 + score3;
        scores.push_back(total);
        grades.push_back(score2grade(total));
    }
    import.close();
    
}

void getCommand(string &command, string &key){
    string c1;
    char ca[100];
    char ka[100];
    char format[]="%s %[^\n]";
    cout << "Please input your command: ";
    getline(cin,c1);
    sscanf(c1.c_str(),format,ca,ka);
    command = ca;
    key = ka;
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    cout << "---------------------------------\n";
    int x = -1;
    for(unsigned int i = 0; i < names.size(); i++){
        if(toUpperStr(names.at(i)) == key){
            x = i;
        }  
    }
    if(x != -1){
        cout<<names.at(x)<<"'s score = "<<scores.at(x)<<endl;
        cout<<names.at(x)<<"'s grade = "<<grades.at(x)<<endl;
    }else{
        cout<<"Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < names.size(); i++){
        if(grades.at(i) == *key.c_str()){
            cout << names.at(i) << " (" << scores.at(i) << ")\n";
        }
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
