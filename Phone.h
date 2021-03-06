// Phone base class
//
// Modified by: Maksym Sagadin

#ifndef PHONE_H
#define PHONE_H
#include <cctype>
#include <string>

using namespace std;


class Phone; //Forward Declaration
ostream &operator << (ostream &, const Phone &);

class Phone
{
    private:
    string modelNo;
    string model;
    string brand;
    int storage;
    double price;

    public:
    Phone() //Default Constructor
    {
        modelNo = "";
        model = " ";
        brand = "";
        storage = 0;
        price = 0;
    }

    Phone (string m) {
        modelNo = m;
        model = "";
        brand = "";
        storage = 0;
        price = 0;
    }

    Phone (string m, string n, string b, int s, double p) //Overload Constructor
    {
        modelNo = m;
        model = n;
        brand = b;
        storage = s;
        price = p;
    }

    //Setters
    void setModelNo(string m) {modelNo = m;}
    void setModel(string n) {model = n;}
    void setBrand(string b) {brand = b;}
    void setStorage(int s) {storage = s;}
    void setPrice(double p) {price = p;}

    //Getters
    string getModelNo() const {return modelNo;}
    string getModel() const {return model;}
    string getBrand() const {return brand;}
    int getStorage() const {return storage;}
    double getPrice() const {return price;}

    friend ostream &operator << (ostream &str, const Phone &obj)
    {
        str << "Model Number: " << obj.modelNo << endl
        << "Model: " << obj.model << endl
        << "Brand: " << obj.brand << endl
        << "Storage Capacity: " << obj.storage << " GB" << endl
        << "Price: $"<< obj.price << endl << endl;

        return str;
    }

};

#endif
