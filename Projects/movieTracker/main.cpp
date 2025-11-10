#include "movieTracker.h"
#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <ios>
#include <fstream>
#include <sstream>

using namespace std;
void displayMenu();
string getStringInput(const string& prompt);
int getIntInput(const string& prompt);
float getFloatInput(const string& prompt);
void addMovie(vector<Movie*>& list);
void addWatchedMovie(vector<Movie*>& toWatchList, vector<Movie*>& watchedList);
void viewList(const vector<Movie*>& list, const string& title);
bool loadToWatchList(vector<Movie*>& list, const string& filename);
bool loadWatchedList(vector<Movie*>& list, const string& filename);
void saveToWatchList(const vector<Movie*>& list, const string& filename);
void saveWatchedList(const vector<Movie*>& list, const string& filename);

void displayMenu()
{
    cout<< "Menu\n";
    cout<< "1. Add a movie to watch \n";
    cout<< "2. Update watched list \n";
    cout<< "3. View 'To Watch' list\n";
    cout<< "4. View 'Watched' list\n";
    cout<< "5. Exit\n";
    cout<< "--------------------\n";
    cout<< "Enter your choice: ";
}

string getStringInput(const string& prompt)
{
    cout<< prompt;
    string input;
    getline(cin, input);
    return input;
}

int getIntInput(const string& prompt)
{
    int input;
    while (true) 
    {
        cout<< prompt;
        cin>> input;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ERROR. Please enter a number.\n";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return input;
        }
    }
}

float getFloatInput(const string& prompt)
{
    float input;
    while (true) 
    {
        cout<< prompt;
        cin>> input;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<< "ERROR. Please enter a number (e.g., 4.5).\n";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return input;
        }
    }
}

void addMovie(vector<Movie*>& list)
{
    cout<< "Add A New Movie\n";
    string title= getStringInput("Title: ");
    string genre= getStringInput("Genre: ");
    int year= getIntInput("Year: ");
    string director= getStringInput("Director: ");
    
    vector<string> actors;
    actors.push_back(getStringInput("Main Actor: "));

    list.push_back(new Movie(title, genre, year, director, actors));
    cout<< "\nMovie added to 'To Watch' list!\n";
}

void addWatchedMovie(vector<Movie*>& toWatchList, vector<Movie*>& watchedList)
{
    cout<< "Update 'Watched' list\n"<<endl;
    if (toWatchList.empty())
    {
        cout<<"Your 'To Watch List' is empty."<<endl;
        return;
    }

    viewList(toWatchList,"Your 'To Watch' List");
    cout<<"\n==================\n";

    int choice= 0;
    while (true)
    {
        choice= getIntInput("Enter the number of the movie (0 to cancel): ");
        if (choice==0)
        {
            return;
        }

        if (choice>0 && choice<= toWatchList.size())
        {
            break;
        }
        else
        {
            cout<<"Invalid Input. Please enter a number between 1 and "<< toWatchList.size()<<"."<<endl;
        }
    }

    float newRating= getFloatInput("Your Rating (0.0-5.0): ");
    int i=  choice-1;

    Movie* movieToMove= toWatchList[i];

    watchedMovie* newWatchedMovie= new watchedMovie
    (
        movieToMove-> getTitle(),
        movieToMove-> getGenre(),
        movieToMove-> getYear(),
        movieToMove-> getDirector(),
        movieToMove-> getActors(),
        newRating
    );

    watchedList.push_back(newWatchedMovie);

    delete movieToMove;
    toWatchList.erase(toWatchList.begin()+i);

    cout<<"\n Successfully updated '"<<newWatchedMovie->getTitle() <<"' to your 'Watched' list!"<<endl;

}

void viewList(const vector<Movie*>& list, const string& title)
{
    cout<< title<< "\n";
    cout<< "====================\n";
            
    if (list.empty())
    {
        cout << "This list is empty.\n";
        return;
    }

    for (size_t i = 0; i < list.size(); ++i)
    {
        cout<< "\n--- Item " << (i + 1) << " ---\n";
        cout<< *(list[i]); 
    }
}

