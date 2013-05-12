/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * shabdarth.c
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
#include "shabdarth.h"

#include <glib.h>
#include <glib/gi18n.h>
#include <glib/gprintf.h>
#include <ctype.h>
#include <gdk/gdk.h>

#include "read_db.h"
#include "gui.h"
#include "list_func.h"

/* For testing propose use the local (not installed) ui file */
/* #define UI_FILE PACKAGE_DATA_DIR"/ui/shabdarth.ui" */
#define FILE_PREFIX "/usr/local/share/shabdarth/"

#define ANJUTA_UI_PREFIX "src/"
#define ANJUTA_DBS_PREFIX "dbs/"

#define APP_UI_PREFIX "ui/"
#define APP_DBS_PREFIX "dbs/"

#define UI_FILE FILE_PREFIX APP_UI_PREFIX "shabdarth.ui"
#define APP_DBS FILE_PREFIX APP_DBS_PREFIX
#define TOP_WINDOW "window"
#define FILE_NAME_LENGTH_SIZE 20

G_DEFINE_TYPE (Shabdarth, shabdarth, GTK_TYPE_APPLICATION);

GtkEntryBuffer *buffer = NULL;
gchar file_loaded_name[FILE_NAME_LENGTH_SIZE];

pop_list_type list_loaded;
/* Define the private structure in the .c file */
#define SHABDARTH_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), SHABDARTH_TYPE_APPLICATION, ShabdarthPrivate))

struct _ShabdarthPrivate
{
	/* ANJUTA: Widgets declaration for shabdarth.ui - DO NOT REMOVE */
	GtkWidget* treeview;
};


/* Create a new window loading a file */
static void
shabdarth_new_window (GApplication *app,
                           GFile        *file)
{
	GtkWidget *window;

	GtkBuilder *builder;
	GError* error = NULL;

	ShabdarthPrivate *priv = SHABDARTH_GET_PRIVATE(app);

	/* Load UI from file */
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_FILE, &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (builder, app);

	/* Get the window object from the ui file */
	mydata.window = GTK_WIDGET (gtk_builder_get_object (builder, TOP_WINDOW));
        if (!mydata.window)
        {
		g_critical ("Widget \"%s\" is missing in file %s.",
				TOP_WINDOW,
				UI_FILE);
        }
	mydata.statusbar = GTK_STATUSBAR (gtk_builder_get_object(builder, "statusbar"));
	mydata.meaning_text_view = GTK_TEXT_VIEW (gtk_builder_get_object(builder, "meaning_text_view"));
	mydata.treeview = GTK_TREE_VIEW (gtk_builder_get_object(builder, "treeview"));
	mydata.input_word = GTK_ENTRY (gtk_builder_get_object(builder, "input_word"));

//
	mydata.statusbar_context_id = gtk_statusbar_get_context_id ( mydata.statusbar,"shabdarth");

int i = 0;
	for( i = 0; i < ALPHABETS; i++ )
		mydata.hash_tab[i] = NULL;

// ************ initialising list_store_arr ************
	for( i = 0; i < ALPHABETS; i++ )
		mydata.list_store_arr[i] = NULL;	
	
	gtk_tree_view_set_headers_visible ( mydata.treeview, FALSE );
//************ clipboard ************** 
	//try GDK_SELECTION_CLIPBOARD or PRIMARY 
	GtkClipboard* clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
	g_signal_connect(clipboard, "owner_change",G_CALLBACK(on_text_selection_changed), NULL);
	
	/* ANJUTA: Widgets initialization for shabdarth.ui - DO NOT REMOVE */
	priv->treeview = GTK_WIDGET (gtk_builder_get_object(builder, "treeview"));
	g_object_unref (builder);
	
	
	gtk_window_set_application (GTK_WINDOW (mydata.window), GTK_APPLICATION (app));
	if (file != NULL)
	{
		/* TODO: Add code here to open the file in the new window */
	}
	gtk_widget_show_all (GTK_WIDGET (mydata.window));

	gtk_statusbar_pop ( mydata.statusbar, mydata.statusbar_context_id );
	gtk_statusbar_push (GTK_STATUSBAR (mydata.statusbar), mydata.statusbar_context_id, "Please enter a word");
	
}


/* GApplication implementation */
static void
shabdarth_activate (GApplication *application)
{
  shabdarth_new_window (application, NULL);
	buffer = gtk_entry_buffer_new (NULL, 0);
	init_list();
}

static void
shabdarth_open (GApplication  *application,
                     GFile        **files,
                     gint           n_files,
                     const gchar   *hint)
{
  gint i;

  for (i = 0; i < n_files; i++)
    shabdarth_new_window (application, files[i]);
}

static void
shabdarth_init (Shabdarth *object)
{

}

