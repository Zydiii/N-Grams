#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <memory>
#include <ctime>
using namespace std;
//�洢�ļ�����
bool set_file(string file_name, vector<string> &words)
{
	ifstream infile;
	stringstream word;
	infile.open(file_name, ios::in);
	if (infile.fail())
	{
		cout << "Can not open the dictionary." << endl;
		return false;
	}
	string w;
	word << infile.rdbuf();
	do
	{
		word >> w;
		words.push_back(w);
	} while (!word.fail());
	return true;
}
//����n_gram map
void n_gram(vector<string> words, map<vector<string>, vector<string>> &n_gram, int n)
{
	for (int i = 0; i < words.size() - n; i++)
	{
		vector<string> gram;
		for (int j = 0; j < n; j++)
		{
			gram.push_back(words[i + j]);
		}
		map<vector<string>, vector<string>>::iterator it;
		if (n_gram.count(gram))
		{
			it = n_gram.find(gram);
			it->second.push_back(words[i + n]);
		}
		else
		{
			vector<string> follow{words[i + n]};
			n_gram[gram] = follow;
		}
	}
}
//��������ĸ�Ǵ�д��N_gram map
void N_gram(vector<string> words, map<vector<string>, vector<string>> &N_gram, int n)
{
	for (int i = 0; i < words.size() - n; i++)
	{
		if (isupper(words[i][0]))
		{
			vector<string> gram;
			for (int j = 0; j < n; j++)
			{
				gram.push_back(words[i + j]);
			}
			map<vector<string>, vector<string>> ::iterator it;
			if (N_gram.count(gram))
			{
				it = N_gram.find(gram);
				it->second.push_back(words[i + n]);
			}
			else
			{
				vector<string> follow{words[i + n]};
				N_gram[gram] = follow;
			}
		}
	}
}
//�������ı�
void randomText(vector<string> &text, map<vector<string>, vector<string>> n_gram, int n, int N)
{
	srand(clock());
	int begin_point = rand() % n_gram.size();//������
	vector<string> gram;
	map<vector<string>, vector<string>> ::iterator it = n_gram.begin();
	for (int i = 0; i < begin_point; i++)
	{
		it++;
	}
	text = it->first;
	gram = it->first;
	for (int i = 0; i < N - n; i++)
	{
		begin_point = rand() % n_gram[gram].size();
		text.push_back(n_gram[gram][begin_point]);
		gram.push_back(n_gram[gram][begin_point]);
		gram.erase(gram.begin());
	}
	if (islower(text[0][0]))//������Ǿ��Ӽ���...
	{
		text.insert(text.begin(), "...");
	}
	if (!(text[text.size() - 1].back() == '!' || text[text.size() - 1].back() == '.' || text[text.size() - 1].back() == '?'))
	{
		text.push_back("...");
	}
}
//�������
void random_text(vector<string> &text, map<vector<string>, vector<string>> n_gram, map<vector<string>, vector<string>> N_gram, int n, int N)
{
	srand(clock());
	int begin_point = rand() % N_gram.size();
	vector<string> gram;
	map<vector<string>, vector<string>>::iterator it = N_gram.begin();//������ĸ��д��N_gram map����������
	for (int i = 0; i < begin_point; i++)
	{
		it++;
	}
	text = it->first;
	gram = it->first;
	for (int i = 0; i < N - n; i++)
	{
		begin_point = rand() % n_gram[gram].size();
		text.push_back(n_gram[gram][begin_point]);
		gram.push_back(n_gram[gram][begin_point]);
		gram.erase(gram.begin());
	}
	//��֤��β�Ǿ��ӵı�����
	while (!(text[text.size() - 1].back() == '!' || text[text.size() - 1].back() == '.' || text[text.size() - 1].back() == '?'))
	{
		text.erase(text.end() - 1);
		begin_point = rand() % n_gram[gram].size();
		text.push_back(n_gram[gram][begin_point]);
		gram.push_back(n_gram[gram][begin_point]);
		gram.erase(gram.begin());
	}
}
int main()
{
	string file_name;
	vector<string> words;
	do
	{
		cout << "Input filename?" << endl;
		cin >> file_name;
	} while (!set_file(file_name, words));
	int n;
	map<vector<string>, vector<string>> _ngram;
	map<vector<string>, vector<string>> _Ngram;
	cout << "Value of N?" << endl;
	cin >> n;
	while (!cin.good())
	{
		cin.clear();
		cin.ignore();
		cout << "Invalid N" << endl;
		cout << "Value of N?" << endl;
		cin >> n;
	}

	n_gram(words, _ngram, n);
	N_gram(words, _Ngram, n);
	//������
	while(true)
	{
	int N;
	cout << "# of random words to generate (0 to quit)? ";
	while (!(cin >> N) || (N != 0 && N < n))
	{
	cin.clear();
	cin.ignore();
	cout << "Invalid n" << endl;
	cout << "# of random words to generate (0 to quit)? ";
	}
	if (N == 0)
	break;
	vector<string> text;
	randomText(text, _ngram, n, N);
	for (string w : text)
	{
	cout << w << " ";
	}
	cout << endl;
	}
	//�������
    /*while(true)
	{
		int N;
		cout << "# of random words to generate (0 to quit)? ";
		while (!(cin >> N) || (N!=0 && N < n))
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid n" << endl;
			cout << "# of random words to generate (0 to quit)? ";
		}
		if (N == 0)
			break;
		vector<string> text;
		random_text(text, _ngram, _Ngram, n, N);
		for ( string w : text)
		{
			cout << w << " ";
		}
		cout << endl;
	}
	*/
	return 0;
}