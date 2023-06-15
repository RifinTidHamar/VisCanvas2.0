// Standalone rule generation program
#include<stdio.h>
#include <stdlib.h>
#include<vector>
#include<iostream>
#include<cmath>
#include<unordered_map>
#include<list>
#include "stdafx.h"

// namespace for ease
using namespace std;

// create structure to hold rule data
struct rule {
	int ruleValFront = 0;
	int ruleValBack = 0;
	int coverageCounter = 0;
	int classCovered = -1; // -1 is default value, but could potentially match a data's class.
	int expansionIndex = -1; // represents the index where the expansion/rule happens
};

void clearRule(rule& usedRule)
{
	usedRule.ruleValFront = 0;
	usedRule.ruleValBack = 0;
	usedRule.coverageCounter = 0;
	usedRule.classCovered = -1;
	usedRule.expansionIndex = -1;
}

struct Expansion
{
	//this is the row, or the set in the data that is being expanded from
	int rowExpandedfrom;
	//These indexes assume the Expansion struct is being used in some sort of table--in this implementation it is an unordered map
	//these indexes represent the key of the table, but not any value in the expansion data itself
	//the values within this variable are parallel to those in expansionDirection
	//there should only be two values at maximum, and one value at minimum for expansionIndexExpandedTo and expansionDirection.
	//the front of the list represent an upward expansion, and the back of the list represents a downward epxansion
	list<int> expansionIndexExpandedTo;
	//these values represent the expansion direction (1: upward, -1: downard) from rowExpandedFrom -> the parallel row of the table[expansionIndexExpandedTo].rowExpandedFrom. 
	list<int> expansionDirection;
	//this is the column or attribute from which the expansion is taking place--there can only be column index per expansion (but a row/set can be apart of two expansions still)
	int columnIndex;
	//if the current expansion is already in a rule, then this should be checked true. By default, expansions are not part of any rule. 
	bool alreadyInARule = false;
};

