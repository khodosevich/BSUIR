#include <iostream>
#include "computer.h"
#include "Portable.h"
#include "Laptop.h"
#include "Tablet.h"
#include "Desktop.h"
#include "Monoblock.h"
using namespace std;


int main() {
   
    Computer lenovo;
    
    lenovo.setBrand("Lenovo");
    lenovo.setModel("legion");

    Portable macbook;
    
    macbook.setBrand("Apple");
    macbook.setModel("M1");
    macbook.setScreen(13);
    macbook.setCharge(100);
    
    Laptop honor;
    
    honor.setBrand("Honor");
    honor.setModel("Vivo");
    honor.setScreen(15);
    honor.setCharge(88);
    honor.SetKeyboard(50);
    
    
    Tablet pc;
    pc.setBrand("Honor");
    pc.setModel("Ultra");
    pc.setScreen(14);
    pc.setCharge(97);
    pc.SetTablet("3g");
    
    
    Desktop asus;
    
    asus.setBrand("Asus");
    asus.setModel("VivoBook");
    asus.SetCorpus("plastic");

    
    Monoblock monoPC;
    
    monoPC.setBrand("Samdung");
    monoPC.setModel("NotePad");
    monoPC.SetScreen(13.5);
    monoPC.SetCorpus("metall");
    
    cout << "========================================================================="<< endl << endl;
    cout << "|Class computer\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|" << endl;
    cout << "|Brand: " << lenovo.getBrand() << "\t" <<"Model: "<< lenovo.getModel() <<"\t\t\t\t\t\t\t\t\t\t\t|" <<endl << endl;
    cout << "========================================================================="<< endl << endl;
    
    cout << "|Class portable\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|" << endl;
    cout << "|Brand: " << macbook.getBrand() << "\t" <<"Model: "<< macbook.getModel()<<"\tCharge: "<<macbook.getCharge() <<"\tScreen: " << macbook.getScreen() <<"\t\t\t\t\t\t|" <<endl << endl;
    cout << "========================================================================="<< endl << endl;
    
   
    
    cout << "|Class Laptop \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|" << endl;
    cout << "|Brand: " << honor.getBrand() << "\t" <<"Model: "<< honor.getModel()<<"\tCharge: "<<honor.getCharge() <<"\tScreen: " << honor.getScreen() <<"\tKeyboard: "<< honor.GetKeyboard() <<"\t\t|" <<endl << endl;
    cout << "========================================================================="<< endl << endl;
    
    
    cout << "|Class Tablet \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|" << endl;
    cout << "|Brand: " << pc.getBrand() << "\t" <<"Model: "<< pc.getModel()<<"\tCharge: "<<pc.getCharge() <<"\tScreen: " << pc.getScreen() <<"\tModem: "<< pc.GetTablet() <<"\t\t|" <<endl << endl;
    cout << "========================================================================="<< endl << endl;
    
    
    cout << "|Class Desktop\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|" << endl;
    cout << "|Brand: " << asus.getBrand() << "\t" <<"Model: "<< asus.getModel()<<"\t\tCorpus: "<<asus.GetCorpus()<< "\t\t\t\t\t\t|" <<endl << endl;
    cout << "========================================================================="<< endl << endl;
    
    cout << "|Class Monoblock\t\t\t\t\t\t\t\t\t\t\t\t\t\t|" << endl;
    cout << "|Brand: " << monoPC.getBrand() << "\t" <<"Model: "<< monoPC.getModel()<<"\tCorpus: "<<monoPC.GetCorpus()<<"\tScreen: "<<
    monoPC.GetSceen()<< "\t\t\t\t|" <<endl << endl;
    cout << "=========================================================================" << endl << endl;
    return 0;
}
