/* @brief Assignment from chapter 6 exercise 6.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Write a program that checks if a sentence is correct according to the
 * “English” grammar in §6.4.1. Assume that every sentence is terminated by
 * a full stop (.) surrounded by whitespace. For example, "birds fly but the
 * fish swim ." is a sentence, but "birds fly but the fish swim" (terminating dot
 * missing) and "birds fly but the fish swim." (no space before dot) are not. For
 * each sentence entered, the program should simply respond “OK” or “not
 * OK.” Hint: Don’t bother with tokens; just read into a string using >>.
 *
 * NOTE: See the "EnglishGrammar.md file for the grammar overview.
 * NOTE: THis program is written with recursive functions. Pay attention to the
 * chain of called functions to get a better understanding of the application.
 *
 * Todo:
 * - Does not finish an analysis if no '.' was entered by the user. E.g. "fish swim"
 * does not return an error.
 * - Does not work well, e.g. "fish the swim ." is "OK", which is obviously not ok.
 */

#include "../std_lib_facilities.h"

/* @brief Checks if input vector is not empty.
 * @input inputWords	A vector of strings
 * @output hasContent	True, if inputVector contains elements
 * */
bool hasContent( vector<string> inputVector)
{
	cout << "DEBUG - hasContent() - inputVector.size()= " << inputVector.size() << endl;
	if (inputVector.size() > 0)
		return true;
	else
		return false;
}

/* @brief Takes an input vector, removes the first element, and returns
 * 		the "remainder" of the vector.
 * @input inputVector 	A vector of strings with more than one element
 * @output vectorSubset A vector of strings that misses the zero element
 * 		of the inputVector. E.g., inputVector = {"a", "b"}
 * 		--> vectorSubset = {"b"}
 * */
vector<string> getSubsetVector( vector<string> inputVector)
{
	//PRE-CONDITION: There need to be at least two elements in the input vector,
	//			because the first accessed element is at index "1".
	if (inputVector.size() < 1)
	{
		throw runtime_error("getSubsetVector() cannot return a subset of vectors, because the input vector contains no element.");
		return {"ERROR in getSubsetVector()"};
	}
	vector<string> vectorSubset {};
	// save all elements after the zero element. --> "i = 1"
	for (int i = 1; i < inputVector.size(); i++)
	{
		vectorSubset.push_back(inputVector[i]);
	}
	return vectorSubset;
}

bool sentence( vector<string> inputWords); // definition needed, because of the recursive structure in this solution.

/* @brief Check if the first word in the input vector is a conjunction or a '.'
 * @input inputWords 	A string of the English language
 * @output isConjunction	Returns true, if the inputWord at the first element is a conjunction, AND
 * 							whether the next words are valid English Grammar.*/
bool conjunction( vector<string> inputWords)
{
	bool isConjunction{false}; // A flag that shows if inputWord at the first element is a conjunction, AND
	 	 	 	 	 	 	   // whether the next words are valid English Grammar.*/
	bool isDot{false};	// Shows that a sentence is at its end
	bool isSentence{true};	// Respects the grammar "Sentence Conjunction Sentence".
							//"true" by default to consider the special case '.'
	vector<string> inputWordsSubset;
	if (inputWords.size() > 1)
	{
		inputWordsSubset = getSubsetVector( inputWords);
		isSentence = sentence( inputWordsSubset ); // check if the following words are valid English grammar
	}

	vector<string> conjunctions = {"and", "or", "but"};
	// check if the first word is a conjunction
	for (string s: conjunctions)
	{
		if (inputWords[0] == s)
			isConjunction = true;
	}
	//Special case: '.' allow the dot to show that the sentence is at its end.
	if ( (inputWords[0] == ".") && (inputWords.size() == 1) )
		isDot = true;
	else if( (inputWords[0] == ".") && (inputWords.size() > 1))
	{
		cerr << "ERROR: Wrong grammar. Please finish a sentence with a '.',  with a preceding ' '(space), and enter only one sentence at a time." << endl;
		isDot = false; // wrong grammar, because it is expected that only one sentence is analyzed
	}

	// Attention: Logic needs to be incorporated, because of the special case '.'
	if (inputWords.size() == 1)// If there is only one element left, then it needs to be the isDot-result.
	{
		if (!isDot) // provide some user information in error case.
			cerr << "ERROR: Wrong grammar. Please finish your sentence with a '.', with a preceding ' '(space)." << endl;
		return isDot;
	}
	else
		return (isConjunction && isSentence);
}

/* @brief Check if the first word in the input vector is a verb
 * @input inputWords 	A string of the English language
 * @output isVerb 		Returns true, if the inputWord at the first element is a verb, AND
 * 						whether the next words follow the English Grammar rules.*/
