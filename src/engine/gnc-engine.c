/********************************************************************
 * gnc-engine.c  -- top-level initialization for Gnucash Engine     *
 * Copyright 2000 Bill Gribble <grib@billgribble.com>               *
 *                                                                  *
 * This program is free software; you can redistribute it and/or    *
 * modify it under the terms of the GNU General Public License as   *
 * published by the Free Software Foundation; either version 2 of   *
 * the License, or (at your option) any later version.              *
 *                                                                  *
 * This program is distributed in the hope that it will be useful,  *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of   *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    *
 * GNU General Public License for more details.                     *
 *                                                                  *
 * You should have received a copy of the GNU General Public License*
 * along with this program; if not, contact:                        *
 *                                                                  *
 * Free Software Foundation           Voice:  +1-617-542-5942       *
 * 59 Temple Place - Suite 330        Fax:    +1-617-542-2652       *
 * Boston, MA  02111-1307,  USA       gnu@gnu.org                   *
 *                                                                  *
 ********************************************************************/

#include <glib.h>
#include <assert.h>

#include "gnc-engine.h"

static GList * engine_init_hooks = NULL;
static gnc_commodity_table * known_commodities = NULL;
static int engine_is_initialized = 0;


/********************************************************************
 * gnc_engine_init
 * initialize backend, load any necessary databases, etc. 
 ********************************************************************/

void 
gnc_engine_init(int argc, char ** argv) {
  gnc_engine_init_hook_t hook;
  GList                  * cur;

  engine_is_initialized = 1;

  /* initialize the commodity table (it starts empty) */
  known_commodities = gnc_commodity_table_new();

  /* call any engine hooks */
  for(cur = engine_init_hooks; cur; cur = cur->next) {
    hook = (gnc_engine_init_hook_t)cur->data;
    if(hook) {
      (*hook)(argc, argv);
    }
  }
}


/********************************************************************
 * gnc_engine_add_init_hook
 * add a startup hook 
 ********************************************************************/

void
gnc_engine_add_init_hook(gnc_engine_init_hook_t h) {
  engine_init_hooks = g_list_append(engine_init_hooks, (gpointer)h);
}


/********************************************************************
 * gnc_engine_commodities()
 * get the global gnc_engine commodity table 
 ********************************************************************/

gnc_commodity_table *
gnc_engine_commodities() {
  assert(engine_is_initialized);
  return known_commodities;
}
