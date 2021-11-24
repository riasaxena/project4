#include "gtest/gtest.h"
#include "MyAVLTree.hpp"
#include "proj4.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <fstream>


namespace{


// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.

// The four tests marked "CheckPoint" are going to be run
// on your submission for the checkpoint code.
// This is worth one-sixth of your grade on the assignment
// and is due at the time marked "checkpoint"


// None of the "checkpoint" tests require you to have
// AVL functionality OR the counting of words.
// Implementing your tree as a plain binary search
// tree is more than enough to pass these tests.

// Of course, you are expected to implement AVL functionality
// for the full project.

// BE SURE TO FULLY TEST YOUR CODE.
// This means making sure your templating is not hard-coding for 
// a specific type, that every function is called somewhere in 
// your test cases, etc. 
// There will NOT be a project 2 style redo for this;  if your 
//  code does not compile, your score will be a zero. 


TEST(CheckPoint, CheckPoint_FindTheRoot)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");

	EXPECT_TRUE( tree.contains(5) );
}

TEST(CheckPoint, CheckPoint_FindOneHop)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(10, "bar");

	EXPECT_TRUE( tree.contains(10) );
}

TEST(CheckPoint, CheckPoint_FindTwoHops)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "sna");
	tree.insert(10, "bar");
	tree.insert(12, "twelve");

	EXPECT_TRUE( tree.contains(12) );
	EXPECT_TRUE( tree.contains(3) );
}



TEST(CheckPoint, CheckPoint_Add5)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "sna");
	tree.insert(10, "bar");
	tree.insert(12, "twelve");
	tree.insert(15, "fifteen");
	EXPECT_TRUE(tree.find(10) == "bar");
	

	EXPECT_TRUE( tree.size() == 5 );
}

TEST(RiaEshaGTest, RotationLeftLeft)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(9, "foo");
	tree.insert(7, "sna");
	
	tree.insert(6, "bar");
	
	EXPECT_TRUE(tree.find(9) == "foo");
	

	
}
TEST(RiaEshaGTest, RotationLeftRight)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(8, "foo");
	tree.insert(2, "sna");
	tree.insert(3, "bar");
	
	
	
	std::vector<int> trav = tree.inOrder();
	std::vector<int> expected = {2, 3, 8};
	EXPECT_TRUE( trav == expected );

	std::vector<int> t = tree.preOrder();
	std::vector<int> e = {3, 2, 8};
	EXPECT_TRUE( t == e );

	EXPECT_TRUE(tree.find(3) == "bar");
	

	
}
TEST(RiaEshaGTest, RotationRightRight)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(4, "foo");
	tree.insert(5, "sna");
	tree.insert(8, "bar");
	EXPECT_TRUE(tree.find(8) == "bar");
	

	

	
}
TEST(RiaEshaGTest, RotationRightLeft)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(6, "foo");
	tree.insert(9, "sna");
	tree.insert(7, "bar");
	
	
	

	
}
TEST(RiaEshaGTest, RotationRootNotChnged)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(1, "foo");
	tree.insert(2, "sna");
	tree.insert(5, "bar");
	tree.insert(4, "bar");
	tree.inOrder();
	
	
	std::vector<int> trav = tree.inOrder();
	std::vector<int> expected = {1, 2, 4, 5};
	EXPECT_TRUE( trav == expected );

	std::vector<int> t = tree.preOrder();
	std::vector<int> e = {2,1, 5, 4};
	EXPECT_TRUE( t == e );
	

	
}
TEST(RiaEshaGTest, RotationManyUnbalanced)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(7, "foo");
	tree.insert(5, "sna");
	tree.insert(25, "bar");
	tree.insert(3, "bar");
	tree.insert(10, "bar");
	tree.insert(50, "bar");
	tree.insert(8, "bar");
	tree.insert(20, "bar");
	tree.insert(30, "bar");
	tree.insert(15, "bar");

	
	std::vector<int> trav = tree.inOrder();
	std::vector<int> expected = {3, 5, 7, 8, 10, 15, 20, 25, 30, 50};
	EXPECT_TRUE( trav == expected );

	std::vector<int> t = tree.preOrder();
	std::vector<int> e = {10, 7, 5, 3, 8, 25, 20, 15, 50, 30};
	EXPECT_TRUE( t == e );
	

	
}



