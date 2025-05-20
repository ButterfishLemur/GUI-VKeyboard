// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>



// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");
//variable behältihren wert zwischen den funktionsaufrufen: zähler funktion: jedes mal wenn aufgerufen wird zähler um eins erhöt. sonst immer zurückgesetzt
//sorgt für Erstellung von ANSI und Unicode kompatiblen programmen. Ohne: Muss code geändert werden je nach dem was benutzt wird.


// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Virtual Keyboard");


// Stored instance handle for use in Win32 API calls such as FindResource
HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//Wert der ende ende der funktion angibt
// !!!CALLBACK!!!
//Funktion, die sich um alles kümmert, was mit dem Fenster zu tun hat.
//PArameter
//Identifikator ein bestimmtes fenster
//Gibt eine Nummer an, bspw 1 bed: fenster hat sich geöfnet usw
//letzten parameter geben an um was es sich bei msg handelt


int WINAPI WinMain(                         //Wie wird funktion aufgerufen 
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,       //Schlüssel für vorherige instanz
    _In_ LPSTR     lpCmdLine,               //Befehlsliste was gemacht werden soll. Programm bekommt input bspw 8908 und weiß links drehen
    _In_ int       nCmdShow                 // Wie soll das erzeugte fenster angezeigt werden //Ohne def standard
)
{
    WNDCLASSEX wcex;                                                //wcex Bauanleitung für Fensterklasse nur für lesbarkeit

    wcex.cbSize = sizeof(WNDCLASSEX);                               //größe in bytes                               
    wcex.style = CS_HREDRAW | CS_VREDRAW;                           //Stil Fensterklasse. hier: wenn fenster in der höhe oder breite verändert wird, wird es neu gezeichnet
    wcex.lpfnWndProc = WndProc;                                     //Zeiger auf die Fensterprozedur, wo werden tastendrücke verarbeitet
    wcex.cbClsExtra = 0;                                            //Zusätzliche Bytes für die Fensterklasse                
    wcex.cbWndExtra = 0;                                            //Zusätzliche Bytes für das Fenster                    
    wcex.hInstance = hInstance;                                     //Handle der Instanz, verwendet um auf resourcen zuzugreifen, die mit Anwendung verbunden sind       
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);         //Icon der Anwendung
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);                     //Mauszeiger                
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);                //Hintergrundfarbe des Fensters hier  standard    
    wcex.lpszMenuName = NULL;                                       //Menü der Anwendung 
    wcex.lpszClassName = szWindowClass;                             //Name der Fensterklasse ist name des Automodells für verweise auf andere fenster die geleich aussehn sollen
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);       //Icon der Anwendung

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    // The parameters to CreateWindowEx explained:
    // WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
    // szWindowClass: the name of the application
    // szTitle: the text that appears in the title bar
    // WS_OVERLAPPEDWINDOW: the type of window to create
    // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    // 500, 100: initial size (width, length)
    // NULL: the parent of this window
    // NULL: this application does not have a menu bar
    // hInstance: the first parameter from WinMain
    // NULL: not used in this application
    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,                 //erweiterter fensterstil mit Titelleiste usw 
        szWindowClass,                          //Fenster soll so aussehen wie oben defiiert    
        szTitle,                                //Titel des fensters    
        WS_OVERLAPPEDWINDOW,                    //Fensterstil: Überlappendes Fenster    
        CW_USEDEFAULT, CW_USEDEFAULT,           // //Position des Fensters
        300, 150,                               // //Größe des Fensters
        NULL,                                   //übergeordnetes Fenster
        NULL,                                   ////kein Menü
        hInstance,                               ////Instanzhandle
        NULL                                    //Zeiger auf zusätzliche Daten für die Fensterprozedur    
    );
    for (int i = 0; i < 5; i++) {

        HWND Button = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"A",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            100 * i,         // x position 
            30,         // y position 
            100,        // Button width
            40,        // Button height
            hWnd,     // Parent window
            NULL,       // No menu.
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.


        if (!hWnd || !Button)
        {
            MessageBox(NULL,
                _T("Call to CreateWindow failed!"),
                _T("Windows Desktop Guided Tour"),
                NULL);

            return 1;
        }


        // The parameters to ShowWindow explained:
        // hWnd: the value returned from CreateWindow
        // nCmdShow: the fourth parameter from WinMain
        ShowWindow(hWnd,
            nCmdShow);
        UpdateWindow(hWnd);                          //Updatet window alle par ticks


    }

        // Main message loop:
        MSG msg;                                     //msg wird hier als Feedback von windows verwendet   
        while (GetMessage(&msg, NULL, 0, 0))            //Wenn sich eine nachicht in der warteschlange befindet, wird sie in msg gespeichert
        {
            TranslateMessage(&msg);                    //Übersetzt Tasteneingaben in Zeichen
            DispatchMessage(&msg);                     //Sendet die nachricht an die fensterprozedur
        }


        return (int)msg.wParam;
    
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;                                        // Struktur wie sieht es aus?
	HDC hdc;                                            // Was ist es für ein endgerät?
	TCHAR greeting[] = _T("Press A Button");   // Text innerhalb der Anwendung

    switch (message)    //wenn message (feedback von windows ist:
    {
    case WM_PAINT:          //programm wird eöfnet 
        
        hdc = BeginPaint(hWnd, &ps);//kreiere das fenster in dem anderen fenster.

        // Here your application is laid out.
        // For this introduction, we just print out "Hello, Windows desktop!"
        // in the top left corner.
        TextOut(hdc,
            5, 5,
            greeting, _tcslen(greeting));
        // End application-specific layout section.

        EndPaint(hWnd, &ps);
        break;
    case WM_COMMAND:

		MessageBox(hWnd, L"Button Clicked", L"Button", MB_OK);

            break;
       

    

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}