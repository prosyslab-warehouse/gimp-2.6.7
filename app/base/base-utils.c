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

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <glib.h>

#ifdef G_OS_WIN32
#include <windows.h>
#endif

#include "base-utils.h"

#define NUM_PROCESSORS_DEFAULT 1

/*  public functions  */

gint
get_number_of_processors (void)
{
  gint retval = NUM_PROCESSORS_DEFAULT;

#ifdef G_OS_UNIX
#if defined(HAVE_UNISTD_H) && defined(_SC_NPROCESSORS_ONLN)
  retval = sysconf (_SC_NPROCESSORS_ONLN);
#endif
#endif
#ifdef G_OS_WIN32
  SYSTEM_INFO system_info;

  GetSystemInfo (&system_info);

  retval = system_info.dwNumberOfProcessors;
#endif

  return retval;
}