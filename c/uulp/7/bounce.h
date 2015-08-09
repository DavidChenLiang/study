/*
 * =====================================================================================
 *
 *       Filename:  bounce.h
 *
 *    Description:  just a funny h
 *
 *        Version:  1.0
 *        Created:  2015年02月07日 16时12分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#define BLANK         ' '
#define DFL_SYMBOL    'o'
#define TOP_ROW       0
#define BOT_ROW       30
#define LEFT_EDGE     0
#define RIGHT_EDGE    70
#define X_INIT        10
#define Y_INIT        10
#define TICKS_PER_SEC 200
#define X_TTM         5
#define Y_TTM         8

struct ppball
{
    int y_pos,x_pos,
	    y_ttm,x_ttm,
	    y_ttg,x_ttg,
	    y_dir,x_dir;
        char symbol;
};

