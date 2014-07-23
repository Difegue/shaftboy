#ifndef DEF_MUSOC
#define DEF_MUSOC

/*

*/
#include <SFML/Audio/Export.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Time.hpp>
#include <limits>

class MusicLoop : public sf::Music
{
/*public:

	Music2();
	Music2(sf::Time beg, sf::Time end);
	bool setLoop(sf::Time beg, sf::Time end);*/

public:

    MusicLoop() :myStart(0), myEnd(std::numeric_limits<std::size_t>::max()), myCurrentPosition(0)
    {
		setVolume(70);
    }

    void setStart(std::size_t sample)
    {
        myStart = sample;
    }

    void setEnd(std::size_t sample)
    {
        myEnd = sample;
    }

private:

	std::size_t myStart;
    std::size_t myEnd;
    std::size_t myCurrentPosition;

    virtual bool onGetData(Chunk& data) //Activates when we get stream data from the original file
    {
        if (sf::Music::onGetData(data))
        {
            // calculate the new position (in sample)
            std::size_t current = data.sampleCount + myCurrentPosition;
            if (current <= myEnd)
            {
                // we're still in [myStart, myEnd], update the current position
                // and leave the returned chunk unchanged
                myCurrentPosition = current;
                return true;
            }
            else
            {
                // we've reached myEnd, adjust the number of samples returned
                // and notify the base class that we need to loop
                data.sampleCount = myEnd - myCurrentPosition;
                myCurrentPosition = myEnd;
                return false;
            }
        }
        else
        {
            // base class requested to stop playback
            return false;
        }
    }

    std::size_t time2Sample(sf::Time time)
    {
        return static_cast<std::size_t>((time.asSeconds()) * getSampleRate() * getChannelCount());
    }

    sf::Time sample2Time(std::size_t sample)
    {
        float zawa = static_cast<float>(sample / getSampleRate() / getChannelCount());
		return sf::seconds(zawa);
    }

    virtual void onSeek(sf::Time time)
    {
        // make time relative to myStart
        myCurrentPosition = myStart + time2Sample(time);
        sf::Music::onSeek(sample2Time(myCurrentPosition));
    }





};

#endif