#include "encryption.hpp"

int main (int argc, char* argv[]) {
    srand(time(NULL));


    string input_file = argv[1];
    string output_file = argv[3];
    
    switch (*argv[2])
    {
    case '1':
        cout << "Shamir" << endl;
        Shamir_code(input_file);
        Shamir_decode("code.txt", "key.txt", output_file);
        break;
    case '2':
        cout << "ElGamal" << endl;
        El_Gamala_coding(input_file);
        El_Gamala_decoding("code.txt", "key.txt", output_file);
        break;
    case '3':
        cout << "Vernam" << endl;
        Vernam_coding(input_file);
        Vernam_decoding("code.txt", "key.txt", output_file);
        break;
    case '4':
        cout << "RSA" << endl;
        RSA_coding(input_file);
        RSA_decoding("code.txt", "key.txt", output_file);
    default:
        break;
    }

    return 0;
}