#include "stdafx.h"
#include "Home.h"
#include "Room.h"
#include "ManagerScreen.h"


Room::Room(
    std::unique_ptr< const Home >  home,
    const std::string&  name,
    size_t              timelimit,
    energy_t            needEnergy,
    const area_t&       area
) :
    mHome( std::move( home ) ),
    name( name ),
    timelimit( timelimit ),
    needEnergy( needEnergy ),
    area( area ),
    // ���������� ��������������� "�����������"
    mSeed( 11 )
{
    DASSERT( mHome );
    DASSERT( !name.empty() );
    DASSERT( timelimit > 0 );
    DASSERT( needEnergy > 0 );
    DASSERT( !area.empty() );

    // ���������� ���� � ��������� ��������� � �������
    const auto ms = ManagerScreen::instance();
    const std::string fileXML =
        PATH_RESOURCE + "/" + ms->selectedResource.directory + "/" +
        name + "/" + name + ".xml";
    const tinyxml2::XMLError error = mXML.LoadFile( fileXML.c_str() );
    DASSERT( error == tinyxml2::XML_SUCCESS );
}




Room::~Room() {
}




std::vector< Room::Item >
Room::currentItemSet() const {

    // ������� ���������� � ��������� � ������� �� XML-����� � �������
    // ��� ��� ��������� ������������ �������� ��������� 'mSeed'
    std::vector< Item >  r;

    const auto room = mXML.FirstChildElement( "room" );
    DASSERT( room );

    // # ��������� �������� ����� �������� ����� ��. ���������: �� ���������
    //   �����������.
    typedef std::pair< int, int >  pairID_t;
    std::vector< pairID_t >  integrity;
    const auto intersections = room->FirstChildElement( "intersections" );
    DASSERT( intersections );
    for (auto intersectionIds = intersections->FirstChildElement( "intersectionIds" );
         intersectionIds;
         intersectionIds = intersectionIds->NextSiblingElement( "intersectionIds" )
    ) {
        std::istringstream  ss( intersectionIds->GetText() );
        std::string  id1;
        std::getline( ss, id1, ',' );
        DASSERT( !id1.empty()
            && "��������� 2 ��������������." );
        std::string  id2;
        std::getline( ss, id2, ',' );
        DASSERT( !id2.empty()
            && "��������� 2 ��������������." );

        const pairID_t  pairID( std::atoi( id1.c_str() ),  std::atoi( id2.c_str() ) );
        integrity.push_back( pairID );

    } // for (auto intersectionIds = ...


    // ����� ������ ��� ���������� � ������� ��������
    std::vector< int /* slot id */ >  located;


    const auto items = room->FirstChildElement( "items" );
    DASSERT( items );
    for (auto item = items->FirstChildElement( "item" );  item;
         item = item->NextSiblingElement( "item" )
    ) {
        const auto name = item->Attribute( "name" );
        DASSERT( name );
        const auto clipName = item->Attribute( "clipName" );
        DASSERT( clipName );

        const auto sax = item->Attribute( "s_a_x" );
        DASSERT( sax );
        const auto say = item->Attribute( "s_a_y" );
        DASSERT( say );
        const coord_t  searchTextureCoord( std::atoi( sax ), std::atoi( say ) );

        const auto saw = item->Attribute( "s_a_w" );
        DASSERT( saw );
        const auto sah = item->Attribute( "s_a_h" );
        DASSERT( sah );
        const dimension_t  searchTextureSize( std::atoi( saw ), std::atoi( sah ) );

        // ������� ��� ����� ��� ����� ��������
        std::vector< Item::Slot >  slots;
        for (auto slot = item->FirstChildElement( "slot" );  slot;
             slot = slot->NextSiblingElement( "slot" )
        ) {
            const auto addName = slot->Attribute( "addName" );
            DASSERT( addName );
            const auto id = slot->Attribute( "id" );
            DASSERT( id );

            const auto rx = slot->Attribute( "r_x" );
            DASSERT( rx );
            const auto ry = slot->Attribute( "r_y" );
            DASSERT( ry );
            const coord_t  location( std::atof( rx ), std::atof( ry ) );

            const auto ax = slot->Attribute( "a_x" );
            DASSERT( ax );
            const auto ay = slot->Attribute( "a_y" );
            DASSERT( ay );
            const coord_t  textureCoord( std::atoi( ax ), std::atoi( ay ) );

            const auto aw = slot->Attribute( "a_w" );
            DASSERT( aw );
            const auto ah = slot->Attribute( "a_h" );
            DASSERT( ah );
            const dimension_t  textureSize( std::atoi( aw ), std::atoi( ah ) );

            const Item::Slot is = {
                static_cast< std::string >( addName ),
                std::atoi( id ),
                location,
                textureCoord,
                textureSize
            };
            slots.push_back( is );

            // @todo optimize ������� ������ ��������� ����.

        } // for (auto slot = item->FirstChildElement( "slot" ); ...

        // ������� ���� ���� (���������� ��������), �������� ������ ����������
        size_t countFor = 0;
        size_t i;
        for (i = rand() % slots.size();  ; i = rand() % slots.size()) {
            const int id = slots[ i ].id;
            bool alreadyLocated = false;
            for (auto ltr = located.cbegin(); ltr != located.cend(); ++ltr) {
                const int lid = *ltr;
                for (auto itr = integrity.cbegin(); itr != integrity.cend(); ++itr) {
                    const auto ids = *itr;
                    alreadyLocated =
                           ((ids.first == id)  && (ids.second == lid))
                        || ((ids.first == lid) && (ids.second == id));
                    // ������� ������ ����
                    if ( alreadyLocated ) { break; }
                }

                // ������� ������ ����
                if ( alreadyLocated ) { break; }

            } // for (auto ltr = located.cbegin(); ...

            if ( !alreadyLocated ) {
                // ���� �� ������������ 'integrity'
                break;
            } else {
                // �� ���� ����� ��� ���������� �������
                const bool test = true;
            }

            // ������������ ������ � XML: ����� ������ �� ������������
            // ��������� ������
            DASSERT( (++countFor < 100)
                && "��� ��������� ������. ��������� ����������� � ���������� XML." );

        } // for (i = rand() % slots.size(); ...


        // id ���������� ���� ����� ��������
        const Item::Slot& slot = slots[ i ];
        located.push_back( slot.id );

        const Item item = {
            name,
            clipName,
            searchTextureCoord,
            searchTextureSize,
            slot,
            // # ������ ������ ��� �������� �����.
            nullptr
        };
        r.push_back( item );
    }

    return r;
}








std::ostream&
operator<<( std::ostream& out,  const Room::Item& item ) {

    out << item.slot.id << "\t" << item.slot.location << "\t" <<
        item.name << " " << (item.clipName + item.slot.addName);

    return out;
}
