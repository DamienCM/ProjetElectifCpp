// Jeu De La Vie.cpp : Définit le point d'entrée de l'application.
//

#include "framework.h"
#include "Jeu De La Vie.h"
#include "Log.h"
#include "Grille.h"
#include <thread>

#define MAX_LOADSTRING 100

// Variables globales :
std::thread myThread;
bool displayMode = false;
bool threadActive;
bool clickGaucheTriggered = false;
bool clickDroitTriggered = false;
bool initialisation = true;
bool variablecontrol = true;
int x, y;
Grille myGrille{ 100,50 };
Log logMain{ "logMain.txt" };
HINSTANCE hInst;                                // instance actuelle
WCHAR szTitle[MAX_LOADSTRING];                  // Texte de la barre de titre
WCHAR szWindowClass[MAX_LOADSTRING];            // nom de la classe de fenêtre principale

// Déclarations anticipées des fonctions incluses dans ce module de code :
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void periodicFunction(HWND hWnd);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Placez le code ici.

    // Initialise les chaînes globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_JEUDELAVIE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Effectue l'initialisation de l'application :
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_JEUDELAVIE));

    MSG msg;
    
    // Boucle de messages principale :

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
//  FONCTION : MyRegisterClass()
//
//  OBJECTIF : Inscrit la classe de fenêtre.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_JEUDELAVIE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(200, 200, 200)));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_JEUDELAVIE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FONCTION : InitInstance(HINSTANCE, int)
//
//   OBJECTIF : enregistre le handle d'instance et crée une fenêtre principale
//
//   COMMENTAIRES :
//
//        Dans cette fonction, nous enregistrons le handle de l'instance dans une variable globale, puis
//        nous créons et affichons la fenêtre principale du programme.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Stocke le handle d'instance dans la variable globale

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
//  FONCTION : WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  OBJECTIF : Traite les messages pour la fenêtre principale.
//
//  WM_COMMAND  - traite le menu de l'application
//  WM_PAINT    - Dessine la fenêtre principale
//  WM_DESTROY  - génère un message d'arrêt et retourne
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    x = (int)LOWORD(lParam)/10;					//Store the current x 
    y = (int)HIWORD(lParam)/10;

    switch (message)
    {
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analyse les sélections de menu :
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

        case WM_RBUTTONDOWN: {
            initialisation = false;
            clickDroitTriggered = true;
            displayMode = !displayMode;

        }
        break;
        case WM_RBUTTONUP: {
            clickDroitTriggered = false;
        }
        break;
        case WM_LBUTTONDOWN:
        {   
            if (initialisation) {
                if (myGrille.isAlive(x, y)) {
                    myGrille.kill(x, y);
                }
                else {
                    myGrille.resurrect(x, y);
                }
                myGrille.paint(hWnd, x, y);

            }
            clickGaucheTriggered = true;

        }
        break;

        case WM_LBUTTONUP: 
        {
            clickGaucheTriggered = false;
        }
        break;        
        
        case WM_PAINT:
        {   
            if (variablecontrol) {
                logMain.Error("Paint All déclenché !");
                myGrille.paintAll(hWnd);
                variablecontrol = false;
            }
            else {
                PAINTSTRUCT ps;
                HDC dc = BeginPaint(hWnd, &ps);

                // do drawing to 'dc' here -- or don't
                EndPaint(hWnd, &ps);
            }
        }
        break;

        
        case WM_MOUSEMOVE: 
        {
            if (clickGaucheTriggered && initialisation) {
                if (myGrille.isAlive(x, y)) {
                    myGrille.kill(x, y);
                }
                else {
                    myGrille.resurrect(x, y);
                }
                myGrille.paint(hWnd, x, y);

            }
        }
        break;
        
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    if (displayMode && !threadActive) {
        myThread=std::thread(periodicFunction, hWnd);
        threadActive = true;
        logMain.Error("Thread lancé");
    }
    else if (displayMode && threadActive) {

    }
    else {
        try {
            logMain.Error("thread joineds");
            myThread.join();
            threadActive = false;
        }
        catch(std::exception){
        }
    }
    return 0;

}
// Gestionnaire de messages pour la boîte de dialogue À propos de.
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


void periodicFunction(HWND hWnd) {
    while (displayMode)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        myGrille.update(hWnd);
        logMain.Error("error no update");
    }
}