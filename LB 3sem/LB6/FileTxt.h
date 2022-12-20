#ifndef LB6_FILETXT_H
#define LB6_FILETXT_H

#include "File.h"
#include <iostream>
#include <fstream>
#include "MyContainer.h"

class FileTxt{

public:
    void WriteToTxtFile( List<Person> &person){

        string Path = "File.txt";

        fstream out(Path,   ios::out | ios::app);


        if (out.is_open())
        {
            for (int i = 0; i < person.getSize(); i++)
            {
                out << person[i];
            }
        }
        else
            out.close();


    }


    void ShowTxtFile(){

        string Path = "File.txt";

        ifstream fin;

        List<Person> person;

        Person x;

        fin.open(Path);

        if(fin.is_open()){

            while (!fin.eof()){

                fin >> x;
                person.push_back(x);

            }

        }

        fin.close();


        for (int i = 0; i < person.getSize(); ++i) {

            person[i].PrintPerson();

        }


    }


};

#endif //LB6_FILETXT_H
