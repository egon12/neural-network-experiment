#include "line_chart.h"
#include <cairo-xlib.h>
#include <stdio.h>

// Variable as a config
int width = 800;

int height = 600;

// Shared variables that need init
cairo_t *cairo;

Window w;

Display *dpy;

// data variables
float *data;

int data_length;

// private function
void paint();

void init_cairo();

void loop_gtk();

float max_from_data();

float min_from_data();

// exported function
int graph_draw_line_chart(float _data[], int data_length) {

  data = _data;

  data_length = _data_length;

  init_cairo();

  // calling paint in the loop
  loop_gtk();

  return 0;
}

void paint() {

  cairo_set_source_rgb(cairo, 1.0, 0.5 ,1.0);

  int gap = width / data_length;
  float max = max_from_data();
  float scale =  height / max;

  cairo_move_to(cairo, 0.0, 0.0);
  for (int i=0; i<data_length; i++) {
    float y = (float) height - scale * data[i];
    cairo_line_to(cairo, (float) i * gap, y);
  }
  cairo_stroke(cairo);

}

float max_from_data() {
  if (data_length < 1) {
    return 1.0;
  }

  float max = data[0];

  for (int i=1; i<data_length; i++) {
    if (max < data[i]) {
      max = data[i];
    }
  }

  return max;
}

float min_from_data() {
  if (data_length < 1) {
    return 1.0;
  }

  float min = data[0];

  for (int i=1; i<data_length; i++) {
    if (min > data[i]) {
      min = data[i];
    }
  }

  return min;
}


void init_cairo() {

  dpy = XOpenDisplay(NULL);

  w = XCreateSimpleWindow(dpy, RootWindow(dpy, 0), 300, 200, width, height, 0, 0, WhitePixel(dpy, 0));
  XSetWindowAttributes winattr;
  winattr.override_redirect = 1;
  XChangeWindowAttributes(dpy, w, CWOverrideRedirect, &winattr);

  XSelectInput(dpy, w, StructureNotifyMask | ExposureMask);
  XMapWindow(dpy, w);

  cairo_surface_t *surface;

  surface = cairo_xlib_surface_create(dpy, w, DefaultVisual(dpy, 0), width, height);
  cairo = cairo_create(surface);
}



void loop_gtk() {

  while (1) {
    XEvent e;
    XNextEvent(dpy, &e);

    switch (e.type) {
      case MapNotify:
      case ConfigureNotify:
      case Expose:
        paint();
        break;
    }
  }
}



/*

int main() {
  float data[] = {
    99.0,
    631.0,
    653.0,
    314.0,
    788.0,
    994.0,
    502.0,
    598.0,
    060.0,
    522.0,
    13.0,
    695.0,
    67.0,
    766.0,
    731.0,
    455.0,
    20.0,
    32.0,
    82.0,
    938.0,
    78.0,
    507.0,
    406.0,
    84.0,
    970.0,
    749.0,
    650.0,
    04.0,
    534.0
  };


  drawplot(data, sizeof(data) / sizeof(data[0]));
}
/**

default:
 g++ `pkg-config --cflags cairo` mainx2.c plotdrawer.c -lcairo -lX11
 ./a.out



  */

