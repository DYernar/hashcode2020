#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <bits/stdc++.h>
#include <typeinfo>
using namespace std;
 
 
struct Book {
   size_t ID;
   size_t Score;
   bool isShipped = false;
};
 
struct library
{
   size_t ID;
   int BookAmount;
   int SignTime;
   int BookPerDay;
   Book* Books;
};
 
bool compareByScore(Book score1, Book score2)
{
   return score1.Score < score2.Score;
}
 
void swapLib(library *xp, library *yp) 
{ 
   library temp = *xp; 
   *xp = *yp; 
   *yp = temp; 
}
 
void swapBook(Book *xp, Book *yp) 
{ 
   Book temp = *xp; 
   *xp = *yp; 
   *yp = temp; 
}
 
 
 
void sortLibraries(library arr[], size_t n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)     
    
   // Last i elements are already in place 
   for (j = 0; j < n-i-1; j++) 
       if (arr[j].SignTime > arr[j+1].SignTime) 
           swapLib(&arr[j], &arr[j+1]); 
}
 
 
void sortByBooks(Book arr[], size_t n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)     
    
   // Last i elements are already in place 
   for (j = 0; j < n-i-1; j++) 
       if (arr[j].Score < arr[j+1].Score) 
           swapBook(&arr[j], &arr[j+1]); 
}
 
 
 
int main(int argc, char const *argv[])
{
 
   size_t bookAmount;
   size_t libraryAmount;
   size_t daysToScan;
 
   ifstream inFile;
  
   inFile.open("f_libraries_of_the_world.txt");
   if (!inFile) {
       cout << "Unablse to open file";
       exit(1); // terminate with error
   }
   inFile>>bookAmount>>libraryAmount>>daysToScan;
 
 
   Book books[bookAmount];
   size_t i = 0;
   for(i=0;i<bookAmount;i++){
       inFile>>books[i].Score;
       books[i].isShipped = false;
   }
 
   library libraries[libraryAmount];
 
 
   for(size_t j = 0; j < libraryAmount; j++) {
       libraries[j].ID = j;
       inFile>>libraries[j].BookAmount>>libraries[j].SignTime>>libraries[j].BookPerDay;
       libraries[j].Books=new Book[libraries[j].BookAmount];
       for (int k = 0; k < libraries[j].BookAmount; k++) {
           int bookind;
           inFile>>bookind;
           Book indBook;
           indBook.Score=books[bookind].Score;
           indBook.ID=bookind;
           libraries[j].Books[k] = indBook;
       }
   }
  
 
 
   sortLibraries(libraries, libraryAmount);
 
   size_t days = 0;
   size_t f = 0;
 
 
   while ((days < daysToScan) && (f < libraryAmount)) {
       days += libraries[f].SignTime;
       f++;
   }
 
   for (size_t i = 0; i < libraryAmount; i++) {
       sortByBooks(libraries[i].Books, libraries[i].BookAmount);
   }
 
 
   ofstream Myfile("f_result.txt");
 
   Myfile<<f<<endl;
  
 
   for (size_t i =0; i <f; i++) {
       if (daysToScan <= 0) {
           break;
       }
       size_t c = (daysToScan - libraries[i].SignTime)*libraries[i].BookPerDay;
 
       if (c >= libraries[i].BookAmount) {
           c = libraries[i].BookAmount;
       }
      
       Myfile<<libraries[i].ID<<" "<< c<<endl;
 
       for (size_t l = 0 ; l <c;l++) {
          
           // if (books[libraries[i].Books[l].ID].isShipped) {
           //     continue;
           // }
 
           Myfile<<libraries[i].Books[l].ID<<" ";
           // books[libraries[i].Books[l].ID].isShipped = true;
       }
       Myfile<<endl;
 
       daysToScan -= libraries[i].SignTime;
   }
 
   //     for(size_t j = 0; j < libraryAmount; j++) {
   //     cout<<"library: "<<j<<" book amount: "<<libraries[j].BookAmount<<" sign time: "<<libraries[j].SignTime<<" book per day "<<libraries[j].BookPerDay<<"\n";
   //     for (int k = 0; k < libraries[j].BookAmount; k++) {
   //         cout<<libraries[j].Books[k].ID<<" score: "<<libraries[j].Books[k].Score<<endl;
   //     }
   //     cout<<endl;
   // }
  
  
 
   Myfile.close();
   return 0;
}