// drive function
void michRuleGen()
{
	// create vectors which hold the cordinate values
	// Hard coded //
	vector<int> x1 = { 0, 1 }; //2
	vector<int> x2 = { 0, 1, 2, 3 }; // 4
	vector<int> x3 = { 0, 1, 2 }; // 3
	vector<int> x4 = { 0, 1, 2 }; // 3

	// create vectors which hold the id values. Last value is class output
	// Hard coded //
	//before using, must remove duplicates
	/*vector<int> id0  =	{ 0, 0, 0, 0, 1 };
	vector<int> id1  =	{ 1, 0, 0, 0, 1 };
	vector<int> id2  =	{ 1, 1, 1, 1, 1 };
	vector<int> id3  =	{ 1, 2, 1, 1, 1 };
	vector<int> id4  =	{ 1, 3, 1, 1, 1 };
	vector<int> id5  =	{ 0, 0, 2, 2, 1 };
	vector<int> id6  =	{ 0, 0, 1, 2, 1 };
	vector<int> id7  =	{ 0, 0, 0, 2, 1 };
	vector<int> id8  =	{ 1, 2, 2, 0, 1 };
	vector<int> id9  =	{ 0, 2, 2, 0, 1 };
	vector<int> id10 =	{ 1, 2, 0, 1, 2 };
	vector<int> id11 =	{ 1, 1, 0, 1, 2 };
	vector<int> id12 =	{ 1, 0, 0, 1, 2 };
	vector<int> id13 =	{ 1, 1, 2, 2, 2 };
	vector<int> id14 =	{ 0, 1, 2, 2, 2 };
	vector<int> id15 =	{ 0, 2, 2, 0, 2 };
	vector<int> id16 =  { 0, 2, 1, 0, 2 };
	vector<int> id17 =  { 0, 2, 0, 0, 2 };
	vector<int> id18 =  { 1, 1, 2, 1, 2 };
	vector<int> id19 =  { 1, 1, 2, 2, 2 };*/

	//before using, must remove duplicates
	//vector<int> id0 =  { 1, 0, 0, 0, 1 };
	//vector<int> id1 =  { 2, 0, 0, 0, 1 };
	//vector<int> id2 =  { 1, 0, 0, 0, 1 };
	//vector<int> id3 =  { 2, 0, 0, 0, 1 };
	//vector<int> id4 =  { 1, 0, 0, 0, 1 };
	//vector<int> id5 =  { 0, 0, 0, 0, 1 };
	//vector<int> id6 =  { 0, 0, 0, 0, 1 };
	//vector<int> id7 =  { 0, 0, 0, 0, 1 };
	//vector<int> id8 =  { 0, 0, 0, 0, 1 };
	//vector<int> id9 =  { 0, 0, 0, 0, 1 };
	//vector<int> id10 = { 3, 0, 0, 0, 2 };
	//vector<int> id11 = { 3, 0, 0, 0, 2 };
	//vector<int> id12 = { 3, 0, 0, 0, 2 };
	//vector<int> id13 = { 3, 0, 0, 0, 2 };
	//vector<int> id14 = { 3, 0, 0, 0, 2 };
	//vector<int> id15 = { 3, 0, 0, 0, 2 };
	//vector<int> id16 = { 3, 0, 0, 0, 2 };
	//vector<int> id17 = { 3, 0, 0, 0, 2 };
	//vector<int> id18 = { 3, 0, 0, 0, 2 };
	//vector<int> id19 = { 3, 0, 0, 0, 2 };

	//no duplicates allowed
	vector<int> id0 = { 4, 0, 0, 0, 1 };
	vector<int> id1 = { 5, 0, 0, 0, 1 };
	vector<int> id2 = { 3, 0, 0, 0, 1 };
	vector<int> id3 = { 6, 0, 0, 0, 1 };
	vector<int> id4 = { 9, 0, 0, 0, 1 };
	vector<int> id5 = { 1, 0, 0, 0, 1 };
	vector<int> id6 = { 2, 0, 0, 0, 1 };
	vector<int> id7 = { 7, 0, 0, 0, 1 };
	vector<int> id8 = { 0, 0, 0, 0, 1 };
	vector<int> id9 = { 8, 0, 0, 0, 1 };
	vector<int> id10 = { 10, 0, 0, 1, 2 };
	vector<int> id11 = { 11, 1, 0, 1, 2 };
	vector<int> id12 = { 12, 0, 0, 1, 2 };
	vector<int> id13 = { 13, 1, 2, 2, 2 };
	vector<int> id14 = { 14, 1, 2, 2, 2 };
	vector<int> id15 = { 13, 2, 2, 0, 2 };
	vector<int> id16 = { 14, 2, 1, 0, 2 };
	vector<int> id17 = { 14, 2, 0, 0, 2 };
	vector<int> id18 = { 13, 1, 2, 1, 2 };
	vector<int> id19 = { 13, 2, 2, 2, 2 };

	/*vector<int> id0 = { 4, 0, 0, 0, 1 };
	vector<int> id1 = { 6, 0, 0, 0, 1 };
	vector<int> id2 = { 3, 0, 0, 0, 1 };
	vector<int> id3 = { 7, 0, 0, 0, 1 };
	vector<int> id4 = { 10, 0, 0, 0, 1 };
	vector<int> id5 = { 1, 0, 0, 0, 1 };
	vector<int> id6 = { 2, 0, 0, 0, 1 };
	vector<int> id7 = { 8, 0, 0, 0, 1 };
	vector<int> id8 = { 0, 0, 0, 0, 1 };
	vector<int> id9 = { 9, 0, 0, 0, 1 };
	vector<int> id10 = { 11, 0, 0, 0, 2 };
	vector<int> id11 = { 12, 0, 0, 0, 2 };
	vector<int> id12 = { 13, 0, 0, 0, 2 };
	vector<int> id13 = { 14, 0, 0, 0, 2 };
	vector<int> id14 = { 15, 0, 0, 0, 2 };
	vector<int> id15 = { 16, 0, 0, 0, 2 };
	vector<int> id16 = { 17, 0, 0, 0, 2 };
	vector<int> id17 = { 100, 0, 0, 0, 2 };
	vector<int> id18 = { 101, 0, 0, 0, 2 };
	vector<int> id19 = { 102, 0, 0, 0, 2 };*/


	// create vector to hold all data
	vector<vector<int>> data;

	// put data into data vector
	data.push_back(id0);
	data.push_back(id1);
	data.push_back(id2);
	data.push_back(id3);
	data.push_back(id4);
	data.push_back(id5);
	data.push_back(id6);
	data.push_back(id7);
	data.push_back(id8);
	data.push_back(id9);
	data.push_back(id10);
	data.push_back(id11);
	data.push_back(id12);
	data.push_back(id13);
	data.push_back(id14);
	data.push_back(id15);
	data.push_back(id16);
	data.push_back(id17);
	data.push_back(id18);
	data.push_back(id19);


	//idea--sort the rows off of the current attribute being tested for matches using count sort. Than find expansions. 
	// find the minimum and maximum for each coordinate/attribute
	// not currently needed
	//vector<int> coordinateMax;
	//vector<int> coordinateMin;

	//for (int dataColumn = 0; dataColumn < (data.at(0).size() - 1); dataColumn++)
	//{
	//	coordinateMax.push_back(data.at(0).at(dataColumn));
	//	coordinateMin.push_back(data.at(0).at(dataColumn));

	//	for (int dataRow = 0; dataRow < data.size(); dataRow++)
	//	{
	//		if (data.at(dataRow).at(dataColumn) > coordinateMax.at(dataColumn))
	//		{
	//			coordinateMax.at(dataColumn) = data.at(dataRow).at(dataColumn);
	//		}
	//		else if(data.at(dataRow).at(dataColumn) < coordinateMin.at(dataColumn))
	//		{
	//			coordinateMin.at(dataColumn) = data.at(dataRow).at(dataColumn);
	//		}
	//	}
	//}


	// create vector of rules generated
	vector<rule> rules;

	// create temporary rule structure for information tracking
	rule* tempRule;

	//this holds all expansions and expansion data; check struct above for more detail
	unordered_map<int, Expansion> expansions;

	// compare the first case against all cases to find where the absolute value of all points subtracted is 1
	// Ex: c1 = {0, 0, 1, 2} and c2 = {1, 0, 1, 2}
	// c1 - c2 = {-1, 0, 0, 0}
	// sum the result = -1
	// take the absolute value = 1
	for (int compXIndex = 0; compXIndex < data.size(); compXIndex++)
	{
		// int vector to store the index of cases which have an absolute value of 1 when compared to the comparison case
		vector<int> matches;

		// vector to hold the difference between the two cases (see example below)
		vector<int> difference;

		// clear matches
		matches.clear();

		// push the current data being compared into the first index of the matches vector
		matches.push_back(compXIndex);

		// comparison case to keep track of current case to be compared
		vector<int> comparisonCase = data.at(compXIndex);

		for (int dataXIndex = 0; dataXIndex < data.size(); dataXIndex++)
		{
			for (int dataYIndex = 0; dataYIndex < (data.at(dataXIndex).size() - 1); dataYIndex++)
			{
				// check that the comparisonX and the dataX are not the same
				if (compXIndex != dataXIndex)
				{
					// subtract the comparison data from the data being compared
					difference.push_back(((comparisonCase.at(dataYIndex)) - (data.at(dataXIndex).at(dataYIndex))));
				}

			}// close dataY

			// add together the difference and check if the absolute value of the difference is 1
			// integer to hold the sum
			int sum = 0;
			for (int diff = 0; diff < difference.size(); diff++)
			{
				// cout << "Difference Value: " << difference.at(diff) << endl;
				sum += difference.at(diff);
			}

			// cout << "Difference Sum ABS: " << abs(sum) << endl;

			// clear difference vector
			difference.clear();

			// check if the absolute value of sum is 1 and if the classes are the same
			if (abs(sum) == 1 && data.at(compXIndex).at(data.at(compXIndex).size() - 1) == data.at(dataXIndex).at(data.at(dataXIndex).size() - 1))
			{
				//cout << "Match " << dataXIndex << " pushed to vector" << endl;
				matches.push_back(dataXIndex);
			}

		}// close dataX

		/*
		// print matches to ensure it is working
		for (int i = 0; i < matches.size(); i++)
		{
			if (i == 0)
			{
				cout << "ID" << matches.at(i) << " has the matches of: " << endl;
			}
			else
			{
				cout << "\tMatch " << i << ":" << " ID" << matches.at(i) << endl;
			}
		}
		*/

		// check if the matches can be expanded
		//=====NOTE: THIS DOES NOT CURRENTLY WORK=====//
		for (int match = 0; match < matches.size(); match++)
		{
			// boolean variable to check if an expandable attribute has already been found
			// this needs to be checked since there can only be one expansion
			bool expansionFound = false;

			// temporary vector to hold this comparisons expandable flags
			vector<int> tempExpansionDirection;

			// temporary vector to hold this comparisons expandable IDs
			vector<int> tempId;

			// temporary vector to hold the index of the expansion
			vector<int> tempColumnInd;

			// the first value in the match vector is the id of the original compared data
			if (match > 0)
			{
				// iterate over the matched dataID to determine if it can be expanded
				//changed dataIndex -> columnIndex
				for (int columnIndex = 0; columnIndex < (data.at(matches.at(match)).size() - 1); columnIndex++)
				{

					// check if the match can be expanded upwards
					if (expansionFound == false && comparisonCase.at(columnIndex) == (data.at(matches.at(match)).at(columnIndex) + 1))
					{
						// set the expansion found flag to true
						expansionFound = true;

						// set the expand flag to show it is an downward expansion
						//changed tempFlags -> tempExpansionFlags
						tempExpansionDirection.push_back(-1);

						// record the expansion index
						//change tempInd -> tempColumnInd
						tempColumnInd.push_back(columnIndex);

						/*
						cout << "Downward Expansion Found in match #" << match << endl;
						cout << "\tData at: " << dataIndex << " is: " << comparisonCase.at(dataIndex) << endl;
						cout << "\tExpansion: " << matches.at(match) << " at: " << match << " is: " << (data.at(matches.at(match)).at(dataIndex) + 1) << endl;
						*/
					}
					// check if the match can be expanded downwards
					else if (expansionFound == false && comparisonCase.at(columnIndex) == (data.at(matches.at(match)).at(columnIndex) - 1))
					{
						// set the expansion found flag to true
						expansionFound = true;

						// set the expand flag to show it is an upward expansion
						tempExpansionDirection.push_back(1);

						// record the expansion index
						tempColumnInd.push_back(columnIndex);

						/*
						cout << "Upward Expansion Found in match #" << match << endl;
						cout << "\tData at: " << dataIndex << " is: " << comparisonCase.at(dataIndex) << endl;
						cout << "\tExpansion: " << matches.at(match) << " at: " << match << " is: " << (data.at(matches.at(match)).at(dataIndex) + 1) << endl;
						*/
					}
					// this means that there are more than one expansions in the match
					// Ex: comparison Case = {0, 1, 0 ,0}
					// 	   match case = {1, 0, 0, 1}
					// In the above example, the difference in the sums is an absolute value of 1, but there is more than one possible expansion
					else if (expansionFound == true && comparisonCase.at(columnIndex) != (data.at(matches.at(match)).at(columnIndex)))
					{
						// remove the last flag pushed into the expansion flag vector
						if (tempExpansionDirection.size() > 0)
						{
							tempExpansionDirection.pop_back();
						}

						if (tempColumnInd.size() > 0)
						{
							tempColumnInd.pop_back();
						}

						break;
					}
					// check if there is an expansion that is too large or too small
					// Ex: ID1 (0, 0, 0, 1), ID2 (0, 0, 0, 3)
					// Ex: ID1 (0, 0, 0, 3), ID2 (0, 0, 0, 1)
					else if ((comparisonCase.at(columnIndex) > (data.at(matches.at(match)).at(columnIndex) + 1)) || (comparisonCase.at(columnIndex) < (data.at(matches.at(match)).at(columnIndex) - 1)))
					{
						// clear the last flag pushed if there are any
						if (tempExpansionDirection.size() > 0)
						{
							tempExpansionDirection.pop_back();
						}

						break;
					}
					// else the comparison case and the data are the same value
					else
					{
						continue;
					}
				}
				// end dataIndex

				if (expansionFound == true && tempExpansionDirection.size() > 0)
				{
					// add the comparison ID to the expandable vector
					tempId.push_back(matches.at(0));

					// add the match which can be expanded to to the expandable vector
					tempId.push_back(matches.at(match));

					Expansion exp;
					//this index uses rowDominant form. It is important to do this incase a row has expansions in different attributes/columns
					//thus there will be an expansion struct for each of those expansions
					//thus those expansions need different indexes
					int expansionsIndex = matches.at(0) + (tempColumnInd.at(0) * data.at(matches.at(0)).size() - 1);

					//the expansion index does not exist
					if (expansions.find(expansionsIndex) == expansions.end())
					{
						//create one
						expansions[expansionsIndex] = exp;
					}
					//fill the rowExpandedFrom and the columnIndex for the individual expansion
					expansions[expansionsIndex].rowExpandedfrom = matches.at(0);
					expansions[expansionsIndex].columnIndex = tempColumnInd.at(0);

					//if the expansionDirection of match is upwards, then the expansion and direction should 
					// go the front of expansionIndexExpandedTo and expansionDirection within expansions. 
					// Otherwise, both will go to the back. 
					//this is how the data is expected to be organized for later on down the road. 
					if (tempExpansionDirection.at(0) == 1)
					{
						expansions[expansionsIndex].expansionDirection.push_front(tempExpansionDirection.at(0));
						expansions[expansionsIndex].expansionIndexExpandedTo.push_front(matches.at(match) + (tempColumnInd.at(0) * data.at(matches.at(0)).size() - 1));
					}
					else
					{
						expansions[expansionsIndex].expansionDirection.push_back(tempExpansionDirection.at(0));
						expansions[expansionsIndex].expansionIndexExpandedTo.push_back(matches.at(match) + (tempColumnInd.at(0) * data.at(matches.at(0)).size() - 1));
					}
					//cout << expansions.size();
				}
			}
		} // end matches

		// clear the expandable and expansion flags
		// expandable.clear();
		// expansionFlags.clear();

	}// close compXIndex

	//cout << "\n";

	//// print the expansions to ensure it is working
	//for (int i = 0; i < expandable.size(); i++)
	//{
	//	for (int j = 0; j < expandable.at(i).size(); j++)
	//	{
	//		if (j == 0)
	//		{
	//			cout << "ID" << expandable.at(i).at(j) << " can expand to: " << endl;
	//		}
	//		else
	//		{
	//			cout << "\tExpand " << i << ":" << " ID" << expandable.at(i).at(j) << endl;
	//			cout << "\tExpand " << i << " Direction " << ": " << expansionFlags.at(i).at(j - 1) << " at index: " << columnExpansionIndexes.at(i).at(j - 1) << endl;
	//		}
	//	}
	//}

	//cout << "\n";


	// check for "a <= X <= b" rules
	// Condition: index is the same
	//			  Ex: column index = 0
	//			  Data 1 = {0, 1, 1, 1}
	//			  Data 2 = {1, 1, 1, 1}
	//			  Data 3 = {2, 1, 1, 1}
	//			  Max for X1 = 2, min = 0
	//			  Rule: 0 <= x1 <= 2, x2 = 1, x3 = 1, x4 = 1

	//here's the gist the following loop:
	// Look at an expansion. Follow through all of it's expansions (in the same attribute) both up and down until there are not more expansions.
	// while doing so, mark each expansion as being in a rule, so that it is not used again--this eliminates non-encompassing rules. 
	// then make a rule based off of that. 
	// then move onto the next expansion. If that next expansion is already in a rule, then move on again. Keep doing that until you find an expansion not already in a rule
	// then start from step 1. 
	// 
	//loops through all expansions in the unordered_map filled in above
	for (auto it : expansions)
	{
		//it.first represents the key, and it.second represents the value--in this case the current expansion
		Expansion curExpansion = it.second;

		//expansionChain will hold the minimum and maximum expansions
		list<int> expansionChain;
		expansionChain.push_back(curExpansion.rowExpandedfrom);


		tempRule = new rule;
		tempRule->expansionIndex = curExpansion.columnIndex;

		//to stop the while loop below
		bool endExpansionRuleCheck = false;

		//going to loop through all of the expansions that can be expanded from the intitial curExpansion
		while (endExpansionRuleCheck == false)
		{
			//if both bools are true, as seen in the bottom if statement, then the while loop ceases and goes onto the next expansion. 
			bool noMoreUpExpansions = false;
			bool noMoreDownExpansions = false;

			//the index within expansions--uses rowDominantForm
			int currentExpansionIndexUp = expansionChain.front() + (curExpansion.columnIndex * data.at(expansionChain.front()).size() - 1);
			int currentExpansionIndexDown = expansionChain.back() + (curExpansion.columnIndex * data.at(expansionChain.back()).size() - 1);

			//the index within expansions of the next expansion--uses rowDominantForm
			int nextExpansionIndexUp = expansions[currentExpansionIndexUp].expansionIndexExpandedTo.front();
			int nextExpansionIndexDown = expansions[currentExpansionIndexDown].expansionIndexExpandedTo.back();

			//if the next expansion is not already in a rule and it's expansion direction from the rowExpandedFrom is uppward
			//then push it to the front of the expansion chain for the next loop
			if (expansions[currentExpansionIndexUp].expansionDirection.front() == 1 && expansions[nextExpansionIndexUp].alreadyInARule == false)
			{
				expansionChain.push_front(expansions[nextExpansionIndexUp].rowExpandedfrom);
			}
			//otherwise mark that there are no more upward expansions from the intitial curExpansion
			else
			{
				noMoreUpExpansions = true;
			}

			//if the next expansion is not already in a rule and it's expansion direction from the rowExpandedFrom is downward
			//then push it to the back of the expansion chain for the next loop
			if (expansions[currentExpansionIndexDown].expansionDirection.back() == -1 && expansions[nextExpansionIndexDown].alreadyInARule == false)
			{
				expansionChain.push_back(expansions[nextExpansionIndexDown].rowExpandedfrom);
			}
			//otherwise mark that there are no more downward expansions from the intitial curExpansion
			else
			{
				noMoreDownExpansions = true;
			}

			//mark that the used current up and down expansions are already in a rule so they are not used again
			//this eliminates non-encompassing rules
			//for example imagine the rules :
			//	R1: 1 <= X <= 2
			//	R2: 0 <= X <= 3
			//only R2 is needed since it fully covers R1. R1 is not encompasssing
			expansions[currentExpansionIndexUp].alreadyInARule = true;
			expansions[currentExpansionIndexDown].alreadyInARule = true;

			//if there are no more upward or downward expansions then break the while loop
			if (noMoreDownExpansions && noMoreUpExpansions)
			{
				endExpansionRuleCheck = true;
			}
		} // end while loop

		// determine if a rule has been generated
		if (expansionChain.size() > 1)
		{
			// add the data to the temporary rule so that it can be added to the rule vector
			// copy the coordinates into the ruleVals vector

			tempRule->ruleValFront = expansionChain.front();
			tempRule->ruleValBack = expansionChain.back();


			// calculate coverage of the rule
			tempRule->coverageCounter = expansionChain.size();

			// put the class in the rule
			tempRule->classCovered = data.at(tempRule->ruleValFront).at(data.at(tempRule->ruleValFront).size() - 1);

			// put the tempRule into the rule vector
			rules.push_back(*tempRule);

			// clear the tempRule so it can be used again
			clearRule(*tempRule);

			// clear the expansionChain so it can be used again
			expansionChain.clear();
		}
		else
		{
			// if the expansion chain vector is smaller 2, there is no possible less than rule
			// clear the expansion Chain vector
			expansionChain.clear();
		}
	} // end expansion outer for loop

	//counting number of cases per class. Currently only recognizes two classes
	int class1Num = 0;
	int class2Num = 0;
	//determine the column index in the data which holds the class number (the last column in the data)
	int columnCount = data.at(0).size() - 1;
	//checks the last class column for every set (row of data) and increases either class1Num or class2Num depending on if the set is in class 1 or 2
	for (int i = 0; i < data.size(); i++)
	{
		if (data.at(i).at(columnCount) == 1)
		{
			class1Num++;
		}
		else
		{
			class2Num++;
		}
	}

	cout << "Total rules: " << rules.size() << endl;

	// print results
	for (int i = 0; i < rules.size(); i++)
	{
		cout << "Rule " << i + 1 << " : " << endl;

		for (int dataPrint = 0; dataPrint < data.at(0).size() - 1; dataPrint++)
		{
			if (dataPrint == rules.at(i).expansionIndex)
			{
				cout << data.at(rules.at(i).ruleValBack).at(dataPrint) << " <= X" << (dataPrint + 1) << " <= " << data.at(rules.at(i).ruleValFront).at(dataPrint) << endl;
			}
			else
			{
				cout << "X" << (dataPrint + 1) << " = " << data.at(rules.at(i).ruleValFront).at(dataPrint) << endl;
			}
		}

		// print the class the rule covers
		cout << "Rule " << (i + 1) << " covers class " << rules.at(i).classCovered << endl;

		cout << "Number of cases covered: " << rules.at(i).coverageCounter << endl;

		int curClass = rules.at(i).classCovered == 1 ? class1Num : class2Num;
		double classCoveragePercent = ((double)rules.at(i).coverageCounter / curClass * 100);
		cout << "Coverage of class: " << classCoveragePercent << "%" << endl;

		// num cases covered divided by the number of cases in the data
		double allCaseCoveragePercent = ((double)rules.at(i).coverageCounter / data.size() * 100);
		cout << "Coverage of all cases: " << (allCaseCoveragePercent) << "%" << endl;

		// cout << "Number of class 1 cases covered: " << rules.at(i).classCovered << endl;

		cout << endl << endl;
	}

	cout << "You have reached the end" << endl;

} // end of main method
