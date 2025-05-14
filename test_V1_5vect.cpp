// test_student.cpp

#include <gtest/gtest.h>
#include "V1.5vect.h"

// Test default constructor
TEST(StudentTest, DefaultConstructor) {
    Student s;
    EXPECT_EQ(s.getName(), "");
    EXPECT_EQ(s.getSurn(), "");
    EXPECT_EQ(s.getEgz(), 0);
    EXPECT_EQ(s.getVid(), 0);
    EXPECT_TRUE(s.getNd().empty());
}

// Test setters and getters
TEST(StudentTest, SettersAndGetters) {
    Student s;
    std::string name = "Jonas";
    std::string surn = "Jonaitis";
    std::vector<int> nd = {9, 8, 7};

    s.setName(name);
    s.setSurn(surn);
    s.setEgz(10);
    s.setNd(nd);
    s.setVid(9.0);

    EXPECT_EQ(s.getName(), "Jonas");
    EXPECT_EQ(s.getSurn(), "Jonaitis");
    EXPECT_EQ(s.getEgz(), 10);
    EXPECT_EQ(s.getVid(), 9.0);
    EXPECT_EQ(s.getNd(), nd);
}

// Test copy constructor
TEST(StudentTest, CopyConstructor) {
    Student s1;
    s1.setName(std::string("Jonas"));
    s1.setSurn(std::string("Jonaitis"));
    s1.setEgz(9);
    s1.setNd(std::vector<int>{8, 7});
    s1.setVid(8.5);

    Student s2(s1);

    EXPECT_EQ(s2.getName(), s1.getName());
    EXPECT_EQ(s2.getSurn(), s1.getSurn());
    EXPECT_EQ(s2.getEgz(), s1.getEgz());
    EXPECT_EQ(s2.getNd(), s1.getNd());
    EXPECT_EQ(s2.getVid(), s1.getVid());
}

// Test move constructor
TEST(StudentTest, MoveConstructor) {
    Student s1;
    s1.setName(std::string("Jonas"));
    s1.setSurn(std::string("Jonaitis"));
    s1.setEgz(9);
    s1.setNd(std::vector<int>{10, 9});
    s1.setVid(9.1);

    Student s2(std::move(s1));

    EXPECT_EQ(s2.getName(), "Jonas");
    EXPECT_EQ(s2.getSurn(), "Jonaitis");
    EXPECT_EQ(s2.getEgz(), 9);
    EXPECT_EQ(s2.getNd(), std::vector<int>({10, 9}));
    EXPECT_EQ(s2.getVid(), 9.1);
}

// Test assignment operator
TEST(StudentTest, AssignmentOperator) {
    Student s1;
    s1.setName(std::string("Jonas"));
    s1.setSurn(std::string("Jonaitis"));
    s1.setEgz(10);
    s1.setNd(std::vector<int>{6, 7});
    s1.setVid(7.6);

    Student s2;
    s2 = s1;

    EXPECT_EQ(s2.getName(), "Jonas");
    EXPECT_EQ(s2.getSurn(), "Jonaitis");
    EXPECT_EQ(s2.getEgz(), 10);
    EXPECT_EQ(s2.getNd(), std::vector<int>({6, 7}));
    EXPECT_EQ(s2.getVid(), 7.6);
}
