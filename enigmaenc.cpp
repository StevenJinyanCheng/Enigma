#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

class Enigma {
private:
    std::vector<std::string> rotors;
    std::string reflector;
    std::map<char, char> plugboard;
    std::vector<int> rotor_positions;

    void rotate_rotors() {
        rotor_positions[0] = (rotor_positions[0] + 1) % 26;
        if (rotor_positions[0] == 0) {
            rotor_positions[1] = (rotor_positions[1] + 1) % 26;
            if (rotor_positions[1] == 0) {
                rotor_positions[2] = (rotor_positions[2] + 1) % 26;
            }
        }
    }

    char encrypt_character(char c) {
        rotate_rotors();

        // Pass through the plugboard
        if (plugboard.find(c) != plugboard.end()) {
            c = plugboard[c];
        }

        // Forward through the rotors
        for (int i = 0; i < 3; ++i) {
            int offset = (c - 'a' + rotor_positions[i]) % 26;
            c = rotors[i][offset];
            c = (c - 'a' - rotor_positions[i] + 26) % 26 + 'a';
        }

        // Pass through the reflector
        c = reflector[c - 'a'];

        // Backward through the rotors
        for (int i = 2; i >= 0; --i) {
            c = (c - 'a' + rotor_positions[i] + 26) % 26 + 'a';
            auto pos = rotors[i].find(c);
            c = (pos - rotor_positions[i] + 26) % 26 + 'a';
        }

        // Pass through the plugboard again
        if (plugboard.find(c) != plugboard.end()) {
            c = plugboard[c];
        }

        return c;
    }

public:
    Enigma(const std::vector<std::string>& rotor_settings, const std::string& reflector_setting, const std::map<char, char>& plugboard_settings)
        : rotors(rotor_settings), reflector(reflector_setting), plugboard(plugboard_settings), rotor_positions(3, 0) {}

    std::string encrypt_message(const std::string& message) {
        std::string encrypted_message;
        for (char c : message) {
            if (isalpha(c)) {
                c = tolower(c);
                encrypted_message += encrypt_character(c);
            } else {
                encrypted_message += c; // Preserve non-alphabetic characters
            }
        }
        return encrypted_message;
    }
};
