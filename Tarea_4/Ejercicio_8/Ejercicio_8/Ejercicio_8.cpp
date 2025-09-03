// Ejercicio_8.cpp : Define el punto de entrada de la aplicación.
//

#include "framework.h"
#include "Ejercicio_8.h"
#include <string>
#include <deque>
#include <cwctype>  
#include <cstdio> 

#define MAX_LOADSTRING 100

// Variables globales:
HINSTANCE hInst;                                // instancia actual
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal
std::wstring g_nombre;
int g_clicks = 0;        // cantidad de clics izquierdos
int g_cx = 0, g_cy = 0;  // tamaño del área cliente

RECT g_panel[3];         // rectángulos de los 3 paneles
const int PADDING = 16;  // margen interior
const int GAP = 12;      // separación entre paneles

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
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

    // TODO: Colocar código aquí.

    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EJERCICIO8, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EJERCICIO8));

    MSG msg;

    // Bucle principal de mensajes:
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
//  FUNCIÓN: MyRegisterClass()
//
//  PROPÓSITO: Registra la clase de ventana.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EJERCICIO8));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_EJERCICIO8);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: Guarda el identificador de instancia y crea la ventana principal
//
//   COMENTARIOS:
//
//        En esta función, se guarda el identificador de instancia en una variable común y
//        se crea y muestra la ventana principal del programa.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Almacenar identificador de instancia en una variable global

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO: Procesa mensajes de la ventana principal.
//
//  WM_COMMAND  - procesar el menú de aplicaciones
//  WM_PAINT    - Pintar la ventana principal
//  WM_DESTROY  - publicar un mensaje de salida y volver
//
//

static void DoLayout(HWND hWnd, int cx, int cy) {
    int usableW = cx - 2 * PADDING;
    int usableH = cy - 2 * PADDING - 2 * GAP; 
    int h = usableH / 3;

    for (int i = 0; i < 3; ++i) {
        int top = PADDING + i * (h + GAP);
        g_panel[i] = { PADDING, top, PADDING + usableW, top + h };
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analizar las selecciones de menú:
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
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        SetBkMode(hdc, TRANSPARENT);

        HBRUSH br1 = CreateSolidBrush(RGB(235, 245, 255));
        HBRUSH br2 = CreateSolidBrush(RGB(235, 255, 235));
        HBRUSH br3 = CreateSolidBrush(RGB(255, 245, 235));
        HBRUSH backs[3] = { br1, br2, br3 };

        auto DrawPanel = [&](int idx, const wchar_t* titulo, const std::wstring& valor) {
            RECT r = g_panel[idx];

            // Fondo
            FillRect(hdc, &r, backs[idx]);
            // Borde
            Rectangle(hdc, r.left, r.top, r.right, r.bottom);

            // Título 
            RECT rTitle = r;
            rTitle.left += PADDING;
            rTitle.top += PADDING;
            rTitle.bottom = rTitle.top + 28;

            DrawTextW(hdc, titulo, -1, &rTitle,
                DT_LEFT | DT_TOP | DT_SINGLELINE | DT_NOPREFIX);

            // Valor 
            RECT rValue = r;
            rValue.left = rTitle.left;
            rValue.top = rTitle.bottom + 6;
            rValue.right -= PADDING;
            rValue.bottom -= PADDING;

            DrawTextW(hdc, valor.c_str(), (int)valor.size(), &rValue,
                DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOPREFIX);
            };

        std::wstring valNombre = g_nombre.empty() ? L"_" : g_nombre;
        DrawPanel(0, L"Nombre (teclado)", valNombre);

        wchar_t bufClics[64];
        swprintf(bufClics, 64, L"Entradas (clics): %d", g_clicks);
        DrawPanel(1, L"Entradas (clics)", bufClics);

        wchar_t bufWH[64];
        swprintf(bufWH, 64, L"%d x %d", g_cx, g_cy);
        DrawPanel(2, L"Tamano (WxH)", bufWH);

        DeleteObject(br1); DeleteObject(br2); DeleteObject(br3);

        EndPaint(hWnd, &ps);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_CREATE:
    {
        RECT rc; GetClientRect(hWnd, &rc);
        g_cx = rc.right - rc.left;
        g_cy = rc.bottom - rc.top;
        DoLayout(hWnd, g_cx, g_cy);
        return 0;
    }
    case WM_SIZE:
    {
        g_cx = LOWORD(lParam);
        g_cy = HIWORD(lParam);
        DoLayout(hWnd, g_cx, g_cy);
        InvalidateRect(hWnd, nullptr, TRUE);
        return 0;
    }
    case WM_CHAR:
    {
        wchar_t ch = static_cast<wchar_t>(wParam);

        if (ch == L'\b') { // backspace
            if (!g_nombre.empty()) g_nombre.pop_back();
        }
        else if (iswprint(ch)) {
            g_nombre.push_back(ch);
        }
        InvalidateRect(hWnd, nullptr, TRUE);
        return 0;
    }
    case WM_LBUTTONDOWN:
    {
        ++g_clicks;
        InvalidateRect(hWnd, nullptr, TRUE);
        return 0;
    }

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Controlador de mensajes del cuadro Acerca de.
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
