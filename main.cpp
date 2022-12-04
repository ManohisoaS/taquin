#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "modules/Taquin.h"
#include <map>

using namespace std;
string random_state()
{
    string full = "012345678";
    string result = "";
    int index = 0;
    while (full.length())
    {
        index = rand() % full.length();
        result += full[index];
        full.erase(index, 1);
    }
    return result;
}

// map<string,int> loadDB()
// {
//     ifstream fichier(DB_NAME);
//     map<string,int> already;
//     if (fichier)
//     {
//         string ligne;
//         string state;
//         int path_length; 
//         while (getline(fichier, ligne))
//         {
//             cout << ligne << endl;
//             state = ligne.substr(0,9);
//             cout << ligne.substr(10).c_str() <<endl;
//             path_length = int(ligne.substr(10).c_str());
//             already.insert({state, path_length});
//             cout << state << ":" <<path_length<<endl;
//         }
//     }
//     else
//     {
//         cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
//     }
//     return already;
// }

int main()
{
    srand(time(0));
    string initial_state = "";
    Taquin taquin;
    // map<string, int> already_finished = {};
    // loadDB();

    // pour tester
    initial_state = "123456078";
    taquin.state = initial_state;
    taquin.solve();
    taquin.show_story();
    taquin.write_inDb();

    // initial_state = random_state();
    // cout << initial_state << endl;

    return 0;
}
