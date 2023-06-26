#include <iostream>
#include <string>

using namespace std;

#include "Playlist.h"

int main(){
    Playlist newPlaylist;
    string playlistTitle;
    // Prompt user for title of playlist
    cout << "Enter playlist's title:" << endl;
    cout << endl;
    getline(cin, playlistTitle);
    if(cin.fail()){
        cout << "Input Failed. Enter new input." << endl;
        getline(cin, playlistTitle);
    }
    newPlaylist.PrintMenu(playlistTitle);

    
    return 0;
}
