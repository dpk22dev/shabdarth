/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) placement 2013 <placement@updesh-desktop>
 * 
 */

#include <config.h>
#include <gtk/gtk.h>
#include "shabdarth.h"



int
main (int argc, char *argv[])
{
	Shabdarth *app;
	int status;


	
  app = shabdarth_new ();
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
