#include <gtk/gtk.h>

static void draw_brush(GtkWidget *widget, gdouble x, gdouble y) {
    cairo_t *cr;
    cr = gdk_cairo_create(gtk_widget_get_window(widget));
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_rectangle(cr, x - 2, y - 2, 4, 4);
    cairo_fill(cr);
    cairo_destroy(cr);
}

static gboolean on_button_press(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        draw_brush(widget, event->x, event->y);
    }
    return TRUE;
}

static gboolean on_motion_notify(GtkWidget *widget, GdkEventMotion *event, gpointer user_data) {
    if (event->state & GDK_BUTTON1_MASK) {
        draw_brush(widget, event->x, event->y);
    }
    return TRUE;
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *drawing_area;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Paint with GTK");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    g_signal_connect(drawing_area, "button-press-event", G_CALLBACK(on_button_press), NULL);
    g_signal_connect(drawing_area, "motion-notify-event", G_CALLBACK(on_motion_notify), NULL);

    gtk_widget_add_events(drawing_area, GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
