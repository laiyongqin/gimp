/* LIBGIMP - The GIMP Library
 * Copyright (C) 1995-2003 Peter Mattis and Spencer Kimball
 *
 * gimppatterns_pdb.c
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <https://www.gnu.org/licenses/>.
 */

/* NOTE: This file is auto-generated by pdbgen.pl */

#include "config.h"

#include "gimp.h"


/**
 * SECTION: gimppatterns
 * @title: gimppatterns
 * @short_description: Functions relating to patterns.
 *
 * Functions relating to patterns.
 **/


/**
 * gimp_patterns_refresh:
 *
 * Refresh current patterns. This function always succeeds.
 *
 * This procedure retrieves all patterns currently in the user's
 * pattern path and updates all pattern dialogs accordingly.
 *
 * Returns: TRUE on success.
 **/
gboolean
gimp_patterns_refresh (void)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gboolean success = TRUE;

  return_vals = gimp_run_procedure ("gimp-patterns-refresh",
                                    &nreturn_vals,
                                    GIMP_PDB_END);

  success = return_vals[0].data.d_status == GIMP_PDB_SUCCESS;

  gimp_destroy_params (return_vals, nreturn_vals);

  return success;
}

/**
 * gimp_patterns_get_list:
 * @filter: An optional regular expression used to filter the list.
 * @num_patterns: The number of patterns in the pattern list.
 *
 * Retrieve a complete listing of the available patterns.
 *
 * This procedure returns a complete listing of available GIMP
 * patterns. Each name returned can be used as input to the
 * gimp_context_set_pattern().
 *
 * Returns: The list of pattern names. The returned value must be freed
 * with g_strfreev().
 **/
gchar **
gimp_patterns_get_list (const gchar *filter,
                        gint        *num_patterns)
{
  GimpParam *return_vals;
  gint nreturn_vals;
  gchar **pattern_list = NULL;
  gint i;

  return_vals = gimp_run_procedure ("gimp-patterns-get-list",
                                    &nreturn_vals,
                                    GIMP_PDB_STRING, filter,
                                    GIMP_PDB_END);

  *num_patterns = 0;

  if (return_vals[0].data.d_status == GIMP_PDB_SUCCESS)
    {
      *num_patterns = return_vals[1].data.d_int32;
      if (*num_patterns > 0)
        {
          pattern_list = g_new0 (gchar *, *num_patterns + 1);
          for (i = 0; i < *num_patterns; i++)
            pattern_list[i] = g_strdup (return_vals[2].data.d_stringarray[i]);
        }
    }

  gimp_destroy_params (return_vals, nreturn_vals);

  return pattern_list;
}
