
/* BALL STUFF */
#define   INIT_TICKS_PER_SEC 150
#define   MAX_TTM   7
#define   MIN_TTM   4
#define   BALL_PIXELS_TO_MOVE 3
#define   MAX_TICKS_PER_SEC_CHANGE 40

/* PADDLE STUFF */
#define   PADDLE_LENGTH  50
#define   PADDLE_OFFSET_FROM_RIGHT_WALL 20
#define   PADDLE_PIXELS_TO_MOVE 5

/* WALL STUFF */
#define   PIXELS_FROM_WIN_EDGE  20
#define   WALL_THICKNESS 3

struct pongBall
{
   int y_pos, x_pos;
   int y_ttm, x_ttm;
   int y_ttg, x_ttg;
   int y_dir, x_dir;
};

struct pongPaddle
{
   int pad_top;
   int pad_bot;
   int pad_col;
};

struct pongWall
{
   int left_col;
   int right_col;
   int top_row;
   int bot_row;
};
