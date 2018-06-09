/* Translate sha1 test from https://github.com/vog/sha1/blob/master/test_sha1.cpp
 * to google test.
 */

#include "gtest/gtest.h"

#include <string>

#include "sha1.hpp"

/*
 * The 3 test vectors from FIPS PUB 180-1
 */
TEST(sha1_test, standard)
{
    // https://www.di-mgt.com.au/sha_testvectors.html
    // https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHA1.pdf

    SHA1 checksum;

    checksum.update("abc");
    EXPECT_EQ(checksum.final(), std::string("a9993e364706816aba3e25717850c26c9cd0d89d"));

    checksum.update("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
    EXPECT_EQ(checksum.final(), std::string("84983e441c3bd26ebaae4aa1f95129e5e54670f1"));

    checksum.update("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu");
    EXPECT_EQ(checksum.final(), std::string("a49b2446a02c645bf419f995b67091253a04a259"));

    for (int i = 0; i < 1000000/200; ++i)
    {
        checksum.update("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
                        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
                        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
                        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
                       );
    }
    EXPECT_EQ(checksum.final(), std::string("34aa973cd4c4daa4f61eeb2bdbad27316534016f"));

    // https://en.wikipedia.org/wiki/SHA-1
    checksum.update("The quick brown fox jumps over the lazy dog");
    EXPECT_EQ(checksum.final(), std::string("2fd4e1c67a2d28fced849ee1bb76e7391b93eb12"));

    checksum.update("The quick brown fox jumps over the lazy cog");
    EXPECT_EQ(checksum.final(), std::string("de9f2c7fd25e1b3afad3e85a0bd17d9b100db4b3"));
}


TEST(sha1_test, slow)
{
    // https://www.di-mgt.com.au/sha_testvectors.html
    SHA1 checksum;
    for (int i = 0; i < 16777216; ++i)
    {
        checksum.update("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno");
    }
    EXPECT_EQ(checksum.final(), std::string("7789f0c9ef7bfc40d93311143dfbe69e2017f592"));
}

TEST(sha1_test, other)
{
    SHA1 checksum;

    EXPECT_EQ(checksum.final(), std::string("da39a3ee5e6b4b0d3255bfef95601890afd80709"));

    checksum.update("");
    EXPECT_EQ(checksum.final(), std::string("da39a3ee5e6b4b0d3255bfef95601890afd80709"));

    checksum.update("abcde");
    EXPECT_EQ(checksum.final(), std::string("03de6c570bfe24bfc328ccd7ca46b76eadaf4334"));

    checksum.update("The quick brown fox jumps over the lazy cog");
    EXPECT_EQ(checksum.final(), std::string("de9f2c7fd25e1b3afad3e85a0bd17d9b100db4b3"));

    SHA1 checksum1, checksum2;
    checksum1.update("abc");
    EXPECT_EQ(checksum2.final(), std::string("da39a3ee5e6b4b0d3255bfef95601890afd80709"));
    EXPECT_EQ(checksum1.final(), std::string("a9993e364706816aba3e25717850c26c9cd0d89d"));
}

