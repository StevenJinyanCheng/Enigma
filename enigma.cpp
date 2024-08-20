#include "enigmaenc.cpp"
#include <fstream>
#include <iostream>
#ifdef _WIN32
#define Xpause system("pause")
#else
#define Xpause system("read -p \"Press any key to continue...\" -n 1")
#endif

int main(int argc, const char *argv[]) {
    // Example rotor settings, reflector, and plugboard settings (all in lowercase)
    std::vector<std::string> rotors = {
        "ekmflgdqvzntowyhxuspaibrcj", // Rotor I
        "ajdksiruxblhwtmcqgznpyfvoe", // Rotor II
        "bdfhjlcprtxvznyeiwgakmusqo"  // Rotor III
    };
    std::string reflector = "yruhqsldpxngokmiebfzcwvjat"; // Reflector B

    // Full plugboard settings with 13 pairs (all in lowercase)
    std::map<char, char> plugboard = {
        {'a', 'z'}, {'z', 'a'},
        {'b', 't'}, {'t', 'b'},
        {'c', 'l'}, {'l', 'c'},
        {'d', 'm'}, {'m', 'd'},
        {'e', 'w'}, {'w', 'e'},
        {'f', 'v'}, {'v', 'f'},
        {'g', 'k'}, {'k', 'g'},
        {'h', 'n'}, {'n', 'h'},
        {'i', 'o'}, {'o', 'i'},
        {'j', 'p'}, {'p', 'j'},
        {'q', 'r'}, {'r', 'q'},
        {'s', 'u'}, {'u', 's'},
        {'x', 'y'}, {'y', 'x'}
    };

    Enigma enigma(rotors, reflector, plugboard);

    std::string message;
    
    if(argc == 2) {
        // If a file path is provided, read the message from the file
        std::ifstream infile(argv[1]);
        if (!infile) {
            std::cerr << "Error opening file: " << argv[1] << std::endl;
            return 1;
        }
        std::getline(infile, message, '\0'); // Read the entire file content
        infile.close();

        // Encrypt the message
        std::string encrypted_message = enigma.encrypt_message(message);

        // Write the encrypted message back to the file
        std::ofstream outfile(argv[1]);
        if (!outfile) {
            std::cerr << "Error opening file for writing: " << argv[1] << std::endl;
            return 1;
        }
        outfile << encrypted_message;
        outfile.close();

        std::cout << "Message encrypted and saved to " << argv[1] << std::endl;
    } else {
        // Otherwise, read the message from the console
        std::cout << "Enter your message: ";
        std::getline(std::cin, message);
        
        // Encrypt the message
        std::string encrypted_message = enigma.encrypt_message(message);

        // Display the original and encrypted message
        std::cout << "Original Message: " << message << std::endl;
        std::cout << "Encrypted Message: " << encrypted_message << std::endl;
        Xpause;
    }

    return 0;
}
