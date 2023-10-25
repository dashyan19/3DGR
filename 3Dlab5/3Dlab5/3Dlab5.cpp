// 3Dlab5.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "3Dlab5.h"

#include "cmath"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

float fi = 0;
float TETA = 90;
float R = -600;

int FLAG = false;
void shape_drawing(HDC hdc);
void vid_preobraz();
void schet2();

float shape[12][4] = 
{
    {-75, 125, -200, 1},        //0 задняя левая нижняя вершина
    {75, 125, -200, 1},         //1 задняя правая нижняя вершина
    {150, 0, -200, 1},          //2 боковая правая нижняя вершина
    {75, -125, -200, 1},        //3 передняя правая нижняя вершина
    {-75, -125, -200, 1},       //4 передняя левая нижняя вершина
    {-150, 0, -200, 1},         //5 боковая левая нижняя вершина

    {-75, 125, 200, 1},         //6 задняя левая нижняя вершина
    {75, 125, 200, 1},          //7 задняя правая нижняя вершина
    {150, 0, 200, 1},           //8 боковая правая нижняя вершина
    {75, -125, 200, 1},         //9 передняя правая нижняя вершина
    {-75, -125, 200, 1},        //10 передняя левая нижняя вершина
    {-150, 0, 200, 1},          //11 боковая левая нижняя вершина
};

float VID[12][4] = { 0 };

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY3DLAB5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3DLAB5));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY3DLAB5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY3DLAB5);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, SW_SHOWMAXIMIZED); // показываем окно на весь экран
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_KEYDOWN:
        switch (wParam) {
        case VK_LEFT:
        {
            if (FLAG == true)
            {
                TETA = TETA - 0.1;
                vid_preobraz();
                InvalidateRect(hWnd, NULL, TRUE);
            }
            else
            {
                TETA = TETA - 0.1;
                schet2();
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        }
        case VK_RIGHT:
        {
            if (FLAG == true)
            {
                TETA = TETA + 0.1;
                vid_preobraz();
                InvalidateRect(hWnd, NULL, TRUE);
            }
            else
            {
                TETA = TETA + 0.1;
                schet2();
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        }
        case VK_UP:
        {
            if (FLAG == true)
            {
                fi = fi + 0.1;
                vid_preobraz();
                InvalidateRect(hWnd, NULL, TRUE);
            }
            else
            {
                fi = fi + 0.1;
                schet2();
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        }
        case VK_DOWN:
        {
            if (FLAG == true)
            {
                fi = fi - 0.1;
                vid_preobraz();
                InvalidateRect(hWnd, NULL, TRUE);
            }
            else
            {
                fi = fi - 0.1;
                schet2();
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        }
        case VK_F6:
        {
            FLAG = true;
            vid_preobraz();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        case VK_F7:
        {
            FLAG = false;
            schet2();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        case VK_F8:
        {
            if (R > -300)
            {
                R = R - 5;
                schet2();
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        }
        case VK_F9:
        {

            if (R < -120)
            {
                R = R + 5;
                schet2();
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        }
        break;
        }

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...

            RECT rect;

            GetWindowRect(hWnd, &rect);
            LONG width = rect.right - rect.left;
            LONG height = rect.bottom - rect.top;

            //переносим началы координат в середину экрана
            SetMapMode(hdc, MM_ANISOTROPIC);
            SetViewportOrgEx(hdc, width / 2, height / 2, NULL);

            //ставим точку в начало координат
            SetPixel(hdc, 0, 0, RGB(255, 0, 0));

            shape_drawing(hdc);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void shape_drawing(HDC hdc)
{

    MoveToEx(hdc, VID[0][0], VID[0][1], NULL);
    LineTo(hdc, VID[1][0], VID[1][1]);
    LineTo(hdc, VID[2][0], VID[2][1]);
    LineTo(hdc, VID[3][0], VID[3][1]);
    LineTo(hdc, VID[4][0], VID[4][1]);
    LineTo(hdc, VID[5][0], VID[5][1]);
    LineTo(hdc, VID[0][0], VID[0][1]);

    MoveToEx(hdc, VID[6][0], VID[6][1], NULL);
    LineTo(hdc, VID[7][0], VID[7][1]);
    LineTo(hdc, VID[8][0], VID[8][1]);
    LineTo(hdc, VID[9][0], VID[9][1]);
    LineTo(hdc, VID[10][0], VID[10][1]);
    LineTo(hdc, VID[11][0], VID[11][1]);
    LineTo(hdc, VID[6][0], VID[6][1]);

    MoveToEx(hdc, VID[0][0], VID[0][1], NULL);
    LineTo(hdc, VID[6][0], VID[6][1]);

    MoveToEx(hdc, VID[1][0], VID[1][1], NULL);
    LineTo(hdc, VID[7][0], VID[7][1]);

    MoveToEx(hdc, VID[2][0], VID[2][1], NULL);
    LineTo(hdc, VID[8][0], VID[8][1]);

    MoveToEx(hdc, VID[3][0], VID[3][1], NULL);
    LineTo(hdc, VID[9][0], VID[9][1]);

    MoveToEx(hdc, VID[4][0], VID[4][1], NULL);
    LineTo(hdc, VID[10][0], VID[10][1]);

    MoveToEx(hdc, VID[5][0], VID[5][1], NULL);
    LineTo(hdc, VID[11][0], VID[11][1]);

}

void vid_preobraz()
{ 
    float matrix[4][4] =
    {{ -sin(TETA), -cos(fi) * cos(TETA),-sin(fi) * cos(TETA),0 },
    { cos(TETA), -cos(fi) * sin(TETA), -sin(fi) * sin(TETA), 0 },
    { 0, sin(fi), -cos(fi), 0 },
    { 0, 100, R, 1} };

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            VID[i][j] = 0;
            for (int k = 0; k < 4; k++)
            {
                VID[i][j] += shape[i][k] * matrix[k][j];
            }
        };
    }
}

void schet2()
{
    float formula[4][4] =
    {
    {-sin(TETA),-cos(fi) * cos(TETA),-sin(fi) * cos(TETA),0},
    {cos(TETA),-cos(fi) * sin(TETA), -sin(fi) * sin(TETA), 0},
    {0, sin(fi), -cos(fi), 0},
    {0, 100, R, 1}
    };

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            VID[i][j] = 0;
            for (int k = 0; k < 4; k++)
            {
                VID[i][j] += shape[i][k] * formula[k][j];
            }
        };
    }

    int k = 0;

    for (int i = 0; i < 12; i++)
    {
        VID[i][k] = VID[i][k] * R / (VID[i][k + 2] + R);
    }

    k = 1;

    for (int i = 0; i < 12; i++)
    {
        VID[i][k] = VID[i][k] * R / (VID[i][k + 1] + R);
    }
}
