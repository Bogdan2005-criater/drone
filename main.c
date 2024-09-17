#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define FIELD_WIDTH 50
#define FIELD_HEIGHT 20
#define MAX_DRONES 5
#define MAX_PUMPKINS 10
#define PUMPKIN_PAIR 3
#define DRONE_PAIR 1
#define AUTOPILOT_DRONE_PAIR 2

typedef struct {
    int x, y;
    int direction;
    int length;
} drone_t;

typedef struct {
    int x, y;
    int collected;
} pumpkin_t;

drone_t drones[MAX_DRONES];
pumpkin_t pumpkins[MAX_PUMPKINS];

enum { LEFT = 1, RIGHT, UP, DOWN };
enum { AUTOPILOT = 1, MANUAL = 0 };

void init_drones() {
    for (int i = 0; i < MAX_DRONES; i++) {
        drones[i].x = rand() % FIELD_WIDTH;
        drones[i].y = rand() % FIELD_HEIGHT;
        drones[i].direction = rand() % 4 + 1;
        drones[i].length = 1;
    }
}

void init_pumpkins() {
    for (int i = 0; i < MAX_PUMPKINS; i++) {
        pumpkins[i].x = rand() % FIELD_WIDTH;
        pumpkins[i].y = rand() % FIELD_HEIGHT;
        pumpkins[i].collected = 0;
    }
}

void draw_pumpkins() {
    attron(COLOR_PAIR(PUMPKIN_PAIR));
    for (int i = 0; i < MAX_PUMPKINS; i++) {
        if (!pumpkins[i].collected) {
            mvprintw(pumpkins[i].y, pumpkins[i].x, "P");
        }
    }
    attroff(COLOR_PAIR(PUMPKIN_PAIR));
}

void move_drone(drone_t *drone) {
    switch (drone->direction) {
        case LEFT:
            drone->x--;
            break;
        case RIGHT:
            drone->x++;
            break;
        case UP:
            drone->y--;
            break;
        case DOWN:
            drone->y++;
            break;
    }
    if (drone->x < 0) drone->x = 0;
    if (drone->x >= FIELD_WIDTH) drone->x = FIELD_WIDTH - 1;
    if (drone->y < 0) drone->y = 0;
    if (drone->y >= FIELD_HEIGHT) drone->y = FIELD_HEIGHT - 1;
}

void draw_drone(drone_t *drone, int pair) {
    attron(COLOR_PAIR(pair));
    mvprintw(drone->y, drone->x, "D");
    attroff(COLOR_PAIR(pair));
}

int check_collision(drone_t *drone) {
    for (int i = 0; i < MAX_PUMPKINS; i++) {
        if (!pumpkins[i].collected && drone->x == pumpkins[i].x && drone->y == pumpkins[i].y) {
            pumpkins[i].collected = 1;
            drone->length++;
            return 1;
        }
    }
    return 0;
}

int find_nearest_pumpkin(drone_t *drone) {
    int nearest_index = -1;
    int min_distance = FIELD_WIDTH * FIELD_HEIGHT;

    for (int i = 0; i < MAX_PUMPKINS; i++) {
        if (!pumpkins[i].collected) {
            int distance = abs(drone->x - pumpkins[i].x) + abs(drone->y - pumpkins[i].y);
            if (distance < min_distance) {
                min_distance = distance;
                nearest_index = i;
            }
        }
    }
    return nearest_index;
}

void autopilot(drone_t *drone) {
    int nearest_pumpkin = find_nearest_pumpkin(drone);
    if (nearest_pumpkin != -1) {
        if (pumpkins[nearest_pumpkin].x > drone->x) {
            drone->direction = RIGHT;
        } else if (pumpkins[nearest_pumpkin].x < drone->x) {
            drone->direction = LEFT;
        } else if (pumpkins[nearest_pumpkin].y > drone->y) {
            drone->direction = DOWN;
        } else {
            drone->direction = UP;
        }
    }
    move_drone(drone);
}

void game_loop(int mode) {
    int ch;
    int autopilot_mode = mode == AUTOPILOT ? 1 : 0;

    while ((ch = getch()) != 'q') {
        clear();
        draw_pumpkins();

        for (int i = 0; i < MAX_DRONES; i++) {
            if (autopilot_mode) {
                autopilot(&drones[i]);
            } else {
                move_drone(&drones[i]);
            }

            draw_drone(&drones[i], i == 0 ? DRONE_PAIR : AUTOPILOT_DRONE_PAIR);

            if (check_collision(&drones[i])) {
                mvprintw(FIELD_HEIGHT + 1, 0, "Drone %d collected a pumpkin!", i + 1);
            }
        }

        mvprintw(FIELD_HEIGHT + 3, 0, "Press 'q' to quit.");
        refresh();
        napms(200);  // Adjust speed of the game
    }
}

int main() {
    srand(time(NULL));

    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(500);  // Set non-blocking input (500ms timeout)
    start_color();
    init_pair(DRONE_PAIR, COLOR_RED, COLOR_BLACK);
    init_pair(AUTOPILOT_DRONE_PAIR, COLOR_YELLOW, COLOR_BLACK);
    init_pair(PUMPKIN_PAIR, COLOR_GREEN, COLOR_BLACK);

    init_drones();
    init_pumpkins();

    mvprintw(FIELD_HEIGHT + 2, 0, "Press 'a' for autopilot mode, 'm' for manual mode, 'q' to quit.");
    refresh();

    int mode;
    do {
        mode = getch();
    } while (mode != 'a' && mode != 'm');

    if (mode == 'a') {
        game_loop(AUTOPILOT);
    } else if (mode == 'm') {
        game_loop(MANUAL);
    }

    endwin();
    return 0;
}
