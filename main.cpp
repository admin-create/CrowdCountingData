//Bounding Box Calculations
//Crowd Simulation Research
//This program obtains hieght and center points fro specific people in a video simulation
//By Benjamin Adame
//12/15/2017

#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>


using namespace std;
using namespace cv;
//Global Constants:
Mat src;
const double deriveHieght=1.75;
//Function Prototype:
int main()
{


    //Variables:
    string txt;
    vector<string>txtFileNames;             //bbtxt files
    vector<string>totalNums;                //total numbers in bbtxtfile
    vector<float>numbersToUse;          //Numbers that are used fro each picture
    int fileCount=0;                                //the number of files
    string numsInTxt;                              //numbers that are read from the file
    int personId=0;
    vector<string>imageNames;       //From subway_md1.txt
    string image;                               //Image name to be read from file
    vector<long int>personIndex;    //Stores the starting postion of the person
    vector<string>image_name_to_use_later;



    //Read each file
    ifstream readTxt;
    readTxt.open("bb.txt");
    while (readTxt>>txt) {
        txtFileNames.push_back(txt);
        fileCount++;
    }
    //Close file
    readTxt.close();
    
    
    //Read Image files
    ifstream readImageName;
    readImageName.open("location.txt");
    while(readImageName>>image)
    {
        imageNames.push_back(image);
    }
    readImageName.close();
    

    //Open the txt files and extract the numbers
for(int count=0;count<fileCount;count++)
{
        
    if((count % 10)==0)
    {
       
            int fileToExtract=count;
            src = imread(imageNames[fileToExtract]);
            //get starting position of person and image name //store into vector// will use later......
            personIndex.push_back((personId+1));
            image_name_to_use_later.push_back(imageNames[fileToExtract]);
        
        
        

            ifstream nums;
            nums.open(txtFileNames[fileToExtract]); //Open individual text file
            while (nums>>numsInTxt)     //Extract numbers from txt file
                {
                    totalNums.push_back(numsInTxt);
                }
            //Replace all commas with spaces inside the one txt file
            for(int num_count=0;num_count<totalNums.size();num_count++)
            {
                replace(totalNums[num_count].begin(), totalNums[num_count].end(), ',', ' ');
                //Convert strings to floating numbers
                stringstream stream(totalNums[num_count]);
                float convertStringToInt;
                while(stream>>convertStringToInt)
                    {
                        //Put numbers in vector
                        numbersToUse.push_back(convertStringToInt);
                    }
            }
        
 
            //Find Each person in the particular image being displayed
            for(int personCount=0;personCount<numbersToUse.size();personCount++)
            {
            //IF statement that exclude any person id number
                if((personCount%5)==0)                  //Every Person Id number starts at the 5th position
                {
                    int thickness=2;              //Line thickness
                    float w,x,y,z;                        //Points for rectangle
                    w=numbersToUse[personCount+1];      //x1
                    x=numbersToUse[personCount+2];       //y1
                    y=numbersToUse[personCount+3];      //x2
                    z=numbersToUse[personCount+4];      //y2
                    //Create bounding box for the image for all the people
                    rectangle(src, Point(w,x), Point(y,z), Scalar(0,0,255),thickness);
                    //Find hieght,center points, and derived hieght;
                    Point center_of_rects(((w+y)/2),((x+z)/2));
                    circle(src, center_of_rects, 1, Scalar(0,0,255),thickness);
                    double pixelHieght = abs(x-z)+1;
                    double h = pixelHieght/deriveHieght;
                    personId++; //count the number of people in image
                    
//          Display person ids, hieght, and center points in a table
                    cout.width(7);
                    cout<<fixed<<setw(10)<<personId<<setw(10)<<setprecision(2)<<h<<setw(10)<<center_of_rects<<endl;
                    putText(src, to_string(personId), center_of_rects, FONT_HERSHEY_SIMPLEX, .5, Scalar(0,255,0));
                    imwrite(imageNames[fileToExtract], src);
                }
                
                
            }
        
        
                numbersToUse.clear();
                nums.close();           //close nums file
                totalNums.clear();
        }//if ends
    }//for ends
    
    //Display starting person index and the number of people in each image
    cout<<endl;
    for(int f=0;f<=image_name_to_use_later.size();f++)
    {
        long int getNumOfPeopleInImage = personIndex[f+1]-personIndex[f];
        cout<<fixed<<setw(10)<<image_name_to_use_later[f]<<setw(10)<<personIndex[f]<<setw(10)<<getNumOfPeopleInImage<<endl;
    }
    

}//main ends















