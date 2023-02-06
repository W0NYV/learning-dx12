#include <Windows.h>
#ifdef _DEBUG
#include <iostream>
#endif

using namespace std;

//デバッグするときに使う
void DebugOutputFormatString(const char* format, ...)
{
#ifdef _DEBUG
	va_list valist;
	va_start(valist, format);
	printf(format, valist);
	va_end(valist);
#endif
}

//面倒だけど書かなければいけない関数
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//ウィンドウが破棄されたら呼ばれる
	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0); //OSに対して「もうこのアプリは終わる」と伝える
		return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

#ifdef _DEBUG
int main()
{
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#endif

	//ウィンドウクラスの生成＆登録
	WNDCLASSEX w = {};

	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProcedure; //コールバック関数の指定
	w.lpszClassName = TEXT("DX12Sample"); //アプリケーションクラス名(適当でよい)
	w.hInstance = GetModuleHandle(nullptr); //ハンドルの取得

	RegisterClassEx(&w); //アプリケーションクラス（ウィンドウクラスの指定をOSに伝える）

	RECT wrc = { 0, 0, 1280, 720 }; //ウィンドウサイズを決める

	HWND hwnd = CreateWindow(w.lpszClassName,//クラス名指定
		TEXT("DX12 Test"),					 //タイトルバーの文字
		WS_OVERLAPPEDWINDOW,				 //タイトルバーと境界線があるウィンドウ
		CW_USEDEFAULT,						 //表示X座標はOSにお任せ
		CW_USEDEFAULT,						 //表示Y座標はOSにお任せ
		wrc.right - wrc.left,				 //ウィンドウ幅
		wrc.bottom - wrc.top,				 //ウィンドウ高
		nullptr,							 //親ウィンドウハンドル
		nullptr,							 //メニューハンドル
		w.hInstance,						 //呼び出しアプリケーションハンドル
		nullptr);							 //追加パラメータ
	
	//ウィンドウ表示
	ShowWindow(hwnd, SW_SHOW);

	MSG msg = {};

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			break;
		}
	}

	//もうクラスは使わないので登録解除する
	UnregisterClass(w.lpszClassName, w.hInstance);

	//DebugOutputFormatString("Show window test.");
	//getchar();
	return 0;
}
