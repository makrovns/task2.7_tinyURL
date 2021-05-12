#pragma once
#include <map>
#include <string>
#include <algorithm>
#include <cmath>

namespace myhash
{
    class Hash
    {
    public:

        Hash() = default;
        
        std::string encode(std::string in_data, size_t hash_size);
        std::string decode(std::string);
    
    private:

        int genSalt(std::string& in_data);
        
        void resize_pow2(std::string& in_data, size_t& hash_size);
        void compress(std::string& in_data);
        void total_Compress(std::string& hash, size_t hash_size);
        
        std::string hash_fun(std::string& in_data);
        int reciveASCII(int x);
        
        std::map<std::string, std::string> hash_table;
    };
}