/* gline.h - Gline database
 * Copyright 2001-2004 srvx Development Team
 *
 * This file is part of srvx.
 *
 * srvx is free software; you can redistribute it and/or modify
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
 * along with srvx; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 */

#ifndef GLINE_H
#define GLINE_H

#include "hash.h"

struct gline {
    /** When the G-line was first created. */
    unsigned long issued;
    /** When the G-line was last modified. */
    unsigned long lastmod;
    /** When the G-line becomes ineffective. */
    unsigned long expires;
    /** When the G-line may be forgotten (the maximum "expires" value
     * from any modification period).
     */
    unsigned long lifetime;
    /** Account or nick name of the person creating the G-line. */
    char *issuer;
    /** user@host mask covered by the G-line. */
    char *target;
    /** What to tell affected users. */
    char *reason;
};

struct gline_discrim {
    unsigned int limit;
    enum { SUBSET, EXACT, SUPERSET } target_mask_type;
    char *issuer_mask;
    char *target_mask;
    char *alt_target_mask;
    char *reason_mask;
    unsigned long max_issued;
    unsigned long min_expire;
    unsigned long min_lastmod;
    unsigned long max_lastmod;
    unsigned long min_lifetime;
    unsigned long max_lifetime;
};

void gline_init(void);
struct gline *gline_add(const char *issuer, const char *target, unsigned long duration, const char *reason, unsigned long issued, unsigned long lastmod, unsigned long lifetime, int announce);
struct gline *gline_find(const char *target);
int gline_remove(const char *target, int announce);
void gline_refresh_server(struct server *srv);
void gline_refresh_all(void);
unsigned int gline_count(void);

typedef void (*gline_search_func)(struct gline *gline, void *extra);
struct gline_discrim *gline_discrim_create(struct userNode *user, struct userNode *src, unsigned int argc, char *argv[]);
unsigned int gline_discrim_search(struct gline_discrim *discrim, gline_search_func gsf, void *data);

#endif /* !defined(GLINE_H) */
