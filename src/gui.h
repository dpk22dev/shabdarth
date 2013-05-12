#ifndef GUI_H
#define GUI_H

#include <glib.h>
#include <gtk/gtk.h>

#define ALPHABETS 26

enum{
	LIST_ITEM = 0,
	N_COLOUMNS
};

typedef enum{
		A=0,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z
}pop_list_type;

struct MyData{
	GHashTable *hash_tab[ ALPHABETS ];
	GtkListStore* list_store;
	GtkWidget* window;
	GtkStatusbar* statusbar;
	gint statusbar_context_id; 	
	GtkTextView* meaning_text_view;
	GtkTreeView* treeview;
	GtkEntry* input_word;
	GtkListStore* list_store_arr[ ALPHABETS ];
}mydata;

#endif