#include <iostream>
#include <string>
#include "HashMap.h"

using namespace std;

int main ()
{
    HashMap<string, float> map;
    map.insert("1", 1.2);
    map.insert("33", 22.1);
    map.insert("23", 33.3);
    map.insert("44", 44.1);
    map.insert("pp", 44.1);
    map.insert("kkkarla", 66);
    map.insert("chichistosa", 69.69);
    map.insert("fornillo", 101.101);
    map.insert("La verdad me viene valiendo kk como la bes", 99);
    map.insert("La mera verdad me viene valiendo kaka pinche Andres Angeloid Humbertoide Alatawer no funca", 666.666);
    map.delete_value("pp");
    /*
    map.deleteValue("1");
    map.deleteValue("33");
    map.deleteValue("23");
    map.deleteValue("44");
    map.deleteValue("kkkarla");
    map.deleteValue("chichistosa");
    map.deleteValue("fornillo");
    map.deleteValue("La verdad me viene valiendo kk como la bes");
    map.deleteValue("La mera verdad me viene valiendo kaka pinche Andres Angeloid Humbertoide Alatawer no funca");
    */
    cout << *map["1"] << endl;
    cout << *map["33"] << endl;
    cout << *map["23"] << endl;
    cout << *map["44"] << endl;
    if (map["pp"] == nullptr)
        cout << "no existe" << endl;
    else
        cout << *map["pp"] << endl;
    cout << *map["kkkarla"] << endl;
    cout << *map["chichistosa"] << endl;
    cout << *map["fornillo"] << endl;
    cout << *map["La verdad me viene valiendo kk como la bes"] << endl;
    cout << *map["La mera verdad me viene valiendo kaka pinche Andres Angeloid Humbertoide Alatawer no funca"] << endl;
    cout << "Tamaño: " << map.size() << endl;
    cout << "Haciendo clear()" << endl;
    map.clear();
    cout << "Tamaño: " << map.size() << endl;

   /*
    for (size_t i = 0; i < map.getBucket().size(); ++i){
        cout << "hash: " << map.getBucket()[i].getHashValue() << endl;
        for (size_t j = 0; j < map.getBucket()[i].getValues().size(); ++j){
            cout << "   key: " << map.getBucket()[i].getValues()[j].getKey() << " | value: " << *map.getBucket()[i].getValues()[j].getValue() << endl;
        }
    }
    */

    return 0;
}
