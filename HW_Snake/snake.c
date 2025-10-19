#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses/ncurses.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>

#define MIN_Y  2
#define CONTROLS  3

enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME=KEY_F(10)};
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=3, MAX_FOOD_SIZE=20, FOOD_EXPIRE_SECONDS=20, SEED_NUMBER=10};

typedef struct food 
{ 
	int x; 
	int y; 
	time_t put_time; 
	char point; 
	uint8_t enable; 
} food;

typedef struct control_buttons
{
    int down;
    int up;
    int left;
    int right;
} control_buttons;

control_buttons default_controls[CONTROLS] = {{KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT}, {'S', 'W', 'A', 'D'}, {'s', 'w', 'a', 'd'}};

typedef struct tail_t
{
    int x;
    int y;
} tail_t;
 
typedef struct snake_t
{
    int x;
    int y;
    int direction;
    size_t tsize;
    tail_t *tail;
    control_buttons controls;
} snake_t;

void initTail(tail_t t[], size_t size)
{
    tail_t init_t={0,0};
    for(size_t i=0; i<size; i++)
    {
        t[i]=init_t;
    }
}

void addTail(struct snake_t *head) 
{    
	head -> tsize ++;  
}

void initHead(snake_t *head, int x, int y, int direction)
{
    head->x = x;
    head->y = y;
    head->direction = direction;
}

void initSnake(snake_t *head, size_t size, int x, int y)
{
	tail_t*  tail  = (tail_t*) malloc(MAX_TAIL_SIZE*sizeof(tail_t));
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y, RIGHT);
    head->tail = tail;
    head->tsize = size+1;
    head->controls = default_controls[0];
}

void initFood(struct food f[], size_t size) 
{ 
	struct food init = {0,0,0,0,0};  
	for(size_t i=0; i<size; i++) 
	{        
		f[i] = init; 
	} 
}

void hideFoodSeed(struct food *fp) 
{     
	mvprintw(fp->y, fp->x, " ");    
}

void putFoodSeed(struct food *fp) 
{ 
	int max_x=0, max_y=0; 
	char spoint[2] = {0};    
	getmaxyx(stdscr, max_y, max_x);        
	fp->x = rand() % (max_x - 1);    
	fp->y = rand() % (max_y - 2) + 1;
	fp->put_time = time(NULL);    
	fp->point = '$';    
	fp->enable = 1;    
	spoint[0] = fp->point;
	mvprintw(fp->y, fp->x, "%s", spoint); 
}


void putFood(struct food f[], size_t number_seeds) 
{ 
	for(size_t i=0; i<number_seeds; i++) 
	{        
		putFoodSeed(&f[i]);
	} 
}

void refreshFood(struct food f[], size_t number_seeds) 
{ 	

	for(size_t i = 0; i < number_seeds; i++) 
	{ 
		if( f[i].put_time ) 
		{
			if( !f[i].enable || (time(NULL) - f[i].put_time) > FOOD_EXPIRE_SECONDS ) 
			{                
				hideFoodSeed(&f[i]);	
			} 
		} 
	}
	for(size_t i = 0; i < number_seeds; i++) 
	{ 
		if( f[i].put_time ) 
		{
			if( !f[i].enable || (time(NULL) - f[i].put_time) > FOOD_EXPIRE_SECONDS ) 
			{                
				putFoodSeed(&f[i]);
			} 
		} 
	}
}

void repairSeed(struct food f[], size_t nfood, struct snake_t *head)
{	
	size_t pair = 1;
	
	while (pair > 0)
	{
		pair = 0;
		for (size_t i = 0; i < nfood; i++) 
		{			
			for (size_t j = i + 1; j < nfood; j++) 
			{
				if (f[i].enable && f[j].enable && f[i].x == f[j].x && f[i].y == f[j].y)
				{
					putFoodSeed(&f[j]);
					pair = pair + 1;
				}
			}
		}
		for (size_t i = 0; i < nfood; i++)
		{
			for (size_t j = 0; j < head->tsize; j++)
			{
				if ((f[i].x == head->tail[j].x) && (f[i].y == head->tail[j].y) && f[i].enable)
				{
					putFoodSeed(&f[j]);
					pair = pair + 1;
				}
			}	
		}
	}
}	

_Bool haveEat(struct snake_t *head, struct food f[]) 
{ 
	for(size_t i=0; i<MAX_FOOD_SIZE; i++) 
	if( f[i].enable && head->x == f[i].x && head->y == f[i].y  ) 
	{            
		f[i].enable = 0; 
		return 1; 
	} return 0;
}

