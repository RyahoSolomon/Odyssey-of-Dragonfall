#ifndef _MUSIC_MANAGER_H_
#define _MUSIC_MANAGER_H_

#include <string>
#include <vector>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include "util.h"

class MusicManager {
public:
    void set_playlist(const std::vector<std::string>& list);
    void on_update(float delta);
    void next();
    static MusicManager* instance();

protected:
    std::vector<std::string> playlist;
    int current_index = -1;

    bool is_fading = false;
    double fade_timer = 0;
    double fade_duration = 2;

    int current_volume = 300;
    int next_volume = 0;
    int max_volume = 300;

    std::string current_alias = "bgm_current";
    std::string next_alias = "bgm_next";

    void play(const std::string& file, const std::string& alias);
    void set_volume(const std::string& alias, int volume);
    void close(const std::string& alias);

    static MusicManager* music_manager;
};

#endif // !_MUSIC_MANAGER_H_
