#include <string>
#include <iostream>
#include <fstream>
using namespace std;
class Huffman
{
 private:
 class BinNode
  {
   public:
   char data;
   BinNode * left, * right;
   BinNode(char item)
   {
    data = item;
    left = right = 0;
   }
  };
 typedef BinNode * BinNodePointer;
 public:
 Huffman();
 void buildDecodingTree(ifstream & codeIn);
 void insert(char ch, string code);
 void decode(ifstream & messageIn);
 void printTree(ostream & out, BinNodePointer root, int indent);
 void displayDecodingTree(ostream & out)
  {
   printTree(out, myRoot, 0);
  }
 private:
 BinNodePointer myRoot;
};
inline Huffman::Huffman()
{
 myRoot = new BinNode('*');
}
void Huffman::buildDecodingTree(ifstream & codeIn)
{
 char ch; 
 string code; 
 for (;;)
 {
 codeIn >> ch >> code;
 if ( codeIn.eof() ) return;
 insert(ch, code);
 }
}
void Huffman::insert(char ch, string code)
{
 Huffman::BinNodePointer p = myRoot; 
 for(int i = 0; i < code.length(); i++)
 {
 switch (code[i])
 {
 case '0' : 
 if (p->left == 0) 
 p->left = new Huffman::BinNode('*');
 p = p->left;
 break;
 case '1' : 
 if (p->right == 0)
 p->right = new Huffman::BinNode('*');
 p = p->right;
 break;
 default:
 cerr << "*** Illegal character in code ***\n";
 exit(1);
 }
 }
 p->data = ch;
}
void Huffman::decode(ifstream & messageIn) //decode
{
 char bit; 
 Huffman::BinNodePointer p; 
 for(;;)
 {
 p = myRoot;
 while (p->left != 0 || p->right != 0)
 {
 messageIn >> bit;
 if ( messageIn.eof() ) return;
 cout << bit;
 if (bit == '0')
 p = p->left;
 else if (bit == '1')
 p = p->right;
 else
 cerr << "Illegal bit: " << bit << " -- ignored\n";
 }
 cout << "--" << p->data << endl;
 }
}
void Huffman::printTree(ostream & out, Huffman::BinNodePointer root,
 int indent)
{
 if (root != 0)
 {
 printTree(out, root->right, indent + 8);
 out << setw(indent) << " " << root->data << endl;
 printTree(out, root->left, indent + 8);
 }
}
int main()   //main
{
 char filename[32];
 cout << "Enter name of code file: ";
 cin >> filename;
 ifstream codestream(filename);
 if (!codestream.is_open())
 {
 cout << "Cannot open code file.\n";
 exit(1);
 }
 Huffman h;
 h.buildDecodingTree(codestream);
 cout << "Here is the Huffman decoding tree:\n";
 h.displayDecodingTree(cout);
 cout << endl;
 cout << "\nName of message file: ";
 cin >> filename;
 ifstream message(filename);
 if (!message.is_open())
 {
 cout << "Cannot open message file.\n";
 exit(1);
 }
 h.decode(message);
}
