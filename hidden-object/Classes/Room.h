#pragma once

#include "structure.h"


class Home;


class Room {
public:
    // ������� � �������
    struct Item;


public:
    // �������� �������.
    // @see ���������� � home.xml.
    const std::string  name;

    // ����� ������� �� ����������� �������, ���.
    const size_t  timelimit;

    // ����������� �������, ����������� ��� ������������ �������.
    const energy_t  needEnergy;

    // ������� ������� � ����.
    const area_t  area;


public:
    Room(
        std::unique_ptr< const Home >  home,
        const std::string&  name,
        size_t              timelimit,
        energy_t            needEnergy,
        const area_t&       area
    );


    virtual ~Room();


    inline const Home*  home() const { return mHome.get(); }


    // @return �������� � �������.
    // �������� ������������� � ��������� ������, � ������ intersections (��.
    // exmpl.xml).
    // "�����������" �������� ����� ������ nextRandomSeed().
    std::vector< Item >  currentItemSet() const;


    // �������������� ��������� ����. ����� ����� ���������.
    // ������ �� ������������ ��������� � ������� - ��. nextRandomSeed
    inline void nextRandomSeed() { mSeed = rand(); }


private:
    std::unique_ptr< const Home >  mHome;

    tinyxml2::XMLDocument  mXML;

    size_t  mSeed;
};








struct Room::Item {

    struct Slot {
        // ������ ����� ���������� �������������� �������� (clipName + addName)
        std::string  addName;

        // �������� ������������� ��������
        int  id;

        // ���������� �������� � �������
        coord_t  location;

        // ������������ � ������� �������� �������� � ���������� ������
        coord_t      textureCoord;
        dimension_t  textureSize;
    };


    // ���� ����������� ��� ������� ��������
    std::string  name;

    // ������ ����� ���������� �������������� ��������
    std::string  clipName;

    // ������������ � ������ ����������� ������� �������� � ������
    // ��� ����������� �� ������ ������
    coord_t      searchTextureCoord;
    dimension_t  searchTextureSize;

    // ��������� ������������ �������� � �������
    // @see currentItemSet()
    Slot  slot;

    // ������ �� ������
    CCSprite*  sprite;
};








std::ostream& operator<<( std::ostream&,  const Room::Item& );
