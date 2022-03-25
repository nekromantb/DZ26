#include "task1.h"
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <map>
#include <fstream>
#include <iomanip>
#include <cassert>

enum condition
{
    STOP,
    PLAY,
    PAUSE
};

class Track
{
    std::string name;
    std::time_t t = std::time(nullptr);
    std::tm* date = std::localtime(&t);
    double duration = 0;

public:

    void getTrackInfo ()
    {
        std::cout << "Track " << name <<" created "<< std::put_time(date, "%d.%m.%y %M:%S") << ", duration is " << duration <<std::endl;
    }

    double getTrackDuration()
    {
        return duration;
    }

    void setTrackDuration(double input)
    {
        duration = input;
    }

    void setTrackName (std::string input)
    {
        name = input;
    }

};

class Player
{
    int condition = STOP;
    std::map<std::string, Track> library_name;
    std::time_t start_playing = std::time(nullptr) ;
    Track playing_now ;
    int size = 1;

public:

    int getPlayerCondition ()
    {
        return condition;
    }

    void play_track()
    {
        if (playing_now.getTrackDuration()-(std::time(nullptr)-start_playing)<=0) condition = STOP;
        if (condition == STOP)
        {
            std::string input;
            std::cout << "Enter track name:" << std::endl;
            std::cin >> input;
            auto it = library_name.find(input);
            playing_now = it->second;
            playing_now.getTrackInfo();
            condition = PLAY;
            start_playing = std::time(nullptr);
        }
        else if (condition == PAUSE)
        {
            std::cout << "Resuming playing" << std::endl;
            condition = PLAY;
            playing_now.getTrackInfo();
            start_playing = std::time(nullptr);
        }
    }

    void pause_track()
    {
        if (playing_now.getTrackDuration()-(std::time(nullptr)-start_playing)<=0) condition = STOP;
        if (condition == PLAY)
        {
            playing_now.setTrackDuration(playing_now.getTrackDuration()-(std::time(nullptr)-start_playing));
            assert (playing_now.getTrackDuration() >=0);
            condition = PAUSE;
            std::cout << "Pause."<< std::endl;
        }
    }

    void stop_track()
    {
        if (playing_now.getTrackDuration()-(std::time(nullptr)-start_playing)<=0) condition = STOP;
        if (condition != STOP)
        {
            condition == STOP;
            std::cout << "Stop."<< std::endl;
        }
    }

    void next_track()
    {
        if (playing_now.getTrackDuration()-(std::time(nullptr)-start_playing)<=0) condition = STOP;
        std::srand (std::time (nullptr));
        auto it = std::next(library_name.begin(), (std::rand() % size));
        playing_now = it->second;
        playing_now.getTrackInfo();
        condition = PLAY;
        start_playing = std::time(nullptr);
    }

    void initialization()
    {
        std::ifstream library ("G:\\work\\Prog\\progs\\DZ26\\library.txt");
        while (!library.eof())
        {
            std::string tr_name;
            double tr_dur;
            Track input;
            library >> tr_name >>tr_dur;
            input.setTrackName(tr_name);
            input.setTrackDuration(tr_dur);
            library_name.insert(std::pair<std::string, Track> (tr_name, input));

        }
        library.close();
        size = library_name.size();
    }
};

void task1()
{
    std::cout << "Player welcomes you!" <<std::endl;
    std::cout << "Commands are \"play\", \"stop\", \"next\", \"pause\", \"exit\"" << std::endl;
    Player* player = new Player();
    player->initialization();
    while (1)
    {
        std::string command;
        std::cin >> command;
        if (command == "play")
            player->play_track();
        else if (command == "stop")
            player->stop_track();
        else if (command == "pause")
            player->pause_track();
        else if (command == "next")
            player->next_track();
        else if (command == "exit")
            break;
    }
    delete player;
    player = nullptr;
    delete player;
}