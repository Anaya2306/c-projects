#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char name[100];
    struct Song* next;
    struct Song* prev;
} Song;

typedef struct {
    Song* current;
} Playlist;

Song* createSong(const char* name) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    strcpy(newSong->name, name);
    newSong->next = newSong->prev = newSong;
    return newSong;
}

void addSong(Playlist* playlist, const char* name) {
    Song* newSong = createSong(name);
    if (playlist->current == NULL) {
        playlist->current = newSong;
    } else {
        Song* last = playlist->current->prev;

        newSong->next = playlist->current;
        newSong->prev = last;

        last->next = newSong;
        playlist->current->prev = newSong;
    }
    printf("Added: %s\n", name);
}

void nextSong(Playlist* playlist) {
    if (playlist->current) {
        playlist->current = playlist->current->next;
        printf("Now playing: %s\n", playlist->current->name);
    } else {
        printf("Playlist is empty.\n");
    }
}

void previousSong(Playlist* playlist) {
    if (playlist->current) {
        playlist->current = playlist->current->prev;
        printf("Now playing: %s\n", playlist->current->name);
    } else {
        printf("Playlist is empty.\n");
    }
}

void removeCurrentSong(Playlist* playlist) {
    if (!playlist->current) {
        printf("Playlist is empty.\n");
        return;
    }

    Song* toRemove = playlist->current;
    if (toRemove->next == toRemove) {
        playlist->current = NULL;
    } else {
        toRemove->prev->next = toRemove->next;
        toRemove->next->prev = toRemove->prev;
        playlist->current = toRemove->next;
    }
    printf("Removed: %s\n", toRemove->name);
    free(toRemove);
}

void displayPlaylist(Playlist* playlist) {
    if (!playlist->current) {
        printf("Playlist is empty.\n");
        return;
    }

    Song* temp = playlist->current;
    printf("Playlist:\n");
    do {
        printf("- %s\n", temp->name);
        temp = temp->next;
    } while (temp != playlist->current);
}

int main() {
    Playlist playlist = {NULL};
    int choice;
    char name[100];

    while (1) {
        printf("\n--- Music Playlist Manager ---\n");
        printf("1. Add Song\n");
        printf("2. Next Song\n");
        printf("3. Previous Song\n");
        printf("4. Remove Current Song\n");
        printf("5. Display Playlist\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("Enter song name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; // remove newline
                addSong(&playlist, name);
                break;
            case 2:
                nextSong(&playlist);
                break;
            case 3:
                previousSong(&playlist);
                break;
            case 4:
                removeCurrentSong(&playlist);
                break;
            case 5:
                displayPlaylist(&playlist);
                break;
            case 6:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
