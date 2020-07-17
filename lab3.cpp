#include "lab3.h"
#include <windows.h>
#include <string>

#define MAX_SEM_COUNT 10

//Threads
HANDLE aThread, bThread, cThread, dThread, eThread, fThread, hThread, gThread, kThread, mThread, pThread, nThread;
//Mutex
HANDLE stdout_mutex;
DWORD IDThread;
//syhrionized sems
HANDLE semK, semP, semM;
HANDLE semA, semB;

unsigned int lab3_thread_graph_id()
{
	return 14;
}

const char* lab3_unsynchronized_threads()
{
	return "cde";
}

const char* lab3_sequential_threads()
{
	return "pkm";
}

void wait(HANDLE name) {
	WaitForSingleObject(name, INFINITE);
}

void release(HANDLE name, int count = 1)
{
	ReleaseSemaphore(name, count, NULL);
}

DWORD WINAPI a(LPVOID pVoid)
{
	for (int i = 0;i < 3;i++) {
		wait(stdout_mutex);
		std::cout << "a" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
	}

	return 0;
}

DWORD WINAPI b(LPVOID pVoid)
{
	for (int i = 0;i < 3;i++) {
		wait(stdout_mutex);
		std::cout << "b" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
	}

	wait(aThread);
	release(semA);

	for (int i = 0;i < 3;i++) {
		wait(stdout_mutex);
		std::cout << "b" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
	}
	return 0;
}

DWORD WINAPI c(LPVOID pVoid)
{
	for (int i = 0;i < 3;i++) {
		wait(stdout_mutex);
		std::cout << "c" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
	}

	wait(bThread);
	release(semA);

	for (int i = 0;i < 3;i++) {
		wait(stdout_mutex);
		std::cout << "c" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
	}
	return 0;
}

DWORD WINAPI d(LPVOID pVoid)
{
	for (int i = 0;i < 3;i++) {
		wait(stdout_mutex);
		std::cout << "d" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
	}
	return 0;
}

DWORD WINAPI e(LPVOID pVoid)
{
	for (int i = 0;i < 3;i++) {
		wait(stdout_mutex);
		std::cout << "e" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
	}

	wait(cThread);
	wait(dThread);
	release(semA);

	for (int i = 0;i < 3;i++) {
		wait(stdout_mutex);
		std::cout << "e" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
	}
	return 0;
}

DWORD WINAPI f(LPVOID pVoid)
{
	for (int i = 0;i < 3;i++) {
		wait(stdout_mutex);
		std::cout << "f" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
	}

	wait(eThread);
	release(semA);

	for (int i = 0;i < 3;i++) {
		wait(stdout_mutex);
		std::cout << "f" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
	}
	return 0;
}

DWORD WINAPI g(LPVOID pVoid)
{
	for (int i = 0;i < 3;i++) {
		wait(stdout_mutex);
		std::cout << "g" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
	}

	wait(fThread);
	wait(hThread);
	release(semA);

	for (int i = 0;i < 3;i++) {
		wait(stdout_mutex);
		std::cout << "g" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
	}
	return 0;
}

DWORD WINAPI h(LPVOID pVoid)
{
	for (int i = 0;i < 3;i++) {
		wait(stdout_mutex);
		std::cout << "h" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
	}
	return 0;
}

DWORD WINAPI k(LPVOID pVoid)
{
	for (int i = 0;i < 3;i++) {
		wait(semK);
		wait(stdout_mutex);
		std::cout << "k" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
		release(semM);
	}

	wait(gThread);
	release(semA);

	for (int i = 0;i < 3;i++) {
		wait(semK);
		wait(stdout_mutex);
		std::cout << "k" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
		release(semM);
	}
	return 0;
}

DWORD WINAPI m(LPVOID pVoid)
{
	for (int i = 0;i < 3;i++) {
		wait(semM);
		wait(stdout_mutex);
		std::cout << "m" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
		release(semK);
	}

	wait(gThread);
	release(semB);

	for (int i = 0;i < 3;i++) {
		wait(semM);
		wait(stdout_mutex);
		std::cout << "m" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
		release(semP);
	}

	wait(pThread);
	wait(kThread);
	release(semA);

	for (int i = 0;i < 3;i++) {
		wait(stdout_mutex);
		std::cout << "m" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
	}
	return 0;
}



