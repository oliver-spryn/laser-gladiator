#include <Windows.h>

class Window {
public : 
	Window(HWND &hwnd, HINSTANCE hInstance, int nCmdShow);
	~Window();

	void build();
	void destroy();

	int getBkgColor() const { return this->bkgColor; }
	bool getFullScreen() const { return this->fullScreen; }
	UINT getHeight() const { return this->height; }
	const char* getName() const { return this->name; }
	const char* getTitle(char*) const { return this->title; }
	UINT getWidth() const { return this->width; }

	void setBkgColor(int bkgColor) { this->bkgColor = bkgColor; }
	void setEventHandler(WNDPROC eventHandler) { this->eventHandler = eventHandler; }
	void setFullScreen(bool fullScreen) { this->fullScreen = fullScreen; }
	void setHeight(UINT height) { this->height = height; }
	void setName(const char* name) { this->name = name; }
	void setTitle(const char* title) { this->title = title; }
	void setWidth(UINT width) { this->width = width; }

private : 
	int bkgColor;
	WNDPROC eventHandler;
	bool fullScreen;
	UINT height;
	HINSTANCE hInstance;
	HWND* hwnd;
	const char *name;
	int nCmdShow;
	const char *title;
	UINT width;
};