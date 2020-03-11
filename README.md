# Coins
### What the program does
Coins takes an input of names and change from the coins.txt file and then reads them as a string and int into a struct called people. It then takes an input from coinTypes.txt, that checks for "COINS" then a count int, then stores each other int into an array to be used as coin amounts. The user can enter 1 to compare a name to the names entered from coins.txt, or 2 to exit the program and print any names previously entered into a change.csv file. If they compare a name and the name is correct, it will print the name, change amount and the most efficent coin distribution that person should recieve.

#### Changes
- None

#### Currently Known Bugs
- If a char letter or symbol is entered when prompt for 1 or 2, it will go to the default case of the switch case and the program will close with an error message
