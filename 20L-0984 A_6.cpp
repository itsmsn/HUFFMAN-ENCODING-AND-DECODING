#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <bitset>
#include <unordered_map>
using namespace std;


//Globals + Proto
class node;
void To_bin(string s);
void binarY_convertor(string s);
void encodeit_To_File(string s);
static string str;
static int extra = 0;
void validate();
struct compare;
void cal_Freq(char str[]);
void encode(node* root, string str, unordered_map<char, string>& compressed_code);
string convertToString(char* a, int size);
void H_Tree(string text);


//Node Structure
class node
{
public:
	char ch;
	int FrequencY;
	node* left, * right;


	node(char ch, int FrequencY, node* left, node* right)
	{
		this->ch = ch;
		this->FrequencY = FrequencY;
		this->left = left;
		this->right = right;
	}

};

//Calcualating Frequencies
void cal_Freq(char str[])
{

	int i, count[256] = { 0 };

	for (i = 0; str[i] != '\0'; i++) 
	{
		count[str[i]]++;
	}

	cout << "\nCHARACTER FREQUENCIES\n";
	for (i = 0; i < 256; i++) 
	{
		if (count[i] != 0) {
			cout << "" << (char)i << " : " << count[i] << endl;
		}
	}
}

//Bool Compare Childs
struct compare
{
	bool operator()(node* l, node* r)
	{

		return (l->FrequencY > r->FrequencY);
	}
};

//Encoding The Stirng
void encode(node* root, string str, unordered_map<char, string>& compressed_code)
{
	if (root == nullptr)
	{
		return;
	}

	if (!root->left && !root->right) 
	{
		compressed_code[root->ch] = str;
	}

	encode(root->left, str + "0", compressed_code);
	encode(root->right, str + "1", compressed_code);
}

//Char to String Convertor
string convertToString(char* a, int size)
{
	int i;
	string s = "";
	for (i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}

//Decoding The String
void decode(node* root, int& index, string str)
{
	if (root == nullptr) 
	{
		return;
	}


	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

//Validating The String Is It Matches The Orignal Data
void validate()
{
	ifstream inp("encoding.txt");
	if (inp)
	{
		cout << "\nVALIDATION STARTED\n";

		//string st;
		//inn >> st;
		char c[2056] = { 0 };
		inp.getline(c, 2056);
		int siz = strlen(c);
		string st = convertToString(c, siz);

		st.pop_back();
		char count = '0';
		inp.seekg(-1, ios::end);
		inp.read(&count, 1);

		string so;
		int size =  st.size();

		cout << "COMPRESSED DATA AFTER READING FROM FILE IS : " << str;

		for (int i = 0; i < st.size(); i++)
		{
			char ch = st[i];
			int dec = (int)ch;
			if (dec >= 0)
			{
				cout << "";
			}
			else
			{
				dec = dec + 256;
			}
			//string temp = bitset<8>(dec).to_string();
		    so = so + bitset<8>(dec).to_string();
			st.erase(0, 1);
			i--;
		}
		cout << endl;
		for (int i = 0; i < extra; i++)
		{
			so.pop_back();
		}
		cout << endl;
		cout << so;

		
		cout << endl;
		cout << "VALIDATION COMPLETED\nDATA MATCHED\n";

	}
	else
	{
		cout << "\nError in Opening The File\n";
	}
}

//Pushing Compressed Data To File 
void encodeit_To_File(string s)
{
	ofstream off("encoding.txt");
	if (off)
	{
		cout << "\nENCODING DONE COMPRESSED FILE CREATED\n";
	}
	else
	{
		cout << "\ERROR IN OPENING THE FILE\n";
	}
	off << str;
	off << extra;
}

//Building HuFFman Tree Structure Using maps and PeroritY Queue
void H_Tree(string text)
{

	unordered_map <char, int> FrequencY;
	for (char ch : text) 
	{
		FrequencY[ch]++;
	}


	priority_queue <node*, vector <node*>, compare> minheap;


	for (auto pair : FrequencY) 
	{
		minheap.push(new node(pair.first, pair.second, nullptr, nullptr));
	}


	while (minheap.size() != 1)
	{

		node* left = minheap.top(); 
		minheap.pop();
		node* right = minheap.top();
		minheap.pop();


		int sum = left->FrequencY + right->FrequencY;
		minheap.push(new node('\0', sum, left, right));
	}


	node* root = minheap.top();


	unordered_map<char, string> compressed_code;
	encode(root, "", compressed_code);

	cout << "HUFFMAN CODES ARE :\n" << '\n';
	for (auto pair : compressed_code) 
	{
		cout << pair.first << " : " << pair.second << '\n';
	}

	cout << "\nORIGNAL STRING IS :\n" << text << '\n';


	string str = "";
	for (char ch : text) 
	{
		str += compressed_code[ch];
	}

	cout << "\nENCODED :\n" << str << '\n';

	int index = -1;

	cout << "\nDECODED : \n";
	while (index < (int)str.size() - 2) 
	{
		decode(root, index, str);
	}

	To_bin(str);
	
}

//Converting Pair oF 8 Strings To Decimal 
void binarY_convertor(string s)
{
	int x = 0;
	int sum = 0;
	for (int i = 0, j = 8; i < 8; i++, j--)
	{
		x = x + (int)s[i];
		x = x - 48;
		if(i != 7)
		{
			x = x << 1;
		}
	}
	//cout << (char)x;
	str.push_back((char)x);
}

//Spliting String in Pair oF 8
void To_bin(string s)
{

	int count = 0;
	string temp;

	int size = s.size();
	for (int i = 0; i < size; i++)
	{
		count++;
		if (count == 8)
		{
			temp = s.substr(0, 8);
		    binarY_convertor(temp);
			s.erase(0, 8);
			count = 0;
		}
	}
	cout << endl;
	if (s.size() < 8 && s.size() > 0)
	{
		for (int i = s.size(); i < 8; i++)
		{
			s.push_back('0');
			extra++;
		}
		binarY_convertor(s);
	}
}


int main()
{
	ifstream inn("data.txt");
	if (inn)
	{
		char c[2056] = { 0 };
		inn.getline(c,2056);
		int size = strlen(c);
		string s = convertToString(c, size);

		cout << "FILE IS OPEN : \n";
		cal_Freq(c);
		cout << endl << s;
		cout << endl;

		H_Tree(s);
		encodeit_To_File(str);
		//validate();
		//string s = "000011110000111111";
		//To_bin(s);
		validate();
	}
	else
	{
		cout << "FILE IS CLOSED TRY AGAIN\n";
	}


	return 0;
}