static void
shabdarth_finalize (GObject *object)
{

	G_OBJECT_CLASS (shabdarth_parent_class)->finalize (object);
}

static void
shabdarth_class_init (ShabdarthClass *klass)
{
	G_APPLICATION_CLASS (klass)->activate = shabdarth_activate;
	G_APPLICATION_CLASS (klass)->open = shabdarth_open;

	g_type_class_add_private (klass, sizeof (ShabdarthPrivate));

	G_OBJECT_CLASS (klass)->finalize = shabdarth_finalize;
}

Shabdarth *
shabdarth_new (void)
{
	g_type_init ();

	return g_object_new (shabdarth_get_type (),
	                     "application-id", "org.gnome.shabdarth",
	                     "flags", G_APPLICATION_HANDLES_OPEN,
	                     NULL);
}

void load_hashtable_list( ){

		char *word = NULL, *entry_word = NULL;
	
		entry_word = gtk_entry_get_text ( mydata.input_word );	
		//	word = g_strchomp( g_strchug( g_strdown( entry_word ) ) );
		//  it has caused a Pango: index out of bound bug so use instead
		word = g_strdown( entry_word );
	
	//
		if( ! isalpha( word[0] ) ){
			//g_print("on_input_word_changed(): enter proper word\n");
			// ************** show proper warning to enter proper word *****************
//
			gtk_statusbar_pop ( mydata.statusbar, mydata.statusbar_context_id );
			gtk_statusbar_push (GTK_STATUSBAR (mydata.statusbar), mydata.statusbar_context_id, "Please enter/select proper english word");
//
			return;
		}								
		//check if hash table is created for word[0] of not
		g_sprintf( file_loaded_name, APP_DBS"%c.db", g_ascii_tolower( word[0] ) );
		//g_print("on_input_word_changed(): filename = %s\n",file_loaded_name);
		
		if( mydata.hash_tab[ g_ascii_toupper(word[0]) - 'A' ] == NULL ){
			//remove the prev word entries
			//remove_all_from_list ();
			//g_print("on_input_word_changed(): generating hash table\n");
			mydata.hash_tab[ g_ascii_toupper(word[0]) - 'A' ] = generate_hash_table( file_loaded_name );
			mydata.list_store_arr[ g_ascii_toupper(word[0]) - 'A' ] = mydata.list_store;
			list_loaded = g_ascii_toupper(word[0]) - 'A';
			//check if hash table is created or not by generate_hash_table() func call				 
			if( mydata.hash_tab[ g_ascii_toupper(word[0]) - 'A' ] == NULL ){
				g_print("on_input_word_changed():\nafter trying to generate_hash_table\nfile: %s could not be located and loaded\n", file_loaded_name );
			}						 
		}else{
			//g_print("on_input_word_changed(): %d", list_loaded );
			if( list_loaded != (g_ascii_toupper(word[0]) - 'A') ){
				//remove_all_from_list ();
//************   we have change here to fasten************ -------------->>>>>>>>>
//load list from pointer else populate it			
				if( mydata.list_store_arr[ g_ascii_toupper(word[0]) - 'A' ] == NULL ){
					populate_list_only( file_loaded_name );
					//g_print("on_input_word_changed(): list populated from file\n" );
				}else{					
					mydata.list_store = mydata.list_store_arr[ g_ascii_toupper(word[0]) - 'A' ];
//					following may be necessary		  
					gtk_tree_view_set_model ( mydata.treeview, GTK_TREE_MODEL(mydata.list_store) );
					//g_print("on_input_word_changed(): list used from previous list\n" );
				}
				
				list_loaded = (g_ascii_toupper(word[0]) - 'A');
			}
		}	
	//
	
}

void on_text_selection_changed(GtkClipboard *clipboard, GdkEvent *event, gpointer data)
{
	char* text = gtk_clipboard_wait_for_text(clipboard), *word =  NULL;
    if(text)
    {
	//printf("%s\n", text);
	//gtk_clipboard_clear(clipboard);
	//gtk_clipboard_set_text( clipboard, "", 0 );
		word = g_strdup( g_strchomp ( g_strchug ( g_strdown( text ) ) ) );
		gtk_entry_set_text ( mydata.input_word, word );
		load_hashtable_list( );
		on_find_clicked();
    }
	free( text );
	free( word );
}

