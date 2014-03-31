#pragma once


class Store {
public:
    Store();


    virtual ~Store();


    // ���������� ������ � ��������� �������.
    void save( const std::string& table,  const std::string& data );




    // @return ��������� ��������� �������� ����.
    // @param room  ���� ������, ���������� ������ ���� � ������ ���������
    //        � ���� 'room'.
    // @param login ���� ������, ���������� ������ ���� � ������ ���������
    //        � ���� 'login'.
    template< typename T >
    T loadLast(
        const std::string&  table,
        const std::string&  returnField,
        const std::string&  login
    ) {
        DASSERT( !table.empty() );
        DASSERT( !returnField.empty() );

        T value = T();
        sqlite3_stmt* stmt;
        const char* tail;
        const std::string s =
            "select max( " + returnField + " ) from " + table +
            " where uid in (select max( uid ) from " + table +
                ( login.empty() ? "" : (" where login like '" + login + "'") ) +
            ")";
        const auto r = sqlite3_prepare_v2( db, s.c_str(), 1000, &stmt, &tail );
        if (r != SQLITE_OK) {
            LOG << "Can't prepare select min value, " << r << std::endl;
        }
        DASSERT( r == SQLITE_OK );
        while (sqlite3_step( stmt ) == SQLITE_ROW) {
            value = sqlite3_column_int( stmt, 0 );
            break;
        }

        return value;
    }




    // @return ��������� ���������� �������� ����.
    // ��������, ����� ��������� ������ (�����������) ����� ������������ �������.
    // @param login ���� ������, ���������� ������ ���� � ������ ���������
    //        � ���� 'login'.
    template< typename T >
    T loadMin(
        const std::string&  table,
        const std::string&  returnField,
        const std::string&  room,
        const std::string&  login
    ) {
        DASSERT( !table.empty() );
        DASSERT( !returnField.empty() );
        DASSERT( !room.empty() );

        T value = T();
        sqlite3_stmt* stmt;
        const char* tail;
        const std::string s =
            "select min( " + returnField + " ) from " + table +
            " where room like '" + room + "'" +
            ( login.empty() ? "" : (" and login like '" + login + "'") ) +
            "";
        const auto r = sqlite3_prepare_v2( db, s.c_str(), 1000, &stmt, &tail );
        if (r != SQLITE_OK) {
            LOG << "Can't prepare select min value, " << r << std::endl;
        }
        DASSERT( r == SQLITE_OK );
        while (sqlite3_step( stmt ) == SQLITE_ROW) {
            value = sqlite3_column_int( stmt, 0 );
            break;
        }

        return value;
    }



private:
    sqlite3*  db;
};
