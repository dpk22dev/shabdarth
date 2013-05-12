#include "read_db.h"
#include "gui.h"
#include "list_func.h"

#include <string.h>

unsigned long counter = 0;
int count = 0;

void find_meaning_put_gui( char *str ){

	if( str == NULL )
		return ;
	
	GSList *list = NULL;
	//g_print("find_meaning_put_gui %s\n", str );
	
	int index = g_ascii_toupper(str[0]) - 'A';

	if( mydata.hash_tab[index] == NULL ){
		fprintf( stderr, "find_meaning_put_gui(): hash tab at index[%d] is NULL", index );
		return ;
	}
	
    list = g_hash_table_lookup ( mydata.hash_tab[index], str );
	if( list == NULL ){
		fprintf( stderr, "could not find in hash table word\n %s", str);
		//put info on status bar
		//gtk_statusbar_push( data.statusbar, data.statusbar_context_id, "Sorry! word could not be found.");		
//
		gtk_statusbar_pop ( mydata.statusbar, mydata.statusbar_context_id );
		gtk_statusbar_push (GTK_STATUSBAR (mydata.statusbar), mydata.statusbar_context_id, "Sorry! word could not be found.");
//
		return ;
	}

	GSList *itr = list;
	GtkTextBuffer *buffer;
	GtkTextIter iter;
	WordInfo *winfo;
	PangoFontDescription *font_desc;
	GdkColor color;
	GtkTextTag *tag;
	
	for( ; itr ; itr = itr -> next ){
		        
		winfo = ( WordInfo* )( itr -> data );
		if( winfo == NULL )
			fprintf(stderr,"find_meaning_put_gui():NULL pointer used for printing\n");
		
		buffer = gtk_text_view_get_buffer ( mydata.meaning_text_view );
/*
		GtkTextIter start, end;
		font_desc = pango_font_description_from_string ("Serif 15");
		gtk_widget_modify_font ( mydata.window, font_desc);
		pango_font_description_free (font_desc);

   Change default color throughout the widget 
		gdk_color_parse ("green", &color);
		gtk_widget_modify_text (mydata.window, GTK_STATE_NORMAL, &color);

   Change left margin throughout the widget 
		gtk_text_view_set_left_margin (GTK_TEXT_VIEW (mydata.meaning_text_view ), 30);

   Use a tag to change the color for just one part of the widget 
		tag = gtk_text_buffer_create_tag (buffer, "blue_foreground",
	   		            "foreground", "blue", NULL);
		gtk_text_buffer_get_start_iter ( buffer, &start );
		gtk_text_buffer_get_end_iter ( buffer, &end );
		
*/
		
		
		gtk_text_buffer_get_iter_at_offset ( buffer, &iter, 0 );		
		gtk_text_buffer_insert( buffer, &iter,"type: ", -1 );
		gtk_text_buffer_insert ( buffer, &iter, winfo -> type, -1 );
		gtk_text_buffer_insert( buffer, &iter,"\n", -1 );
		
		gtk_text_buffer_insert( buffer, &iter, winfo -> mean, -1 );
		gtk_text_buffer_insert( buffer, &iter,"\n", -1 );				

//
//		gtk_text_buffer_apply_tag ( buffer, tag, &start, &end );
//		
		
	}
//
		gtk_statusbar_pop ( mydata.statusbar, mydata.statusbar_context_id );
		gtk_statusbar_push (GTK_STATUSBAR (mydata.statusbar), mydata.statusbar_context_id, "Word found!");
//
	
}

void key_destroy( gpointer data ){
	//g_print("key_destroy(): destroying %s\n", (char*)data );
	g_free ( data );
}

void value_destroy( gpointer list ){
	
	//g_print("value_destroy(): trying destroying data\n");
	/*
	GSList *itr = (GSList *)list;
	for( ; itr ; itr = itr -> next )
        remove_structure( itr -> data );
	*/  
}

void put_hash_table( GHashTable *hash, char *key, WordInfo *wss ){

	if( wss == NULL )
		return ;
	 
	WordInfo *winfo = ( WordInfo* )malloc( sizeof(WordInfo) );
	winfo -> ntype = wss -> ntype;
	winfo -> type = malloc( winfo -> ntype );
	strcpy( winfo -> type, wss -> type );

	winfo -> nmean = wss -> nmean;
	winfo -> mean = malloc( winfo -> nmean );
	strcpy( winfo -> mean, wss -> mean );

	g_hash_table_insert ( hash, key, g_slist_append( g_hash_table_lookup(hash, key), winfo) );
	//causes slowness
	//g_print("put_hash_table %s\n", key );		
	
}

GHashTable *generate_hash_table( gchar *filename ){
	
	GHashTable *hash = g_hash_table_new_full ( g_str_hash, g_str_equal, (GDestroyNotify)key_destroy, (GDestroyNotify)value_destroy );
	FILE *ifp = fopen( filename, "rb" );
//********************	
	init_list();
	// trying below instead of init_list() doesn't show treeview
	//mydata.list_store = gtk_list_store_new ( N_COLOUMNS, G_TYPE_STRING );
	
//*********
	//g_printf("generate_hash_table:opening file %s\n", filename );
//*********
	if( ifp == NULL ){
		fprintf( stderr,"generate hash table():open reading file error\n");
		exit( EXIT_FAILURE );
	}
	char word[ WORD_SIZE ], temp[ TEMP_SIZE ];
	unsigned int nword, ntype, nmean;
//
	gtk_statusbar_pop ( mydata.statusbar, mydata.statusbar_context_id );
	gtk_statusbar_push (GTK_STATUSBAR (mydata.statusbar), mydata.statusbar_context_id, "Generating Hash Table and populating list...");		
//	
	while( fread( &nword, sizeof(nword), 1, ifp ) != 0 ){
		
		counter++;
		
		WordInfo *tempinfo = ( WordInfo *)malloc( sizeof(WordInfo) );
		fread( temp, nword, 1, ifp );
//		printf("read word: %s\n", temp );
		strcpy( word, temp );
		
		fread( &ntype, sizeof(ntype), 1, ifp );
		fread( temp, ntype, 1, ifp );	
//		printf("read type: %s\n", temp );
		tempinfo -> ntype = ntype;
		tempinfo -> type = malloc( ntype );
		strcpy( tempinfo -> type, temp );
		
		fread( &nmean, sizeof(nmean), 1, ifp );
		fread( temp, nmean, 1, ifp );	
//		printf("read mean: %s\n", temp );
		tempinfo -> nmean = nmean;
		tempinfo -> mean = malloc( nmean );
		strcpy( tempinfo -> mean, temp );

		put_hash_table( hash, g_ascii_strdown(g_strdup( word ),strlen(word) ) , tempinfo );
		//also populates list
//***************** ---- > cause of error 
		add_to_list( g_ascii_strdown(word, strlen(word)) );
//*********
//	g_printf("generate_hash_table: reached here\n" );
//*********

		free( tempinfo -> type );
		free( tempinfo -> mean );
		free( tempinfo );
		
	}
//	put list_store into list_store_arr
	
//
		gtk_statusbar_pop ( mydata.statusbar, mydata.statusbar_context_id );
		gtk_statusbar_push (GTK_STATUSBAR (mydata.statusbar), mydata.statusbar_context_id, "List ready for use. You can select item from list.");
//	
	return hash;
}
