#include <windows.h>
#include <algorithm>
#define shift int
LRESULT _stdcall WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
const int LEFT = -5;
const int RIGHT = 5;
const int TOP = 5;
const int BOTTOM = -5;
shift static_shift = 0;
int _stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;										// сначала описывается оконный класс wc, затем создается окно hWnd
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;							// имя оконной процедуры, закрепленной за данным классом
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;							// идентификатор приложения, содержащий адрес начала выделенной ему области памяти
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = 0;								// меню в оконном классе отсутствует
	wc.lpszClassName = (LPCSTR)"class";					// имя оконного класса, используемое при создании экземпляров окна

	RegisterClass(&wc);									// регистрация класса wc
	HWND hWnd = CreateWindow(							// hWnd - дескриптор, идентифицирующий окно; функция создания окна заполняет дескриптор hWnd ненулевым значением
	            (LPCSTR)"class",						// имя оконного класса
	            (LPCSTR)"Win32 Application Example",	// заголовок окна
	            WS_OVERLAPPEDWINDOW,					// стиль окна
				200,200,400,400,						// координаты на экране левого верхнего угла окна, его ширина и высота
	            NULL,NULL,hInstance,NULL);

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	MSG msg;

	while(GetMessage(&msg,NULL,0,0))					// основной цикл, который ожидает сообщения и рассылает их соответствующим окнам	
	{													// функция GetMessage() выбирает из очереди сообщение и заносит его в структуру msg
		TranslateMessage(&msg);
		DispatchMessage(&msg);							// передача сообщения в оконную процедуру (точнее, функция DispatchMessage оповещает систему о необходимости вызова оконной процедуры)
	}

	return 0;
}
std::pair<int, int> dekToScreen(std::pair<double, double> coors, HDC dc);
void TestDrawing(HDC dc, bool isThis);
void TestDrawing1(HDC dc);
void horizontalAxeMovingDuringGeneralDrawingOperationInCaseOfThereWereAnyAxisBefore(HDC dc, RECT r, shift Int);
void verticalAxePreDrawingBeforGeneralDrawingOperationInCaseOfThereWereNotAnyAxisBefore( HDC dc, RECT r);
void horizontalAxePreDrawingBeforGeneralDrawingOperationInCaseOfThereWereNotAnyAxisBefore( HDC dc, RECT r);
void TestDrawing(HDC dc, bool isThis, shift Int);
void moveCameraToUp( HDC dc);
void moveCameraToDown( HDC dc);
LRESULT _stdcall WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// оконная процедура
{
	switch(msg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		case WM_SIZE:
		{
			InvalidateRect(hWnd,NULL,FALSE);
			return 0;
		}

		case WM_PAINT:
		{

		}
		case WM_RBUTTONDOWN:
		{
			HDC dc = GetDC(hWnd);	    // функция GetDC возвращает контекст устройства, в котором хранится информация о том, в какое окно производится вывод, каковы размеры рабочей области окна hWnd, в какой точке экрана находится начало координат рабочей области и т.п.
			TestDrawing(dc, 0);
			ReleaseDC(hWnd,dc);			// функция ReleaseDC сообщает системе, что связанный с окном hWnd контекст dc больше не нужен
			return DefWindowProc(hWnd,msg,wParam,lParam);
		}
		case WM_LBUTTONDOWN:
		{
			HDC dc = GetDC(hWnd);		// функция GetDC возвращает контекст устройства, в котором хранится информация о том, в какое окно производится вывод, каковы размеры рабочей области окна hWnd, в какой точке экрана находится начало координат рабочей области и т.п.
			TestDrawing(dc, 1);
			ReleaseDC(hWnd,dc);			// функция ReleaseDC сообщает системе, что связанный с окном hWnd контекст dc больше не нужен
			return DefWindowProc(hWnd,msg,wParam,lParam);
		}
		case WM_KEYDOWN:
			{
				switch(wParam) {
				case VK_UP:{
					HDC dc = GetDC(hWnd);
					moveCameraToUp(dc);
					ReleaseDC(hWnd,dc);
					return DefWindowProc(hWnd,msg,wParam,lParam);
							 }
				case VK_DOWN:{
					HDC dc = GetDC(hWnd);
					moveCameraToDown(dc);
					ReleaseDC(hWnd,dc);
					return DefWindowProc(hWnd,msg,wParam,lParam);
							 }
					}
				}
		default:
			return DefWindowProc(hWnd,msg,wParam,lParam);
	}
	return 0;
}

