#pragma once

#include "structure.h"


class Room;


// ���������� � ����.
class Home : public std::enable_shared_from_this< Home > {
public:
    typedef std::set< std::string >  roomSet_t;


public:
    Home( const std::string& fileXML );

    virtual ~Home();


    // @return ������ ����������� ������� � ������.
    dimension_t sizeRoomAtlas() const;


    // @return ������ ����������� ������� � ������� ����������.
    dimension_t sizeRoomInterface() const;


    // @return ������� �������.
    scale_t scaleRoom() const;


    // @return ������ ���� ������ � ����.
    roomSet_t allRooms() const;


    // # ���� ������� � �������� ������ �� ����������, ���������� nullptr.
    std::shared_ptr< Room >  room( const std::string& name ) const;


    // @return ������� ������� ���������� ������ ��� ������������ �������.
    energy_t needEnergy( const std::string& nameRoom ) const;


    // @return ������ ������� ������� ��� ������������ �������.
    bool enoughEnergy( const std::string& nameRoom ) const;


    inline const tinyxml2::XMLElement*  rootXML() const { return mXML.RootElement(); }


    // # ������� ���������� ������������� (� XML �� ������� ��������� ���������
    //   ������� == ������).
    static area_t area( const tinyxml2::XMLElement* rootArea );


    static dimension_t size( const tinyxml2::XMLElement* rootSize );


private:
    tinyxml2::XMLDocument  mXML;
};
