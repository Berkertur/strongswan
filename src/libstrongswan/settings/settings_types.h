/*
 * Copyright (C) 2010-2014 Tobias Brunner
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

/**
 * Internal data types and functions shared between the parser and t.
 *
 * @defgroup settings_types settings_types
 * @{ @ingroup settings
 */

#ifndef SETTINGS_TYPES_H_
#define SETTINGS_TYPES_H_

typedef struct kv_t kv_t;
typedef struct section_t section_t;

#include "collections/array.h"

/**
 * Key/value pair.
 */
struct kv_t {

	/**
	 * Key string, relative, not the full name.
	 */
	char *key;

	/**
	 * Value as string.
	 */
	char *value;
};

/**
 * Section containing subsections and key value pairs.
 */
struct section_t {

	/**
	 * Name of the section.
	 */
	char *name;

	/**
	 * Fallback sections, as section_t.
	 */
	array_t *fallbacks;

	/**
	 * Subsections, as section_t.
	 */
	array_t *sections;

	/**
	 * Key value pairs, as kv_t.
	 */
	array_t *kv;
};

/**
 * Create a key/value pair.
 *
 * @param key		key (gets adopted)
 * @param value		value (gets adopted)
 * @return			allocated key/value pair
 */
kv_t *settings_kv_create(char *key, char *value);

/**
 * Destroy a key/value pair.
 *
 * @param this		key/value pair to destroy
 */
void settings_kv_destroy(kv_t *this);

/**
 * Create a section with the given name.
 *
 * @param name		name (gets adopted)
 * @return			allocated section
 */
section_t *settings_section_create(char *name);

/**
 * Destroy a section.
 *
 * @param this		section to destroy
 */
void settings_section_destroy(section_t *this);

/**
 * Extend the first section with the values and sub-sections of the second
 * section, from where they are consequently moved/removed (but there might
 * still remain some leftovers).
 *
 * @param base		base section to extend
 * @param extension	section whose data is extracted
 */
void settings_section_extend(section_t *base, section_t *extension);

/**
 * Callback to find a section by name
 */
int settings_section_find(const void *a, const void *b);

/**
 * Callback to sort sections by name
 */
int settings_section_sort(const void *a, const void *b, void *user);

/**
 * Callback to find a key/value pair by key
 */
int settings_kv_find(const void *a, const void *b);

/**
 * Callback to sort kv pairs by key
 */
int settings_kv_sort(const void *a, const void *b, void *user);

#endif /** SETTINGS_TYPES_H_ @}*/
