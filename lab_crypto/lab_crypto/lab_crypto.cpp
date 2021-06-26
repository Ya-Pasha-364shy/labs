#include <iostream>
using namespace std;

int power(int a, int b, int m) {
    long int res = 1;
    while (b > 0)
    {
        res = (res * a) % m;
        --b;
    }
    return res % m;
}


class Rsa
{
private:
    // message 
    int message;
    // public keys:
    int n, d;
    // private keys:
    int c, p, q;

public:
    Rsa(int x, int y, int z, int k) : p(x), q(y), n(z), d(k)
    {
        cout << "Data has been set !" << endl;
    }

    void set_c()
    {
        for (int i = 0; i < 10; i++)
        {
            if (i * d % ((p - 1) * (q - 1)) == 1) {
                c = i;
                cout << "c = " << c << endl;
                break;
            }
            else
                continue;
        }
    }

    int send_message(const Rsa& obj, int mes)
    {
        message = mes;
        int result = power(message, obj.d, obj.n);
        return result;
    }

    int decode(const Rsa& obj, int mes)
    {
        return power(mes, obj.c, obj.n);
    }

};

int main()
{
    Rsa alice(5, 7, 35, 5);
    Rsa bob(3, 11, 33, 3);
    alice.set_c();          // 5
    bob.set_c();            // 7    

    // Now we realize a simple dialog with Bob and Alice
    while (true)
    {
        cout << "Enter a message for encoding and send: ";
        int mes;
        cin >> mes; // 15

        int en_mes = alice.send_message(bob, mes);
        cout << "Messge has been send: " << en_mes << endl; // 9

        cout << "You need for decoding this message?\n(yes-1|no-0): ";
        short answer;
        cin >> answer;

        if (answer)
            cout << "This is what was encrypted: " << bob.decode(alice, en_mes) << endl;
        else
        {
            cout << "Bye !" << endl;
            break;
        }
    }

    return 0;
}