void
on_find_clicked ( )
{

	GtkTextBuffer *buffer;
	
	buffer = gtk_text_view_get_buffer ( mydata.meaning_text_view );	
	gtk_text_buffer_set_text ( buffer, "",-1);

	char *word, *entry_word;
	entry_word = gtk_entry_get_text ( mydata.input_word );
	
	word = g_strchomp( g_strchug( g_strdown( entry_word ) ) );
	//g_string_ascii_down () instead for comp
	
/*
	********** convert data. to mydata. **************
	gchar *message = g_strdup_printf("Finding word %s", word);	
	gtk_statusbar_pop( mydata.statusbar, mydata.statusbar_context_id );
//	data.statusbar_context_id = gtk_statusbar_get_context_id ( data.statusbar,"on_find_clicked");
	gtk_statusbar_push( data.statusbar, data.statusbar_context_id, message);
*/	
	if( strlen(word) != 0 )
		find_meaning_put_gui( word );
	//gtk_widget_show( data.window );	
	//gtk_statusbar_pop( data.statusbar, data.statusbar_context_id );
	//gtk_statusbar_push( data.statusbar, data.statusbar_context_id,"Fill or choose a word" );
	
}

void
on_input_word_activate (GtkEntry *entry, gpointer user_data)
{

	char *word = NULL, *entry_word = NULL;
	
	entry_word = gtk_entry_get_text ( mydata.input_word );	
	word = g_strchomp( g_strchug( g_strdown( entry_word ) ) );

	if( strlen( word ) == 0 ){
		//g_print("on_input_word_activate():word is NULL\n");
		//avoid some latency by commenting below
//
		gtk_statusbar_pop ( mydata.statusbar, mydata.statusbar_context_id );
		gtk_statusbar_push (GTK_STATUSBAR (mydata.statusbar), mydata.statusbar_context_id, "Please enter a word");
//		remove_all_from_list();	// empty the list as there is no word to search for									
//		if we empty the list it causes a bug of not loading the list of same word although
//		hash table is still there
	}else{
		//it is cause of latency
//		g_print("on_input_word_activate():word= %s\n", word );
		if( ! isalpha( word[0] ) ){
			//g_print("on_input_word_activate(): enter proper word\n");
			// *************** show proper warning to enter proper word **********************
//
			gtk_statusbar_pop ( mydata.statusbar, mydata.statusbar_context_id );
			gtk_statusbar_push (GTK_STATUSBAR (mydata.statusbar), mydata.statusbar_context_id, "Please enter proper english word");
//
			return;
		}								
		//check if hash table is created for word[0] of not
		g_sprintf( file_loaded_name, APP_DBS"%c.db", g_ascii_tolower( word[0] ) );
//		g_print("on_input_word_activate(): filename = %s\n",file_loaded_name);
		
		if( mydata.hash_tab[ g_ascii_toupper(word[0]) - 'A' ] == NULL ){
			//remove the prev word entries
			//remove_all_from_list ();
//			g_print("on_input_word_activate(): generating hash table\n");
			mydata.hash_tab[ g_ascii_toupper(word[0]) - 'A' ] = generate_hash_table( file_loaded_name );
			mydata.list_store_arr[ g_ascii_toupper(word[0]) - 'A' ] = mydata.list_store;
			list_loaded = g_ascii_toupper(word[0]) - 'A';
			//check if hash table is created or not by generate_hash_table() func call				 
			if( mydata.hash_tab[ g_ascii_toupper(word[0]) - 'A' ] == NULL ){
				g_print("on_input_word_activate():\nafter trying to generate_hash_table\nfile: %s could not be located and loaded\n", file_loaded_name );
			}						 
		}else{
			//g_print("on_input_word_activate(): %d", list_loaded );
			if( list_loaded != (g_ascii_toupper(word[0]) - 'A') ){				
				//
				if( mydata.list_store_arr[ g_ascii_toupper(word[0]) - 'A' ] == NULL ){
					populate_list_only( file_loaded_name );
					//g_print("on_input_word_changed(): list populated from file\n" );
				}else{					
					mydata.list_store = mydata.list_store_arr[ g_ascii_toupper(word[0]) - 'A' ];
//					following may be necessary		  
					gtk_tree_view_set_model ( mydata.treeview, GTK_TREE_MODEL(mydata.list_store) );
					//g_print("on_input_word_changed(): list used from previous list\n" );
				}
				
				list_loaded = (g_ascii_toupper(word[0]) - 'A');
				//
			}
		}	
			
	}
	
	on_find_clicked();
	
}

void
on_treeview_cursor_changed (GtkTreeView *treeview, gpointer user_data)
{
//	g_print("on treeview cursor changed called\n");
	GtkTreeModel *model;
	GtkTreeIter iter;
	gchar *word = NULL;
	GtkTreeSelection *selection;

	selection = gtk_tree_view_get_selection ( mydata.treeview );
		
	if( gtk_tree_selection_get_selected (  selection , &model, &iter ) ){
		gtk_tree_model_get ( model, &iter, LIST_ITEM, &word, -1);
		//cause of latency
		//g_print("row selection: %s\n", word);
		gtk_entry_set_text ( mydata.input_word, g_strdup(word) );
//
		gtk_statusbar_pop ( mydata.statusbar, mydata.statusbar_context_id );
		gtk_statusbar_push (GTK_STATUSBAR (mydata.statusbar), mydata.statusbar_context_id, "searching for selected word");
//
		on_find_clicked ();			
	}	
	g_free( word );
	
}

