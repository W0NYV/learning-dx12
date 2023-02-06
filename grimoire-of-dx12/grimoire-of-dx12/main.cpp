#include <Windows.h>
#ifdef _DEBUG
#include <iostream>
#endif

using namespace std;

//�f�o�b�O����Ƃ��Ɏg��
void DebugOutputFormatString(const char* format, ...)
{
#ifdef _DEBUG
	va_list valist;
	va_start(valist, format);
	printf(format, valist);
	va_end(valist);
#endif
}

//�ʓ|�����Ǐ����Ȃ���΂����Ȃ��֐�
LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//�E�B���h�E���j�����ꂽ��Ă΂��
	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0); //OS�ɑ΂��āu�������̃A�v���͏I���v�Ɠ`����
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

	//�E�B���h�E�N���X�̐������o�^
	WNDCLASSEX w = {};

	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProcedure; //�R�[���o�b�N�֐��̎w��
	w.lpszClassName = TEXT("DX12Sample"); //�A�v���P�[�V�����N���X��(�K���ł悢)
	w.hInstance = GetModuleHandle(nullptr); //�n���h���̎擾

	RegisterClassEx(&w); //�A�v���P�[�V�����N���X�i�E�B���h�E�N���X�̎w���OS�ɓ`����j

	RECT wrc = { 0, 0, 1280, 720 }; //�E�B���h�E�T�C�Y�����߂�

	HWND hwnd = CreateWindow(w.lpszClassName,//�N���X���w��
		TEXT("DX12 Test"),					 //�^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,				 //�^�C�g���o�[�Ƌ��E��������E�B���h�E
		CW_USEDEFAULT,						 //�\��X���W��OS�ɂ��C��
		CW_USEDEFAULT,						 //�\��Y���W��OS�ɂ��C��
		wrc.right - wrc.left,				 //�E�B���h�E��
		wrc.bottom - wrc.top,				 //�E�B���h�E��
		nullptr,							 //�e�E�B���h�E�n���h��
		nullptr,							 //���j���[�n���h��
		w.hInstance,						 //�Ăяo���A�v���P�[�V�����n���h��
		nullptr);							 //�ǉ��p�����[�^
	
	//�E�B���h�E�\��
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

	//�����N���X�͎g��Ȃ��̂œo�^��������
	UnregisterClass(w.lpszClassName, w.hInstance);

	//DebugOutputFormatString("Show window test.");
	//getchar();
	return 0;
}
