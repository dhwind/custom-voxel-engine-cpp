
#ifndef WINDOW_EVENTS_HPP
#define WINDOW_EVENTS_HPP

class Events
{
public:
    static bool *_keys;
    static unsigned int *_frames;
    static unsigned int _current;

    static float deltaX;
    static float deltaY;
    static float x;
    static float y;

    static bool _cursor_locked;
    static bool _cursor_started;

    static int initialize();
    static void pullEvents();

    static bool pressed(int keycode);
    static bool jpressed(int keycode);

    static bool clicked(int button);
    static bool jclicked(int button);

    static void toggleCursorLock();
};

#endif // WINDOW_EVENTS_HPP