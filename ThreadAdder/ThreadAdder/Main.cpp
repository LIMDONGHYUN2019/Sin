#include<iostream>
#include<tchar.h>
#include<Windows.h>

using namespace std;

static int total = 0;

DWORD WINAPI ThreadProc(LPVOID lpPraram)
{
	DWORD* ptr = (DWORD*)lpPraram;
	DWORD numone = *ptr;
	DWORD numtwo = *(ptr + 1);

	for (DWORD i = numone; i <= numtwo; i++)
	{
		total += i;
	}

	return 0;
}

int main()
{
	DWORD dwThreadID[3];
	HANDLE hThread[3];

	DWORD paramThread[] = { 1,3,4,7,8,10 };

	hThread[0] = CreateThread(NULL, 0,
		ThreadProc, (LPVOID)(&paramThread[0]),
		0, &dwThreadID[0]);

	hThread[1] = CreateThread(NULL, 0,
		ThreadProc, (LPVOID)(&paramThread[2]),
		0, &dwThreadID[1]);

	hThread[2] = CreateThread(NULL, 0,
		ThreadProc, (LPVOID)(&paramThread[4]),
		0, &dwThreadID[2]);

	if (hThread[0] == NULL || hThread[1] == NULL || hThread[2] == NULL)
	{
		_tprintf(_T("Thread creation fault!!!! \n"));
		return -1;
	}

	WaitForMultipleObjects(3, hThread, TRUE, INFINITE);

	_tprintf(_T("total  (1  ~  10) : %d  \n"), total);

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hThread[2]);

	return 0;

}