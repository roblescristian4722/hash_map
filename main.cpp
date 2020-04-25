#include <iostream>
#include <string>
#include "hash_map.h"

using namespace std;

int main ()
{
    HashMap<string, float> map;
    map.insert("1", 1.5);
    map.insert("33", 22.1);
    map.insert("23", 33.3);
    map.insert("44", 44.1);
    map.insert("pp", 44.1);
    map.insert("kkkarla", 66);
    map.insert("chichistosa", 69.69);
    map.insert("fornillo", 101.101);
    map.insert("La verdad me viene valiendo kk como la bes", 99);
    map.insert("La mera verdad me viene valiendo kaka pinche Andres Angeloid Humbertoide Alatawer no funca", 666.666);
    map.delete_value("1");
    map.delete_value("pp");
    /*
    map.delete_value("33");
    map.delete_value("1");
    map.delete_value("23");
    map.delete_value("44");
    map.delete_value("kkkarla");
    map.delete_value("chichistosa");
    map.delete_value("fornillo");
    map.delete_value("La verdad me viene valiendo kk como la bes");
    map.delete_value("La mera verdad me viene valiendo kaka pinche Andres Angeloid Humbertoide Alatawer no funca");
    */
   cout << "size: " << map.size() << endl;
    if (map["1"] == nullptr)
        cout << "1 no existe" << endl;
    else
        cout << *map["1"] << endl;
    *map["33"] = 33;
    cout << *map["33"] << endl;
    cout << *map["23"] << endl;
    cout << *map["44"] << endl;
    if (map["pp"] == nullptr)
        cout << "pp no existe" << endl;
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

    return 0;
}
