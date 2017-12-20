#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include <X11/Xlib.h>
#include <X11/extensions/dpms.h>

char* monitor(BOOL onoff, CARD16 state) {
  if (!onoff) return "n/a";
  switch (state) {
  case DPMSModeOn: return "on";
  case DPMSModeStandby: return "standby";
  case DPMSModeSuspend: return "suspend";
  case DPMSModeOff: return "off";
  }
  return "n/a";
}

int main(int argc, char **argv) {
  Display* dpy = XOpenDisplay(argc > 1 ? argv[1] : getenv("DISPLAY"));
  if (!dpy) errx(1, "unable to open display");

  CARD16 state, standby, suspend, off;
  BOOL onoff;
  int dummy;

  if ( !(DPMSQueryExtension(dpy, &dummy, &dummy) && DPMSCapable(dpy)))
    errx(1, "no DPMS support");

  DPMSGetTimeouts(dpy, &standby, &suspend, &off);
  DPMSInfo(dpy, &state, &onoff);

  printf("dpms_status=%d\n"
	 "dpms_monitor=%s\n"
	 "dpms_standby=%d\n"
	 "dpms_suspend=%d\n"
	 "dpms_off=%d\n",
	 onoff, monitor(onoff, state), standby, suspend, off);
}
