#include <iostream>
#include <string>
using namespace std;

const int MAX_EQUIPMENT = 30;

struct Equipment
{
    string id;
    string category;
    float power;
    float maxTemp;
    int maintenanceInterval;
    float accumulatedHours;
    float hoursUsed;
    float temperature;
    string status;
};

Equipment eq[MAX_EQUIPMENT];
int countEq = 0;

int findEquipment(string id)
{
    for(int i=0;i<countEq;i++)
    {
        if(eq[i].id == id)
        return i;
    }
    return -1;
}

void addEquipment()
{
    if(countEq >= MAX_EQUIPMENT)
    {
        cout<<"Storage Full\n";
        return;
    }

    cout<<"Enter Equipment ID: ";
    cin>>eq[countEq].id;

    cout<<"Enter Equipment Category: ";
    cin>>eq[countEq].category;

    cout<<"Enter Power (Watts): ";
    cin>>eq[countEq].power;

    cout<<"Enter Maximum Safe Temperature: ";
    cin>>eq[countEq].maxTemp;

    cout<<"Enter Maintenance Interval (Hours): ";
    cin>>eq[countEq].maintenanceInterval;

    eq[countEq].accumulatedHours = 0;
    eq[countEq].hoursUsed = 0;
    eq[countEq].temperature = 0;
    eq[countEq].status = "NORMAL";

    countEq++;

    cout<<"Equipment Added Successfully\n";
}

void updateUsage()
{
    string id;
    cout<<"Enter Equipment ID: ";
    cin>>id;

    int index = findEquipment(id);

    if(index == -1)
    {
        cout<<"Equipment Not Found\n";
        return;
    }

    cout<<"Enter Hours Used (0-24): ";
    cin>>eq[index].hoursUsed;

    if(eq[index].hoursUsed < 0 || eq[index].hoursUsed > 24)
    {
        cout<<"Invalid Hours\n";
        return;
    }

    cout<<"Enter Current Temperature: ";
    cin>>eq[index].temperature;

    eq[index].accumulatedHours += eq[index].hoursUsed;

    float maxTemp = eq[index].maxTemp;
    float temp = eq[index].temperature;

    if(temp > maxTemp)
        eq[index].status = "CRITICAL";
    else if(temp >= 0.9 * maxTemp)
        eq[index].status = "WARNING";
    else
        eq[index].status = "NORMAL";

    cout<<"Equipment Status: "<<eq[index].status<<endl;

    if(eq[index].accumulatedHours >= eq[index].maintenanceInterval)
    {
        cout<<"Maintenance Due Alert for Equipment: "<<eq[index].id<<endl;
    }
}

void displayEquipment()
{
    if(countEq == 0)
    {
        cout<<"No Equipment Records\n";
        return;
    }

    for(int i=0;i<countEq;i++)
    {
        float energy = (eq[i].power / 1000) * eq[i].hoursUsed;

        cout<<"\nEquipment ID: "<<eq[i].id<<endl;
        cout<<"Category: "<<eq[i].category<<endl;
        cout<<"Hours Used: "<<eq[i].hoursUsed<<endl;
        cout<<"Temperature: "<<eq[i].temperature<<endl;
        cout<<"Energy Consumption: "<<energy<<" kWh"<<endl;
        cout<<"Status: "<<eq[i].status<<endl;
    }
}

void generateReport()
{
    float totalEnergy = 0;

    for(int i=0;i<countEq;i++)
    {
        float energy = (eq[i].power / 1000) * eq[i].hoursUsed;
        totalEnergy += energy;
    }

    float cost = totalEnergy * 0.50;
    float surcharge = 0;

    if(totalEnergy > 8)
    {
        surcharge = cost * 0.20;
    }

    float finalCost = cost + surcharge;

    cout<<"\nDAILY ENERGY REPORT\n";
    cout<<"Total Energy Consumption: "<<totalEnergy<<" kWh\n";
    cout<<"Electricity Cost: RM"<<cost<<endl;

    if(surcharge > 0)
    {
        cout<<"Surcharge Applied: RM"<<surcharge<<endl;
    }

    cout<<"Final Cost: RM"<<finalCost<<endl;
}

void menu()
{
    cout<<"\nSMART WORKSHOP EQUIPMENT SAFETY MONITORING SYSTEM\n";
    cout<<"1. Add Equipment\n";
    cout<<"2. Update Daily Usage & Temperature\n";
    cout<<"3. Display Equipment Information\n";
    cout<<"4. Generate Energy Report\n";
    cout<<"5. Exit\n";
}

int main()
{
    int choice;

    do
    {
        menu();

        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1:
                addEquipment();
                break;

            case 2:
                updateUsage();
                break;

            case 3:
                displayEquipment();
                break;

            case 4:
                generateReport();
                break;

            case 5:
                cout<<"System Terminated\n";
                break;

            default:
                cout<<"Invalid Choice\n";
        }

    }while(choice != 5);

    return 0;
}