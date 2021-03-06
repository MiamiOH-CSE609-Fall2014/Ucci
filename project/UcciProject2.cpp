#include<iostream>
#include<vector>
#include<stdexcept>
#include<cstdlib>
#include<string>
#include<math.h>
#include<stdio.h>

using namespace std;

vector<string> all_names;
vector<double> all_grades;
vector<char> Curved_Letter_Grade;
int Array= 1;

string Name = "";
string LetterCurved = "";
double Grade = -1.0;
double avg = 0.0;
double std_deviation = 0.0;

void GetInput(){
  //run a loop for user input until they enter "none"
  while(true)
  {
  try
   {
     Name = "";
     Grade = -1;
     //get student's name
     cout << Array << ")\tEnter Student's name:\t";
     getline(cin, Name);

     //stop reading in names and grades
     if(Name.compare("none") == 0 )
       {
	 break;
       }

     //get grade
     cout << "\tEnter grade:\t";
     cin >> Grade;
     if(cin.fail())
       {
	 cin.clear();
	 cin.ignore(80, '\n');
	 throw out_of_range("Cannot input words");
       }
     cin.ignore();
     //verify grades are within range
     if(Grade  < 0.0 || Grade  > 100.0)
       {
	 throw out_of_range("Grade is not between 0 and 100");
       }

     //push back entered names and grades to be stored
     all_names.push_back(Name);
     all_grades.push_back(Grade);
     Array++;
   }
 catch(out_of_range error)
   {
     cout << error.what() << ":\tPlease re-enter student's Full name then theirgrade:\n\n";
   }
  }

}

void Calc_std_dev()
{
  //calculate average grade
  for(int i = 0; i < all_grades.size(); i++)
    {
      avg += all_grades[i];
    }
  avg = avg/all_grades.size();

  //calculate standard deviation
  for(int i = 0; i < all_grades.size(); i++) 
    {
      std_deviation += pow( (all_grades[i] - avg), 2.0);
    }
  std_deviation = sqrt(std_deviation/all_grades.size());
}

char CurvedGrade(double grade)
{
  if(grade > avg + (1.5*std_deviation))
    return 'A';
  else if (avg + (.5*std_deviation) < grade && grade < avg + (1.5*std_deviation))
    return 'B';
  else if (avg + (-.5*std_deviation) < grade && grade < avg + (.5*std_deviation))
    return 'C';
  else if (avg+ (-1.5*std_deviation) < grade && grade < avg + (-.5*std_deviation))
    return 'D';
  else
    return 'F';
}

void Grading_Scale()
{
  cout << "\n\n";
  cout << "Grading scale" << endl;
  if(avg + (1.5*std_deviation) > 100)
    cout << "A above 100.0%" << endl;
  else
  printf("A above %.1f%%\n",(avg+(1.5*std_deviation)));
  printf("B %.1f%% - %.1f%%\n",(avg + (.5*std_deviation)), (avg + (1.5*std_deviation)));
  printf("C %.1f%% - %.1f%%\n",(avg + (-.5*std_deviation)), (avg + (.5*std_deviation)));
  printf("D %.1f%% - %.1f%%\n",(avg + (-1.5*std_deviation)), (avg + (-.5*std_deviation)));
  printf("F below %.1f%%\n\n", (avg + (-1.5*std_deviation)));
}

int main ()
{
  cout << "\nPlease enter student's first and last name then hit enter.\nThen enter their grade.\nEnter none as a name to quit.\n\n";
  
  GetInput();
  
  Calc_std_dev();
  
  Grading_Scale();

  
  for(int i = 0; i < all_grades.size(); i++)
    {
      Curved_Letter_Grade.push_back(CurvedGrade(all_grades[i]));
    }

  
  printf("   Name\t\t\t\t Score\t\tGrade\n");
  for(int i = 0; i < all_names.size(); i++)
  {
    Name = all_names[i];
    LetterCurved = Curved_Letter_Grade[i];
    printf("%d. %-30s%.1f%%\t\t%s\n",i+1, Name.c_str(), all_grades[i], LetterCurved.c_str());
   
  }
  
  printf("\nClass Average \t   =\t%.2f%%\nStandard Deviation =\t%.2f\n\n", avg, std_deviation);

  return 0;
}
