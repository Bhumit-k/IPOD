#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "sort_shuffle.h"

void sort_songs(char artist[][50], char title[][3][50], int num_artists) {
    for (int i = 0; i < num_artists; i++) {
        for (int j = 0; j < 2 && title[i][j][0] != '\0'; j++) {
            for (int k = j+1; k < 3 && title[i][k][0] != '\0'; k++) {
                // Sort by artist first
                if (strcmp(artist[i], artist[i]) > 0) {
                    char temp_artist[50];
                    strcpy(temp_artist, artist[i]);
                    strcpy(artist[i], artist[j]);
                    strcpy(artist[j], temp_artist);
                    char temp_title[50];
                    strcpy(temp_title, title[i][0]);
                    strcpy(title[i][0], title[j][0]);
                    strcpy(title[j][0], temp_title);
                    strcpy(temp_title, title[i][1]);
                    strcpy(title[i][1], title[j][1]);
                    strcpy(title[j][1], temp_title);
                    strcpy(temp_title, title[i][2]);
                    strcpy(title[i][2], title[j][2]);
                    strcpy(title[j][2], temp_title);
                }
                    // Then sort by title
                else if (strcmp(title[i][j], title[i][k]) > 0) {
                    char temp_title[50];
                    strcpy(temp_title, title[i][j]);
                    strcpy(title[i][j], title[i][k]);
                    strcpy(title[i][k], temp_title);
                }
            }
        }
    }
}

void create_playlist(char artist[][50], char title[][3][50], int num_artists) {
    srand(time(NULL));
    int num_songs = 0;
    for (int i = 0; i < num_artists; i++) {
        for (int j = 0; j < 3; j++) {
            if (title[i][j][0] != '\0') {
                num_songs++;
            }
        }
    }
    char playlist[num_songs][50];
    int played_songs = 0;
    while (played_songs < num_songs) {
        int artist_index = rand() % num_artists;
        int song_index = rand() % 3;
        if (title[artist_index][song_index][0] != '\0') {
            bool song_played = false;
            for (int i = played_songs - 1; i >= 0 && i >= played_songs - 5; i--) {
                if (strcmp(playlist[i], title[artist_index][song_index]) == 0) {
                    song_played = true;
                    break;
                }
            }
            if (!song_played) {
                strcpy(playlist[played_songs], title[artist_index][song_index]);
                played_songs++;
            }
        }
    }
    printf("Playlist:\n");
    for (int i = 0; i < num_songs; i++) {
        printf("%d. %s\n", i+1, playlist[i]);
    }
}
