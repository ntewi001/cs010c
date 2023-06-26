#include "Playlist.h"
#include <iostream>

using namespace std;


Playlist::~Playlist(){
    // edge case no nodes
    if(head == nullptr){
    }
    // edge case 1 node
    else if(head == tail){
        delete head;
        head = tail = nullptr;
    }
    // more than 2 nodes
    else {
        PlaylistNode *next = head->GetNext();
        while(next != nullptr){
            delete head;
            head = next;
            next = next->GetNext();
        }
        delete head;
    }
}
// inserts the object's node after the node in the parameter
void PlaylistNode::InsertAfter(PlaylistNode *nodeAfter){
    //set parameter node's next to object's next to not lose object's next
    nodeAfter->SetNext(this->nextNodePtr);
    //set object's next to the parameter node
    this->SetNext(nodeAfter);
    
}
void PlaylistNode::SetNext(PlaylistNode *nodeAfter){
    nextNodePtr = nodeAfter;
    // sets object's next to the parameter's node
}

void PlaylistNode::PrintPlaylistNode() const{
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}



// private helper function to display options
void Playlist::DisplayOptions() const{
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl << endl;
    cout << "Choose an option:" << endl;
}

void Playlist::PrintMenu(const string &playlistTitle){
    char userInput;
    
    if(cin >> userInput){
    }
    else{
        cout << "Input Failed. Enter new input." << endl;
        cin >> userInput;
    }
        while(userInput != 'q'){
            if(userInput == 'a'){
                AddSong();
            }
            else if(userInput == 'd'){
                RemoveSong();
            }
            else if(userInput == 'c'){
                ChangeSongPosition();
            }
            else if(userInput == 's'){
                OutputSongsSpecificArtist();
            }
            else if(userInput == 't'){
                TimeOfPlaylist();
            }
            else if(userInput == 'o'){
                cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;
                OutputFullPlaylist();
            }

            if(cin >> userInput){
            }
            else{
                cout << "Input Failed. Enter new input." << endl;
                cin >> userInput;
            }
            cin.ignore();
            
            if(userInput != 'q'){
                cout << playlistTitle << " PLAYLIST MENU" << endl;
                DisplayOptions();
            }
        }
        cout << playlistTitle << " PLAYLIST MENU" << endl;
        DisplayOptions();
}

void Playlist::AddSong(){

    string songID;
    string songName;
    string artistName;
    int songLength;

    cout << "ADD SONG" << endl;
    cout << "Enter song's unique ID:" << endl;
    cout << "Enter song's name:" << endl;
    cout << "Enter artist's name:" << endl;
    cout << "Enter song's length (in seconds):" << endl << endl;

    if(cin >> songID){
        cin.ignore(1);
    }
    else{
        cout << "Input Failed. Enter new input." << endl;
        cin >> songID;
    }
    getline(cin, songName);
    if(cin.fail()){
        cout << "Input Failed";
        getline(cin,songName);
    }
    getline(cin, artistName);
    if(cin.fail()){
        cout << "Input Failed";
        getline(cin, artistName);
    }
    if(cin >> songLength){
    }
    else{
        cout << "Input Failed. Enter new input." << endl;
        cin >> songLength;
    }
    cin.ignore(1);
    AddSong(songID, songName, artistName, songLength);
}

void Playlist::AddSong(const string &ID, const string &songName, const string &artistName, const int &songLength){
    PlaylistNode *newSong = new PlaylistNode(ID, songName, artistName, songLength);
    // if there is an empty playlist
    if(head == nullptr){
        head = tail = newSong;
    }
    // more than one node
    else {
        tail->InsertAfter(newSong);
        tail = newSong;
    }

}

void Playlist::RemoveSong(){
    string userInput;
    cout << "REMOVE SONG" << endl;
    cout << "Enter song's unique ID:" << endl;

    getline(cin,userInput);
    if(cin.fail()){
        cout << "Input Failed. Enter new input." << endl;
        getline(cin,userInput);
    }
    RemoveSong(userInput);
}

// private helper
void Playlist::RemoveSong(const string &songID) {
    // edge case: if no nodes do nothing
    if(head == nullptr){
    }
    // edge case: if one node then delete if songID is equal to the head's and then dellallocate
    else if(head == tail){
        if(songID == head->GetID()){
            cout << "\"" << head->GetSongName() << "\"" << " removed." << endl;
            delete head;
            head = tail = nullptr;
        }
    }
    // cases with more than one node
    else{
        PlaylistNode *curr = head->GetNext();
        PlaylistNode *prev = head;
        while(curr != nullptr){
            // if id is found then remove id
            if(curr->GetID() == songID){
                cout << "\"" << curr->GetSongName() << "\"" << " removed." << endl << endl; 
                prev->SetNext(curr->GetNext());
                delete curr;
                curr = prev->GetNext();
            }
            // else move on to the next node until the end of list
            else{
                prev = prev->GetNext();
                curr = curr->GetNext();
            }
        }
    }
}

