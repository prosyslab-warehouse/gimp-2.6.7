/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <glib.h>

#ifndef GIMP_CONSOLE_COMPILATION
#include <gtk/gtk.h>
#endif
#include <fontconfig/fontconfig.h>
#include <pango/pango.h>
#include <pango/pangoft2.h>

#include "libgimpbase/gimpbase.h"

#include "version.h"

#include "about.h"
#include "gimp-intl.h"

static void
gimp_show_one_library_version (const gchar *package,
                               int          build_time_major,
                               int          build_time_minor,
                               int          build_time_micro,
                               int          run_time_major,
                               int          run_time_minor,
                               int          run_time_micro)
{
  g_print ("%s: %s %d.%d.%d, %s %d.%d.%d\n",
           package,
           _("compiled against version"),
           build_time_major, build_time_minor, build_time_micro,
           _("running against version"),
           run_time_major, run_time_minor, run_time_micro);
}

static void
gimp_show_library_versions (void)
{
#ifndef GIMP_CONSOLE_COMPILATION
  gimp_show_one_library_version
    ("GTK+",
     GTK_MAJOR_VERSION, GTK_MINOR_VERSION, GTK_MICRO_VERSION,
     gtk_major_version, gtk_minor_version, gtk_micro_version);
#endif
  gimp_show_one_library_version
    ("Pango",
     PANGO_VERSION_MAJOR, PANGO_VERSION_MINOR, PANGO_VERSION_MICRO,
     pango_version () / 100 / 100, pango_version () / 100 % 100, pango_version () % 100);
  gimp_show_one_library_version
    ("GLib",
     GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION,
     glib_major_version, glib_minor_version, glib_micro_version);
  gimp_show_one_library_version
    ("Fontconfig",
     FC_MAJOR, FC_MINOR, FC_REVISION,
     FcGetVersion () / 100 / 100, FcGetVersion () / 100 % 100, FcGetVersion () % 100);
}

void
gimp_version_show (gboolean be_verbose)
{
  g_print (_("%s version %s"), GIMP_NAME, GIMP_VERSION);
  g_print ("\n");

  if (be_verbose)
    {
      g_print ("\n");
      gimp_show_library_versions ();
    }
}
