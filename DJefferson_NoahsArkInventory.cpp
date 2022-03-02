//*******************************************************************************
//Programmer's Name: Destiny Jefferson
//Date: February 16, 2022
//Program Title: Noah's Ark Inventory Application
//Program Description: This program should be able to (a) prompt the user for
//input as to whether or not they want to check the inventory of animals or
//continue letting time pass. As time passes, said animals will reproduce and 
//more animals are added to the inventory. User should be able to see age of
//animal, gender, and species when they decide to check inventory.
//*******************************************************************************

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


class Animal {

public:
    //enumerators for species & gender
    enum species_t { LION, FOX, HAWK, RAVEN, TETRA, SALMON };
    enum gender_t { MALE, FEMALE };

    //base constructor
    Animal() = default;

    //overloaded constructor (we use this one)
    Animal(species_t species, gender_t gender, int age) noexcept :
        age_(age), species_(species), gender_(gender) {
    }

    void userPrompts() {//for the UI, duh
        while (userInput != 3) {
            cout << "You have been on the ark for ";
            convertTime(months);
            cout << " Would you like to : " << endl;
            cout << "     1 - Let another month pass" << endl;
            cout << "     2 - Check inventory" << endl;
            cout << "     3 - Quit" << endl;
            cout << ">> ";
            cin >> userInput;

            while ((userInput > 3 || userInput == 0) || !cin) {//for incorrect input testing
                cin.clear();
                cin.ignore();
                cout << "Your input type is incorrect. Please try again." << endl;
                cout << ">> ";
                cin >> userInput;
            }
            //pathway from user input menu
            switch (userInput) { //let's time pass (and animals age)
            case 1:
                cout << endl;
                //check for new offspring 1st at current age
                createNewAni();
                //age all animals by 1 month & increment time
                months += 1;
                addAge(); //time is incremented AFTER all calcs are performed
                break;
            case 2:
                cout << endl;
                createNewAni();
                //return list of anis on ship (age, species, and gender)
                printAll();
                months += 1;
                //add 1 to all ani ages
                addAge();
                cout << endl;
                break;
            }
        }
        if (userInput == 3) {
            cout << "Thank you for playing! Goodbye!";
        }
    }


    static void addAge() {//ages up all animals in vector
        for (size_t i = 0; i < animals.size(); i++) {
            int num = animals[i].age() + 1;
            animals[i].setAge(num);
        }

    }

    //adds new Animal to vector/inventory
    static void add(species_t species, gender_t gender, int age) {

        animals.emplace_back(species, gender, age);
    }


    bool inHeat() const { //not static bc checks one animal at a time

        if (gender() == MALE) { //males do not reproduce
            return false;
        }

        bool heat = false;
        //only evals to true if correct species, gender, and age range
        if (this->species() == Animal::SALMON && this->gender() == Animal::FEMALE && (this->age() % 6 == 0 && this->age() != 0)) {
            heat = true;
        }
        else if (this->species() == Animal::TETRA && this->gender() == Animal::FEMALE && (this->age() % 6 == 0 && this->age() != 0)) {
            heat = true;
        }
        else if (this->species() == Animal::RAVEN && this->gender() == Animal::FEMALE && (this->age() % 9 == 0 && this->age() != 0)) {
            heat = true;
        }
        else if (this->species() == Animal::HAWK && this->gender() == Animal::FEMALE && (this->age() % 9 == 0 && this->age() != 0)) {
            heat = true;
        }
        else if (this->species() == Animal::LION && this->gender() == Animal::FEMALE && (this->age() % 12 == 0 && this->age() != 0)) {
            heat = true;
        }
        else if (this->species() == Animal::FOX && this->gender() == Animal::FEMALE && (this->age() % 12 == 0 && this->age() != 0)) {
            heat = true;
        }
        return heat;
    }

    void createNewAni() { //Currently only creates one new animal as opposed to 1 for all who are in heat **CHECK THIS PART**
        for (size_t i = 0; i < animals.size(); i++) {
            if (animals[i].inHeat())
                add(animals[i].species(), randomGen(), 0);
        }
    }

    gender_t randomGen() {//randomize animal gender for newborns
        gender_ = rand() % 2 == 0 ? Animal::MALE : Animal::FEMALE;

        return gender_;
    }

    species_t species() const { //returns species
        return species_;
    }

    gender_t gender() const { //returns animal gender if stable
        return gender_;
    }

    int age() const { //returns animal age
        return age_;
    }

    int setAge(int num) {//allows us to change the animal age & save it
        age_ = num;
        return age_;
    }

    //print func
    void print() const { //not static bc only printing about 1 animal
        static const char* const species_text[] = { "lion", "fox", "hawk", "raven", "tetra", "salmon" }; //converts enum vals to strings for output

        // uses a conditional to convert gender to string
        //also our main way of listing all animals in inventory
        cout << (gender() == MALE ? "male" : "female") << " " << species_text[species()] << ", " << age() << " months old" << endl;
    }

    //lol another print func
    static void printAll() { //static bc for all animals
        for (size_t i = 0; i < animals.size(); i++) {
            cout << "Animal #" << i + 1 << ": I am a ";
            animals[i].print();
        }
    }

    static const vector <Animal>& list() {//makes list of anis to return
        return animals;
    }

    void convertTime(int mths) {//converts months to years
        int years, leftoverMths;

        years = mths / 12;
        leftoverMths = mths - (years * 12);

        cout << years << " year(s) and " << leftoverMths << " month(s).";

    }

private:
    //member vars
    int age_ = 0, userInput = 1, months = 11;
    species_t species_ = LION;
    gender_t gender_ = MALE;

    static vector<Animal> animals;
};

//our lovely vector
vector<Animal> Animal::animals;

int main() {

    srand(time(NULL));
    Animal Zoo;

    // add initial animals by calling the static member function of Animal
    Animal::add(Animal::LION, Animal::FEMALE, 11);
    Animal::add(Animal::LION, Animal::MALE, 11);
    Animal::add(Animal::FOX, Animal::FEMALE, 11);
    Animal::add(Animal::FOX, Animal::MALE, 11);
    Animal::add(Animal::HAWK, Animal::FEMALE, 11);
    Animal::add(Animal::HAWK, Animal::MALE, 11);
    Animal::add(Animal::RAVEN, Animal::FEMALE, 11);
    Animal::add(Animal::RAVEN, Animal::MALE, 11);
    Animal::add(Animal::TETRA, Animal::FEMALE, 11);
    Animal::add(Animal::TETRA, Animal::MALE, 11);
    Animal::add(Animal::SALMON, Animal::FEMALE, 11);
    Animal::add(Animal::SALMON, Animal::MALE, 11);

    Zoo.userPrompts();

}