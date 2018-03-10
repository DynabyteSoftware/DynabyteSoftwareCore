#include "Console.h"
#include <iostream>

#ifdef WIN32
//#include <cstdio>
#include <Windows.h>

static HANDLE STDIN = GetStdHandle(STD_INPUT_HANDLE);
static const size_t RECORD_SIZE = 1;
#else
#include <termios.h>
#endif

using namespace DynabyteSoftware;
using namespace std;

const ConsoleKeyInfo Console::readKey(bool intercept)
{
  ConsoleModifiers modifiers = ConsoleModifiers::None;
  ConsoleKey key;
  char keyChar;
  #ifdef WIN32
  DWORD currentConsoleMode;
  DWORD numEvents;
  INPUT_RECORD input[RECORD_SIZE];
  GetConsoleMode(STDIN, &currentConsoleMode);
  SetConsoleMode(STDIN, 0);
  FlushConsoleInputBuffer(STDIN);

  do
  {
    ReadConsoleInput(STDIN, input, RECORD_SIZE, &numEvents);
  }
  while(input->Event.KeyEvent.wVirtualKeyCode >= 16 && //we keep reading until non-modifier keys
        input->Event.KeyEvent.wVirtualKeyCode <= 18); //are pressed.

  if ((input->Event.KeyEvent.dwControlKeyState & LEFT_ALT_PRESSED) ||
      (input->Event.KeyEvent.dwControlKeyState & RIGHT_ALT_PRESSED))
  {
    modifiers |= ConsoleModifiers::Alt;
  }
  if ((input->Event.KeyEvent.dwControlKeyState & LEFT_CTRL_PRESSED) ||
    (input->Event.KeyEvent.dwControlKeyState & RIGHT_CTRL_PRESSED))
  {
    modifiers |= ConsoleModifiers::Control;
  }
  if (input->Event.KeyEvent.dwControlKeyState & SHIFT_PRESSED)
  {
    modifiers |= ConsoleModifiers::Shift;
  }
  key = (ConsoleKey)input->Event.KeyEvent.wVirtualKeyCode;
  keyChar = input->Event.KeyEvent.uChar.AsciiChar;
  SetConsoleMode(STDIN, currentConsoleMode);
  #else
  struct termios current, temp;
  tcgetattr(0, &current); /* grab old terminal i/o settings */
  temp = current; /* make new settings same as old settings */
  temp.c_lflag &= ~ICANON; /* disable buffered i/o */
  temp.c_lflag &= ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &temp); /* use these new terminal i/o settings now */
  keyChar = getchar();
  if(keyChar <= 26)
  {
    modifiers = ConsoleModifiers::Control;
    int offset = keyChar - 1;    
    keyChar = 'a' + offset;
    key = (ConsoleKey)((int)ConsoleKey::A + offset);
  }
  else if(keyChar <= 52)
  {
    modifiers = ConsoleModifiers::Alt;
    int offset = keyChar - 27;
    keyChar = 'a' + offset;
    key = (ConsoleKey)((int)ConsoleKey::A + offset);
  }
  else if(keyChar >= 'a' && keyChar <= 'z')
  {
    modifiers = ConsoleModifiers::None;
    int offset = keyChar - 'a';
    key = (ConsoleKey)((int)ConsoleKey::A + offset);
  }
  else if(keyChar >= 'A' && keyChar <= 'Z')
  {
    modifiers = ConsoleModifiers::Shift;
    key = (ConsoleKey)keyChar;
  }
  else
  {
    modifiers = ConsoleModifiers::None;
    key = (ConsoleKey)keyChar;
  }
  
  tcsetattr(0, TCSANOW, &current);
  #endif

  if(!intercept)
    cout << keyChar;
  return {modifiers, key, keyChar};
}
