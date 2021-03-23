/* 
Date: 12/07/2018
Section: (Section 5)
Assignment: (Assignment# 7)
Due Date: (12/07/2018)
About this project: To gain experience with using an array of structures,
    as well as with dynamic allocation of an array. This program provides
    further practice in file input, strings (either c-strings or string objects,
    programmer's choice), function building, and general code task problem
    solving and layout.
Assumptions: (Assumes user inputs correct file name to access the code
              and have it execute the hunt, the stats, and the ball inventory)

*/

#include <iostream>
#include <cstdlib> // for srand and rand
#include <ctime>  // for time
#include <iomanip> //setprecision
#include <fstream> //call files
#include <cctype> //declares a set of functions to classify & transform individual char
#include <string>
using namespace std;

//structure Type
struct pokemon
{
    int number; //numbers given to the pokemon
    string name; //name of pokemon
    string type; //type of pokemon
    int percent; //catch %
    int caught; //amount of pokemon caught
    int seen;   //amount of pokemon seen
};

//Function declaration.
void menu();
void hunt(pokemon * pokeSize, int pokedexSize, int ball_choice, int& pokeball, int& greatball, int& ultraball);
void pokestats(pokemon * pokeSize, int pokedexSize);
void inventory(int pokeball, int greatball, int ultraball);

int main()
{
    int pokedexSize, ball_choice;
    string filename, name;
    char choice;
    ifstream pokemons;
    int pokeball = 10;
    int greatball = 10;
    int ultraball = 10;

    srand ((unsigned int)time(0)); //seeding function, called only ONCE. @ the beginning

    do
    {
        //User inputs filename
        cout << "Enter the name of the file to open > ";
        getline(cin, filename);

        //Error checking
        pokemons.open(filename.c_str()); //Error checks works
        if(!pokemons)
        {
            cout << "Sorry, file cannot be opened! try again!\n";
        }
    }while(!pokemons);

        //Giving the amount of pokemons in the file
        pokemons >> pokedexSize;
        pokemon * pokeSize = new pokemon[pokedexSize];
        //Running the file through array to calculate all the structs
        for(int i = 0; i < pokedexSize; i++)
        {
            pokemons >> pokeSize[i].number;

            pokemons >> pokeSize[i].name;

            pokemons >> pokeSize[i].type;

            pokemons >> pokeSize[i].percent;

            pokeSize[i].caught = 0;

            pokeSize[i].seen = 0;

        }
        /*
        *  File closed dont want to run it more than once when running the entire
        *  code.
        */
        pokemons.close();

           //Have user input their name
           cout << "\nWhat's your name, trainer? > ";
           getline(cin, name);

           cout << "\nWelcome, " << name << ", to the COP3363 Safari Zone!\n";
           cout << "You'll have 30 chances to catch Pokemon, make them count!\n";
           cout << "The game will end once you run out of balls or if you choose to quit early\n\n";

  do
  {
        menu();
        cout << "Selection > ";
        cin >> choice;


        //error checking menu and loops it till user picks one of the correct choices.
        while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != 'Q' && choice != 'q')
        {
          cout << "Invalid Entry.\n";
          cout << "Selection > ";
          cin >> choice;
        }


        switch(choice)
        {
          case '1' : //Hunt for a Pokemon!
                   hunt(pokeSize, pokedexSize, ball_choice, pokeball, greatball, ultraball);
          break;
          case '2' : //Pokedex Statistics.
                   pokestats(pokeSize, pokedexSize);
          break;
          case '3' : //Print Inventory.
                   inventory(pokeball, greatball, ultraball);
          break;
        }
   }while(choice != 'Q' && choice != 'q'); //User Quits & stats of the game will appear
       pokestats(pokeSize, pokedexSize);
       cout << "bye!!";

