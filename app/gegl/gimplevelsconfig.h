/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * gimplevelsconfig.h
 * Copyright (C) 2007 Michael Natterer <mitch@gimp.org>
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

#ifndef __GIMP_LEVELS_CONFIG_H__
#define __GIMP_LEVELS_CONFIG_H__


#define GIMP_TYPE_LEVELS_CONFIG            (gimp_levels_config_get_type ())
#define GIMP_LEVELS_CONFIG(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_LEVELS_CONFIG, GimpLevelsConfig))
#define GIMP_LEVELS_CONFIG_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  GIMP_TYPE_LEVELS_CONFIG, GimpLevelsConfigClass))
#define GIMP_IS_LEVELS_CONFIG(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_LEVELS_CONFIG))
#define GIMP_IS_LEVELS_CONFIG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GIMP_TYPE_LEVELS_CONFIG))
#define GIMP_LEVELS_CONFIG_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  GIMP_TYPE_LEVELS_CONFIG, GimpLevelsConfigClass))


typedef struct _GimpLevelsConfigClass GimpLevelsConfigClass;

struct _GimpLevelsConfig
{
  GObject               parent_instance;

  GimpHistogramChannel  channel;

  gdouble               gamma[5];

  gdouble               low_input[5];
  gdouble               high_input[5];

  gdouble               low_output[5];
  gdouble               high_output[5];
};

struct _GimpLevelsConfigClass
{
  GObjectClass  parent_class;
};


GType   gimp_levels_config_get_type      (void) G_GNUC_CONST;

void    gimp_levels_config_reset         (GimpLevelsConfig     *self);
void    gimp_levels_config_reset_channel (GimpLevelsConfig     *self,
                                          GimpHistogramChannel  channel);


#endif /* __GIMP_LEVELS_CONFIG_H__ */