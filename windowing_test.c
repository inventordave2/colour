#include <stdio.h>
#include <SDL2/SDL.h>

#ifdef _WIN32
#include <windows.h>
#include <ole2.h>
#include <objbase.h>
#endif

// Window structure
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width;
    int height;
#ifdef _WIN32
    HWND hwnd; // Native Windows handle
    HWND com_hwnd; // COM object window handle
#endif
} Window;

// Initialize SDL and create window
Window *create_window(const char *title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return NULL;
    }

    Window *win = (Window *)malloc(sizeof(Window));
    win->width = width;
    win->height = height;
    win->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  width, height, SDL_WINDOW_SHOWN);
    if (!win->window) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        free(win);
        return NULL;
    }

    win->renderer = SDL_CreateRenderer(win->window, -1, SDL_RENDERER_ACCELERATED);
    if (!win->renderer) {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(win->window);
        SDL_Quit();
        free(win);
        return NULL;
    }

#ifdef _WIN32
    // Get native HWND
    SDL_SysWMinfo wminfo;
    SDL_VERSION(&wminfo.version);
    if (SDL_GetWindowWMInfo(win->window, &wminfo)) {
        win->hwnd = wminfo.info.win.window;
    } else {
        fprintf(stderr, "SDL_GetWindowWMInfo failed: %s\n", SDL_GetError());
        win->com_hwnd = NULL;
    }
#else
    // Non-Windows placeholder
#endif

    return win;
}

// Destroy window and cleanup
void destroy_window(Window *win) {
    if (!win) return;
#ifdef _WIN32
    if (win->com_hwnd) DestroyWindow(win->com_hwnd);
#endif
    if (win->renderer) SDL_DestroyRenderer(win->renderer);
    if (win->window) SDL_DestroyWindow(win->window);
    free(win);
    SDL_Quit();
}

// Windows-specific: Embed a COM object (e.g., WebBrowser control)
#ifdef _WIN32
int attach_com_object(Window *win, const char *prog_id, int x, int y, int width, int height) {
    HRESULT hr = CoInitialize(NULL); // Initialize COM
    if (FAILED(hr)) {
        fprintf(stderr, "CoInitialize failed: %lx\n", hr);
        return 0;
    }

    // Convert prog_id to CLSID
    CLSID clsid;
    hr = CLSIDFromProgID(OLESTR(prog_id), &clsid);
    if (FAILED(hr)) {
        fprintf(stderr, "CLSIDFromProgID failed: %lx\n", hr);
        CoUninitialize();
        return 0;
    }

    // Create instance of COM object
    IOleObject *ole_obj = NULL;
    hr = CoCreateInstance(&clsid, NULL, CLSCTX_INPROC_SERVER, &IID_IOleObject, (void **)&ole_obj);
    if (FAILED(hr)) {
        fprintf(stderr, "CoCreateInstance failed: %lx\n", hr);
        CoUninitialize();
        return 0;
    }

    // Set up IOleClientSite and IOleInPlaceSite (simplified, implement as needed)
    // Embed into window
    hr = OleSetClientSite(ole_obj, NULL); // Minimal client site
    if (FAILED(hr)) {
        fprintf(stderr, "OleSetClientSite failed: %lx\n", hr);
        ole_obj->lpVtbl->Release(ole_obj);
        CoUninitialize();
        return 0;
    }

    // Activate and show the object
    hr = ole_obj->lpVtbl->DoVerb(ole_obj, OLEIVERB_SHOW, NULL, NULL, win->hwnd, NULL);
    if (FAILED(hr)) {
        fprintf(stderr, "DoVerb failed: %lx\n", hr);
        ole_obj->lpVtbl->Release(ole_obj);
        CoUninitialize();
        return 0;
    }

    // Get the window handle of the COM object
    IOleWindow *ole_win = NULL;
    hr = ole_obj->lpVtbl->QueryInterface(ole_obj, &IID_IOleWindow, (void **)&ole_win);
    if (SUCCEEDED(hr)) {
        ole_win->lpVtbl->GetWindow(ole_win, &win->com_hwnd);
        ole_win->lpVtbl->Release(ole_win);
    }

    // Position the COM window
    if (win->com_hwnd) {
        SetWindowPos(win->com_hwnd, HWND_TOP, x, y, width, height, SWP_SHOWWINDOW);
    }

    ole_obj->lpVtbl->Release(ole_obj);
    CoUninitialize();
    return 1;
}
#else
// Non-Windows placeholder for COM
int attach_com_object(Window *win, const char *prog_id, int x, int y, int width, int height) {
    fprintf(stderr, "COM objects are not supported on this platform.\n");
    return 0;
}
#endif

// Render a placeholder for non-Windows or fallback
void render_fallback(Window *win, int x, int y, int width, int height) {
    SDL_SetRenderDrawColor(win->renderer, 200, 200, 200, 255);
    SDL_Rect rect = { x, y, width, height };
    SDL_RenderFillRect(win->renderer, &rect);
    SDL_SetRenderDrawColor(win->renderer, 0, 0, 0, 255);
    // Could add text rendering with SDL_ttf if needed
}

// Main loop
void run_event_loop(Window *win) {
    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Clear renderer
        SDL_SetRenderDrawColor(win->renderer, 255, 255, 255, 255);
        SDL_RenderClear(win->renderer);

        // Render fallback for non-Windows or if COM failed
#ifndef _WIN32
        render_fallback(win, 50, 50, 200, 150);
#endif

        SDL_RenderPresent(win->renderer);
        SDL_Delay(10);
    }
}

int main() {
    Window *win = create_window("GUI with COM", 800, 600);
    if (!win) return 1;

#ifdef _WIN32
    // Example: Embed WebBrowser control (Internet Explorer)
    if (!attach_com_object(win, "Shell.Explorer", 50, 50, 700, 500)) {
        fprintf(stderr, "Failed to attach COM object, falling back to placeholder.\n");
        render_fallback(win, 50, 50, 700, 500);
    }
#else
    render_fallback(win, 50, 50, 700, 500);
#endif

    run_event_loop(win);
    destroy_window(win);
    return 0;
}

