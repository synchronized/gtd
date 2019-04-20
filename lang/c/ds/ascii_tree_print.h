#ifndef _ASCII_TREE_PRINT_H
#define _ASCII_TREE_PRINT_H

/**
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * !!!Code originally from /http://www.openasthra.com/c-tidbits/printing-binary-trees-in-ascii/
 * !!! Just saved it, cause the website is down.
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * Printing Binary Trees in Ascii

 *     Here we are not going to discuss what binary trees are
 * (please refer this, if you are looking for binary search trees),
 * or their operations but printing them in ascii.

 *     The below routine prints tree in ascii for a given Tree representation
 * which contains list of nodes, and node structure is this
 */

/**
 * get left children, right children, fill buffer
 */
typedef void (*ascii_tree_build_handler)(void *t, char *buf, void **left, void **right);

void ascii_tree_print(void *t, ascii_tree_build_handler cb);

#endif
