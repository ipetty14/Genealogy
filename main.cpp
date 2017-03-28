//
//  main.cpp
//  Genealogy Project
//
//  Created by Ian Petty on 12/9/16.
//  Copyright © 2016 Ian Petty. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "list1.h"
#include "node.h"

using namespace std;

/***********************************************
 * NODE : LEVEL DISPLAY
 * This function traverses the list and displays 
 * the generations.
 ***********************************************/
template<class T>
void Node<T>::levelDisplay()
{
    const int MAX = 150;
    Node<T> *queue[MAX];
    Node<T> *temp;
    int front = 0;
    int back = 0;
    int count = 0;
    int numPeople = 0;
    bool newGeneration = false;
    
    queue[back++] = this;
    int saveBack = back;
    
    while (front != back)
    {
        temp = queue[front];
        front = (front + 1) % MAX;
        if (temp != NULL)
        {
            // visit
            if (front == saveBack)
            {
                newGeneration = true;
                
                if (count == 0)
                    cout << "The Ancestors of " << temp->data.givenName
                    << " " << temp->data.lastName << ":" << endl;
                if (count == 1)
                    cout << "Parents:" << endl;
                if (count == 2)
                    cout << "Grandparents:" << endl;
                if (count == 3)
                    cout << "Great Grandparents:" << endl;
                if (count == 4)
                    cout << "2nd Great Grandparents:" << endl;
                if (count == 5)
                    cout << "3rd Great Grandparents:" << endl;
                if (count == 6)
                    cout << "4th Great Grandparents:" << endl;
                if (count == 7)
                    cout << "5th Great Grandparents:" << endl;
                if (count == 8)
                {
                    //do nothing
                }
                
                count++;
            }
            else
                newGeneration = false;
            
            if(numPeople != 0)
            {
                cout.width(4);
                cout << "        ";
                if(temp->data.givenName != "")
                    cout << temp->data.givenName;
                if(temp->data.lastName != "")
                {
                    if(temp->data.givenName != "")
                        cout << " " << temp->data.lastName;
                    else
                        cout << temp->data.lastName;
                }
                
                if(temp->data.birthday != "")
                {
                    cout << ", b. " << temp->data.birthday << endl;
                }
                else
                    cout << endl;
            }
            
            numPeople++;
            
            // end Visit
            if (temp->pFather)
            {
                queue[back] = temp->pFather;
                back = (back + 1) % MAX;
            }
            
            if (newGeneration)
                saveBack = back;
            
            if (temp->pMother)
            {
                queue[back] = temp->pMother;
                back = (back + 1) % MAX;
            }
        }
    }

}

/***********************************************
 * MAIN : SET FAMILIES
 * This function sets each of the family pointers
 * for each person in the file. Calls the function
 * LEVEL DISPLAY to display the generations.
 ***********************************************/
void setFamilies(List<Person> people, string lines[], int count)
{
    Family families[200];
    int familyIndex = 0;
    
    for(int i = 0; i < count; i++)
    {
        if(lines[i][0] == '0' && lines[i][2] == '@' && lines[i][3] == 'F')
        {
            Family newFamily;
            int fatherID = 0;
            int motherID = 0;
            int childID = 0;
            familyIndex++;
            
            for(int index = i + 1; lines[index][0] != '0'; index++)
            {
                if(lines[index][2] == 'H')
                    fatherID = index;
                if(lines[index][2] == 'W')
                    motherID = index;
                if(lines[index][2] == 'C')
                    childID = index;
            }
            
            if(fatherID > 0)
            {
                string tempFather;
                for(int k = 9; lines[fatherID][k] != '@'; k++)
                    tempFather += lines[fatherID][k];
                
                newFamily.father = atoi(tempFather.c_str());
            }
            else
                newFamily.father = 0;
            
            if(motherID > 0)
            {
                string tempMother;
                for(int l = 9; lines[motherID][l] != '@'; l++)
                    tempMother += lines[motherID][l];
                
                newFamily.mother = atoi(tempMother.c_str());
            }
            else
                newFamily.mother = 0;
            
            if(childID > 0)
            {
                string tempChild;
                for(int j = 9; lines[childID][j] != '@'; j++)
                    tempChild += lines[childID][j];
                
                newFamily.child = atoi(tempChild.c_str());
            }
            else
                newFamily.child = 0;
            
            families[familyIndex] = newFamily;
        }
    }
    
    for(int i = 0; i <= familyIndex; i++)
    {
        ListIterator<Person> childIt = people.begin();
        while(childIt.p != NULL && childIt.p->data.id != families[i].child)
        {
            childIt++;
        }
        
        ListIterator<Person> fatherIt = people.begin();
        while(fatherIt.p != NULL && fatherIt.p->data.id != families[i].father)
        {
            fatherIt++;
        }
        
        ListIterator<Person> motherIt = people.begin();
        while(motherIt.p != NULL && motherIt.p->data.id != families[i].mother)
        {
            motherIt++;
        }
        
        if(childIt.p != NULL)
        {
            if(fatherIt.p != NULL)
                childIt.p->pFather = fatherIt.p;
            if(motherIt.p != NULL)
                childIt.p->pMother = motherIt.p;
        }
    }
    
    ListIterator<Person> familyIt = people.begin();
    while(familyIt.p->data.id != 1 && familyIt != people.end())
    {
        familyIt++;
    }
    
    cout << endl;
    
    familyIt.p->levelDisplay();
}

