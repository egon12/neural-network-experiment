#include "line_chart.h"
#include <cairo-xlib.h>
#include <stdio.h>

// Variable as a config
int width = 800;
int height = 600;

int padding_right  = 30;
int padding_top    = 30;
int padding_left   = 30;
int padding_bottom = 30;

// Shared variables that need init
cairo_t *cairo;
Window w;
Display *dpy;

// data variables
float *data;
int data_length;

float x_scale_multiplier;
float y_scale_multiplier;

// private function
void paint();
void init_cairo();
void loop_gtk();
void set_x_scale();
void set_y_scale();
float scale_x(int input);
float scale_y(float input);
float max_from_data();
float min_from_data();

// exported function
int graph_draw_line_chart(float _data[], int _data_length) {

  data = _data;

  data_length = _data_length;

  set_x_scale();

  set_y_scale();
  printf("x = %f, y = %f \n", x_scale_multiplier, y_scale_multiplier);

  init_cairo();

  // calling paint in the loop
  loop_gtk();

  return 0;
}

void paint() {

  cairo_set_source_rgb(cairo, 1.0, 0.5 ,1.0);

  cairo_move_to(cairo, padding_left, height - padding_bottom);
  for (int i=0; i<data_length; i++) {
    cairo_line_to(cairo, scale_x(i), scale_y(data[i]));
  }
  cairo_stroke(cairo);

}

void set_x_scale() {
  x_scale_multiplier = (width - padding_left - padding_right) / data_length + 1;
}

void set_y_scale() {
  y_scale_multiplier = (height - padding_top - padding_bottom) / max_from_data();
}

float scale_x(int input) {
  return padding_left + x_scale_multiplier * (float) input;
}

float scale_y(float input) {
  return height - padding_bottom - y_scale_multiplier *  input;
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

  w = XCreateSimpleWindow(dpy, RootWindow(dpy, 0), 0, 0, width, height, 0, 0, WhitePixel(dpy, 0));
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



