#define FIELD_SIZE_HEIGHT 96
#define FIELD_SIZE_WEIGHT 60
#define GAMEOVER_SIZE_HEIGHT 6
#define GAMEOVER_SIZE_WEIGHT 99
#define YOUWON_SIZE_WEIGHT 99
#define YOUWON_SIZE_HEIGHT 6
char moveBall(int, int, char [*][*], int *, char *);
int checkCollision(char);
void drawMap(int, int, char [*][*], int);
void clearField(void);
int checkWon(char);