void moveCameraToUp(HDC dc){
	TestDrawing(dc, 1, 10);
}

void moveCameraToDown(HDC dc){
	TestDrawing(dc, 1, -10);
}

//WM_KEYDOWN; wParam vk_left
void verticalAxePreDrawingBeforGeneralDrawingOperationInCaseOfThereWereNotAnyAxisBefore( HDC dc, RECT r) {
	MoveToEx(dc, r.right /  2, r.top, NULL);
	LineTo(dc, r.right / 2, r.bottom);
}

void horizontalAxePreDrawingBeforGeneralDrawingOperationInCaseOfThereWereNotAnyAxisBefore( HDC dc, RECT r) {
	MoveToEx(dc, r.left, r.bottom / 2, NULL);
	LineTo(dc, r.right, r.bottom / 2);
}

void horizontalAxeMovingDuringGeneralDrawingOperationInCaseOfThereWereAnyAxisBefore(HDC dc, RECT r, shift Int){

	MoveToEx(dc, r.left, r.bottom / 2 + Int, NULL);
	LineTo(dc, r.right, r.bottom / 2 + Int);	
}
void TestDrawing(HDC dc, bool isThis)
{
	RECT r;
	GetClientRect(WindowFromDC(dc),&r);
	Rectangle(dc,0,0,r.right,r.bottom);
	
	horizontalAxePreDrawingBeforGeneralDrawingOperationInCaseOfThereWereNotAnyAxisBefore(dc, r);
	verticalAxePreDrawingBeforGeneralDrawingOperationInCaseOfThereWereNotAnyAxisBefore(dc, r);
	MoveToEx(dc,r.right,r.top,NULL);	
	for(double i = 1; i < 10000; i += 0.01) {
		double x = -5 + i / 100;
		std::pair<double, double> coors;
		coors.first = x;
		coors.second = x * x;
		coors = dekToScreen(coors, dc);
		LineTo(dc, coors.first, coors.second);
	}
}

void TestDrawing(HDC dc, bool isThis, shift Int) {
	static_shift += Int;
	
	RECT r;
	GetClientRect(WindowFromDC(dc),&r);
	Rectangle(dc,0,0,r.right,r.bottom);
	
	horizontalAxeMovingDuringGeneralDrawingOperationInCaseOfThereWereAnyAxisBefore(dc, r, static_shift);
	verticalAxePreDrawingBeforGeneralDrawingOperationInCaseOfThereWereNotAnyAxisBefore(dc, r);
	MoveToEx(dc, r.right, r.top, NULL);	
	for(double i = 1; i < 10000; i += 0.01) {
		double x = -5 + i / 100;
		std::pair<double, double> coors(x, x*x);
		coors = dekToScreen(coors, dc);
		LineTo(dc, coors.first, coors.second + static_shift);
	}
}

std::pair<int, int> dekToScreen(std::pair<double, double> coors, HDC dc){
	std::pair<int, int> retValue;
	RECT r;
	GetClientRect(WindowFromDC(dc), &r);
	retValue.first = (int)(r.right * (coors.first - LEFT) / (RIGHT - LEFT));
	retValue.second = (int)(r.bottom * (TOP - coors.second) / (TOP - BOTTOM));
	return retValue;
}
//Homogen
