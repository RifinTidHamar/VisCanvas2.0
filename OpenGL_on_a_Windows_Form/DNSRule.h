#include <vector>

using namespace std;

public class DNSRule
{
public:
	
	//Consturctors:
	DNSRule();

	//Methods:
	void addAttribute(double);
	void addCoordinate(int);
	double getMostRecentAttribute();

	//Getters and Setters:
	void setAttributesUsed(vector<double>);
	vector<double> getAttributesUsed();
	void setNegatedAttributesIndexes(vector<double>);
	vector<double> getNegatedAttributesIndexes();
	void setCoordinatesUsed(vector<int>);
	vector<int> getCoordinatesUsed();
	void setCasesUsed(vector<int>);
	vector<int> getCasesUsed();
	void setCorrectCases(int);
	int getCorrectCases();
	void setIncorrectCases(int);
	int getIncorrectCases();
	void setTotalCases(int);
	int getTotalCases();
	void setRuleClass(int);
	int getRuleClass();
	void setHasChanged(bool);
	bool getHasChanged();
	void setPrecision(double);
	double getPrecision();
	void setTotalCoverage(double);
	double getTotalCoverage();

	//public variables; Why would you need to make a getter and setter for a variable? I might as well just use the variable 
	//if I can still read and modify it
	vector<int> orIndexes; //this will have the indexes of the used Attributes which are OR, for example: x1 = 5 or x1 = 2
	vector<int> andIndexes;
	vector<double> negatedAttributesIndexes; //list of negated attributes.
	bool combinedRule = false;
	bool markedForErasal = false;

private:

	vector<double> attributesUsed; //list of attributes used.
	vector<int> coordinatesUsed; //list of coordinates used.
	vector<int> casesUsed; //list of cases used.
	int correctCases; //Total correct cases in the rule.
	int incorrectCases; //Total incorrect cases in the rule.
	int totalCases; //Total cases in the rule.
	int ruleClass; //the class the rule predicts.
	bool hasChanged = false; //records if a rule has been changed between coordinates.
	double precision;
	double totalCoverage;

};//End of class.