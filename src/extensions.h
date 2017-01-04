/**
 * @file extensions.h
 * @author Radek Krejci <rkrejci@cesnet.cz>
 * @brief libyang support for YANG extension implementations.
 *
 * Copyright (c) 2016 CESNET, z.s.p.o.
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */

#ifndef LY_EXTENSIONS_H_
#define LY_EXTENSIONS_H_

#include "tree_schema.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Callback to check that the extension can be instantiated inside the provided node
 *
 * @param[in] parent The parent of the instantiated extension.
 * @param[in] parent_type The type of the structure provided as \p parent.
 * @param[in] substmt_type libyang does not store all the extension instances in the structures where they are
 *                         instantiated in the module. In some cases (see #LYEXT_SUBSTMT) they are stored in parent
 *                         structure and marked with flag to know in which substatement of the parent the extension
 *                         was originally instantiated.
 * @return 0 - yes
 *         1 - no
 *         2 - ignore / skip without an error
 */
typedef int (*lyext_check_position_clb)(const void *parent, LYEXT_PAR parent_type, LYEXT_SUBSTMT substmt_type);

/**
 * @brief Callback to check that the extension instance is correct - have
 * the valid argument, all the mandatory substatements, etc.
 *
 * @param[in] type The type of the structure provided as \p parent.
 * @param[in] parent The parent of the instantiated extension.
 * @return 0 - yes
 *         1 - no
 *         2 - ignore / skip without an error
 */
typedef int (*lyext_check_result_clb)(struct lys_ext_instance *ext);

struct lyext_plugin {
    LYEXT_TYPE type;                          /**< type of the extension, according to it the structure will be casted */

    lyext_check_position_clb check_position; /**< callbcak for testing that the extension can be instantiated
                                                   under the provided parent. Mandatory callback. */
    lyext_check_result_clb check_result;     /**< callback for testing if the argument value of the extension instance
                                                   is valid. Mandatory if the extension has the argument. */
};

struct lyext_plugin_list {
    const char *module;          /**< name of the module where the extension is defined */
    const char *revision;        /**< optional module revision - if not specified, the plugin applies to any revision,
                                      which is not an optional approach due to a possible future revisions of the module.
                                      Instead, there should be defined multiple items in the plugins list, each with the
                                      different revision, but all with the same pointer to the plugin extension. The
                                      only valid use case for the NULL revision is the case the module has no revision. */
    const char *name;            /**< name of the extension */
    struct lyext_plugin *plugin; /**< plugin for the extension */
};

#if 0
// future use
struct lyext_substmt_info {
    uint8_t cardinality;  /**< allowed cardinality of the substatement */
    uint16_t number;      /**< real number of the substatements (e.g. size of the allocated array) */
    size_t offset;        /**< offset of the stored substatement structure/value/pointer-to */
};
#endif


#ifdef __cplusplus
}
#endif

#endif /* LY_EXTENSIONS_H_ */
