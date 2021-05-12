#include "hash_library.hpp"


int myhash::Hash::reciveASCII(int x)
{
    while (!(((x <= 57) && (x >= 48)) || ((x <= 90) && (x >= 65)) || ((x <= 122) && (x >= 97))))
    {
        if (x < 48)
            x += 24;
        else
            x -= 47;
    }

    return x;
}

std::string myhash::Hash::hash_fun(std::string& in_data)
{
    std::string hash = "";
    unsigned long temp_hash = 0;
    size_t in_size = in_data.size();
    
    for (size_t i = 0; i != in_size; ++i) 
    {
        temp_hash  = static_cast<int>(in_data[i]) + (temp_hash << 6) + (temp_hash << 16) - temp_hash;
        hash += reciveASCII(temp_hash % 31);
    }

    return hash;
}

void myhash::Hash::resize_pow2(std::string& in_data, size_t& hash_size)
{
    size_t size_in_pow2 = in_data.size();
    
    double lg_hash = log(hash_size) / log(2.0);
    double lg_in = log(size_in_pow2) / log(2.0);

    if (lg_hash - static_cast<int>(lg_hash) != 0)
        hash_size = (1 << (static_cast<int>(lg_hash) + 1));

    if (lg_in - static_cast<int>(lg_in) != 0)
        size_in_pow2 = (1 << (static_cast<int>(lg_in) + 1));

    if (size_in_pow2 < hash_size)
        size_in_pow2 = hash_size;

    size_t len_resize = size_in_pow2 - in_data.size();

    for (size_t i = 0; i != len_resize; ++i) 
        in_data += reciveASCII(in_data[i] + in_data[i + 1]);
}

void myhash::Hash::compress(std::string& in_data)
{
    size_t mid = in_data.size() / 2;
    size_t end = in_data.size() - 1;

    std::string temp = "";

    for(size_t i = 0; i != mid; ++i)
    {
        temp += reciveASCII(in_data[i] + in_data[end - i]);
    }

    in_data = temp;
}

void myhash::Hash::total_Compress(std::string& hash, size_t hash_size)
{
    size_t ost_len = hash.size() - hash_size;
    ost_len += ost_len == 0 ? 1 : 0;
    
    size_t size_comp = hash.size() / ost_len;
    std::string af_comp = "";

    for (int comp = 0; af_comp.size() < hash_size - 1; ++comp)
    {
        if (comp % size_comp == 0)
            af_comp += reciveASCII(hash[comp] + hash[comp + 1]);
        else
            af_comp += hash[comp];
    }
    hash = af_comp;
}

int myhash::Hash::genSalt(std::string& in_data)
{
    int sum = 0;

    for_each(in_data.begin(), in_data.end(), [&sum](char c)
        {
            sum += static_cast<int>(c);
        });

    return sum;
}

std::string myhash::Hash::encode(std::string in_data, size_t hash_size )
{
    if (hash_size > 3 && in_data.size() >= 2 && in_data.size() < 100) 
    {
        size_t hash_size_pow2 = hash_size;
        std::string in_data_pow2 = in_data;

        int salt = genSalt(in_data);
        
        resize_pow2(in_data_pow2, hash_size_pow2);
        
        std::string af_hash = hash_fun(in_data_pow2);

        while (af_hash.size() != hash_size_pow2)
            compress(af_hash);
        
        total_Compress(af_hash, hash_size);

        af_hash += reciveASCII(salt);

        hash_table[af_hash] = in_data;

        return af_hash;
    }

    return "";
}

std::string myhash::Hash::decode(std::string in_hash)
{
    auto res = hash_table.find(in_hash);

    return res == hash_table.end() ? "" : res->second;
}