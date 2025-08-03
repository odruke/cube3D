#include "cube_test.h"
#include <limits.h>

int send_scp(pid_t pid) {
	char tty_path[1024];
	char ruta_fd0[1024];
	snprintf(ruta_fd0, sizeof(ruta_fd0), "/proc/%d/fd/0", pid);

	ssize_t len = readlink(ruta_fd0, tty_path, sizeof(tty_path)-1);
	if (len < 0) {
		perror("readlink");
		printf("readlink failed\n");
		return -1;
	}
	else
		printf("readlink success\n");

	tty_path[len] = '\0';

	int fd = open(tty_path, O_WRONLY);
	if (fd < 0) {
		printf("open tty failed\n");
		perror("open tty");
		return -1;
	}
	else
		printf("open tty success\n");

	char esc = 27; // 0x1B
	if (write(fd, &esc, 1) != 1) {
		printf("write failed\n");
		perror("write");
		close(fd);
		return -1;
	}
	else
		printf("write sucess\n");
	close(fd);
	return 0;
}

Window find_window_by_name(Display *dpy, Window root, const char *name) {
    Window returned_root, parent;
    Window *children;
    unsigned int nchildren;
    char *window_name = NULL;

    if (XFetchName(dpy, root, &window_name) && window_name) {
        if (strstr(window_name, name)) {
            XFree(window_name);
            return root;
        }
        XFree(window_name);
    }

    if (XQueryTree(dpy, root, &returned_root, &parent, &children, &nchildren)) {
        for (unsigned int i = 0; i < nchildren; i++) {
            Window w = find_window_by_name(dpy, children[i], name);
            if (w) {
                XFree(children);
                return w;
            }
        }
        if (children) XFree(children);
    }
    return 0;
}

int send_escape_key_x11(pid_t pid)
{
	(void)pid;
    Display *dpy = XOpenDisplay(NULL);
    if (!dpy) return -1;
	Window root;
	Window win;
	root = DefaultRootWindow(dpy);
	win = find_window_by_name(dpy, root, "cub3D");

    // Find window belonging to the process
    // Send actual X11 KeyPress event
    // KeyCode keycode = XKeysymToKeycode(display, XK_Escape);
    // XTestFakeKeyEvent(display, keycode, True, 0);
    // XTestFakeKeyEvent(display, keycode, False, 0);
    // XFlush(display);


    XKeyEvent ev;
    KeyCode kc = XKeysymToKeycode(dpy, XK_Escape);
    if (!kc) {
        fprintf(stderr, "No pude traducir XK_Escape\n");
        return -1;
    }
    // Parámetros comunes
    ev.display     = dpy;
    ev.window      = win;
    ev.root        = DefaultRootWindow(dpy);
    ev.subwindow   = None;
    ev.time        = CurrentTime;
    ev.x           = ev.y = ev.x_root = ev.y_root = 0;
    ev.same_screen = True;
    ev.state       = 0;
    ev.keycode     = kc;

    // KeyPress
    ev.type = KeyPress;
    if (XSendEvent(dpy, win, True, KeyPressMask, (XEvent*)&ev) == 0) {
        fprintf(stderr, "Error en XSendEvent press\n");
        return -1;
    }
    // KeyRelease
    ev.type = KeyRelease;
    if (XSendEvent(dpy, win, True, KeyReleaseMask, (XEvent*)&ev) == 0) {
        fprintf(stderr, "Error en XSendEvent release\n");
        return -1;
    }
    XFlush(dpy);
    return 0;

    XCloseDisplay(dpy);
    return 0;
}