bool loadToWatchList(vector<Movie*>& list, const string& filename)
{
    ifstream inStream(filename);
    if (!inStream) 
    {
        cout<< "Error: Could not open " << filename<<".";
        return false; 
    }

    string title, genre, yearStr, director, actor;
    int year;

    while (getline(inStream, title) &&
           getline(inStream, genre) &&
           getline(inStream, yearStr) &&
           getline(inStream, director) &&
           getline(inStream, actor))
    {
        stringstream sString(yearStr);
        sString >> year;
        
        vector<string> actors;
        if (!actor.empty()) {
            actors.push_back(actor);
        }
        
        list.push_back(new Movie(title, genre, year, director, actors));
    }
    inStream.close();
    return true;
}
bool loadWatchedList(vector<Movie*>& list, const string& filename)
{
    ifstream inStream(filename);
    if (!inStream) 
    {
        return false;
    }

    string title, genre, yearStr, director, actor, ratingStr;
    int year;
    float rating;

    while (getline(inStream, title) &&
           getline(inStream, genre) &&
           getline(inStream, yearStr) &&
           getline(inStream, director) &&
           getline(inStream, actor) &&
           getline(inStream, ratingStr))
    {
        stringstream ssYear(yearStr);
        ssYear>> year;
        stringstream ssRating(ratingStr);
        ssRating>> rating;

        vector<string> actors;
        if (!actor.empty()) {
            actors.push_back(actor);
        }
        
        list.push_back(new watchedMovie(title, genre, year, director, actors, rating));
    }
    inStream.close();
    return true;
}

void saveToWatchList(const vector<Movie*>& list, const string& filename)
{
    ofstream outStream(filename);
    if (!outStream) {
        cout << "Error: Could not open " << filename << ".";
        return;
    }

    for (const Movie* moviePtr : list) {
        outStream<< moviePtr->getTitle() << endl;
        outStream<< moviePtr->getGenre() << endl;
        outStream<< moviePtr->getYear() << endl;
        outStream<< moviePtr->getDirector() << endl;
        
        if (!moviePtr->getActors().empty()) {
            outStream << moviePtr->getActors()[0] << endl;
        } else {
            outStream<< endl; 
        }
    }
    outStream.close();
    cout<< "Saved to "<< filename<< endl;
}

void saveWatchedList(const vector<Movie*>& list, const string& filename)
{
    ofstream outStream(filename);
    if (!outStream) {
        cout<< "Error: Could not open " << filename << " for writing.\n";
        return;
    }

    for (const Movie* moviePtr : list) {
        const watchedMovie* wMovie = dynamic_cast<const watchedMovie*>(moviePtr);
        
        if (wMovie) { 
            outStream<< wMovie->getTitle()<< endl;
            outStream<< wMovie->getGenre()<< endl;
            outStream<< wMovie->getYear() << endl;
            outStream<< wMovie->getDirector()<< endl;
            
            if (!wMovie->getActors().empty()) {
                outStream<< wMovie->getActors()[0]<< endl;
            } else {
                outStream<< endl;
            }
            
            outStream<< wMovie->getRating()<< endl; 
        }
    }
    outStream.close();
    cout<< "Saved to "<< filename<< endl;
}

int main()
{
     const string fToWatch = "toWatch.txt";
    const string fWatched = "watched.txt";

    vector<Movie*> toWatchList;
    vector<Movie*> watchedList;
    
    cout<< "Loading movie lists\n";
    
    if (!loadToWatchList(toWatchList, fToWatch)) 
    {
        return 1;
    }
    
    if (!loadWatchedList(watchedList, fWatched)) 
    {
        cout << "No 'Watched' file found. Starting with an empty list.\n";
    }   

    int choice = 0;

    while (choice != 5)
    {
        displayMenu();
        cin>> choice;

        if (cin.fail())
        {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<< "Invalid input. Please enter a number.\n\n";
            continue; 
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout<< endl; 

        switch (choice)
        {
            case 1:
                addMovie(toWatchList);
                break;
            case 2:
                addWatchedMovie(toWatchList, watchedList);
                break;
            case 3:
                viewList(toWatchList, "'To Watch' List");
                break;
            case 4:
                viewList(watchedList, "'Watched' List");
                break;
            case 5:
                cout << "Saving lists\n";
                saveToWatchList(toWatchList, fToWatch);
                saveWatchedList(watchedList, fWatched);
                break;
            default:
                cout<< "Invalid choice. Please select from 1-5.\n";
                break;
        }
        cout<< endl; 
    }

    cout<< "Cleaning up memory..."<< endl;

    for (Movie* ptr : toWatchList)
    {
        delete ptr;
    }
    for (Movie* ptr : watchedList)
    {
        delete ptr;
    }

    cout<< "Complete. Exiting."<< endl;
    return 0;
}