/***********************************************
 * MAIN : WRITE TO FILE
 * This function writes the sorted data to the
 * file "sorted.dat" in the local directory.
 ***********************************************/
void writeToFile(List<Person> sortedList)
{
    ofstream fout;
    fout.open("sorted.dat");
    
    for(ListIterator<Person> it = sortedList.begin(); it != sortedList.end(); it++)
    {
        if(it.p->data.givenName != "")
            fout << it.p->data.givenName;
        if(it.p->data.lastName != "")
        {
            if(it.p->data.givenName != "")
                fout << " " << it.p->data.lastName;
            else
                fout << it.p->data.lastName;
        }
        
        if(it.p->data.birthday != "")
        {
            fout << ", b. " << it.p->data.birthday << endl;
        }
        else
            fout << endl;
    }
    
    fout.close();
}

/***********************************************
 * MAIN : IS LESS
 * This function compares the person objects 
 * based on the parameters given and then returns
 * true or false. This gives an index for the 
 * function PARSE FILE to insert the person.
 ***********************************************/
bool isLess(ListIterator<Person> &it, Person &newPerson)
{
    bool less = false;
    
    if(newPerson.lastName != "" && it.p->data.lastName != "")
    {
        string tempDataLastName;
        string tempPersonLastName;
        
        tempDataLastName = it.p->data.lastName;
        tempPersonLastName = newPerson.lastName;
        
        //Next two for loops take each last name and make them uppercase.
        //This is done for the sake of comparing the last names.
        for (int i = 0; i < tempDataLastName.size(); i++)
            tempDataLastName[i] = toupper(tempDataLastName[i]);
        
        for (int i = 0; i < tempPersonLastName.size(); i++)
            tempPersonLastName[i] = toupper(tempPersonLastName[i]);
        
        if(tempDataLastName < tempPersonLastName)
            less = true;
        
        if(tempDataLastName == tempPersonLastName)
        {
            if(it.p->data.givenName < newPerson.givenName)
                less = true;
            
            if(it.p->data.givenName == newPerson.givenName)
            {
                if(it.p->data.birthYear < newPerson.birthYear)
                    less = true;
            }
        }
    }
    else if(it.p->data.lastName == "" && newPerson.lastName != "")
    {
        less = true;
    }
    else if(it.p->data.lastName != "" && newPerson.lastName == "")
    {
        less = false;
    }
    else if (it.p->data.givenName != "" && newPerson.givenName != "")
    {
        if(it.p->data.givenName < newPerson.givenName)
            less = true;
        if(it.p->data.givenName == newPerson.givenName)
        {
            if(it.p->data.birthYear < newPerson.birthYear)
                less = true;
        }
    }
    
    return less;
}

/***********************************************
 * MAIN : PARSE FILE
 * This function reads the .ged file and looks
 * for the relevant personal information. Once
 * done it calls the functions above and then
 * inserts the person into the list of people.
 ***********************************************/
void parseFile(string lines[], int count)
{
    List<Person> people;
    
    for(int i = 0; i < count; i++)
    {
        if(lines[i][0] == '0' && lines[i][2] == '@' && lines[i][3] == 'I')
        {
            Person newPerson;
            //Get the person's ID.
            string tempCode;
            for(int j = 4; lines[i][j] != '@'; j++)
            {
                tempCode += lines[i][j];
            }
            newPerson.id = atoi(tempCode.c_str());
            
            //Get the person's last name.
            for (int index = 7; index < lines[i+3].length(); index++)
            {
                newPerson.lastName += lines[i+3][index];
            }
            
            //Get the person's first name.
            for (int index = 7; index < lines[i+2].length(); index++)
            {
                newPerson.givenName += lines[i+2][index];
            }
            
            //Get the person's birthday
            int indexBirthday = i;
            while(lines[indexBirthday] != "1 BIRT")
            {
                if (lines[indexBirthday + 1][2] == '@')
                    break;
                
                indexBirthday++;
            }
            
            indexBirthday++;
            if (lines[indexBirthday][2] == 'D')
            {
                for (int l = 7; l < lines[indexBirthday].length(); l++)
                {
                    newPerson.birthday += lines[indexBirthday][l];
                }
                
                for (int m = lines[indexBirthday].length() - 4.0; m < lines[indexBirthday].length(); m++)
                {
                    newPerson.birthYear += lines[indexBirthday][m];
                }
            }
            else
            {
                newPerson.birthday = "";
                newPerson.birthYear = "";
            }
            
            ListIterator<Person> it = people.begin();
            bool less = false;
            if(!people.empty())
            {
                less = isLess(it, newPerson);
                while(it.p != NULL && less)
                {
                    it++;
                    if(it.p != NULL)
                        less = isLess(it, newPerson);
                }
                
                people.insert(it, newPerson);
            }
            else
            {
                people.push_back(newPerson);
            }
            
            it = people.begin();
        }
    }
    
    writeToFile(people);
    setFamilies(people, lines, count);
}

/***********************************************
 * MAIN : MAIN
 * This is the driver function of the program. 
 * It reads in the file given from the command 
 * line and then stores the data. It passes the
 * data to the function PARSE FILE.
 ***********************************************/
int main(int argc, const char * argv[]) {
    
    string lines[7456];
    int count = 0;
    
    ifstream fin(argv[1]);
    
    if(fin.fail())
    {
        cout << "Couldn't open file.\n";
    }
    
    while(getline(fin, lines[count]))
    {
        count++;
    }
    
    fin.close();
    
    parseFile(lines, count);
    
    return 0;
}
