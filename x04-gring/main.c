/* main.c
 *
 * Copyright (C) 2010 Christian Hergert <chris@dronelabs.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "g-ring.h"

static void
test_GRing_ref (void)
{
	GRing *ring;

	ring = g_ring_sized_new(sizeof(gdouble), 60, NULL);
	g_assert(ring);
	g_ring_unref(ring);
}

static void
test_GRing_with_double (void)
{
	GRing *ring;
	gdouble d;

	ring = g_ring_sized_new(sizeof(gdouble), 60, NULL);
	g_assert(ring);

	d = 3.;
	g_ring_append_val(ring, d);
	d = g_ring_get_index(ring, gdouble, 0);
	g_assert(d == 3.);
	d = g_ring_get_index(ring, gdouble, 1);
	g_assert(d == 0.);

	d = 4.;
	g_ring_append_val(ring, d);
	d = g_ring_get_index(ring, gdouble, 0);
	g_assert(d == 4.);
	d = g_ring_get_index(ring, gdouble, 1);
	g_assert(d == 3.);
	d = g_ring_get_index(ring, gdouble, 2);
	g_assert(d == 0.);

	d = 6.;
	g_ring_append_val(ring, d);
	d = g_ring_get_index(ring, gdouble, 0);
	g_assert(d == 6.);
	d = g_ring_get_index(ring, gdouble, 1);
	g_assert(d == 4.);
	d = g_ring_get_index(ring, gdouble, 2);
	g_assert(d == 3.);
	d = g_ring_get_index(ring, gdouble, 3);
	g_assert(d == 0.);

	g_ring_unref(ring);
}

static void
test_GRing_with_int (void)
{
	GRing *ring;
	gint i;

	ring = g_ring_sized_new(sizeof(gint), 10, NULL);
	i = g_ring_get_index(ring, gint, 0);
	g_assert_cmpint(i, ==, 0);
	i = 10;
	g_ring_append_val(ring, i);
	i = g_ring_get_index(ring, gint, 0);
	g_assert_cmpint(i, ==, 10);
	i = 20;
	g_ring_append_val(ring, i);
	i = g_ring_get_index(ring, gint, 0);
	g_assert_cmpint(i, ==, 20);
	i = g_ring_get_index(ring, gint, 1);
	g_assert_cmpint(i, ==, 10);
	g_ring_unref(ring);
}

static gboolean test_GRing_with_array_result = FALSE;

static void
test_GRing_with_array_cb (gpointer data)
{
	GArray **ar = data;
	test_GRing_with_array_result = TRUE;
	g_array_unref(*ar);
}

static void
test_GRing_with_array (void)
{
	GRing *ring;
	GArray *ar0;
	GArray *ar1;
	GArray *ar2;
	gpointer tmp;

	ring = g_ring_sized_new(sizeof(GArray*), 2, test_GRing_with_array_cb);
	ar0 = g_array_new(FALSE, TRUE, sizeof(gdouble));
	ar1 = g_array_new(FALSE, TRUE, sizeof(gdouble));
	ar2 = g_array_new(FALSE, TRUE, sizeof(gdouble));

	g_ring_append_val(ring, ar0);
	g_ring_append_val(ring, ar1);
	tmp = g_ring_get_index(ring, GArray*, 0);
	g_assert(tmp == ar1);
	tmp = g_ring_get_index(ring, GArray*, 1);
	g_assert(tmp == ar0);

	/*
	 * Make sure that ar0 was dispoased as we ran over it.
	 */
	g_ring_append_val(ring, ar2);
	tmp = g_ring_get_index(ring, GArray*, 0);
	g_assert(tmp == ar2);
	tmp = g_ring_get_index(ring, GArray*, 1);
	g_assert(tmp == ar1);
	g_assert_cmpint(test_GRing_with_array_result, ==, TRUE);

	g_ring_unref(ring);
}

static void
test_GRing_foreach_cb (gpointer data,
                       gpointer user_data)
{
   gboolean *success = user_data;
   *success = FALSE;
}

static void
test_GRing_foreach_cb2 (gpointer data,
                        gpointer user_data)
{
   gboolean *success = user_data;
   gpointer *p = data;

   if (*p) {
      g_assert(*p == GINT_TO_POINTER(1234));
      *success = TRUE;
   }
}

static void
test_GRing_foreach (void)
{
   GRing *ring;
   gboolean success = TRUE;
   gpointer data = GINT_TO_POINTER(1234);

   ring = g_ring_sized_new(sizeof(gpointer), 20, NULL);
   g_ring_foreach(ring, test_GRing_foreach_cb, &success);
   g_assert(success);

   success = FALSE;
   g_ring_append_val(ring, data);
   g_ring_foreach(ring, test_GRing_foreach_cb2, &success);
   g_assert(success);

   g_ring_unref(ring);
}

gint
main (gint   argc,   /* IN */
      gchar *argv[]) /* IN */
{
	g_test_init(&argc, &argv, NULL);

	g_test_add_func("/GRing/ref", test_GRing_ref);
	g_test_add_func("/GRing/with_double", test_GRing_with_double);
	g_test_add_func("/GRing/with_int", test_GRing_with_int);
	g_test_add_func("/GRing/with_array", test_GRing_with_array);
	g_test_add_func("/GRing/foreach", test_GRing_foreach);

	return g_test_run();
}
