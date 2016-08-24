#include <iostream>
#include <string>
#include <fstream>


using namespace std;

int main() {

	char choice = NULL;							//cannot use tolower on a string
	string message;
	string codeword = "";						//can't check an unitialised string
	int numAdd = 0;
	int key = 0;
	ofstream outFile;
	ifstream inFile;


	cout << endl << "Welcome to Codebreaker 3000, a 'Sate of the art' 32 bit encrypter.\n";

	while (choice != 'q')						//loops back to the main options, while choice value is not 'q'
	{
		cout << "\nWill you be [E]ncrypting / [D]ecrypting, or [Q]uit to exit ? ";

		cin >> choice;
		choice = tolower(choice);				//iterates through characters of sting, converting each to lower case

		if (choice == 'e')
		{
			cout << "\nYou have chosen Encryption. \nPlease enter the message to encrypt: ";

			cin.ignore();						//clears the cin buffer
			getline(cin, message);				//reads console input with no delimiters, and assigns to string variable

			cout << "\nThe encryption key is devised from any 4 digit codeword of your choice.";
			while (codeword.length() != 4)		//nested while loop with boolean expression. Loops back to codeword input request
			{
				cout << "\nPlease enter your desired codeword : ";

				cin >> codeword;
				if (codeword.length() != 4)		//validates codeword length
				{
					cout << "\n\nCodeword must be 4 digits...";
				}
			}

			//Encryption Key Generator

			for (int i = 0; i < codeword.length(); i++)		//for loop increments value of vaiable i once per iteration if i is less than codeword length
			{
				key += codeword[i] - 96;				//assigns value of key + value of codeword character at index [i] - 96 to current value of key
			}
			while (key > 9)								//loops method until value of key is equal to, or less than 9
			{
				numAdd = key % 10;						//assigns remainder to numAdd after dividing by 10
				key = key / 10;							//divides key by 10 and asigns truncated int value to key
				key += numAdd;							//adds values of key and numAdd, then assigns sum to key
			}

			//cout << "The encryption key is " << key << endl << endl;		//This line tests the result of the encryption key generator

			for (int i = 0; i < message.length(); i++)		//for loop increments value of vaiable i once per iteration if i is less than message length
			{
				//message[i] += key;
				if ((message[i] += key) > 126) //Current index of message is incremented by the key value in the comparison statement
				{
					message[i] -= 95;			//subtracts 95 from ascii value at current index of message string, then reassigns same index
				}

			}

			cout << "Your encrypted message (between the << >>) now reads:\n\n<<" << message << ">>\n\n";
			cout << "Would you like to save this message to a file Y/N ? ";

			cin >> choice;
			choice = tolower(choice);

			if (choice == 'y')
			{
				outFile.open("codebreaker.txt");
				outFile << message << endl;
				outFile.close();

				cout << "\nAll done...\n";
			}

			else if (choice == 'n')
			{
				cout << "Okay, nothing was saved." << endl << endl;
				system("pause");
			}

			else
			{
				cout << "Sorry, you entered something else." << endl << endl;
				system("pause");
			}

		}

		else if (choice == 'd')
		{
			cout << "\nYou have chosen Decryption. \n\nDecrypt from the codebreaker file Y/N ? ";

			cin >> choice;
			choice = tolower(choice);
				
			if (choice == 'y')
			{
				inFile.open("codebreaker.txt");
				inFile >> message;
			}
			else if (choice == 'n')
			{

				cout << "\nPlease enter the message to decrypt: ";

				cin.ignore();
				getline(cin, message);
			}

			cout << "\nPlease enter your decryption codeword: ";

			cin >> codeword;

			for (int i = 0; i < codeword.length(); i++)
			{
				key += codeword[i] - 96;
			}

			while (key > 9)
			{
				numAdd = key % 10;
				key = key / 10;
				key += numAdd;
			}

			for (int i = 0; i < message.length(); i++)
			{
				//message[i] += key;
				if ((message[i] -= key) < 32) //Current index of message is incremented by the key value in the comparison statement
				{
					message[i] += 95;
				}

			}
			cout << "\nYour decrypted message (between the << >>) is:\n\n<<" << message << ">>\n\n";
			cout << "Would you like to save the decrypted message to file Y/N ? ";
			cin >> choice;
			choice = tolower(choice);

			if(choice == 'y')
			{
				outFile.open("codebreaker.txt");
				outFile << message << endl;
				outFile.close();

				cout << "\nAll done...\n\n";
			}
			else if (choice == 'n')
			{
				cout << "\nOkay, nothing was saved.\n\n";
			}
		}
	}

	return 0;
}


