#include "Window.h"

Window::Window(HWND &hwnd, HINSTANCE hInstance, int nCmdShow) : 
	hwnd(&hwnd), hInstance(hInstance), nCmdShow(nCmdShow),
	bkgColor(WHITE_BRUSH), fullScreen(false), name("DEFAULT"), title("DEFAULT") {

}

Window::~Window() {
	//DestroyWindow(*hwnd);
}

void Window::build() {
	WNDCLASSEX wcx;

//Build the properties of the main window
	wcx.cbClsExtra = 0;
	wcx.cbSize = sizeof(wcx);
	wcx.cbWndExtra = 0;
	wcx.hbrBackground = static_cast<HBRUSH>(GetStockObject(this->bkgColor));
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hIcon = NULL;
	wcx.hIconSm = NULL;
	wcx.hInstance = this->hInstance;
	wcx.lpfnWndProc = this->eventHandler;
	wcx.lpszClassName = this->name;
	wcx.lpszMenuName = NULL;
	wcx.style = CS_HREDRAW | CS_VREDRAW;

//Register the window class
	if (RegisterClassEx(&wcx) == 0) {
		//throw new Window_Error("FATAL ERROR: Could not register the window");
	}

//Create the style of the window
	DWORD style = this->fullScreen ? WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE : WS_OVERLAPPEDWINDOW;

//Create the winddow
	*hwnd = CreateWindow(
		this->name,
		this->title,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		this->width,
		this->height,
		static_cast<HWND>(NULL),
		static_cast<HMENU>(NULL),
		this->hInstance,
		static_cast<LPVOID>(NULL)
	);

	if (!this->hwnd) {
		//throw new Window_Error("FATAL ERROR: Could not create the window");
	}

//Adjust the size of the window to match the given dimensions
	if(!this->fullScreen) {
        RECT clientRect;
        GetClientRect(*hwnd, &clientRect);

        MoveWindow(
			*hwnd,
			0,
			0,
			this->width + (this->width - clientRect.right),
			this->height +(this->height - clientRect.bottom),
			TRUE
		);
    }

//Show the window
    ShowWindow(*hwnd, this->nCmdShow);
}

void Window::destroy() {
	DestroyWindow(*hwnd);
}