bool verb( vector<string> inputWords)
{
	bool isVerb {false}; // True, if the inputWord at the first element is a verb, AND
	 	 	 	 	 	 // whether the next words follow the English Grammar rules.
	bool isConjunction {false};
	vector<string> verbs = {"rules", "fly", "swim"}; // The accepted verbs
	vector<string> inputWordsSubset;
	inputWordsSubset = getSubsetVector( inputWords );
	isConjunction = conjunction( inputWordsSubset);
	// check if the input vector is a known verb in the first element.
	for (string s: verbs)
	{
		if (inputWords[0] == s)
			isVerb = true;
	}
	// now consider, that the verb is followed by valid English grammar
	if (isConjunction)
	{
		// continue. Important: Do NOT overwrite the previous "isVerb" analysis.
	}
	else // The words after the verb are invalid English grammar
		isVerb = false;
	return isVerb;
}

/* @brief Check if the first word in the input vector is a noun
 * @input inputWords 	A string of the English language
 * @output isNoun 		Returns true, if the inputWord at the first element is a noun, AND
 * 						whether the next words follow the English Grammar rules.
 * */
bool noun( vector<string> inputWords)
{
	bool isVerb {false}; // Returns true if the given string is a known verb
	vector<string> inputWordsSubset;
	inputWordsSubset = getSubsetVector(inputWords);
	isVerb = verb( inputWordsSubset );
	bool isNoun {false}; // Returns true, if the inputWord at the first element is a noun, AND
	 	 	 	 	 	 // whether the next words follow the English Grammar rules.
	vector<string> nouns = {"birds", "fish", "C++"}; // The accepted nouns
	// check if the first word in inputWords is a known noun:
	for (string s: nouns)
	{
		if (inputWords[0] == s)
			isNoun = true;
	}
	return isNoun;
}

/* @brief Check if the first words in the input vector is an English article, e.g. 'the'.
 * @input inputWords	A sentence of the English language.
 * @output isSentence	Returns true, if the inputWord at the first element is a noun, AND
 * 						whether the next words follow the English Grammar rules.
 * */
bool article( vector<string> inputWords)
{
	// The challenge with an article is that it can (!) be used in front of a noun,
	// but it does not necessarily have to!
	bool isArticle{false}; // returns true if the first word in the input Words is an article
	bool isSentence{false};		// returns true if the following words follow the "English" grammar rules.
	vector<string> articles = {"the"}; // The accepted articles

	// check if the first word in inputWords is an article
	for (string s : articles)
	{
		if (inputWords[0] == s)
		{
			isArticle = true;
			isSentence = sentence( getSubsetVector(inputWords) ); // Check for a noun in the following word, because an article was found.
			return ( isArticle && isSentence );// This is the easy case that an article was found
		}
	}

	// Now deal with the case that an article was not found, but still the inputWords is a
	// "correct" English sentence (E.g. "birds fly but the fish swim .")
	if (isArticle == false)
	{
		// Check if the inputWords are a "correct" English sentence, and then compare to
		// the previous "isArticle" result.
		isSentence = noun(inputWords);
	}

	// Now try to solve the contradiction between isArticle and isSentence. isSentence is dominant,
	// because it does not matter if "swim fish ." or "fish swim ." is entered, since an article was not entered.
	if (isSentence)
		return true;
	else
		return false;
}

/* @brief Check if an input of strings represents an English sentence.
 * @input inputWords	A sentence of the English language as defined in the EnglishGrammar.md-file.
 * @output isSentence	A bool that symbolizes correct English grammar. Equals "true", if grammar is correct.
 * */
bool sentence( vector<string> inputWords)
{
	// PRE-CONDITION: inputWords needs a size larger than 0
	if ( hasContent( inputWords ) )
	{
		// continue.
	}
	else
	{
		throw runtime_error("sentence() received an empty input.");
		return 0; //
	}
	// PRE-CONDITION: inputWords needs at least a noun, a verb, and a '.'
	if (inputWords.size() < 3) return false;

	bool isSentence{false}; // A flag that symbolizes correct grammar (true).
	isSentence = article( inputWords );
	return isSentence;
}

int main()
{
	cout << "This application is supposed to check for 'correct English grammar'." << endl;
	cout << "Please type in a valid English sentence finished by a dot '.', and the" << endl;
	cout << "application will check the grammar." << endl;
	cout << "You can exit the application by pressing 'Ctrl' + 'z' " << endl;
	cout << "Please type in your English sentence:" << endl;

	bool isSentence {false};	// A flag that symbolizes correct grammar (true).
	vector<string> words; // saves the user's input

	// allow to run the program many times
	while (true)
	{
		//collect the words in a vector
		for (string temp; cin >> temp;)
		{
			words.push_back(temp);
			if (temp == ".") break; // Sentence comes to an end with the '.'
			if ( temp[temp.length()] == '.') break; // Sentence comes to an end with the '.'
			cout << "DEBUG - temp[temp.length()]: " << temp[temp.length()] << endl;
		}
		isSentence = sentence(words);
		if (isSentence) cout << "--- OK" << endl;
			else cout << "--- Not OK" << endl;
		cout << "Please type in a new sentence or exit the application with 'Ctrl + Z':" << endl;
		words.clear(); // reset the string, before the next sentence is entered.
	}

	keep_window_open();
	return 0;
}
