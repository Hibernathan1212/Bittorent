//
//  main.cpp
//  Bittorent
//
//  Created by Nathan Thurber on 23/6/24.
//

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>

std::string decode_bencoded_value(const std::string& encoded_value)
{
    //strings (5:hello => hello)
    if (std::isdigit(encoded_value[0])) {
        size_t colon_index = encoded_value.find(':');
        if (colon_index != std::string::npos) {
            std::string number_string = encoded_value.substr(0, colon_index);
            int64_t number = std::atoll(number_string.c_str());
            std::string str = encoded_value.substr(colon_index + 1, number);
            return str;
        } else {
            throw std::runtime_error("Invalid encoded value: " + encoded_value);
        }
    }
    //ints (i52e => 52)
    else if (encoded_value[0] == 'i' && encoded_value[encoded_value.length() - 1] == 'e')
    {
        std::string str = encoded_value.substr(1, encoded_value.size()-2);
        return str.c_str();
    
    }
    //lists
    else if (encoded_value[0] == 'l' && encoded_value[encoded_value.length() - 1] == 'e')
    {
        int counter = 1;
        std::string result;
        result.push_back('[');
        while (counter < encoded_value.length() - 1)
        {
            if (std::isdigit(encoded_value[counter])) 
            {
                size_t colon_index = encoded_value.find(':');
                if (colon_index != std::string::npos)
                {
                    std::string number_string = encoded_value.substr(counter, colon_index);
                    int64_t number = std::atoll(number_string.c_str());
                    std::string str = encoded_value.substr(colon_index + counter, number);
                    for(int i = 0; i < number; i++)
                    {
                        result.push_back(str[i]);
                    }
                    counter += number + 2;
                }
            }
            else if (encoded_value[counter] == 'i')
            {
                for (int i = 1; i < encoded_value.length() -2; i++)
                {
                    if (std::isdigit(encoded_value[counter + i]))
                        result.push_back(encoded_value[counter + i]);
                    else
                    {
                        counter += i+2;
                        break;
                    }
                }

                std::string str = encoded_value.substr(1, encoded_value.size()-2);
                result.push_back(std::atoll(str.c_str()));
            }
            else
            {
                throw std::runtime_error("Invalid encoded value: " + encoded_value);
            }
            if (counter < encoded_value.length() - 2)
            {
                result.push_back(',');
                result.push_back(' ');
            }
        }
        result.push_back(']');
        return result;
    
    }
    else
    {
        throw std::runtime_error("Unhandled encoded value: " + encoded_value);
    }
}

int main(int argc, char* argv[]) {
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    //if (argc < 2) {
    //    std::cerr << "Usage: " << argv[0] << " decode <encoded_value>" << std::endl;
    //    return 1;
    //}

    //std::string command = argv[1];

    std::string command;
    command = "decode";
    
    std::cout << "Encoded data to be decoded:" << std::endl;
    
    
    std::string encoded_value;
    std::cin >> encoded_value;
    
    if (command == "decode") {
        //if (argc < 3) {
        //    std::cerr << "Usage: " << argv[0] << " decode <encoded_value>" << std::endl;
        //    return 1;
        //}
        // You can use print statements as follows for debugging, they'll be visible when running tests.
        // std::cout << "Logs from your program will appear here!" << std::endl;

        //std::string encoded_value = argv[2];
        std::string decoded_value = decode_bencoded_value(encoded_value);
        std::cout << decoded_value << std::endl;
    } 
    else
    {
        std::cerr << "unknown command: " << command << std::endl;
        return 1;
    }

    return 0;
}