void
on_treeview_row_activated (GtkTreeView *treeview, GtkTreePath *treepath, GtkTreeViewColumn *treeviewcolumn, gpointer user_data)
{
	GtkTreeModel *model;
	GtkTreeIter iter;
	gchar *word;
	
	model = gtk_tree_view_get_model ( mydata.treeview );
	
	if( gtk_tree_model_get_iter ( model, &iter, treepath ) ){
			gtk_tree_model_get ( model, &iter, LIST_ITEM, &word, -1);
			//g_print("double click: row contains %s\n", word);
	}

	gtk_entry_set_text ( mydata.input_word, g_strdup(word) );
//
		gtk_statusbar_pop ( mydata.statusbar, mydata.statusbar_context_id );
		gtk_statusbar_push (GTK_STATUSBAR (mydata.statusbar), mydata.statusbar_context_id, "searching for selected word");
//
	on_find_clicked ();
	g_free( word );
}

// ****************** --------->

void 
on_match_select( GtkEntryCompletion *widget, GtkTreeModel *model, GtkTreeIter *iter, gpointer user_data )
{  
	GValue value = {0, };
	//gtk_tree_model_get_string_from_iter ()
	gtk_tree_model_get_value(model, iter, LIST_ITEM, &value);
//	g_print("You have selected %s\n", g_value_get_string(&value));
	gtk_entry_set_text ( mydata.input_word, g_value_get_string(&value) );
	on_find_clicked();
	g_value_unset(&value);
	return;
}

void
on_input_word_changed (GtkEditable *editable, gpointer user_data)
{
//	g_print("on_input_word_changed called\n");
	char *word = NULL, *entry_word = NULL;
	
	entry_word = gtk_entry_get_text ( mydata.input_word );	
//	word = g_strchomp( g_strchug( g_strdown( entry_word ) ) );
//  it has caused a Pango: index out of bound bug so use instead
	word = g_strdown( entry_word );

	if( strlen( word ) == 0 ){
		//g_print("on_input_word_changed():word is NULL\n");
		//avoid some latency by commenting below
		//remove_all_from_list();		
		return ;	//return as word is NULL and nothing to do
	}

	if( strlen( word ) == 1 ){		
//
//		g_print("on_input_word_changed():word= %s\n", word );
		load_hashtable_list();
//	
	//list is loaded use it for auto completion
		GtkEntryCompletion *completion;
		completion = gtk_entry_completion_new();
		gtk_entry_completion_set_text_column(completion, LIST_ITEM );
		gtk_entry_set_completion(GTK_ENTRY(mydata.input_word), completion);
		g_signal_connect(G_OBJECT (completion), "match-selected",G_CALLBACK (on_match_select), NULL);
		gtk_entry_completion_set_model(completion, GTK_TREE_MODEL(mydata.list_store));		
//		
	}
}

//******************** <------------

// this may work selection-received
/*
void
on_input_word_selection_received (GtkWidget *widget, GtkSelectionData *selectiondata, guint arg, gpointer user_data)
{
	g_print("on_input_word_selection_received(): text received\n");
}
*/

gboolean destroy_hash_table( gpointer key, gpointer value, gpointer user_data ){
	
	g_free ( key );
	
	GSList *itr = (GSList *)value;
	WordInfo *winfo;
	
	for( ; itr ; itr = itr -> next ){		       
		winfo = ( WordInfo* )( itr -> data );
		g_free ( winfo -> type );
		g_free ( winfo -> mean );
	}
	
	g_slist_free ( value );
	return TRUE;
	
}

void
destroy (GtkWidget *widget, gpointer user_data)
{
	//g_print("destroying window\n");
	//free all memory used by hash table and list_store_arr
	int i = 0;
	for( i = 0; i < ALPHABETS; i++ ){
		if( mydata.list_store_arr[i] != NULL )
			gtk_list_store_clear ( (GtkListStore* )mydata.list_store_arr[i] );		
	}

	for( i = 0; i < ALPHABETS; i++ ){
		if( mydata.hash_tab[i] != NULL ){
			//g_hash_table_foreach_remove( mydata.hash_tab[i],(GHRFunc) destroy_hash_table, NULL );
			g_hash_table_destroy ( mydata.hash_tab[i]);
		}
	}
	
	gtk_main_quit();
}
