#include <iostream>
#include <exception>
#include <unordered_map>
using namespace std;

class myexception
{
public:
    const char *what() const throw()
    {
        return "INSUFFICIENT BALANCE REQUEST NOT COMPLEATED";
    }
};

class Bank
{
private:
    int userID;
    int password;
    float balance;
    int accNO;

public:
    void createACC()
    {
        cout << "ENTER USER ID : ";
        cin >> userID;

        cout << "ENTER PASSWORD : ";
        cin >> password;

        cout << "CONFIRM PASSWORD : ";
        int confirm;
        cin >> confirm;

        if (confirm == password)
        {
            cout << "INITIALISE BALANCE : ";
            cin >> balance;
            cout << "ENTER ACC NO : ";
            cin >> accNO;
            cout << "ACCOUNT CREATED" << endl;
        }
        else
        {
            cout << "PASSWORD DOES NOT MATCH" << endl;
        }
    }

    int getUserID()
    {
        return this->accNO;
    }

    float getBalance()
    {
        return this->balance;
    }

    void login(unordered_map<int, Bank> &users)
    {
        int ID;
        int pass;
        cout << "CONFORM USER ID : ";
        cin >>ID;

        cout << "ENTER PASSWORD : ";
        cin >> pass;

        if (ID == this->accNO && pass == this->password)
        {
            cout << "LOGIN SUCCESSFUL \n";
            int choice = 0;
            while (choice != 4)
            {
                cout << "1. CHECK BALANCE , 2. TRANSFER MONEY , 3. ADD MONEY , 4. EXIT \n";
                cin >> choice;
                switch (choice)
                {
                case 1:
                    cout << "YOUR CURRENT BALANCE IS : " << this->balance << endl;
                    break;
                case 2:
                    cout << "ENTER RECIVER ACCOUNT NUMBER : ";
                    int reciverid;
                    cin >> reciverid;

                    if (users.find(reciverid) != users.end())
                    {
                        cout << "ENTER AMOUNT TO TRANSFER : ";
                        float amount;
                        cin >> amount;

                        try
                        {
                            if (amount <= this->balance)
                            {
                                this->balance -= amount;
                                users[reciverid].balance += amount;
                                cout << "TRANSACTION SUCCESSFUL \n";
                            }
                            else
                            {
                                myexception e;
                                throw e;
                            }
                        }
                        catch (myexception &e)
                        {
                            cout << e.what() << endl;
                        }
                    }
                    else
                    {
                        cout << "RECIPIENT ACCOUNT NOT FOUND \n";
                    }
                    break;
                case 3:
                    cout << "ENTER AMOUNT TO ADD : ";
                    float add;
                    cin >> add;
                    this->balance += add;
                    cout << "TRANSACTION ADD SUCCESSFUL \n";
                    break;
                case 4:
                    cout << "EXITING ... \n";
                    break;
                default:
                    cout << "INVALID OPTION" << endl;
                }
            }
        }
        else
        {
            cout << "INVALID USER ID OR PASSWORD \n";
        }
    }
};

int main()
{
    unordered_map<int, Bank> users;
    int choice;
    while (1)
    {
        cout << "1. CREATE ACCOUNT , 2. LOGIN , 3. EXIT \n";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            Bank account;
            account.createACC();
            // map se account kai object and id ko jor do
            // GIVES ACC NO
            users[account.getUserID()] = account; // CHANGE IT TO USER ACCOUNT NUMBER
            break;
        }
        case 2:
        {
            // user map se verify
            int loginID;
            cout << "ENTER ACCOUNT NUMBER : ";
            cin >> loginID;

            if (users.find(loginID) != users.end())
            {
                users[loginID].login(users);
            }
            else
            {
                cout << "ACCOUNT NOT FOUND \n";
            }
            break;
        }
        case 3:
            cout << "EXITING" << endl;
            return 0;
        default:
            cout << "INVALID OPTION" << endl;
        }
    }
}
