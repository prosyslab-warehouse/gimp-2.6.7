/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * gimpoperationposterize.c
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

#include "config.h"

#include <gegl.h>

#include "libgimpcolor/gimpcolor.h"
#include "libgimpmath/gimpmath.h"

#include "gegl-types.h"

#include "gimpoperationposterize.h"


enum
{
  PROP_0,
  PROP_LEVELS
};


static void     gimp_operation_posterize_get_property (GObject       *object,
                                                       guint          property_id,
                                                       GValue        *value,
                                                       GParamSpec    *pspec);
static void     gimp_operation_posterize_set_property (GObject       *object,
                                                       guint          property_id,
                                                       const GValue  *value,
                                                       GParamSpec    *pspec);

static gboolean gimp_operation_posterize_process      (GeglOperation *operation,
                                                       void          *in_buf,
                                                       void          *out_buf,
                                                       glong          samples);


G_DEFINE_TYPE (GimpOperationPosterize, gimp_operation_posterize,
               GEGL_TYPE_OPERATION_POINT_FILTER)

#define parent_class gimp_operation_posterize_parent_class


static void
gimp_operation_posterize_class_init (GimpOperationPosterizeClass * klass)
{
  GObjectClass                  *object_class    = G_OBJECT_CLASS (klass);
  GeglOperationClass            *operation_class = GEGL_OPERATION_CLASS (klass);
  GeglOperationPointFilterClass *point_class     = GEGL_OPERATION_POINT_FILTER_CLASS (klass);

  object_class->set_property = gimp_operation_posterize_set_property;
  object_class->get_property = gimp_operation_posterize_get_property;

  point_class->process       = gimp_operation_posterize_process;

  gegl_operation_class_set_name (operation_class, "gimp-posterize");

  g_object_class_install_property (object_class,
                                   PROP_LEVELS,
                                   g_param_spec_int ("levels",
                                                     "Levels",
                                                     "Posterize levels",
                                                     2, 256, 10,
                                                     G_PARAM_READWRITE |
                                                     G_PARAM_CONSTRUCT));
}

static void
gimp_operation_posterize_init (GimpOperationPosterize *self)
{
}

static void
gimp_operation_posterize_get_property (GObject    *object,
                                       guint       property_id,
                                       GValue     *value,
                                       GParamSpec *pspec)
{
  GimpOperationPosterize *self = GIMP_OPERATION_POSTERIZE (object);

  switch (property_id)
    {
    case PROP_LEVELS:
      g_value_set_int (value, self->levels);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
gimp_operation_posterize_set_property (GObject      *object,
                                       guint         property_id,
                                       const GValue *value,
                                       GParamSpec   *pspec)
{
  GimpOperationPosterize *self = GIMP_OPERATION_POSTERIZE (object);

  switch (property_id)
    {
    case PROP_LEVELS:
      self->levels = g_value_get_int (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static gboolean
gimp_operation_posterize_process (GeglOperation *operation,
                                  void          *in_buf,
                                  void          *out_buf,
                                  glong          samples)
{
  GimpOperationPosterize *self   = GIMP_OPERATION_POSTERIZE (operation);
  gfloat                 *src    = in_buf;
  gfloat                 *dest   = out_buf;
  gfloat                  levels = self->levels - 1.0;
  glong                   sample;

  for (sample = 0; sample < samples; sample++)
    {
      dest[RED_PIX]   = RINT (src[RED_PIX]   * levels) / levels;
      dest[GREEN_PIX] = RINT (src[GREEN_PIX] * levels) / levels;
      dest[BLUE_PIX]  = RINT (src[BLUE_PIX]  * levels) / levels;
      dest[ALPHA_PIX] = src[ALPHA_PIX];

      src  += 4;
      dest += 4;
    }

  return TRUE;
}