void go(snake_t *head)
{
    char ch = '@';
    int max_x=0;
    int max_y=0;
    getmaxyx(stdscr, max_y, max_x); // macro - размер терминала
    mvprintw(head->y, head->x, " "); // очищаем один символ
    switch (head->direction)
    {
        case LEFT:
            if(head->x <= 0) head->x = max_x; // Циклическое движение, чтобы не уходить за пределы экрана
            mvprintw(head->y, --(head->x), "%c", ch);
        break;
        case RIGHT:
			if(head->x >= max_x) head->x = 0;
            mvprintw(head->y, ++(head->x), "%c", ch);
        break;
        case UP:
			if(head->y <= 0) head->y = max_y;
            mvprintw(--(head->y), head->x, "%c", ch);
        break;
        case DOWN:
			if(head->y >= max_y) head->y = 0;
            mvprintw(++(head->y), head->x, "%c", ch);
        break;
        default:
        break;
    }
    refresh();
}

int checkDirection(snake_t* snake, const int32_t key)
{
	for (int i=0; i<CONTROLS; i++)
    {
		snake->controls = default_controls[i];
		
		if ((key == snake->controls.up)    && (snake->direction == DOWN))  return 1;
		if ((key == snake->controls.down)  && (snake->direction == UP))    return 1;
		if ((key == snake->controls.left)  && (snake->direction == RIGHT)) return 1;
		if ((key == snake->controls.right) && (snake->direction == LEFT))  return 1;
	}
	return 0;
}

void changeDirection(snake_t* snake, const int32_t key)
{     
    for (int i=0; i<CONTROLS; i++)
    {
		snake->controls = default_controls[i];	
    
		if ((key == snake->controls.down))
			snake->direction = DOWN;
		else if ((key == snake->controls.up))
			snake->direction = UP;
		else if ((key == snake->controls.right))
			snake->direction = RIGHT;
		else if ((key == snake->controls.left))
			snake->direction = LEFT;
	}
}

void goTail(snake_t *head)
{
    char ch = '*';
    mvprintw(head->tail[head->tsize-1].y, head->tail[head->tsize-1].x, " ");
    for(size_t i = head->tsize-1; i>0; i--)
    {
        head->tail[i] = head->tail[i-1];
        if( head->tail[i].y || head->tail[i].x)
            mvprintw(head->tail[i].y, head->tail[i].x, "%c", ch);
    }
    head->tail[0].x = head->x;
    head->tail[0].y = head->y;
}

int isCrush(snake_t *head)
{
	tail_t* tale_tmp = head->tail;
	
	for (size_t i = head->tsize-1; i>0; i--)
	{
		if ((head->x == tale_tmp[i].x) && (head->y == tale_tmp[i].y))
		{	 
			return 1;	 
		}
	}
	return 0;
}

int main()
{	
	int direction_status, crush_status, eat_status;
	
	snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
	food*  seeds  = (food*) malloc(MAX_FOOD_SIZE*sizeof(food));
    
    initSnake(snake,START_TAIL_SIZE,10,10);
    initscr();
    keypad(stdscr, TRUE);
    raw();                
    noecho();           
    curs_set(FALSE);    
    mvprintw(0, 1,"Use arrows for control. Press 'F10' for EXIT");
    timeout(0);
    	    
    initFood(seeds,MAX_FOOD_SIZE);
    putFood(seeds,SEED_NUMBER);

    int key_pressed=0;
    while( key_pressed != STOP_GAME )
    {
        key_pressed = getch();
        direction_status = checkDirection(snake, key_pressed);
        if (direction_status) continue;
        go(snake);
        goTail(snake);
        eat_status = haveEat(snake, seeds);
        if (eat_status) addTail(snake);
        refreshFood(seeds, SEED_NUMBER);
        repairSeed(seeds, SEED_NUMBER,snake);
        crush_status = isCrush(snake);
        if (crush_status) break;
        timeout(50);
        changeDirection(snake, key_pressed);
    }
    while( key_pressed != STOP_GAME )
    {
        mvprintw(1, 1,"GAME OVER");
        mvprintw(2, 1,"Press 'F10' for EXIT");
        key_pressed = getch();
    }
    free(snake->tail);
    free(snake);
    endwin();
    return 0;
}
