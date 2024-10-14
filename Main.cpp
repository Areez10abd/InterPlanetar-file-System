
/*
#include <iostream>
using namespace std;
#include "BigInt.h"
#include <cstdlib>
#include <ctime>
#include <opencv2/opencv.hpp>
//#include "DoublyLinkedList.h"
#include "RoutingTable.h"
#include "sha1.hpp"
#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
  
	
	int identifier;
	cout << "Enter Identifier Space: ";
	cin >> identifier;
	CircularLinkedList CL(identifier);
	CL.insert(1);
	CL.deletion(1);
	//CL.deletion(29);
	CL.insert(9);
	CL.insert(4);
	CL.insert(14);
	CL.insert(18);
	CL.insert(11);
	CL.insert(20);
	CL.insert(21);
	CL.insert(28);
	CL.updateRoutingTable();
	CL.display();
	cout << endl;
	CL.displayRoutingTable();
	//CL.traverseRoutingTable(28, 12);
	return 0;
	
//    int choice;
   
    cout << "_|_|_|      _|_|_|      _|_|_|    _|_|_|      _|_|          _|  _|_|_|_|    _|_|_|  _|_|_|_|_|\n";
    cout << "_|    _|  _|            _|    _|  _|    _|  _|    _|        _|  _|        _|            _|    \n";
    cout << "_|    _|    _|_|        _|_|_|    _|_|_|    _|    _|        _|  _|_|_|    _|            _|    \n";
    cout << "_|    _|        _|      _|        _|    _|  _|    _|  _|    _|  _|        _|            _|    \n";
    cout << "_|_|_|    _|_|_|        _|        _|    _|    _|_|      _|_|    _|_|_|_|    _|_|_|      _|    \n";
    cout << "______________________________________________________________________________________________\n" << endl;

    //---------------
    int identifier;
    cout << "Enter Identifier Space: ";
    cin >> identifier;
    CircularLinkedList CL(identifier);

    string ams;
    cout << "Enter the number of active machines: ";
    cin >> ams;
   // int am = stoi(ams);

  //  string ams = to_string(am);

   
    while (BigInt(ams) > CL.totalSize) {
        cout << "Machines should be in between 0 and " << CL.totalSize<< endl;
        cin >> ams;
        //cout << CL.totalSize << ' ' << ams << endl;
    }
    

    int choice;
    cout << "1. Assign ids manually?\n2. Assign ids automatically(Any other key)?\n";
    cin>>choice;

    if (choice == 1) {
        for (BigInt i(0); i < BigInt(ams); i++) {
            string id;
          
            cout << "Enter id for " << i + 1 << " machine: ";
            cin >> id;
              BigInt s(id);
            while (s > CL.totalSize|| CL.nodealreadyexists(id)) {
                if (s > CL.totalSize) {
                    cout << "Enter values between 0 and " << CL.totalSize - 1 << endl;
                }
                if(CL.nodealreadyexists(id)) {
                    cout << "This machine is already active.";
                    cin >> id;
                    continue;
                }
                cin >> id;

                //---
                s.BigSize = 0;
                while (id[s.BigSize] != '\0')
                {
                    s.BigSize++;
                }
                s.Big = new char[s.BigSize + 1];
                s.Big[s.BigSize] = '\0';
                for (int copy = 0; copy < s.BigSize; copy++)
                {
                    s.Big[copy] = id[copy];
                }

                //---
            }
          
            CL.insertion(id);
        
        }
    }
    else {
        srand(time(0));
        for (BigInt i(0); i < BigInt(ams); i++) {   
            //choice = rand() % am;
            //while (CL.nodealreadyexists(choice)) {
              //  choice = rand() % am;
            //}
            //cout << choice << ' ';
            CL.insertion(i);
        }
        cout << endl;
    }

    //---------------

    cout << " __       __  ________  __    __  __    __  \n";
    cout << "|  \\     /  \\|        \\|  \\  |  \\|  \\  |  \ \n";
    cout << "| $$\\   /  $$| $$$$$$$$| $$\\ | $$| $$  | $$ \n";
    cout << "| $$$\\ /  $$$| $$__    | $$$\\| $$| $$  | $$ \n";
    cout << "| $$$$\\  $$$$| $$  \\   | $$$$\\ $$| $$  | $$ \n";
    cout << "| $$\\$$ $$ $$| $$$$$   | $$\\$$ $$| $$  | $$ \n";
    cout << "| $$ \\$$$| $$| $$_____ | $$ \\$$$$| $$__/ $$ \n";
    cout << "| $$  \\$ | $$| $$     \\| $$  \\$$$ \\$$    $$ \n";
    cout << " \\$$      \\$$ \\$$$$$$$$ \\$$   \\$$  \\$$$$$$  \n";
    do {
        cout << "____________________________________________\n";
        cout << "* 1. xxxxxxxxxxx                           *\n";
        cout << "* 2. xxxxxxxxxxx                           *\n";
        cout << "* 3. Print Btree of any machine            *\n";
        cout << "* 4. Insert file                           *\n";
        cout << "* 5. Remove data and print updated B-tree  *\n";
        cout << "* 6. Print routing table of machines       *\n";
        cout << "* 7. Add new machine on the fly            *\n";
        cout << "* 8. Remove machine on the fly             *\n";
        cout << "* 0. Exit                                  *\n";
        cout << "____________________________________________\n";

        cout << "Enter your choice: ";
        cin >> choice;
        string path,mid;
        int hval;
        switch (choice) {
        case 1:
            // specifyNumberOfMachines();
            break;
        case 2:
            //specifyIdentifierSpace();
            break;
        case 3:
            //manuallyAssignIds();
            cout << "Enter id of machine whose btree you want to print: ";
            cin >> mid;
            CL.displaymybtree(BigInt(mid));
            break;
        case 4:
            //insertFiles();
        {
            //-----
            cout << "Enter path of file: ";
            cin >> path;
          //  cv::Mat image = cv::imread(path);

            //namedWindow("image", WINDOW_NORMAL);

            // Display the image in a window
           // cv::imshow("image", image);

            // Wait for a key press and then close the window
            //cv::waitKey(0);
            //cv::destroyAllWindows();

            //-----
            
            CL.addfile(path);
            break;
        }
        case 5:
            //removeData();
            cout << "Enter hash value of file you want to remove: ";
            cin >> hval;
            break;
        case 6:
            //printRoutingTable();
            CL.updateRoutingTable();
            CL.display();
            cout << endl;
            CL.displayRoutingTable();
            break;
        case 7:
        {
            //addNewMachine();
          //-------------------------
            string i;
            cout << "Enter id for machine: ";
            cin >> i;
            BigInt s2(i);
            while (s2 > CL.totalSize || CL.nodealreadyexists(i)) {
                if (s2 > CL.totalSize) {
                    cout << "Enter values between 0 and " << CL.totalSize - 1 << endl;
                }
                if (CL.nodealreadyexists(i)) {
                    cout << "This machine is already active.";
                    cin >> i;
                    continue;
                }
                cin >> i;

                //---
                s2.BigSize = 0;
                while (i[s2.BigSize] != '\0')
                {
                    s2.BigSize++;
                }
                s2.Big = new char[s2.BigSize + 1];
                s2.Big[s2.BigSize] = '\0';
                for (int copy = 0; copy < s2.BigSize; copy++)
                {
                    s2.Big[copy] = i[copy];
                }

                //---
            }
            CL.insertion(i);
        }
        //----------------------------
            break;
        case 8:
        {
            string rm;
            cout << "Enter machine id you want to remove: ";
            cin >> rm;
            CL.deletion(BigInt(rm));

        }
            //removeMachine();
            break;
        case 0:
            cout << "Exiting the program\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

*/

