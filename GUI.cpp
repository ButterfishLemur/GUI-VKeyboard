// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <string>
#include <array>
#include <vector>

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


//x,y position des fensters	braucht man nicht, Offset:

//Funktion Modifizierter String
struct ButtonInfo {

	std::wstring text; // Text des Buttons
	int x; // x-Position des Buttons
	int y; // y-Position des Buttons
	int width; // Breite des Buttons
	int height; // Höhe des Buttons
};

// Benutzerdefinierte Einstellungen für bestimmte Tasten
struct CustomButton {
	std::wstring text;
	int x; // x-Position des Buttons
	int y;
	int width;
	int height;
	int spacing;

	// Optional: weitere Eigenschaften wie Farbe, Font etc.
};


int WINAPI WinMain(                         //Wie wird funktion aufgerufen 
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,       //Schlüssel für vorherige instanz
	_In_ LPSTR     lpCmdLine,               //Befehlsliste was gemacht werden soll. Programm bekommt input bspw 8908 und weiß links drehen
	_In_ int       nCmdShow                 // Wie soll das erzeugte fenster angezeigt werden //Ohne def standard
)
{
	WNDCLASSEX wcex = {};                                                //wcex Bauanleitung für Fensterklasse nur für lesbarkeit

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
	
	

	HWND hWnd = CreateWindowEx(

		WS_EX_OVERLAPPEDWINDOW,
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 350,							//position letztes taste abgreifen lies: höhe und breite des fensters sind dynamisch mit den tasten
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd) {
		MessageBox(NULL, _T("Call to CreateWindowEx failed!"), _T("Fehler"), MB_ICONERROR);
		return 1;
	}

	//Standard Werte
	const int defaultWidth = 40;
	const int defaultHeight = 30;
	const int spacing = 5;
	const int startX = 10;
	const int startY = 40;

	// Tastatur-Layout: Zeilen, Tasten
	std::vector<std::vector<std::wstring>> keyboardRows = {
		{ L"ESC",L"F1", L"F2", L"F3", L"F4", L"F5", L"F6", L"F7", L"F8", L"F9", L"F10", L"F11", L"F12"}, 
		{ L"^", L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"0", L"ß", L"´",L"BACK" },
		{ L"TAB", L"Q", L"W", L"E", L"R", L"T", L"Z", L"U", L"I", L"O", L"P", L"Ü", L"+" ,L"RETURN"},
		{ L"CAPS LOCK", L"A", L"S", L"D", L"F", L"G", L"H", L"J", L"K", L"L", L"Ö", L"Ä",L"#" },
		{ L"LSHIFT", L"<", L"Y", L"X", L"C", L"V", L"B", L"N", L"M", L",", L".", L"-",L"RSHIFT" },
		{ L"LCTRL", L"LWIN", L"ALT", L"SPACE", L"ALT GR", L"RWIN", L"MENU", L"RCTRL" }
	};

	// Beispiel: Zwei benutzerdefinierte Tasten
	
        // Update the initialization of the `customButtons` vector to ensure proper construction of `CustomButton` objects.  
        std::vector<CustomButton> customButtons = {  
            {L"ESC", startX, startY, 60, defaultHeight, spacing+45},  
			{L"F4", startX, startY, defaultWidth, defaultHeight, spacing+45},
			{L"F8", startX, startY, defaultWidth,defaultHeight, spacing + 45 },
            {L"BACK", startX, startY, 150, defaultHeight, spacing},  
            {L"TAB", startX, startY, 60, defaultHeight, spacing},  
			{L"+", startX, startY, 60, defaultHeight, spacing+15},
			{L"RETURN", startX, startY, 95, 2*defaultHeight+5,spacing},
            {L"CAPS LOCK", startX, startY, 90, defaultHeight, spacing},  
            {L"LSHIFT", startX, startY, 55, defaultHeight, spacing},  
            {L"RSHIFT", startX, startY, 180, defaultHeight, spacing},  
            {L"SPACE", startX, startY, 240, defaultHeight, spacing}  ,
			{ L"LCTRL", startX, startY, 65, defaultHeight, spacing },
			{ L"LWIN", startX, startY, 65, defaultHeight, spacing },
			{ L"ALT", startX, startY, 65, defaultHeight, spacing },
			{ L"ALT GR", startX, startY, 65, defaultHeight, spacing },
			{ L"RWIN", startX, startY, 65, defaultHeight, spacing },
			{ L"MENU", startX, startY, 65, defaultHeight, spacing },
			{ L"RCTRL", startX, startY, 70, defaultHeight, spacing },
		
		
			//Block2


			//Num

		
{
		   
}
	};

	std::vector<ButtonInfo> flatButtons;
	int y = startY;
	for (const auto& row : keyboardRows) {
		int x = startX;
		for (const auto& key : row) {
			// Standardwerte
			int w = defaultWidth;
			int h = defaultHeight;
			int s = spacing;

			// Prüfen, ob Taste benutzerdefiniert ist
			for (const auto& custom : customButtons) {
				if (custom.text == key) {
					w = custom.width;
					h = custom.height;
					s = custom.spacing;
					break;
				}
			}

			flatButtons.push_back({ key, x, y, w, h });
			x += w + s;
		}
		y += defaultHeight + spacing;
	}

	// Button-Erstellung
	for (size_t i = 0; i < flatButtons.size(); ++i) {
		const ButtonInfo& info = flatButtons[i];
		CreateWindowW(
			L"BUTTON",
			info.text.c_str(),
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			info.x, info.y, info.width, info.height,
			hWnd,
			(HMENU)(INT_PTR)(100 + i),
			hInst,
			NULL
		);
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


// Main message loop:
	MSG msg;                                     //msg wird hier als Feedback von windows verwendet   

	while (GetMessage(&msg, NULL, 0, 0)) // Check for messages in the queue.  
	{
		TranslateMessage(&msg); // Translate keyboard input messages.  
		DispatchMessage(&msg);  // Dispatch the message to the appropriate window procedure.  
	}


	return (int)msg.wParam;

}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
			greeting,int( _tcslen(greeting)));
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