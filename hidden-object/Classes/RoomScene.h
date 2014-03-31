#pragma once

#include "Room.h"


class Home;


class RoomScene : public cocos2d::CCLayerColor {
public:
    typedef std::vector< Room::Item >  items_t;

    // ���������� ��������� � �������.
    const size_t  countAllItems;


public:
    RoomScene( std::shared_ptr< Room > room );

    virtual ~RoomScene();


    // Here's a difference. Method 'init' in cocos2d-x returns bool,
    // instead of returning 'id' in cocos2d-iphone.
    virtual bool init();


    // there's no 'id' in cpp, so we recommand to return the
    // exactly class pointer
    cocos2d::CCScene* scene();


    void update( float dt );


    virtual bool ccTouchBegan( CCTouch*, CCEvent* );
    virtual void ccTouchMoved( CCTouch*, CCEvent* );
    virtual void ccTouchEnded( CCTouch*, CCEvent* );
    virtual void ccTouchCancelled( CCTouch*, CCEvent* );
    

    inline std::shared_ptr< const Room > room() const { return mRoom; }
    inline std::shared_ptr< Room >       room()       { return mRoom; }


    // @return ��������� �� ������� � ������� ��� �� ����� ������, ����
    //         �������� �� �������� ���������� ���.
    items_t::iterator  item( const coord_t& );


    // ������� ������: ��������� �� �������.
    void collectedItem( items_t::iterator& );


private:
    //void removeItemSeq( CCObject* );
    void removeItemSeq( CCNode* );

    // @return ������ � ����� ������� ���� ������� (����������� �� ����� ����).
    bool pressTopLeftCorner( const coord_t& point ) const;

    void updateRestTime();

    // ������� ���������.
    void completedSuccess();
    void completedFailure();


private:
    std::shared_ptr< Room >  mRoom;
    items_t                  mItems;

    CCLabelTTF*  mRestTime;
};
