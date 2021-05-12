#include <gtest/gtest.h>
#include "hash_library.hpp"
#include <iostream>

TEST(myhash_test, test_for_encode_decode)
{
    myhash::Hash hash;

    std::string f_site = "https://github.com/headikk";
    std::string s_site = "https://github.com/headikk/task2.7";
    std::string t_site = "https://github.com/headikk/task2.1";
    std::string fo_site = "https://github.com/headikk/task2.2";
    std::string fi_site = "https://github.com/headikk/task2.3";

    std::string f_hash = hash.encode(f_site, 4);
    std::string s_hash = hash.encode(s_site, 5);
    std::string t_hash = hash.encode(t_site, 6);
    std::string fo_hash = hash.encode(fo_site, 7);
    std::string fi_hash = hash.encode(fi_site, 4);

    std::string f_res = hash.decode(f_hash);
    std::string s_res = hash.decode(s_hash);
    std::string t_res = hash.decode(t_hash);
    std::string fo_res = hash.decode(fo_hash);
    std::string fi_res = hash.decode(fi_hash);

    ASSERT_EQ(f_hash.size(), 4);
    ASSERT_EQ(s_hash.size(), 5);
    ASSERT_EQ(t_hash.size(), 6);
    ASSERT_EQ(fo_hash.size(), 7);
    ASSERT_EQ(fi_hash.size(), 4);

    ASSERT_EQ(f_site, f_res);
    ASSERT_EQ(s_site, s_res);
    ASSERT_EQ(t_site, t_res);
    ASSERT_EQ(fo_site, fo_res);
    ASSERT_EQ(fi_site, fi_res);
}

TEST(myhash_test, test_for_many_almost_the_same_elements_for_not_same_hash)
{
    myhash::Hash hash;

    std::vector<std::string> sites = {{"https://github.com/headikw"}, {"https://github.com/headikq"}, {"https://github.com/headike"}, 
    {"https://github.com/headikk"}, {"https://github.com/headikr"}, {"https://github.com/headikt"}, {"https://github.com/headiky"}, 
    {"https://github.com/headiks"},{"https://github.com/headiku"}, {"https://github.com/headiko"}, {"https://github.com/headikp"}, 
    {"https://github.com/headika"}, {"https://github.com/headikd"}, {"https://github.com/headikf"}, {"https://github.com/headikg"},
    {"https://github.com/headikh"}, {"https://github.com/headikj"}, {"https://github.com/headikz"}, {"https://github.com/headikl"} };

    for(auto& element : sites)
    {
        element = hash.encode(element, 5);        
    }

    for(size_t i = 0; i != sites.size(); ++i)
    {
        for(size_t j = 0; j != sites.size(); ++j)
        {
            if(i == j)
                continue;

            ASSERT_NE(sites[i], sites[j]);
        }
    }
    

}

TEST(myhash_test, test_for_no_equal_elemnt_in_hash_table)
{
    myhash::Hash hash;

    std::string f_site = "https://github.com/headikk";
    std::string s_site = "https://github.com/headikk/task2.7";

    std::string f_hash = hash.encode(f_site, 4);
    std::string s_hash = hash.encode(s_site, 5);

    ASSERT_EQ(hash.decode("Hellow"), "");   
}

TEST(myhash_test, test_for_empty_hash_table)
{
    myhash::Hash hash;



    ASSERT_EQ(hash.decode("Hellow"), "");   
}

TEST(myhash_test, test_for_almost_the_same_elements)
{
    myhash::Hash hash;

    std::string f_site = "aaaaaaaaaa";
    std::string s_site = "aaaaaaaaab";

    std::string f_hash = hash.encode(f_site, 5);
    std::string s_hash = hash.encode(s_site, 5);

    ASSERT_NE(f_hash, s_hash);   
}

TEST(myhash_test, test_for_the_same_elements)
{
    myhash::Hash hash;

    std::string f_site = "https://github.com/headikk";
    std::string s_site = "https://github.com/headikk";

    std::string f_hash = hash.encode(f_site, 5);
    std::string s_hash = hash.encode(s_site, 5);

    ASSERT_EQ(f_hash, s_hash);   
}

TEST(myhash_test, test_for_super_short_elements)
{
    myhash::Hash hash;

    std::string f_site = "h";

    std::string f_hash = hash.encode(f_site, 5);

    ASSERT_EQ(f_hash, "");   
}

TEST(myhash_test, test_for_super_long_elements_more_than_a_hundred)
{
    myhash::Hash hash;

    std::string f_site = "qdhyekfharenvkfoaudkvmdhftresgvkfjcdjfhvgdkdoeigmvnghdugjvkdlepoiqmflvmczxlfmslfmw;eearmra;mrf;amf;amgfhdisfkdn";

    std::string f_hash = hash.encode(f_site, 5);

    ASSERT_EQ(f_hash, "");   
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}