#pragma once

#include <string>
using namespace std;

class PlaylistNode{
 public: 
  PlaylistNode()
    : uniqueID("none"),
      songName("none"),
      artistName("none"),
      songLength(0),
      nextNodePtr(nullptr)
  {
  }
  PlaylistNode(string _uniqueID, string _songName, string _artistName, int _songLength)
    : uniqueID(_uniqueID),
      songName(_songName),
      artistName(_artistName),
      songLength(_songLength),
      nextNodePtr(nullptr)
  {
  }

  void InsertAfter(PlaylistNode *);
  void SetNext(PlaylistNode *);
  void PrintPlaylistNode() const;
  
  const string &GetID() const {return uniqueID;}     
  const string &GetSongName() const {return songName;}     
  const string &GetArtistName() const {return artistName;} 
  int GetSongLength() const {return songLength;}
  PlaylistNode* GetNext() const {return nextNodePtr;}    

 private:
  string uniqueID;
  string songName;
  string artistName;
  int songLength;
  PlaylistNode* nextNodePtr;
  



};


class Playlist{
 public:
  Playlist()
    : head(nullptr),
      tail(nullptr)
  {
  }
  ~Playlist();
  
  void PrintMenu(const string &string);
  void AddSong();
  void RemoveSong();
  void ChangeSongPosition();
  void OutputFullPlaylist() const;
  void OutputSongsSpecificArtist();
  void TimeOfPlaylist();

 private:
  void DisplayOptions() const;
  PlaylistNode* head;
  PlaylistNode* tail;
  void AddSong(const string &ID, 
               const string &songName, 
               const string &artistName, 
               const int &songLength);
  void RemoveSong(const string &string);
  void ChangeSongPosition(const int &, int &);
  void OutputSongsSpecificArtist(const string &);
  
  Playlist(const Playlist &);
  Playlist & operator=(const Playlist &);
};