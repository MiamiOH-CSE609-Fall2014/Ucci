#include<iostream>
#include<tuple>
#include<string>
#include<vector>
#include<fstream>
#include<map>

using namespace std;

string digrams[] = {"AA", "AG", "AC", "AT", "GA", "GG", "GC", "GT", "CA", "CG", "CC", "CT", "TA", "TG", "TC", "TT"};

map<string, int> index;


tuple< string, vector<string>, string> parseFastaFile(string name_of_file)
{
  string header = "";
  vector<string> comments;
  string sequence = "";
  string strTmp = "";

  ifstream file(name_of_file);

  while(file.good())
    {
      getline(file, strTmp);
      if(strTmp.substr(0,1) == ">")
	{
	  header = strTmp;
	}
      else if(strTmp.substr(0,1) == ";")
	{
	  comments.push_back(strTmp);
	}
      else
	{
	  sequence += strTmp;
	}
    }

  return make_tuple(header, comments, sequence);
}

map< string, int > digramFreqScores(string s)
{
  map< string, int >scores;

  for(int i = 0; i < 16; i++)
    {
      string tmp_dna = s;
      int count = 0;

      int index = 0;
      while(true)
	{
	  index = tmp_dna.find(digrams[i]);
	  if(index == string::npos)
	    {
	      break;
	    }
	  else
	    {
	      tmp_dna.replace(index, 1, "X");
	      count++;
	    }
	}
      scores[digrams[i]] = count;
    }
  return scores;
}


vector< vector<int> > digramFreqMatrix( map< string, int > matrixMap)
{
  vector< vector<int> > matrix;
  vector<int> tmp;
  int index = 0;
  for(int i = 0; i < 16; i++)
    {
      tmp.push_back(matrixMap[digrams[i]]);
      index++;

      if(index == 4)
	{
	  matrix.push_back(tmp);
	  index = 0;
	  tmp.clear();
	}

    }
  return matrix;
}

vector< vector<int> > parseScoringFile(string file_name)
{
  vector< vector<int> > parse_score_matrix;
  vector<int> temp;
  string strTmp = "";
  ifstream file(file_name);

  while(file.good())
    {
      temp.clear();
      getline(file, strTmp);
      int current;
      int next = -1;

      do
	{
	  current = next+1;
	  next = strTmp.find_first_of(',', current);
	  temp.push_back(atoi(strTmp.substr(current, next-current).c_str()));
	}
      while(next != string::npos);
      if(parse_score_matrix.size() < 4)
	parse_score_matrix.push_back(temp);
    }
  return parse_score_matrix;
}

tuple<int, int> scoreSequence(string haystack, string needles, vector< vector<int> > scoring_m)
{
  int max_index = 0;
  int high_scorer = 0;
  int current_score = 0;
  string first, second;
  
  for(int i = 0; i < haystack.length() - needles.length() +1; i++)
    {
      current_score = 0;
      string::iterator Haystack = haystack.begin();
      string::iterator Needle;
      advance(Haystack, i);

      for(Needle = needles.begin(); Needle < needles.end(); Needle++)
	{
	  first = *Needle;
	  second = *Haystack;

	  current_score += scoring_m[index[first]][index[second]];
	  Haystack++;
	}

      
      if(current_score >= high_scorer)
	{
	  high_scorer = current_score;
	  max_index = i;
	}
    }

  return make_tuple(max_index, high_scorer);
}

tuple< int, int, string >findHighScore(string seq, vector<string> comp, vector< vector<int> > scoring_m)
{
  int max_pos = 0;
  int high_scorer = 0;
  string needle = "";

  tuple<int, int> temp;

  for(int i = 0; i < comp.size(); i++)
    {
      temp = scoreSequence(seq, comp[i], scoring_m);
      if(get<1>(temp) > high_scorer)
	{
	  high_scorer = get<1>(temp);
	  max_pos = get<0>(temp);
	  needle = comp[i];
	}
    }

  return make_tuple(max_pos, high_scorer, needle);
}


int main(int argc, char* argv[])
{
  if(argc != 3)
    {
      cout << "Specify 2 file names." << endl;
      return 1;
    }

  index["A"] = 0;
  index["G"] = 1;
  index["C"] = 2;
  index["T"] = 3;

  string file1, file2;
  file1 = argv[1];
  file2 = argv[2];

  tuple<string, vector<string>, string> parsed = parseFastaFile(file1);

  map< string, int > matrixMap = digramFreqScores(get<2>(parsed));

  cout << "\tDiagram Frequency Matrix\n\t   A  G  C  T\n";
  string header[] = {"A", "G", "C", "T"};
  int index = 0;
  for(int i = 0; i < 4; i++)
    {
      cout << "\t" << header[i];
      cout << "  " << matrixMap[digrams[index]];
      cout << " " << matrixMap[digrams[index+1]];
      cout << " " << matrixMap[digrams[index+2]];
      cout << " " << matrixMap[digrams[index+3]];
      index = index + 4;
      cout << endl;
    }

  vector< vector<int> > scoreMatrix = digramFreqMatrix(matrixMap);

  vector< vector<int> > scoring_m = parseScoringFile(file2);

  cout << "\n\tScoring Matrix\n\t   A G C T" << endl;

  for(int first = 0; first < scoring_m.size(); first++)
    {
      cout << "\t" << header[first] << "  ";
      for(int second = 0; second < scoring_m[first].size(); second++)
	{
	  cout << scoring_m[first][second] << " ";
	}
      cout << endl;
    }
  cout << endl;

  tuple<int, int> score = scoreSequence("GTGTCT", "TCT", scoring_m);

  vector<string> comp;
  int number_of_scores_wanted;
  string num_seq;
  cout << endl;
  cout << "How many sequences would you like to score? ";
  cin >> number_of_scores_wanted;

  for(int i = 0; i < number_of_scores_wanted; i++)
    {
      cout << "Enter sequence # " << (i+1) << " on one line:\n";
      cin >> num_seq;
      comp.push_back(num_seq);
    }

  cout << endl;

  vector<string> seq;
  for(int i = 0; i < number_of_scores_wanted; i++)
    {
      seq.clear();
      seq.push_back(comp[i]);
      tuple<int, int, string> high_score = findHighScore(get<2>(parsed), seq, scoring_m);
      cout << "Sequence:" << endl;
      cout << get<2>(high_score) << endl;
      cout << "Score: " << get<1>(high_score) << " at position " << get<0>(high_score) << endl;
      cout << endl;
    }


  return 0;2;
 }
