#include "music_manager.h"

MusicManager* MusicManager::music_manager = nullptr;
MusicManager* MusicManager::instance()
{
    if (music_manager == nullptr)
    {
        music_manager = new MusicManager();
    }
    return music_manager;
}

void MusicManager::on_update(float delta)
{
    if (!is_fading) return;

    fade_timer += delta;

    float half = fade_duration * 0.5f;

    int cur_vol = max_volume;
    int nxt_vol = 0;

    if (fade_timer <= half)
    {
        float t = fade_timer / half;
        if (t > 1.0f) t = 1.0f;

        t = t * t * (3 - 2 * t);

        cur_vol = int((1.0f - t) * max_volume);
        nxt_vol = 0;
    }
    else
    {
        float t = (fade_timer - half) / half;
        if (t > 1.0f) t = 1.0f;

        t = t * t * (3 - 2 * t);

        cur_vol = 0;
        nxt_vol = int(t * max_volume);
    }

    set_volume(current_alias, cur_vol);
    set_volume(next_alias, nxt_vol);

    if (fade_timer >= fade_duration)
    {
        close(current_alias);

        std::swap(current_alias, next_alias);

        is_fading = false;
        fade_timer = 0.0f;
    }
}


void MusicManager::play(const std::string& file, const std::string& alias)
{
    MCIERROR err = mciSendString(string_to_wstring("close " + alias).c_str(), 0, 0, 0);
    err = mciSendString(string_to_wstring("open \"" + file + "\" type mpegvideo alias " + alias).c_str(), 0, 0, 0);
    err = mciSendString(string_to_wstring("play " + alias).c_str(), 0, 0, 0);
}

void MusicManager::set_volume(const std::string& alias, int volume)
{
    mciSendString(string_to_wstring("setaudio " + alias + " volume to " + std::to_string(volume)).c_str(), 0, 0, 0);
}

void MusicManager::close(const std::string& alias)
{
    mciSendString(string_to_wstring("close " + alias).c_str(), 0, 0, 0);
}

void MusicManager::set_playlist(const std::vector<std::string>& list)
{
    playlist = list;

    if (!playlist.empty())
    {
        int next_index = 0;

        play(playlist[next_index], next_alias);
        set_volume(next_alias, 0);

        is_fading = true;
        fade_timer = 0;
        current_index = next_index;
    }
}

void MusicManager::next()
{
    if (playlist.empty()) return;

    int next_index = (current_index + 1) % playlist.size();

    play(playlist[next_index], next_alias);
    set_volume(next_alias, 0);

    is_fading = true;
    fade_timer = 0;
    current_index = next_index;
}