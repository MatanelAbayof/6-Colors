#pragma once
//---- include section ------
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include "ResourceLoader.h"

//---- using section --------
using std::string;

namespace GUI {
/*
 * SoundManager class. 
 * this is Singleton design pattern
 */
class SoundManager : public GUI::ResourceLoader
{
public:
	// get interface
    static SoundManager& getInterface();
	// play sound (from memory)
	void playSound(const string& name, float pitch = 1.f);
	// play background music (from stream)
	void playBackgroundMusic(const string& name);
	// stop background music
	void stopBackgroundMusic();
	// convert to string
	virtual string toString() const override;
private:
	// sounds buffers map
	std::unordered_map<string, sf::SoundBuffer> m_soundsBuffers;
	// background musics map (name and path)
	std::unordered_map<string, string> m_backMusics;
	// media players
	std::vector<sf::Sound> m_mediaPlayers;
	// background music
	sf::Music m_backMusicPlayer;
	// constructor
	SoundManager();	
	// load sounds buffers from files
	void loadSoundsBuffers();
	// load background musics (name and path)
	void loadBackgroundMusics();
	// find free media player from list
	sf::Sound& findFreeMediaPlayer();
	// disable copy
	SoundManager& operator=(const SoundManager&) = delete;
	SoundManager(const SoundManager&) = delete;
};
}
