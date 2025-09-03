#include <windows.h>
#include <tchar.h>

#define MAX_LOADSTRING 100

#define ID_BTN_CONTENIDO   1001
#define ID_BTN_EXAMEN      1002
#define ID_BTN_DOCENTES    1003
#define ID_STATIC_CONTENT  2001
#define ID_TIMER_LOADING   3001

// Variables globales:
HINSTANCE hInst;               
WCHAR     szTitle[MAX_LOADSTRING] = L"Demo Win32";
WCHAR     szWindowClass[MAX_LOADSTRING] = L"DemoWin32Class";
HWND      g_hMainWnd = NULL;
HWND      g_btnContenido = NULL, g_btnExamen = NULL, g_btnDocentes = NULL, g_lblContent = NULL;

const int SIDEBAR_WIDTH = 180;
bool      g_loading = false;
WCHAR     g_pendingText[512] = L"";

// Declaraciones:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

// Utilidades
void StartLoading(HWND hWnd, const wchar_t* nextText) {
    // Mostrar Cargando… y activar timer 5s
    SetWindowTextW(g_lblContent, L"Cargando...");
    lstrcpynW(g_pendingText, nextText, _countof(g_pendingText));

    if (g_loading) KillTimer(hWnd, ID_TIMER_LOADING);
    SetTimer(hWnd, ID_TIMER_LOADING, 5000, NULL); // 5 segundos
    g_loading = true;
}

void DoLayout(HWND hWnd, int cx, int cy) {
    // Distancias
    const int m = 10;
    const int btnH = 40;
    const int btnW = SIDEBAR_WIDTH - 2 * m;

    // Botones en la barra lateral
    if (g_btnContenido) MoveWindow(g_btnContenido, m, 20, btnW, btnH, TRUE);
    if (g_btnExamen)    MoveWindow(g_btnExamen, m, 20 + btnH + 10, btnW, btnH, TRUE);
    if (g_btnDocentes)  MoveWindow(g_btnDocentes, m, 20 + 2 * (btnH + 10), btnW, btnH, TRUE);

    // Lado derecho 
    int rightX = SIDEBAR_WIDTH + m;
    int rightW = max(50, cx - SIDEBAR_WIDTH - 2 * m);
    int rightH = max(30, cy - 2 * m);
    if (g_lblContent) MoveWindow(g_lblContent, rightX, m, rightW, rightH, TRUE);
}

// Punto de entrada
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE ,
    _In_ LPWSTR ,
    _In_ int nCmdShow)
{
    hInst = hInstance;

    MyRegisterClass(hInstance);
    if (!InitInstance(hInstance, nCmdShow)) return FALSE;

    // Bucle de mensajes
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

// Registrar clase de ventana
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex{};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = szWindowClass;
    return RegisterClassExW(&wcex);
}

// Crear ventana principal
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    g_hMainWnd = CreateWindowW(szWindowClass, szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 900, 500,
        nullptr, nullptr, hInstance, nullptr);

    if (!g_hMainWnd) return FALSE;

    ShowWindow(g_hMainWnd, nCmdShow);
    UpdateWindow(g_hMainWnd);
    return TRUE;
}

// Eventos
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // Crear botones
        g_btnContenido = CreateWindowExW(0, L"BUTTON", L"Contenido",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            0, 0, 0, 0, hWnd, (HMENU)ID_BTN_CONTENIDO, hInst, NULL);

        g_btnExamen = CreateWindowExW(0, L"BUTTON", L"Examen",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            0, 0, 0, 0, hWnd, (HMENU)ID_BTN_EXAMEN, hInst, NULL);

        g_btnDocentes = CreateWindowExW(0, L"BUTTON", L"Docentes",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            0, 0, 0, 0, hWnd, (HMENU)ID_BTN_DOCENTES, hInst, NULL);

        // Contenido 
        g_lblContent = CreateWindowExW(WS_EX_CLIENTEDGE, L"STATIC",
            L"Seleccione una opcion en la barra lateral.",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            0, 0, 0, 0, hWnd, (HMENU)ID_STATIC_CONTENT, hInst, NULL);

        // Layout inicial
        RECT rc; GetClientRect(hWnd, &rc);
        DoLayout(hWnd, rc.right - rc.left, rc.bottom - rc.top);
    }
    break;

    case WM_SIZE:
    {
        int cx = LOWORD(lParam);
        int cy = HIWORD(lParam);
        DoLayout(hWnd, cx, cy);
    }
    break;

    case WM_COMMAND:
    {
        const int id = LOWORD(wParam);
        switch (id)
        {
        case ID_BTN_CONTENIDO:
            StartLoading(hWnd, L"Texto de ejemplo para la seccion CONTENIDO.\r\n\r\nAqui iria la informacion del programa, unidades, materiales, etc.");
            break;
        case ID_BTN_EXAMEN:
            StartLoading(hWnd, L"Texto de ejemplo para la seccion EXAMEN.\r\n\r\nFechas, modalidad, criterios de evaluacion, y recomendaciones.");
            break;
        case ID_BTN_DOCENTES:
            StartLoading(hWnd, L"Texto de ejemplo para la seccion DOCENTES.\r\n\r\nListado, horarios de consulta y medios de contacto.");
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;

    case WM_TIMER:
        if (wParam == ID_TIMER_LOADING) {
            // 5s pasaron: mostrar el contenido
            SetWindowTextW(g_lblContent, g_pendingText);
            KillTimer(hWnd, ID_TIMER_LOADING);
            g_loading = false;
        }
        break;

    case WM_DESTROY:
        if (g_loading) KillTimer(hWnd, ID_TIMER_LOADING);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
