/*
 * =====================================================================================
 *
 *       Filename:  spell.h
 *
 *    Description:  spell
 *
 *        Version:  1.0
 *        Created:  2015年08月08日 18时11分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Liang (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef SPELL_H
#define SPELL_H
#define SPELL_SIZE 31

int
spell(char (*dictionary)[SPELL_SIZE],int size, const char *word);
#endif