void Playlist::ChangeSongPosition(){
    int currPos;
    int newPos;

    //prompt user for inputs
    cout << "CHANGE POSITION OF SONG" << endl;
    cout << "Enter song's current position:" << endl;
    if(cin >> currPos){
    }
    else{
        cout << "Input Failed. Enter new input." << endl;
        cin >> currPos;
    }
    cout << "Enter new position for song:" << endl;
    if(cin >> newPos){
    }
    else{
        cout << "Input Failed. Enter new input." << endl;
        cin >> newPos;
    }

    ChangeSongPosition(currPos, newPos);
}
// newPos is not const because in the case that it is less than 1(out of bounds) we set it to 1
void Playlist::ChangeSongPosition(const int &oldPos, int &newPos){
    if(head == nullptr || head == tail){
        return;
    }
    if(newPos < 1){
        newPos = 1;
    }
    PlaylistNode *prev = nullptr;
    PlaylistNode *curr = nullptr;
    int count = 1;
    string songName;
    //search through the list for node containing oldPos and the node before it
    for(PlaylistNode *garbage = head; garbage != nullptr && count <= oldPos; garbage = garbage->GetNext()){
        prev = curr;
        curr = garbage;
        ++count;
    }
    songName = curr->GetSongName();

    //unlink the node from the list
    if(prev != nullptr){
        prev->SetNext(curr->GetNext());
    } 
    //edge case if head
    else{
        head = curr->GetNext();
    }
    //unlink's curr's next to make sure there are no dangling pointers
    curr->SetNext(nullptr);

    count = 1;
    PlaylistNode *target = nullptr;

    //search through the list for node containing newPos 
    // loop termiantes when != nullptr so that when at max will cap at the last node
    for(PlaylistNode *garbage = head; garbage != nullptr && count < newPos; garbage = garbage->GetNext()){
        target = garbage;
        ++count;
    }
    // edge case to make oldnode to head
    if(count == 1){
        curr->SetNext(head);
        head = curr;
    }
    // edge case for tail
    else if(target == tail){
        target->InsertAfter(curr);
        tail = target;
    }
    else{
        target->InsertAfter(curr);
    }
    
    cout << "\"" << songName << "\"" << " moved to position " << newPos << endl;
    cout << endl;
}

void Playlist::OutputFullPlaylist() const{
    // if list is emtpy
    if(head == nullptr){
        cout << "Playlist is empty" << endl;
    }
    // if there is one node or more in the list
    else{
        int i = 1;
        PlaylistNode *curr = head;
        while(curr->GetNext() != nullptr){
            cout << i << "." << endl;
            curr->PrintPlaylistNode();
            cout << endl;
            ++i;
            curr = curr->GetNext();
        }
        // last node without extra newline
        if(curr != nullptr){
            cout << i << "." << endl;
            curr->PrintPlaylistNode();
        }
        
    }

    cout << endl;
}

void Playlist::OutputSongsSpecificArtist(){
    // prompt inputs and then call private helper
    string artistName;
    cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
    cout << "Enter artist's name:" << endl;
    getline(cin, artistName);
    if(cin.fail()){
        cout << "Input Failed. Enter new input." << endl;
        getline(cin,artistName);
    }
    cout << endl;
    OutputSongsSpecificArtist(artistName);
}

void Playlist::OutputSongsSpecificArtist(const string &artistName){
    // if list is emtpy
    if(head == nullptr){
        cout << "Playlist is empty" << endl;
    }
    // if there is one node or more in the list
    else{
        int i = 1;
        PlaylistNode *curr = head;
        while(curr != nullptr){
            if(artistName == curr->GetArtistName()){
                cout << i << "." << endl;
                curr->PrintPlaylistNode();
                cout << endl;
            }
            ++i;
            curr = curr->GetNext();
        }        
    }
}

void Playlist::TimeOfPlaylist(){
    cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
    int sum = 0;
    for(PlaylistNode *garbage = head; garbage != nullptr; garbage = garbage->GetNext()){
        sum += garbage->GetSongLength();
    }
    cout << "Total time: " << sum << " seconds" << endl << endl;
}