TEST(PostCheckPoint, InOrderTraversal)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "sna");
	tree.insert(10, "bar");
	tree.insert(12, "twelve");
	tree.insert(15, "fifteen");

	std::vector<int> trav = tree.inOrder();
	std::vector<int> expected = {3, 5, 10, 12, 15};
	EXPECT_TRUE( trav == expected );
}

TEST(PostCheckPoint, PostOrderTraversal)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "sna");
	tree.insert(10, "bar");
	tree.insert(12, "twelve");
	tree.insert(15, "fifteen");


	std::vector<int> trav = tree.postOrder();
	
	std::vector<int> expected = {3, 10, 15, 12, 5};
	EXPECT_TRUE( trav == expected );
}



TEST(PostCheckPoint, JackSparrow)
{
	std::string quote = "I'm dishonest, and a dishonest man you can ";
	quote += "always trust to be dishonest. Honestly. It's the honest ";
	quote += "ones you want to watch out for, because you can never ";
	quote += "predict when they're going to do something incredibly... stupid.";

	std::istringstream stream( quote );

	MyAVLTree<std::string, unsigned> tree;

	countWords(stream, tree);
	EXPECT_TRUE(tree.find("dishonest") == 3);
}



TEST(PostCheckPoint, JackSparrow2)
{
	std::string quote = "I'm dishonest, and a Dishonest man you can ";
	quote += "always trust to be dishonest. Honestly. It's the honest ";
	quote += "ones you want to watch out for, because you can never ";
	quote += "predict when they're going to do something incredibly... stupid.";

	std::istringstream stream( quote );
	MyAVLTree<std::string, unsigned> tree;
	countWords(stream, tree);
	EXPECT_TRUE(tree.find("dishonest") == 3);
}

TEST(PostCheckPoint, Hamlet)
{
	MyAVLTree<std::string, unsigned> tree; 
 	std::fstream fs;
 	fs.open("/home/ics46/projects/proj4/gtest/hamletact1.txt");
 	countWords(fs, tree);
	
 	EXPECT_TRUE(tree.find("lord") == 60);
	EXPECT_TRUE(tree.find("hamlet") == 103);
	EXPECT_TRUE(tree.find("speak") == 27);


}
TEST(PostCheckPoint, HamletOpen)
{
	MyAVLTree<std::string, unsigned> tree; 
 	std::fstream fs;
 	fs.open("/home/ics46/projects/proj4/gtest/hamletopen.txt");
 	countWords(fs, tree);

 	EXPECT_TRUE(tree.find("francisco") == 10);
	EXPECT_TRUE(tree.find("holla") == 1);
	EXPECT_TRUE(tree.find("farewell") == 1);
}


TEST(RiaEshaGTest, quiz4test2)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(25, "foo");
	tree.insert(20, "sna");
	tree.insert(50, "bar");
	tree.insert(10, "bar");
	tree.insert(35, "bar");
	tree.insert(55, "bar");
	tree.insert(30, "bar");
	tree.insert(45, "bar");
	tree.insert(40, "bar");

	
	//tree.print2DUtil(tree.root, 0);
	

	
}

TEST(RiaEshaGTest, quiz4test1)
{
	MyAVLTree<int, std::string> tree;
	tree.insert(25, "foo");
	tree.insert(20, "sna");
	tree.insert(35, "bar");
	tree.insert(10, "bar");
	tree.insert(30, "bar");
	tree.insert(45, "bar");
	tree.insert(40, "bar");
	tree.insert(55, "bar");
	tree.insert(50, "bar");

	
	//tree.print2DUtil(tree.root, 0);
	

	
}

}