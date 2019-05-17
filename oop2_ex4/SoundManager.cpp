//---- include section ------
#include "SoundManager.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <exception>
#include "LoadResourceException.h"

//---- using section --------
using Json = nlohmann::json;

GUI::SoundManager& GUI::SoundManager::getInterface()
{
	static SoundManager soundManager;
	return soundManager;
}

void GUI::SoundManager::playSound(const string& name, float pitch)
{
	// check if have this sound
	auto it = m_soundsBuffers.find(name);
	if (it == m_soundsBuffers.end())
		throw LoadResourceException("Cannot find the sound with name=" + name);
	// load sound
	sf::Sound& mediaPlayer = findFreeMediaPlayer();
	mediaPlayer.setPitch(pitch);
	mediaPlayer.setBuffer(it->second);
	// play sound
	mediaPlayer.play();
}

void GUI::SoundManager::playBackgroundMusic(const string& name)
{
	// check if have this sound
	auto it = m_backMusics.find(name);
	if (it == m_backMusics.end())
		throw LoadResourceException("Cannot find the background music with name=" + name);
	// load music
	if(!m_backMusicPlayer.openFromFile(it->second))
		throw LoadResourceException("Cannot load music from file =" + it->second);
	// play background music
	m_backMusicPlayer.play();
}

void GUI::SoundManager::stopBackgroundMusic()
{
	m_backMusicPlayer.stop();
}

string GUI::SoundManager::toString() const
{
	string soundsStr = "SoundManager: { soundsNames={ ";
	int count = 0;
	for (auto it = m_soundsBuffers.cbegin(); it != m_soundsBuffers.cend(); ++it) {
		soundsStr += it->first;
		if(count + 1 < static_cast<int>(m_soundsBuffers.size()))
			soundsStr += ", ";
		count++;
	}
	soundsStr += " }, backgroundMusicNames={ ";
	count = 0;
	for (auto it = m_backMusics.cbegin(); it != m_backMusics.cend(); ++it) {
		soundsStr += it->first;
		if (count + 1 < static_cast<int>(m_backMusics.size()))
			soundsStr += ", ";
		count++;
	}
	soundsStr += " }, num of media players=" + std::to_string(m_mediaPlayers.size()) + " " + ResourceLoader::toString() + " }";
	return soundsStr;
}

GUI::SoundManager::SoundManager()
{
	m_backMusicPlayer.setLoop(true);
	loadSoundsBuffers();
	loadBackgroundMusics();
}

void GUI::SoundManager::loadSoundsBuffers()
{
	// sounds directory
	string soundsDir = "sounds";
	// open JSON file
	string jsonFilePath = soundsDir + "/sounds.json";
	std::ifstream jsonFile(jsonFilePath);
	if (!jsonFile.is_open())
		throw LoadResourceException("Cannot open file " + jsonFilePath);

	// try parse JSON
	try {
		// load sounds buffers from JSON to map
		Json soundsJson;
		jsonFile >> soundsJson;

		// parse JSON to sounds map
		Json& jsonSoundsObj = soundsJson["sounds"];
		// iterate the sounds array
		for (Json::const_iterator it = jsonSoundsObj.cbegin(); it != jsonSoundsObj.cend(); ++it) {
			// get sound info
			const Json& jsonSoundObj = *it;
			string name = jsonSoundObj["name"].get<string>();
			string path = jsonSoundObj["path"].get<string>();
			// add sound buffer to map
			m_soundsBuffers[name] = sf::SoundBuffer();
			string soundPath = soundsDir + "/" + path;
			if(!m_soundsBuffers[name].loadFromFile(soundPath))
				throw LoadResourceException("Cannot load the sound from path " + soundPath);
		}
	}
	catch (const nlohmann::detail::parse_error& ex) { // error when parse JSON
		throw LoadResourceException("Cannot parse the JSON file " + jsonFilePath + ", the error: " + ex.what());
	}
}

void GUI::SoundManager::loadBackgroundMusics()
{
	// sounds directory
	string soundsDir = "sounds";
	// open JSON file
	string jsonFilePath = soundsDir + "/back_musics.json";
	std::ifstream jsonFile(jsonFilePath);
	if (!jsonFile.is_open())
		throw LoadResourceException("Cannot open file " + jsonFilePath);

	// try parse JSON
	try {
		// load sounds buffers from JSON to map
		Json soundsJson;
		jsonFile >> soundsJson;

		// parse JSON to sounds map
		Json& jsonSoundsObj = soundsJson["back_musics"];
		// iterate the sounds array
		for (Json::const_iterator it = jsonSoundsObj.cbegin(); it != jsonSoundsObj.cend(); ++it) {
			// get sound info
			const Json& jsonSoundObj = *it;
			string name = jsonSoundObj["name"].get<string>();
			string path = jsonSoundObj["path"].get<string>();
			// add to map		
			string musicPath = soundsDir + "/" + path;
			m_backMusics[name] = musicPath;
		}
	}
	catch (const nlohmann::detail::parse_error& ex) { // error when parse JSON
		throw LoadResourceException("Cannot parse the JSON file " + jsonFilePath + ", the error: " + ex.what());
	}
}

sf::Sound& GUI::SoundManager::findFreeMediaPlayer()
{
	// check free media player
	for (auto& mediaPlayer : m_mediaPlayers) {
		if (mediaPlayer.getStatus() != sf::SoundSource::Status::Playing)
			return mediaPlayer;
	}
	// create new media player
	m_mediaPlayers.push_back(sf::Sound());
	return m_mediaPlayers[m_mediaPlayers.size() - 1]; // return last media player
}
