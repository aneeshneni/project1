#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/*
    File struct that holds:
    string: Title
    string: URL
    int: Popularity Score
*/
// Akshar Driving here
struct Story {
    string title;
    string url;
    int popularity;
};

/*
    Function to read stories file and returns an array of File structs
*/
// Akshar done driving, Aneesh Driving here
Story* readStories(string filename, int &size) {
    // Open file
    ifstream storyFile;
    storyFile.open(filename);

    // Read file line by line
    string line;
    getline(storyFile, line);
    size = stoi(line);

    // malloc array of story structs
    Story* stories = (Story*) malloc(sizeof(Story) * size);

    int i = 0;
    while (getline(storyFile, line)) {
        // Split line by comma
        string title = line;
        getline(storyFile, line);
        string url = line;
        getline(storyFile, line);
        int popularity = stoi(line);

        // Create story struct
        Story story;
        story.title = title;
        story.url = url;
        story.popularity = popularity;

        // Add story to array
        stories[i] = story;
        i++;
    }

    // Close file
    storyFile.close();

    // Return array of stories
    return stories;
}

/*
    Function to find the mode of array of stories, if no mode exists, return -1
*/
// Aneesh done driving, Akshar driving here
int findMode(Story* stories, int size) {
    // Create array of popularity scores
    int* popularityScores = (int*) malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        popularityScores[i] = stories[i].popularity;
    }

    // Sort popularity scores [COULD MAKE INTO FUNCTION]
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (popularityScores[i] > popularityScores[j]) {
                int temp = popularityScores[i];
                popularityScores[i] = popularityScores[j];
                popularityScores[j] = temp;
            }
        }
    }

    // Find mode
    int mode = -1;
    int maxCount = 0;
    int count = 1;
    for (int i = 0; i < size; i++) {
        if (popularityScores[i] == popularityScores[i + 1]) {
            count++;
        } else {
            if (count > maxCount) {
                maxCount = count;
                mode = popularityScores[i];
            }
            count = 1;
        }
    }

    // Free memory
    free(popularityScores);

    // Return mode
    return mode;
}

/*
    Function to print stories given mode
*/
// Akshar done driving, Aneesh driving here
void printStories(Story* stories, int mode, int size) {
    // Print mode    
    cout << "Mode: " << mode << "\n" << endl;


    // Print stories with mode popularity score
    for (int i = 0; i < size; i++) {
        if (stories[i].popularity == mode) {
            cout << stories[i].title << endl;
            cout << stories[i].url << "\n" << endl;  
        }
    }
}


/*
    Function to read user file and returns an array of File structs
*/
// Aneesh done driving, Akshar driving here
int main() {

    // Read stories file
    string storyName;
    cout << "Enter stories filename: ";
    cin >> storyName;
    string inputFile = "/Users/aneeshn/Downloads/CS 105C/" + storyName;

    int size;
    Story* stories = readStories(inputFile, size);

    // Find mode
    int mode = findMode(stories, size);

    // Print stories given mode
    printStories(stories, mode, size);

    // Free stories array
    free(stories);

    return 0;
}

