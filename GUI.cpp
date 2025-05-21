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

//Funktion Modifizierter String
std::wstring ModifyString(const std::wstring& taste, const std::wstring& posx, const std::wstring& posy, const std::wstring& hight, const std::wstring& width) {
	{
	

	return posx, posy, hight, width; // Rückgabe des modifizierten Strings
}





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

	//Zeile 1 (Esc,F1 bis F12)

	//zeile 2 (^ Zahlen)
	
	//Zeile 3 (Tab, QWERTZ..)
	//wchar_t letters[] = { L'Q', L'W', L'E', L'R', L'T', L'Z', L'U', L'I',L'O', L'P'}; // Define the array of letters
	
	//Aussehen richtige tastatur
	//array mit arrays


	std::vector<std::wstring> parameterbutton = {10,10,600,60};


	std::vector<std::vector<std::wstring>>ArrayOfArrays;
	//Zeile 1 (Startet mit Esc und mit F12)
	//Unterteilung in 4 Stücke (Esc[größe ändern], 3x4 F-Tasten[Standard])
	//esc
	//F1 bis F12 (sequenz alle 4 Tasten Abstand von 1 Taste)
	std::vector<std::wstring>zeile1 = { L"ESC",L"F1", L"F2", L"F3", L"F4", L"F5", L"F6", L"F7", L"F8", L"F9", L"F10", L"F11", L"F12"};
	
	//zeile2 (Startet mit ^ und endet mit BACK)
	//keine Unterteilung, nur BACK taste doppelt so lang wie normal
	std::vector<std::wstring>zeile2 = { L"^", L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"0", L"ß", L"´",L"BACK" };

	//zeile3 (Startet mit Tab und endet mit +)
	//Tab länger, rest normal
	std::vector<std::wstring>zeile3 = { L"TAB", L"Q", L"W", L"E", L"R", L"T", L"Z", L"U", L"I", L"O", L"P", L"Ü", L"+" };
	
	//zeile4 (Startet mit Caps und endet mit #)
	//Caps länger als normal, rest normal
	std::vector<std::wstring>zeile4 = { L"CAPS LOCK", L"A", L"S", L"D", L"F", L"G", L"H", L"J", L"K", L"L", L"Ö", L"Ä",L"#" };

	//zeile5 (Startet mit lShift und endet mit rShift)
	//normal, rshift doppelt so lang wie normal
	std::vector<std::wstring>zeile5 = { L"LSHIFT", L"<", L"Y", L"X", L"C", L"V", L"B", L"N", L"M", L",", L".", L"-",L"RSHIFT" };

	//zeile6 (Startet mit lCtrl und endet mit rCtrl)
	//alle tastenlängen x 1.3, außer Space länge 6x normal
	std::vector<std::wstring>zeile6 = { L"CTRL", L"WIN", L"ALT", L"SPACE", L"ALT GR", L"WIN", L"MENU", L"CTRL" };


	//zeilen Arays werden in ArrayOfArrays gespeichert
	ArrayOfArrays.push_back(zeile1);
	ArrayOfArrays.push_back(zeile2);
	ArrayOfArrays.push_back(zeile3);
	ArrayOfArrays.push_back(zeile4);
	ArrayOfArrays.push_back(zeile5);
	ArrayOfArrays.push_back(zeile6);


	
	//Modifizieren der strinparamert

	for(auto& zeile : ArrayOfArrays) {
		for(auto& taste : zeile) {
			taste = ModifyString(posx, posy, hight, width); //Modifizieren der strinparamert 
		}
	}

		





	for (int i = 0; i < _countof(ArrayOfArrays); ++i) {


		// Fix for C6201: Ensure the buffer size is sufficient and correctly used  

		// Replace this line:  
		// wchar_t btnText[2] = { letters[i], L'\0' }; // Null-terminated string  

		// With the following code:  
		const wchar_t* btnText = ArrayOfArrays[i].c_str(); // Use c_str() to get a null-terminated wchar_t* from std::wstring

		int ypos = (i / 13) * 70 + 70;
		int xpos = (i % 13) * 100;




	//Modifizieren der strinparamert 
	
	

	

	//Taste = string mit parametern 
	//Struktur def. Höhe, breite, abstand, position


	//Ich will : den array positionen 4 Parameter zuordnen, wie die TAB taste ist länger als die ander, Q ist normal usw

	//doppelte vorschleife: läge Array und dann länge _array

	




		HWND Button = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed  
			btnText,    // Use the null-terminated string for the button text  //ArrayOfArrays wird ausgelesen : L"X"
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles  
			xpos,    // x position												//parameter für die positionx (abstand)
			ypos,    // y position												//parameter für die positiony	
			100,        // Button width											//parameter für die breite
			40,         // Button height										//parameter für die höhe
			(HWND)hWnd,       // Parent window
			hWnd,       // Parent window  
			NULL,       // No menu  
			(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
			NULL        // Pointer not needed  
		);

		// Fix for E0167: Use a null-terminated string (btnText) instead of a single wchar_t (letters[i])

		if (!hWnd || !Button)
		{
			MessageBox(NULL,
				_T("Call to CreateWindow failed!"),
				_T("Windows Desktop Guided Tour"),
				NULL);

			return 1;
		}

		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
	}



	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
							//Updatet window alle par ticks




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