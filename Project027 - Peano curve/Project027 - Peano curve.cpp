// Project027 - Peano curve.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Project027 - Peano curve.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int sizeofsqr = 5;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJECT027PEANOCURVE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT027PEANOCURVE));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT027PEANOCURVE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT027PEANOCURVE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

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
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

void peano(HDC hdc, int x, int y, int width, int height) {

    Rectangle(hdc, x - 1, y, x + 1, y - 4 * sizeofsqr);
    Rectangle(hdc, x - 2 * sizeofsqr, y - 4 * sizeofsqr - 1, x + 1, y - 4 * sizeofsqr + 1);
    Rectangle(hdc, x - 2 * sizeofsqr - 1, y - 4 * sizeofsqr, x - 2 * sizeofsqr + 1, y);
    Rectangle(hdc, x - 2 * sizeofsqr, y - 1, x - 4 * sizeofsqr, y + 1);
    Rectangle(hdc, x - 4 * sizeofsqr - 1, y, x - 4 * sizeofsqr + 1, y - 4 * sizeofsqr);

    Rectangle(hdc, x - 4 * sizeofsqr + 1, y - 4 * sizeofsqr, x - 4 * sizeofsqr - 1, y - 6 * sizeofsqr);

}
//void set_points(POINT A, POINT B, POINT C, POINT D, POINT E, POINT F, int bottomsqrx, int bottomsqry, bool undef) {
//
//    if (undef) {
//
//        A.x = bottomsqrx;
//        A.y = bottomsqry;
//        B.x = A.x;
//        B.y = A.y - 4 * sizeofsqr;
//        C.x = B.x - 2 * sizeofsqr;
//        C.y = B.y;
//        D.x = A.x - 2 * sizeofsqr;
//        D.y = A.y;
//        E.x = D.x - 2 * sizeofsqr;
//        E.y = D.y;
//        F.x = C.x - 2 * sizeofsqr;
//        F.y = C.y;
//
//    } 
//
//
//}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{   

    static POINT sqr_centre = { sqr_centre.x = sizeofsqr, sqr_centre.y = sizeofsqr };
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
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
            int width, height;

            SelectObject(hdc, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hdc, RGB(255, 255, 255));

            RECT rect;
            GetClientRect(hWnd, &rect);
            width = rect.right - rect.left;
            height = rect.bottom - rect.top;

            int numofsqrcolumns = (width / sizeofsqr) / 2;
            int numofsqrrows = (height / sizeofsqr) / 2;

            int bottomsqrx = 0, bottomsqry = 0;

            for (int i = 0; i < numofsqrrows; sqr_centre.y += sizeofsqr * 2, i++) {

                for (int j = 0; j < numofsqrrows /*numofsqrcolumns*/ ; sqr_centre.x += sizeofsqr * 2, j++) {

                    Rectangle(hdc, sqr_centre.x - sizeofsqr / 2, sqr_centre.y - sizeofsqr / 2, sqr_centre.x + sizeofsqr / 2, sqr_centre.y + sizeofsqr / 2);
                    bottomsqrx = sqr_centre.x;
                    bottomsqry = sqr_centre.y;

                }

                sqr_centre.x = sizeofsqr;

            }
            
            SelectObject(hdc, GetStockObject(DC_PEN));
            SetDCPenColor(hdc, RGB(255, 0, 0));

            //POINT A, B , C, D, E, F;
            //bool startptsundef = true;
            //set_points(A, B, C, D, E, F, bottomsqrx, bottomsqry, startptsundef);
            //peano(hdc, A, B, C, D, E, F);
            peano(hdc, bottomsqrx, bottomsqry, width, height);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_SIZE:
        sqr_centre.x = sizeofsqr, sqr_centre.y = sizeofsqr;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam); 
    }
    return 0;
}

// Message handler for about box.
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
