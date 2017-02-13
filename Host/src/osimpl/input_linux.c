#include <X11/extensions/XTest.h>
#include <X11/extensions/dpms.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>

/*static void WakeUp(Display *display) {
	CARD16 power_level = 0;
	BOOL state = 0;
	Status status = 0;

	status = DPMSInfo(display, &power_level, &state);
	if (status && state && power_level)
		DPMSForceLevel(display, 0);

	XResetScreenSaver(display);
}*/

static inline void SendKeycode(int keyCode) {
	Display *display = XOpenDisplay(NULL);
	if (display != NULL) {
		//WakeUp(display);

		switch (keyCode)
		{
		case 8:
			XTestFakeKeyEvent(display, XKeysymToKeycode(display, 0xff08), True, CurrentTime );
			XTestFakeKeyEvent(display, XKeysymToKeycode(display, 0xff08), False, CurrentTime );
			break;

		case 13:
			XTestFakeKeyEvent(display, XKeysymToKeycode(display, 0xff0d), True, CurrentTime );
			XTestFakeKeyEvent(display, XKeysymToKeycode(display, 0xff0d), False, CurrentTime );
			break;
		}
		XFlush(display);
		XCloseDisplay(display);
	}
}

static inline void SendKeysymWithShiftKey(int keySym) {
	Display *display = XOpenDisplay(NULL);
	KeyCode kc;
	if (display != NULL) {
		// set keycode
		kc = XKeysymToKeycode(display, keySym);

		// if the specified KeySym is defined
		if (kc != 0) {
			//WakeUp(display);

			kc = XKeysymToKeycode (display, XK_Shift_L);
			XTestFakeKeyEvent(display, kc, True, CurrentTime);
			XFlush(display);

			kc = XKeysymToKeycode(display, keySym);
			XTestFakeKeyEvent(display, kc, True, CurrentTime );
			XTestFakeKeyEvent(display, kc, False, CurrentTime );
			XFlush(display);

			kc = XKeysymToKeycode (display, XK_Shift_L);
			XTestFakeKeyEvent(display, kc, False, CurrentTime);
			XFlush(display);
		}
		XCloseDisplay(display);
	}
}

static inline void SendKeysym(int keySym) {
	Display *display = XOpenDisplay(NULL);
	KeyCode kc;
	if (display != NULL) {
		// set keycode
		kc = XKeysymToKeycode(display, keySym);
		// if the specified KeySym is defined
		if (kc != 0) {
                	//WakeUp(display);
			XTestFakeKeyEvent(display, kc, True, CurrentTime );
			XTestFakeKeyEvent(display, kc, False, CurrentTime );
			XFlush(display);
		}
		XCloseDisplay(display);
	}
}

static inline void SendClick(int button, Bool down) {
	Display *display = XOpenDisplay(NULL);
	if (display != NULL) {
                //WakeUp(display);

		XTestFakeButtonEvent(display, button, down, CurrentTime);
		XFlush(display);
		XCloseDisplay(display);
	}
}

static inline void SendMouseMove(int X, int Y) {
	Display *display = XOpenDisplay(NULL);
	if (display != NULL) {
                //WakeUp(display);

		XTestFakeRelativeMotionEvent(display, X, Y, CurrentTime);
		XFlush(display);
		XCloseDisplay(display);
	}
}