return 0;
}
//prints out the menu
void menu()
{
  cout << "1 - Hunt for a Pokemon!\n";
  cout << "2 - Pokedex Statistics.\n";
  cout << "3 - Print Inventory.\n";
  cout << "4 - List Pokemon By Type\n";
  cout << "Q - Quit\n";
}
/*
* Hunt Generates the random pokemon.
* What pokemon ball the user wants to use to catch the pokemon with.
* See if user caught pokemon.
* Error checking when they have ran out of pokemon balls & incorrect inputs.
*/
void hunt(pokemon * pokeSize, int pokedexSize, int ball_choice, int& pokeball, int& greatball, int& ultraball)
{
    //Generates the random pokemons
    int rName = rand() % (pokedexSize - 1);
    cout << "\nA wild "<<  pokeSize[rName].name << "has appeared!\n\n";
    pokeSize[rName].seen++;

    cout << "Choose a ball to throw:\n";
    cout << "1 - Poke Ball      (You have: " << pokeball << ")\n";
    cout << "2 - Great Ball     (You have: " << greatball << ")\n";
    cout << "3 - Ultra Ball     (You have: " << ultraball << ")\n";

    bool answer = false;
    do
    {
      cout << "Selection > ";
      cin >> ball_choice;

      //Checking when user has ran out of balls to end game & print stats.
      if(pokeball == 0 && greatball == 0 && ultraball == 0)
      {
        cout << "You ran out of pokemon balls\n";
        pokestats(pokeSize, pokedexSize);
        exit(0);
      }
      else
      {
            //Generates random number
            int rNum = 1 + (rand() % 100);
            if(ball_choice == 1)
            {
              if(pokeball > 0)
              {
                cout << "Threw a Poke Ball!\n";
                --pokeball;
                answer = true;
                  //if/else to see if the user caught the pokemon or see if the pokemon ran.
                  if(rNum >= 1 && rNum <= pokeSize[rName].percent)
                  {
                      cout << "Congratulations! You caught " << pokeSize[rName].name << "!\n\n";
                      pokeSize[rName].caught++;
                      pokeSize[rName].percent++;
                  }
                  else
                  {
                     cout << pokeSize[rName].name << " ran away. :-( \n\n";
                  }
               }
               else
               {
                 cout << "You ran out of Pokeballs!\n";
               }
            }
            else if(ball_choice == 2)
            {
              if(greatball > 0)
              {
                cout << "Threw a Great Ball!\n";
                --greatball;
                answer = true;
                  //if/else to see if the user caught the pokemon or see if the pokemon ran.
                  if(rNum >= 1 && rNum <= pokeSize[rName].percent + 20)
                  {
                      cout << "Congratulations! You caught " << pokeSize[rName].name << "!\n\n";
                          pokeSize[rName].caught++;
                  }
                  else
                  {
                      cout << pokeSize[rName].name << " ran away. :-( \n\n";

                  }
              }
              else
              {
                cout << "You ran out of Great Balls!\n";
              }
            }
            else if (ball_choice == 3)
            {
              if(ultraball > 0)
              {
                cout << "Threw a Ultra Ball!\n";
                --ultraball;
                answer = true;
                  //if/else to see if the user caught the pokemon or see if the pokemon ran.
                  if(rNum >= 1 && rNum <= pokeSize[rName].percent + 40)
                  {
                      cout << "Congratulations! You caught " << pokeSize[rName].name << "!\n\n";
                          pokeSize[rName].caught++;

                  }
                  else
                  {
                      cout << pokeSize[rName].name << " ran away. :-( \n\n";
                  }
              }
              else
              {
                 cout << "You ran out of Ultra Balls!\n";
              }
            }
            else
            {
              //Error checking for incorrect user input
              cout << "Invalid Selection. Try again.\n";
              cout << "Selection > ";
              cin >> ball_choice;
           }
       }
     }while(answer == false);
}

void pokestats(pokemon * pokeSize, int pokedexSize)
{
  int pokeCaught = 0;
  int pokeSeen = 0;
  double catchRate = 0.0;
  cout << "\nPOKEDEX:\n";

  //Help print out the stats in the correct spacing :)
  for(int i = 0; i < pokedexSize; i++)
  {
      cout << left << setw(3)<<  "no" << left << setw(6) << i + 1;
      cout << left << setw(15) << pokeSize[i].name;
      cout << left <<  setw(1) << "Seen: "<< right << setw(1) <<  pokeSize[i].seen;
      cout << left << setw(1) << " Caught: " << pokeSize[i].caught << endl;

      pokeCaught += pokeSize[i].caught;
      pokeSeen += pokeSize[i].seen;

  }
    //Percentage of the amount of pokemons the user caught to the amount of pokemon the user saw.
    catchRate = ((double)(pokeCaught)/(pokeSeen))* 100;
    cout << "Total Pokemon Caught: " << pokeCaught << " Total Pokemon Seen: " << pokeSeen << "\n";
    cout << "Overall Catch Rate: " << fixed << showpoint <<  setprecision(2) <<  catchRate << "%\n\n";
}

void inventory(int pokeball, int greatball, int ultraball)
{
   cout << "you have:\n";
   cout << pokeball << " PokeBalls\n";
   cout << greatball << " Great Balls\n";
   cout << ultraball << " Ultra Balls\n\n";
}
