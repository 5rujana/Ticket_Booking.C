#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX_MOVIES 10
#define MAX_SEATS_PER_MOVIE 200
#define MAX_AC_SEATS 100
#define MAX_NON_AC_SEATS 100

// Structures
typedef struct {
    char name[50];
    int price;
} Movie;

typedef struct {
    int movieId;
    int isAc;
    int isBooked;
} Seat;

Movie movies[MAX_MOVIES];
Seat seats[MAX_MOVIES][MAX_SEATS_PER_MOVIE];

int numMovies = 0;


void addMovie() {
    if (numMovies >= MAX_MOVIES) {
        printf("Maximum number of movies reached.\n");
        return;
    }

    Movie newMovie;
    printf("Enter movie name: ");
    scanf("%s", newMovie.name);
    printf("Enter price for AC seats: ");
    scanf("%d", &newMovie.price);

    Movie nonACMovie;
    strcpy(nonACMovie.name, newMovie.name);
    printf("Enter price for Non-AC seats: ");
    scanf("%d", &nonACMovie.price);

    movies[numMovies++] = newMovie;
    movies[numMovies++] = nonACMovie;

    printf("Movies added successfully.\n");
}


void displayMovies() {
    printf("Movies available:\n");
    for (int i = 0; i < numMovies; i++) {
        printf("%d. %s\n", i + 1, movies[i].name);
    }
}

void bookSeat() {
    int movieChoice;
    int seatChoice;
    int acChoice;

    displayMovies();
    printf("Select a movie: ");
    scanf("%d", &movieChoice);
    movieChoice--;

    if (movieChoice < 0 || movieChoice >= numMovies) {
        printf("Invalid movie selection.\n");
        return;
    }

    printf("Select seat type:\n");
    printf("1. AC\n");
    printf("2. Non-AC\n");
    scanf("%d", &acChoice);

    if (acChoice != 1 && acChoice != 2) {
        printf("Invalid seat type selection.\n");
        return;
    }

    int maxSeats = (acChoice == 1) ? MAX_AC_SEATS : MAX_NON_AC_SEATS;
    displaySeats(movieChoice);
    printf("Select a seat (1-%d): ", maxSeats);
    scanf("%d", &seatChoice);
    seatChoice--;

    if (seatChoice < 0 || seatChoice >= maxSeats) {
        printf("Invalid seat selection.\n");
        return;
    }

    if (seats[movieChoice][seatChoice].isBooked) {
        printf("Seat already booked.\n");
        return;
    }

    seats[movieChoice][seatChoice].isBooked = 1;
    printf("Seat booked successfully!\n");
}

void displaySeats(int movieId) {
    printf("Seats for %s:\n", movies[movieId].name);
    for (int i = 0; i < (movies[movieId].price == 0 ? MAX_AC_SEATS : MAX_NON_AC_SEATS); i++) {
        if (!seats[movieId][i].isBooked) {
            printf("%d. Seat %d\n", i + 1, i + 1);
        }
    }
}

void initializeSeats() {
    for (int i = 0; i < MAX_MOVIES; i++) {
        for (int j = 0; j < MAX_SEATS_PER_MOVIE; j++) {
            seats[i][j].movieId = -1;
            seats[i][j].isAc = -1;
            seats[i][j].isBooked = 0;
        }
    }
}


int main() {
    initializeSeats();

    int role;
    do {
        printf("Select a role:\n");
        printf("1. Producer\n");
        printf("2. Customer\n");
        printf("0. Exit\n");
        scanf("%d", &role);

        switch (role) {
            case 1:
                addMovie();
                break;
            case 2:
                displayMovies();
                bookSeat();
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid role selection. Please try again.\n");
                break;
        }
    } while (role != 0);

    return 0;
}