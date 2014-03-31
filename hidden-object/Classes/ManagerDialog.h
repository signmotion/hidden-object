#pragma once


class AppDelegate;
class AboutRoomDialog;
class ResultRoomDialog;
class NeedEnergyDialog;


// ���������� ������ ���������� ����.
class ManagerDialog {
public:
    const Resource  selectedResource;


private:
    ManagerDialog( const Resource&  selectedResource );


public:
    static inline ManagerDialog* instance() {
        DASSERT( mInstance
            && "�������� �������� ������ ���� ����������� �� ��������� � instance()." );
        return mInstance;
    }


    virtual ~ManagerDialog();


    void showAboutRoom();
    inline void closeAboutRoom() { mAboutRoomDialog.reset(); }

    void showResultRoom();
    inline void closeResultRoom() { mResultRoomDialog.reset(); }

    void showNeedEnergy();
    inline void closeNeedEnergy() { mNeedEnergyDialog.reset(); }


private:
    std::shared_ptr< AboutRoomDialog >   mAboutRoomDialog;
    std::shared_ptr< ResultRoomDialog >  mResultRoomDialog;
    std::shared_ptr< NeedEnergyDialog >  mNeedEnergyDialog;

    static ManagerDialog*  mInstance;

    friend AppDelegate;
};
