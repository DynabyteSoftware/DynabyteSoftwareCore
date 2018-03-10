#include "Console.h"
#include <iostream>

#ifdef WIN32
//#include <cstdio>
#include <Windows.h>

static HANDLE STDIN = GetStdHandle(STD_INPUT_HANDLE);
static const size_t RECORD_SIZE = 1;
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
  #endif

  if(!intercept)
    cout << keyChar;
  return {modifiers, key};
}