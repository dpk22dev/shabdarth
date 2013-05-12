#include <stdlib.h>

#include "list_func.h"
#include "gui.h"

char *prev = NULL;

void init_list( ){
	
//	g_print("init_list() called\n");
	GtkCellRenderer *rend;
	GtkTreeViewColumn *col;	

	rend = gtk_cell_renderer_text_new ();
	col = gtk_tree_view_column_new_with_attributes("List Item",rend, "text", LIST_ITEM, NULL );
	gtk_tree_view_append_column ( mydata.treeview, col );
	
	mydata.list_store = gtk_list_store_new ( N_COLOUMNS, G_TYPE_STRING );
	gtk_tree_view_set_model ( mydata.treeview, GTK_TREE_MODEL(mydata.list_store) );
//	g_object_unref( store );
	
}

void add_to_list( gchar *str ){

	//causes slowness
//	g_print("add_to_list: %s\n", str );

	if( g_strcmp0 ( str, prev ) == 0 )
		return ;
	
	GtkTreeIter itr;
	
	//mydata.list_store = GTK_LIST_STORE( gtk_tree_view_get_model(mydata.treeview) ) ; 
//	gtk_tree_view_set_model ( mydata.treeview, NULL );
	gtk_list_store_append( mydata.list_store, &itr );
	gtk_list_store_set( mydata.list_store, &itr, LIST_ITEM, str, -1 );
//	gtk_tree_view_set_model ( mydata.treeview, GTK_TREE_MODEL(mydata.list_store) );


	prev = g_strdup( str );
		
}

void remove_all_from_list( ){

	gtk_tree_view_set_model ( mydata.treeview, NULL );
	gtk_list_store_clear ( mydata.list_store );
	gtk_tree_view_set_model ( mydata.treeview, GTK_TREE_MODEL(mydata.list_store) );
	
}

void populate_list_only ( char *filename ){
	
	FILE *ifp = fopen( filename, "rb" );
	if( ifp == NULL ){
		fprintf( stderr,"populate_list_only():open reading file error\n");
		exit( EXIT_FAILURE );
	}
	char word[ WORD_SIZE ], temp[ TEMP_SIZE ];
	unsigned int nword, ntype, nmean;
	
	while( fread( &nword, sizeof(nword), 1, ifp ) != 0 ){
						
		fread( temp, nword, 1, ifp );
//		printf("read word: %s\n", temp );
		strcpy( word, temp );
		
		fread( &ntype, sizeof(ntype), 1, ifp );
		fread( temp, ntype, 1, ifp );	
//		printf("read type: %s\n", temp );		
		
		fread( &nmean, sizeof(nmean), 1, ifp );
		fread( temp, nmean, 1, ifp );	
//		printf("read mean: %s\n", temp );				
		//also populates list
		add_to_list( g_ascii_strdown(word, strlen(word)) );
		
	}
	
}
