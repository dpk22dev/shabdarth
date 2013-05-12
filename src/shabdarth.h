/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * shabdarth.h
 * Copyright (C) 2013 placement <placement@updesh-desktop>
 * 
 * shabdarth is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * shabdarth is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SHABDARTH_
#define _SHABDARTH_

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define SHABDARTH_TYPE_APPLICATION             (shabdarth_get_type ())
#define SHABDARTH_APPLICATION(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), SHABDARTH_TYPE_APPLICATION, Shabdarth))
#define SHABDARTH_APPLICATION_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), SHABDARTH_TYPE_APPLICATION, ShabdarthClass))
#define SHABDARTH_IS_APPLICATION(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SHABDARTH_TYPE_APPLICATION))
#define SHABDARTH_IS_APPLICATION_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), SHABDARTH_TYPE_APPLICATION))
#define SHABDARTH_APPLICATION_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), SHABDARTH_TYPE_APPLICATION, ShabdarthClass))

typedef struct _ShabdarthClass ShabdarthClass;
typedef struct _Shabdarth Shabdarth;
typedef struct _ShabdarthPrivate ShabdarthPrivate;

struct _ShabdarthClass
{
	GtkApplicationClass parent_class;
};

struct _Shabdarth
{
	GtkApplication parent_instance;

	ShabdarthPrivate *priv;

};

GType shabdarth_get_type (void) G_GNUC_CONST;
Shabdarth *shabdarth_new (void);

/* Callbacks */
void destroy (GtkWidget *widget, gpointer user_data);

void on_input_word_destroy (GtkWidget *widget, gpointer user_data);

gboolean on_input_word_selection_request_event (GtkWidget *widget, GdkEvent *event, gpointer user_data);

void on_input_word_selection_received (GtkWidget *widget, GtkSelectionData *selectiondata, guint arg, gpointer user_data);

void on_input_word_selection_get (GtkWidget *widget, GtkSelectionData *selectiondata, guint arg, guint arg1, gpointer user_data);

void on_input_word_activate (GtkEntry *entry, gpointer user_data);
void on_input_word_changed (GtkEditable *editable, gpointer user_data);
void on_treeview_cursor_changed (GtkTreeView *treeview, gpointer user_data);
void on_treeview_row_activated (GtkTreeView *treeview, GtkTreePath *treepath, GtkTreeViewColumn *treeviewcolumn, gpointer user_data);
void on_text_selection_changed(GtkClipboard *clipboard, GdkEvent *event, gpointer data);
G_END_DECLS

#endif /* _APPLICATION_H_ */