DWORD WINAPI n(LPVOID pVoid)
{
	for (int i = 0;i < 3;i++) {
		wait(stdout_mutex);
		std::cout << "n" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
	}
	return 0;
}

DWORD WINAPI p(LPVOID pVoid)
{
	for (int i = 0;i < 3;i++) {
		wait(semP);
		wait(stdout_mutex);
		std::cout << "p" << std::flush;
		ReleaseMutex(stdout_mutex);
		computation();
		release(semK);
	}
	return 0;
}

int lab3_init()
{
	stdout_mutex = CreateMutex(NULL, false, NULL);
	if (stdout_mutex == NULL)
		return GetLastError();

	semA = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
	if (semA == NULL)
		return GetLastError();
	semB = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
	if (semB == NULL)
		return GetLastError();

	semM = CreateSemaphore(NULL, 1, MAX_SEM_COUNT, NULL);
	if (semM == NULL)
		return GetLastError();
	semK = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
	if (semK == NULL)
		return GetLastError();
	semP = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
	if (semP == NULL)
		return GetLastError();

	aThread = CreateThread(NULL, 0, (a), 0, 0, &IDThread);
	if (aThread == NULL)
		return GetLastError();
	bThread = CreateThread(NULL, 0, (b), 0, 0, &IDThread);
	if (bThread == NULL)
		return GetLastError();
	
	wait(aThread);
	wait(semA);

	cThread = CreateThread(NULL, 0, (c), 0, 0, &IDThread);
	if (cThread == NULL)
		return GetLastError();

	wait(bThread);
	wait(semA);

	dThread = CreateThread(NULL, 0, (d), 0, 0, &IDThread);
	if (dThread == NULL)
		return GetLastError();
	eThread = CreateThread(NULL, 0, (e), 0, 0, &IDThread);
	if (eThread == NULL)
		return GetLastError();

	wait(cThread);
	wait(dThread);
	wait(semA);

	fThread = CreateThread(NULL, 0, (f), 0, 0, &IDThread);
	if (fThread == NULL)
		return GetLastError();

	wait(eThread);
	wait(semA);

	hThread = CreateThread(NULL, 0, (h), 0, 0, &IDThread);
	if (hThread == NULL)
		return GetLastError();
	gThread = CreateThread(NULL, 0, (g), 0, 0, &IDThread);
	if (gThread == NULL)
		return GetLastError();

	wait(fThread);
	wait(hThread);
	wait(semA);

	kThread = CreateThread(NULL, 0, (k), 0, 0, &IDThread);
	if (kThread == NULL)
		return GetLastError();
	mThread = CreateThread(NULL, 0, (m), 0, 0, &IDThread);
	if (mThread == NULL)
		return GetLastError();

	wait(gThread);
	wait(semA);
	wait(semB);


	pThread = CreateThread(NULL, 0, (p), 0, 0, &IDThread);
	if (pThread == NULL)
		return GetLastError();

	wait(pThread);
	wait(kThread);
	wait(semA);

	nThread = CreateThread(NULL, 0, (n), 0, 0, &IDThread);
	if (nThread == NULL)
		return GetLastError();

	wait(mThread);
	wait(nThread);

	CloseHandle(semM);
	CloseHandle(semK);
	CloseHandle(semP);

	CloseHandle(aThread);
	CloseHandle(eThread);
	CloseHandle(cThread);
	CloseHandle(bThread);
	CloseHandle(dThread);
	CloseHandle(kThread);
	CloseHandle(fThread);
	CloseHandle(mThread);
	CloseHandle(gThread);
	CloseHandle(hThread);
	CloseHandle(nThread);
	CloseHandle(pThread);
	CloseHandle(stdout_mutex);

	return 0;
}
