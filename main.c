#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sort_shuffle.h"

#define MAX_ARTISTS 4
#define MAX_SONGS 3
#define MAX_TITLE_LEN 50
#define MAX_PLAYLIST_LEN 24
#define MIN_SONG_GAP 5

int main() {
    char a[MAX_ARTISTS][MAX_TITLE_LEN];
    char title[MAX_ARTISTS][MAX_SONGS][MAX_TITLE_LEN];
    int num_artists = 0;

    // Read input from user
    while (num_artists < MAX_ARTISTS) {
        printf("Enter artist name (or press Enter to finish): ");
        fgets(a[num_artists], MAX_TITLE_LEN, stdin);
        if (a[num_artists][0] == '\n') {
            break;
        }
        a[num_artists][strcspn(a[num_artists], "\n")] = '\0'; // remove trailing newline
        for (int i = 0; i < MAX_SONGS; i++) {
            printf("Enter song title (or press Enter to finish): ");
            fgets(title[num_artists][i], MAX_TITLE_LEN, stdin);
            if (title[num_artists][i][0] == '\n') {
                break;
            }
            title[num_artists][i][strcspn(title[num_artists][i], "\n")] = '\0'; // remove trailing newline
        }
        num_artists++;
    }

    // Sort songs by artist and title
    sort_songs(a, title, num_artists);

    // Print sorted list of songs
    printf("\nSorted list of songs:\n");
    for (int i = 0; i < num_artists; i++) {
        printf("%s:\n", a[i]);
        for (int j = 0; j < MAX_SONGS && title[i][j][0] != '\0'; j++) {
            printf("  %s\n", title[i][j]);
        }
    }

    create_playlist(a,title,num_artists);
    // Generate random playlist
    printf("\nRandom playlist:\n");
    srand(time(NULL)); // seed the random number generator with current time
    int num_songs = 0;
    char playlist[MAX_PLAYLIST_LEN][MAX_TITLE_LEN];
    while (num_songs < MAX_PLAYLIST_LEN) { // generate 12-song playlist
        for (int i = 0; i < num_artists && num_songs < MAX_PLAYLIST_LEN; i++) {
            for (int j = 0; j < MAX_SONGS && title[i][j][0] != '\0' && num_songs < MAX_PLAYLIST_LEN; j++) {
                // Check if the song has been played less than 5 songs ago
                int can_play = 1;
                for (int k = num_songs - 1; k >= num_songs - MIN_SONG_GAP && k >= 0; k--) {
                    if (strcmp(playlist[k], title[i][j]) == 0) {
                        can_play = 0;
                        break;
                    }
                }
                if (can_play) {
                    strcpy(playlist[num_songs], title[i][j]);
                    printf("%d. %s - %s\n", num_songs+1, a[i], title[i][j]);
                    num_songs++;
                }
            }
        }
    }

    return 0;
}
