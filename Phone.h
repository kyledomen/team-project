// Phone base class
//
// Modified by: Maksym Sagadin

#ifndef PHONE_H
#define PHONE_H
#include <cctype>
#include <string>

#include <iostream> //delete this later

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

    //Other Functions
    bool operator < (const Phone &right) //Overload < operator
    {
        bool status;

        string a = modelNo;
        string b = right.modelNo;
        a[0] = toupper(a[0]);
        b[0] = toupper(b[0]);
//        cout << "\t*** " << a << endl << b << endl;
        if (a < b)
//        if (modelNo < right.modelNo)
            status = true;
        else
            status = false;

        return status;
    }

    bool operator > (const Phone &right) //Overload > operator
    {
        bool status;

        string a = model;
        string b = right.model;
        a[0] = toupper(a[0]);
        b[0] = toupper(b[0]);
        if (a > b)
            status = true;
        else
            status = false;

        return status;
    }

    bool operator == (const Phone &right) //Overload == operator
    {
        /*
        bool status;
        if (modelNo == right.modelNo)
            status = true;
        else
            status = false;

        return status;*/
        //std::cout << "yuh";
        //std::cout << modelNo << "  " << right.modelNo << "\n";
        return (modelNo == right.modelNo);
        //return (modelNo.compare(right.modelNo) == 0);
    }

    friend ostream &operator << (ostream &str, const Phone &obj)
    {
        str << "Model Number: " << obj.modelNo << endl
        << "Model: " << obj.model << endl
        << "Brand: " << obj.brand << endl
        << "Storage Capacity: " << obj.storage << endl
        << "Price: "<< obj.price << endl << endl;

        return str;
    }

};

#endif
