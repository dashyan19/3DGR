// lab1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab1.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

//Количесвто вершин
const int NumbVertex = 14;

//Координаты фигуры
double myCoord[14][4] = { {1050, 125, 1, 0},   //1
                          {1070, 90, 1, 1},    //2
                          {1090, 125, 1, 1},   //3
                          {1090, 280, 1, 1},   //4
                          {1050, 280, 1, 1},   //5
                          {1050, 125, 1, 1},   //6
                          {1050, 260, 1, 0},   //7
                          {1030, 220, 1, 1},   //8
                          {1030, 350, 1, 1},   //9
                          {1050, 260, 1, 1},   //10
                          {1090, 260, 1, 0},   //11
                          {1110, 220, 1, 1},   //12
                          {1110, 350, 1, 1},   //13
                          {1090, 260, 1, 1} }; //14

//Аффинные преобразования
double mTrans1[3][3] = { {1, 0, 0},
                         {0, 1, 0},
                         {-80, 160, 1} }; //перемещение (-1; 2)

double mTrans2[3][3] = { {2, 0, 0},
                         {0, 1, 0},
                         {-1000, 0, 1} }; //масштабирование (уменьшение объекта в 4 раза)

double mTrans3[3][3] = { {0, 1, 0},
                         {1, 0, 0},
                         {0, 0, 1} }; //зеркальное отображение (относительно прямой y=x)

//Умножение матриц
void Multiply_matrix(double mTrans[3][3]);

//Дополнительная матрица для пункта "отрисовать заново"
void two_matrix();

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
    LoadStringW(hInstance, IDC_LAB1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB1);
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

            case IDM_TRANSLATION:
                Multiply_matrix( mTrans1);
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);
                break;

            case IDM_DILATATION:
                Multiply_matrix(mTrans2);
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);
                break;

            case IDM_REFLECTION:
                Multiply_matrix(mTrans3);
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);
                break;

            case IDM_AGAIN:
                two_matrix();
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);
                break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...

            //

            for (int i = 0; i < 14; i++)
            {
                    if (myCoord[i][3] == 0)
                    {
                        MoveToEx(hdc, myCoord[i][0], myCoord[i][1], NULL);
                    }
                    else if (myCoord[i][3] == 1)
                    {
                        LineTo(hdc, myCoord[i][0], myCoord[i][1]);
                    }

            }

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

void Multiply_matrix(double mTrans[3][3]) 
{
    double newmatrix[NumbVertex][4] = { {0, 0, 0, 0},
                                        {0, 0, 0, 1},
                                        {0, 0, 0, 1},
                                        {0, 0, 0, 1},
                                        {0, 0, 0, 1},
                                        {0, 0, 0, 1},
                                        {0, 0, 0, 0},
                                        {0, 0, 0, 1},
                                        {0, 0, 0, 1},
                                        {0, 0, 0, 1},
                                        {0, 0, 0, 0},
                                        {0, 0, 0, 1},
                                        {0, 0, 0, 1}, 
                                        {0, 0, 0, 1}, };

    for (int i = 0; i < NumbVertex; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                newmatrix[i][j] += myCoord[i][k] * mTrans[k][j];
            }
        }
    }

    for (int i = 0; i < NumbVertex; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            myCoord[i][j] = newmatrix[i][j];
        }
    }
}

void two_matrix()
{
    double newmatrix[14][4] = { {1050, 125, 1, 0},   //1
                              {1070, 90, 1, 1},    //2
                              {1090, 125, 1, 1},   //3
                              {1090, 280, 1, 1},   //4
                              {1050, 280, 1, 1},   //5
                              {1050, 125, 1, 1},   //6
                              {1050, 260, 1, 0},   //7
                              {1030, 220, 1, 1},   //8
                              {1030, 350, 1, 1},   //9
                              {1050, 260, 1, 1},   //10
                              {1090, 260, 1, 0},   //11
                              {1110, 220, 1, 1},   //12
                              {1110, 350, 1, 1},   //13
                              {1090, 260, 1, 1} }; //14
   
    for (int i = 0; i < NumbVertex; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            myCoord[i][j] = newmatrix[i][j];
        }
    }

}