#include <iostream>
using namespace std;
#include "BigInt.h"
#include <cstdlib>
#include <fstream>
#include <ctime>
#include "RoutingTable.h"
#include "sha1.hpp"
#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    cout << "_|_|_|      _|_|_|      _|_|_|    _|_|_|      _|_|          _|  _|_|_|_|    _|_|_|  _|_|_|_|_|\n";
    cout << "_|    _|  _|            _|    _|  _|    _|  _|    _|        _|  _|        _|            _|    \n";
    cout << "_|    _|    _|_|        _|_|_|    _|_|_|    _|    _|        _|  _|_|_|    _|            _|    \n";
    cout << "_|    _|        _|      _|        _|    _|  _|    _|  _|    _|  _|        _|            _|    \n";
    cout << "_|_|_|    _|_|_|        _|        _|    _|    _|_|      _|_|    _|_|_|_|    _|_|_|      _|    \n";
    cout << "______________________________________________________________________________________________\n" << endl;

    //---------------
    int identifier;
    cout << "Enter Identifier Space: ";
    cin >> identifier;
    CircularLinkedList CL(identifier);

    string ams;
    cout << "Enter the number of active machines: ";
    cin >> ams;
    // int am = stoi(ams);

   //  string ams = to_string(am);


    while (BigInt(ams) > CL.totalSize) {
        cout << "Machines should be in between 0 and " << CL.totalSize << endl;
        cin >> ams;
        //cout << CL.totalSize << ' ' << ams << endl;
    }


    int choice;
    cout << "1. Assign ids manually?\n2. Assign ids automatically(Any other key)?\n";
    cin >> choice;

    if (choice == 1) {
        for (BigInt i(0); i < BigInt(ams); i++) {
            string id;

            cout << "Enter id for " << i + 1 << " machine: ";
            cin >> id;
            BigInt s(id);
            while (s > CL.totalSize || CL.nodealreadyexists(id)) {
                if (s > CL.totalSize) {
                    cout << "Enter values between 0 and " << CL.totalSize - 1 << endl;
                }
                if (CL.nodealreadyexists(id)) {
                    cout << "This machine is already active.";
                    cin >> id;
                    continue;
                }
                cin >> id;

                //---
                s.BigSize = 0;
                while (id[s.BigSize] != '\0')
                {
                    s.BigSize++;
                }
                s.Big = new char[s.BigSize + 1];
                s.Big[s.BigSize] = '\0';
                for (int copy = 0; copy < s.BigSize; copy++)
                {
                    s.Big[copy] = id[copy];
                }

                //---
            }

            CL.insertion(id);

        }
    }
    else {
        srand(time(0));
        for (BigInt i(0); i < BigInt(ams); i++) {
            //choice = rand() % am;
            //while (CL.nodealreadyexists(choice)) {
              //  choice = rand() % am;
            //}
            //cout << choice << ' ';
            cout << i << " ";
            CL.insertion(i);
        }
        cout << endl;
    }
    CL.updateRoutingTable();
    //---------------

    cout << " __       __  ________  __    __  __    __  \n";
    cout << "|  \\     /  \\|        \\|  \\  |  \\|  \\  |  \ \n";
    cout << "| $$\\   /  $$| $$$$$$$$| $$\\ | $$| $$  | $$ \n";
    cout << "| $$$\\ /  $$$| $$__    | $$$\\| $$| $$  | $$ \n";
    cout << "| $$$$\\  $$$$| $$  \\   | $$$$\\ $$| $$  | $$ \n";
    cout << "| $$\\$$ $$ $$| $$$$$   | $$\\$$ $$| $$  | $$ \n";
    cout << "| $$ \\$$$| $$| $$_____ | $$ \\$$$$| $$__/ $$ \n";
    cout << "| $$  \\$ | $$| $$     \\| $$  \\$$$ \\$$    $$ \n";
    cout << " \\$$      \\$$ \\$$$$$$$$ \\$$   \\$$  \\$$$$$$  \n";
    do {
        cout << "____________________________________________\n";
        cout << "* 1. Refresh                               *\n";
        cout << "* 2. Search for file                       *\n";
        cout << "* 3. Print Btree of any machine            *\n";
        cout << "* 4. Insert file                           *\n";
        cout << "* 5. Remove data                           *\n";
        cout << "* 6. Print routing table of machines       *\n";
        cout << "* 7. Add new machine on the fly            *\n";
        cout << "* 8. Remove machine on the fly             *\n";
        cout << "* 0. Exit                                  *\n";
        cout << "____________________________________________\n";

        cout << "Enter your choice: ";
        cin >> choice;
        string path, mid;
        int hval;
        switch (choice) {
        case 1:
            // specifyNumberOfMachines();
            break;
        case 2:
            //specifyIdentifierSpace();
        {

            //---

            int type;
            int hash;
            string hashStr;
            string path;
            cout << "Type: 1- String, 2- Int: ";
            cin >> type;
            switch (type)
            {
            case 1:
                cout << "Enter hash string: ";
                cin >> hashStr;
                path=CL.search(hashStr);
                break;
            case 2:
                cout << "Enter hash integer: ";
                cin >> hash;
                path=CL.search(hash);
                break;
            default:
                cout << "Invalid Input";
            }


            //---

       
            if (path != "0") {
                // Check if the file has a .txt extension using string manipulation
                std::size_t dotPos = path.find_last_of('.');
                if (dotPos != std::string::npos && path.substr(dotPos) == ".txt") {
                    std::ifstream inputFile(path);

                    if (!inputFile.is_open()) {
                        std::cerr << "Error opening file: " << path << std::endl;
                        return 1;
                    }

                    std::string line;
                    while (std::getline(inputFile, line)) {
                        std::cout << line << std::endl;
                    }

                    inputFile.close();
                }
                else {
                    cv::Mat image = cv::imread(path);

                    namedWindow("image", WINDOW_NORMAL);

                    //  Display the image in a window
                    cv::imshow("image", image);

                    // Wait for a key press and then close the window
                    cv::waitKey(0);
                    cv::destroyAllWindows();

                }
            }

            
        }
            break;
        case 3:
            //manuallyAssignIds();
            cout << "Enter id of machine whose btree you want to print: ";
            cin >> mid;
            CL.displaymybtree(BigInt(mid));
            break;
        case 4:
            //insertFiles();
            cout << "Enter path of file: ";
            cin >> path;
            CL.addfile(path);
            break;
        case 5:
            //removeData();
             //---
        {
            int type;
            int hash;
           
                cout << "Enter hash integer: ";
                cin >> hash;
                CL.removefile(hash);
              
      
            break;

        }
            //---
        
        case 6:
            //printRoutingTable();
            CL.display();
            cout << endl;
            CL.displayRoutingTable();
            break;
        case 7:
        {
            //addNewMachine();
          //-------------------------
            string i;
            cout << "Enter id for machine: ";
            cin >> i;
            BigInt s2(i);
            while (s2 > CL.totalSize || CL.nodealreadyexists(i)) {
                if (s2 > CL.totalSize) {
                    cout << "Enter values between 0 and " << CL.totalSize - 1 << endl;
                }
                if (CL.nodealreadyexists(i)) {
                    cout << "This machine is already active.";
                    cin >> i;
                    continue;
                }
                cin >> i;

                //---
                s2.BigSize = 0;
                while (i[s2.BigSize] != '\0')
                {
                    s2.BigSize++;
                }
                s2.Big = new char[s2.BigSize + 1];
                s2.Big[s2.BigSize] = '\0';
                for (int copy = 0; copy < s2.BigSize; copy++)
                {
                    s2.Big[copy] = i[copy];
                }

                //---
            }
            CL.insertion(i);
            CL.updateRoutingTable();
            break;
        }
        //----------------------------

        case 8:
        {
            string rm;
            cout << "Enter machine id you want to remove: ";
            cin >> rm;
            CL.deletion(BigInt(rm));
            CL.updateRoutingTable();
            break;
        }
        //removeMachine();
        break;
        case 0:
            cout << "Exiting the program\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}