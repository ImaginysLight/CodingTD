#include"Audio.h"

SimpleAudioEngine* Audio::audio = SimpleAudioEngine::getInstance();

string Audio::GetBackgroundAudio()
{
	string result = "";
	vector<string> music = {
		"Audio/Czardas - Vittorio Monti Piano Transcription .mp3",
		"Audio/Canon in D Major.mp3",
		"Audio/Chaconne F Minor.mp3",
		"Audio/BWV 846 - Prelude 1 in C Major.mp3",
		"Audio/Luigi Boccherini - String Quintet in E Major, Op.11 No.5.mp3",
	};
	result = music[Tool::CreateRandomNumber(0, music.size() - 1)];

	return result;
}

string Audio::GetBrightAudio()
{
	string result = "";
	vector<string> music = {
		"Audio/Eine kleine Nachtmusik - K525.mp3",
		"Audio/Symphony no 5 mov 4.mp3"
	};
	result = music[Tool::CreateRandomNumber(0, music.size() - 1)];
	return result;
}

string Audio::GetSadAudio()
{
	string result = "";
	vector<string> music = {
		"Audio/Preludium and Allegro.mp3",
		"Audio/Prelude Op 28 No 4 in E minor.mp3",
		"Audio/BWV 1068 - Suite No. 3 in D major.mp3"
	};
	result = music[Tool::CreateRandomNumber(0, music.size() - 1)];
	return result;
}

string Audio::GetButtonClickAudio()
{
	string result = "";
	vector<string> music = {
		"Audio/Button Click 1.wav",
		"Audio/Button Click 2.wav",
		"Audio/Button Click 3.wav",
		"Audio/Button Click 4.wav",
		"Audio/Button Click 5.wav"
	};
	result = music[Tool::CreateRandomNumber(0, music.size() - 1)];
	return result;
}

string Audio::GetCorrectAudio()
{
	string result = "";
	vector<string> music = {
		"Audio/Correct 1.wav",
		"Audio/Correct 2.mp3",
		"Audio/Correct 3.wav"
	};
	result = music[Tool::CreateRandomNumber(0, music.size() - 1)];
	return result;
}

string Audio::GetBattleAudio()
{
	string result = "";
	vector<string> music = {
		"Audio/Sonata no 8 mov 3.mp3",
		"Audio/Op.10 No.4.mp3",
		"Audio/Op.25 No.12.mp3",
		"Audio/Op.25 No.11.mp3",
		"Audio/Chopin sonata no 2 mov 1",
		"Audio/Chopin sonata no 2 mov 2"
	};
	result = music[Tool::CreateRandomNumber(0, music.size() - 1)];
	return result;
}

string Audio::GetSpawnAudio()
{
	string result = "";
	vector<string> music = {
		"Audio/Spawn 1.wav",
		"Audio/Spawn 2.wav",
		"Audio/Spawn 3.wav",
		"Audio/Spawn 4.wav",
		"Audio/Spawn 5.wav"
	};
	result = music[Tool::CreateRandomNumber(0, music.size() - 1)];
	return result;
}

void Audio::UpdateAudio()
{
	if (!Audio::audio->isBackgroundMusicPlaying()) {
		Audio::audio->playBackgroundMusic(Audio::GetBackgroundAudio().c_str(), false);
	}
}
