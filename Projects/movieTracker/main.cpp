#include "movieTracker.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cout<<"Test"<<endl;

    // 1. Create a "To Watch" movie (Base Class)
    vector<string> duneActors = {"Timothee Chalamet", "Zendaya"};
    Movie toWatch("Dune: Part Two", "Sci-Fi", 2024, "Denis Villeneuve", 
                  "Paul Atreides unites with the Fremen...", duneActors);

    // 2. Create a "Watched" movie (Derived Class)
    vector<string> oppActors = {"Cillian Murphy", "Emily Blunt"};
    watchedMovie watched("Oppenheimer", "Biographical Drama", 2023, "Christopher Nolan", 
                         "The story of J. Robert Oppenheimer...", oppActors, 5.0);


    // 3. Test the output (uses our 'friend operator<<')
    
    cout << "\n--- 'To Watch' List Item ---" << endl;
    cout << toWatch << endl;
    
    cout << "--- 'Watched' List Item ---" << endl;
    cout << watched << endl;

    // 4. Test Inheritance and Virtual Functions
    // We can use a base 'Movie' pointer to hold a 'WatchedMovie' object
    Movie* pMovie = &watched;
    cout << "--- Test Polymorphism ---" << endl;
    cout << "Title: " << pMovie->getTitle() << endl; // Uses base method
    
    // Because getRatingString() is 'virtual', this call
    // correctly runs the 'WatchedMovie' version!
    cout << "Rating: " << pMovie->getRatingString() << endl; 

    return 0;
}
