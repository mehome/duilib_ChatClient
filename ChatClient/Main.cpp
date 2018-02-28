// ChatClient.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Common.h"
#include "ChatMainWnd.h"
#include "LoginWnd.h"
#include "Client.h"
#include "ThreadPool.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	HRESULT hr = ::CoInitialize(NULL);
	if (FAILED(hr))
		return 0;

	Client *client = new Client;
	ThreadPool *threadPool = new ThreadPool;

	LoginWnd *loginWnd = new LoginWnd(client, threadPool);
	if (loginWnd == NULL)
		return 0;
	loginWnd->Create(NULL, _T("登录"), UI_WNDSTYLE_FRAME | WS_POPUP, NULL, 0, 0, 0, 0);
	loginWnd->CenterWindow();
	if( loginWnd->ShowModal() == 0)
		return 0;

	shared_ptr<ChatMainWnd> mainWnd(new ChatMainWnd);
	if (mainWnd == NULL)
		return 0;
	mainWnd->Create(NULL, L"聊天", UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	mainWnd->CenterWindow();
	mainWnd->ShowWindow();

	CPaintManagerUI::MessageLoop();

	delete client;
	::CoUninitialize();
	return 0;
}

