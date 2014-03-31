#pragma once

#include <string>


// ���� � ����� ��������.
static const std::string  PATH_RESOURCE = "Resources";


// ���� � ����� ��������������� ��������� � �������� ������.
static const std::string  PATH_STORE = PATH_RESOURCE + "/store";
static const std::string  PLAYER_TABLE_STORE = "player";


// �������� XML-�����, � ������� ����� ���������� � ����.
static const std::string  HOME_FILE_NAME = "home.xml";


// �������� ����� ��������������� ������.
static const std::string  LOGIN = "test@email.com";


// ����������� ���-�� �������, ������� �������� ����� ��� ������� ����.
#ifdef _DEBUG
// # ����� ����� ����� � ���� �� ������.
static const size_t MIN_ENERGY = 30;
#else
static const size_t MIN_ENERGY = 0;
#endif


// ��������� ���������� ����������� ������ ������ �� �������, ���.
// ��������, ��� == 10, ������� ����������� ������ �������.
static const size_t COST_ENERGY = 10;


// ������� ��������� ����� ������ ����� � �������, ����� �������
// ��������� ����������.
// # �������� ������� ��� ������������, ����� �� ���������� ��� ��������, �
//   ������ �������� ���������.
static const size_t COMPLETED_COUNT_ITEMS = 4;


// ��� �������.
#ifdef _DEBUG
#define ASSERT(EXPR)   assert(EXPR);
#define DASSERT(EXPR)  if (!(EXPR)) __debugbreak();

#define QUOTE_(WHAT)      #WHAT
#define QUOTE(WHAT)       QUOTE_(WHAT)
#define DBG(format, ...)  printf("%s: "format, __FILE__":"QUOTE(__LINE__), ## __VA_ARGS__)

#define LOG  std::cout

#else
#define ASSERT(EXPR)      ((void)0)
#define DASSERT(EXPR)     ((void)0)
#define DBG(format, ...)  ((void)0)
#define LOG           ((void)0)

#endif
