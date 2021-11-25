#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include <cctype>
#include<map>
#include <time.h>//for creating clock_t objects
using namespace std;

int main(int argc, char *argv[]){
    clock_t timerStart, timerEnd;
    timerStart = clock();
	double elapsed_seconds;
    string filename = argv[1];
    int numberOfWords= atoi(argv[2]);
    int i=0;
    string s;
    ifstream inputFile;
    map<string, int>mymap={};
    if(FILE *file = fopen(filename.c_str(), "r")) {
         //Open file
    inputFile.open(filename);
    }
    else{
        cout<<"Your file could not be found.\n";
        return 0;
    }
   
    //Add all words in file to map
    while(inputFile >> s){
        //Erase punctuation
       s.erase (std::remove_if (s.begin (), s.end (), ::ispunct), s.end ());
       //Transform to uppercase
       transform(s.begin(), s.end(), s.begin(),[](unsigned char c){ return std::toupper(c); });
       //Sort strings alphabetically
       if ( mymap.find(s) == mymap.end() ) {
        // not found
        mymap.insert(pair<string,int>(s,1));

        } else {
        // found
        mymap[s]++;
        }
        i++;
    }

    //Close the input file
    inputFile.close();

    //Find most common words in map using max_element
    for(int i=0;i<numberOfWords;i++){

    using pair_type = decltype(mymap)::value_type;

    auto pr = max_element
    (
    begin(mymap), end(mymap),
    [] (const pair_type & p1, const pair_type & p2) {
        return p1.second < p2.second;
    }
    );

    cout << pr->first << '\n';
    mymap.erase(pr->first);

    }
    timerEnd = clock();
    elapsed_seconds = double(timerEnd - timerStart) / CLOCKS_PER_SEC;
	cout << "Sorted "<<i<<" words in "<<elapsed_seconds<<" seconds."<<endl;
    return 0;
}