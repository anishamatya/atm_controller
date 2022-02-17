# atm_controller
ATM controller assignment

# Background:
This program was built and tested using mingw32-gcc.exe (tdm-1) 5.1.0 in Codeblocks. This can be built in Windows CMD command line using the .bat script file.

# How to build
Open a cmd terminal in windows, go the project directory and run build_run.bat

# How to use
At start the program will give two options. Enter 0 to run the ATM controller, or 1 to run tests.
![01_enter_atm_mode](https://user-images.githubusercontent.com/99900985/154531327-13d49f63-7678-448f-8626-316021fd2d26.jpg)
Comments in the prompt will explain which option will do what operation

Inserting an ATM card is simulated by entering an 8 character alphanumeric string. This alphanumeric string is compared against the record inside bank_rec_bin.dat, which represents the records in the bank. Is the alphanumeric string is in this record, the ATM card is considered to be valid. Otherwise the user is prompted to insert ATM card again.

If a valid ATM card is found, enter the 4 digit pin number. If PIN number is not correct the operation will be aborted and user will be asked to enter ATM card again. If it is correct user will be prompted to select his account (either a checking account or saving account)

Once a valid option for account is selected the user will be prompted to select an operation to be perfomred (See Balance/Deposit/Withdraw)

A sample sequence of commands showing ATM insertion -> PIN entry -> Account selection -> view balance operation is shown below:
![02_sample_sequence](https://user-images.githubusercontent.com/99900985/154532610-2224a29c-d658-438e-acc5-bb2397ed9e67.jpg)

A deposit or withdraw operation will alter the total balance for that account in the bank's record. three operations can be performed on the checking account (see balance/deposit/withdraw) while only two operations can be performed in the savings account (see balance/deposit)

# How to test
Operation of the ATM controller can be tested for various types of input by using a sequence of inputs recorded in the atm_test_input.txt file. To run tests, select option 1 at the beginning of the program
![03_test_menu](https://user-images.githubusercontent.com/99900985/154533286-0f7862d1-a9f6-4f35-a284-995b3015359e.jpg)
For convenience of the tester the test menu also contains an option to view the entire record of the bank (this feature is not part of the ATM controller program and is purely a debugging and testing feature. IF feature can be easily removed from the source code if needed). This will show the entire content of bank_rec_bin.dat in text form. Select option 1 in this menu to run the automated tests. In the tests a sequence of inputs will be taken from the file atm_test_input.txt, they will be supplied to the ATM controller interface and the ATM controller's output and the expected output will be displayed. A screenshot of a sample test run is shown below:  

![04_test_run](https://user-images.githubusercontent.com/99900985/154534078-13d6a8dc-3f0d-4d1b-8496-657b3be3cccf.jpg)

# Assumptions:
1) The ATM controller program is assumed to run forever. This means once started the ATM controller will not exit. Error conditions such as invalid ATM card or invalid PIN number will return the user back to the first menu (enter ATM card)
2) Validation of user inputs is not done. For example, it is expected that user will enter an 8 character alphanuric string to simulate ATM card, or exactly 4 numeric digits for the PIN.
3) It is assumed that the ATM machine will not run out of cash. Users will be continuously able to withdraw from the ATM as long as they have enough balance in their own account

# Bank record format
Bank records are stored in the binary file bank_rec_bin.dat. The record format uses the struct BankAccStructure defined in bank_function.h. The first integer in the binary file represents the number of records. This is followed by the actual record data. This is stored in the following order:
1) 8 character alphanumeric string representing ATM card
2) character string for first name
3) character string for last name
4) long integer for checking account number
5) long integer for checking account balance
5) long integer for savings account number
6) long integer for savings account balance
7) integer for PIN

bank_rec_bin.dat contains the PIN number but the bank API, defined in bank_function.c, will not return the pin number to the ATM controller function defind in main.c. The bank api will only let the ATM controller know whether the supplied PIN is correct or not.

# test file format
User inputs for test are stored in the text file atm_test_input.txt. The test inputs follow the format shown in the struct TestCaseStruct defined in main.c. The fist entry in the file shows number of test cases. The test instructions are stored in the following order:
1) ATM card alphanumeric string
2) PIN
3) Account type (checking = 0, savings = 1)
4) Account operation (see balance = 0, deposit = 1, withdraw = 2)
5) Integer number for deposit/withdraw amount
6) Text string for comment, to show expected output of test

# extra features
A tool to generate a bank accoutn record file (bank_rec_bin.dat) is given in /tool. Compile tihs tool using /tool/build_tool.bat. The on screen instructions will explain which bank record entry is being entered. The first input should be the number of records you wish to enter, which will be followed by the actual bank record entries.

For convenience, a pristine copy of bank_rec_bin.dat that I used for my tests is given in /bank_record_orig. /bank_record_orig/bank_rec_txt_ver.txt shows the data in bank_rec_bin.dat. These files are only provided for reference and convenience.



