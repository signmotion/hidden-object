#pragma once

#include "structure.h"


class AppDelegate;
class Home;
class Store;


// ���������� �� ������.
class Player {
public:
    // �����, ���������� �� ������������ �������.
    typedef std::pair< size_t /* min */, size_t /* sec */ >  restTime_t;


    const std::string  login;


private:
    Player(
        const std::string&             login,
        std::unique_ptr< const Home >  home
    );


public:
    static inline Player* instance() {
        DASSERT( mInstance
            && "����� ������ ���� ����������� �� ��������� � instance()." );
        return mInstance;
    }


    virtual ~Player();


    // @return ������� ������� ������.
    inline energy_t energy() const { return mEnergy; }


    // @return �����, ����� ��������� ��������� ���������� �������, ���.
    inline size_t lastTimeAddEnergy() const { return mLastTimeAddEnergy; }


    // ���������� ��� ���������� �������.
    void addEnergy();


    // ���������� ��� ���������� ������� (��� ��������� � �������).
    void subEnergy();


    // @return �������, � ������� ��������� ����� ��� � ������� ���������� �����.
    inline void room( const std::string& name ) { mRoom = name; }

    inline std::string room() const { return mRoom; }


    // @return ����� ������� �� ������������ �������, ���.
    inline void timelimit( size_t limit ) { mTimelimit = limit; }

    inline size_t timelimit() const { return mTimelimit; }


    // @return �����, ���������� �� ������������ �������, ���.
    inline void restTime( size_t rt ) { mRestTime = rt; }

    inline size_t restTime() const { return mRestTime; }


    // @return ���������� ��������� � ������� ���������.
    inline void findItems( size_t count ) { mFindItems = count; }

    inline size_t findItems() const { return mFindItems; }


    // @return ������� ������� ���������.
    inline bool completed() const {
        return (findItems() >= COMPLETED_COUNT_ITEMS);
    }


    // @return ����������� �����, �� ������� ���� �������� �������, ���.
    size_t minTime() const;


    // ��������� ���������� �� ������������ ������� �����.
    inline void decreaseRestTime( size_t dt ) {
        if (mRestTime >= dt) { mRestTime -= dt; }
    }


    // @return ������� ����� ������ ������� ��� ������������ �������.
    energy_t needEnergy() const;


    // @return � ������ ���������� ������� ��� ����������� �������.
    bool enoughEnergy() const;


    // @return ������� ����� � ����, ��.
    inline size_t currentTime() const {
        struct cc_timeval  now;
        CCTime::gettimeofdayCocos2d( &now, nullptr );
        const auto ct = (now.tv_sec * 1000 + now.tv_usec / 1000);
        return static_cast< size_t >( ct );
    }


    // ��������� ������� �������� � �������������� ���������.
    void save();


private:
    // ���������� � ����.
    std::unique_ptr< const Home >  mHome;

    // ������� ������� ������.
    energy_t  mEnergy;

    // �����, ����� ��������� ��������� ���������� �������, ���.
    size_t  mLastTimeAddEnergy;

    // �������, � ������� ��������� ����� ��� � ������� ���������� �����.
    std::string  mRoom;

    // ����� ������� �� ������������ �������, ���.
    size_t  mTimelimit;

    // �����, ���������� �� ������������ �������, ���.
    size_t  mRestTime;

    // ���������� ��������� � ������� ���������.
    size_t  mFindItems;

    // �������������� ���������.
    std::unique_ptr< Store >  mStore;

    static Player*  mInstance;

    friend AppDelegate;
};
