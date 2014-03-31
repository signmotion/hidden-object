#pragma once


class AppDelegate;
class HomeScene;
class RoomScene;


// ����������� ������ ����.
class ManagerScreen {
public:
    const Resource  selectedResource;


private:
    ManagerScreen( const Resource& selectedResource );


public:
    static inline ManagerScreen* instance() {
        DASSERT( mInstance
            && "�������� ������� ������ ���� ����������� �� ��������� � instance()." );
        return mInstance;
    }


    virtual ~ManagerScreen();


    void goToHome();


    void goToRoom( const std::string& name );


private:
    std::shared_ptr< HomeScene >  mHomeScene;
    std::shared_ptr< RoomScene >  mRoomScene;

    static ManagerScreen*  mInstance;

    friend AppDelegate;
};
