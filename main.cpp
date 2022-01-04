#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;
string Check_File_Open_or_Not(string);
string Chek_Key(string);
string Check_Mode(string mode);

int main(int argc, const char* argv[]) {
    if (argc != 3) {
        cerr << "Error: Use three parameters\n";
        return 1;
    }
    string mode(argv[1]); // Режим работы
    string file_name(argv[2]); // Имя файла
    mode = Check_Mode(mode); //Проверка режима работы
    file_name = Check_File_Open_or_Not(file_name); // проверка пути к файлу
    string line;
    string key;
    if (mode == "encryption") {  //Режим шифрования
        std::ofstream File_recording(file_name, ios_base::out | std::ios::binary);
        cout << "Enter the string you want to encrypt." << endl;
        getline(cin,line); //Ввод строки, которая будет зашифрована
        cout << "Enter the key." << endl;
        cin >> key; //Ввод ключа
        key = Chek_Key(key); //Проверка ключа
        srand(static_cast<unsigned int>(stoi(key)));
        for (int i = 0; i < line.size(); i += 1) {
            unsigned int gamma = rand();
            unsigned int line_gamma = ((static_cast<unsigned int>(line[i])) ^ gamma) & 0xFF;
            unsigned int line_encrypt = ((line_gamma >> 2) & 0xFF) | ((line_gamma << 6) & 0xFF); // Сдвиг с наложением маски
            unsigned char a = line_encrypt;
            File_recording << a;
        }
        File_recording.close();
        cout << "The text was successfully encrypted." << endl;
        cout << endl;
    }
    if (mode == "decryption") { //Режим расшифрования
        std::ifstream File_Reading(file_name, ios_base::in | std::ios::binary);
        getline(File_Reading, line);
        cout << "Enter the key." << endl;
        cin >> key; //Ввод ключа
        key = Chek_Key(key); //Проверка ключа
        srand(static_cast<unsigned int>(stoi(key)));
        for (int i = 0; i < line.size(); i += 1) {
            unsigned int gamma = rand();
            unsigned int symbol = static_cast<unsigned int>(line[i]) & 0xFF;
            unsigned int line_decrypt = ((symbol >> 6) & 0xFF) | ((symbol << 2) & 0xFF); // Сдвиг с наложением маски
            unsigned char a = (line_decrypt ^ gamma) & 0xFF;
            cout << a;
        }
        File_Reading.close();
        cout << endl;
        cout << "The text was successfully decrypted." << endl;
        cout << endl;
    }
    return 0;
}

string Check_File_Open_or_Not(string file_name)
{
    std::ofstream file(file_name, ios_base::app | std::ios::binary);
    while (file.is_open() == 0) {
        cout << "Wrong file path." << endl;
        cout << "Try a different file path." << endl;
        cin >> file_name;
    }
    file.close();
    return file_name;
}

string Check_Mode(string mode)
{
    while (mode != "encryption" and mode != "decryption") { //Проверка режима работы
        cout << "Incorrect operation mode." << endl;
        cout << "Enter (encryption) or (decryption)." << endl;
        cin >> mode;
    }
    return mode;
}

string Chek_Key(string key)
{
    bool flag = true;
    for (char i : key)
    {
        if (!isdigit(i))
        {
            flag = false;
            break;
        }
    }
    while (key.empty() or key.length() > 9 or key[0] == '-' or flag == 0)
    {
        if (key.empty())
            cout << "The key is empty. Enter another one." << endl;
        else if (flag == 0 and key[0] != '-')
            cout << "The entered value is not a number. Enter another one." << endl;
        else if (key.length() > 9 or key[0] == '-')
            cout << "The key length must not be less than 0 and greater than 4 billion. Enter another one." << endl;
        cin >> key;
        flag = true;
        for (char i : key)
        {
            if (!isdigit(i))
            {
                flag = false;
                break;
            }
        }
    }
    return key;
}