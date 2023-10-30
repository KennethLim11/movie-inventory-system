//Kenneth Lim
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;

class Video{ //class that handles the videos
	public: 
	    int VideoId;
	    string MovieTitle;
	    string Genre;
	    string Production;
	    int Copies;
	    int size = 0;
	    Video* next;
	    void readVideoFile();
	    void insertVideo();
	    void showVideoDetails();
	    void checkVideoAvailability();
	    void displayAllVideos();
	    int extractIntegerWords(string str);
	    string eraseMovieAndGenre(string str);
	    string eraseProduction(string str);
};

class Customer{//class that handles the customers
	public: 
	    int CustomerId;
	    string CustomerName;
	    string Address;
	    Customer* next;
	    int sizeC = 0;
	    void enqueueCustomer(int size, int add);
	    int readCustomer();
	    int extractIntegerWords(string str);
	    void displayAllCustomer();
	    string eraseName(string str);
	    string eraseAddress(string str);
};

class RentedVideo{//class that handles the videos rented by the customers
	public: 
	    int RentedVideoId;
	    RentedVideo* next;
};

class CustomerChild: public Customer{//class that handles the customers who rented videos
	public: 
	    int RentId;//customer id
	    void readCustomerRent();
	    RentedVideo* RentVideoPtr;//pointer to rented video linked list(stack)
	    CustomerChild* next;
};

Video* VideoHead = NULL;//pointer to start of video linked list
Customer* front = NULL;//pointer to start of customer queue
Customer* rear = NULL;//pointer to the last customer in queue
CustomerChild* ChildHead = NULL;//pointer to start of customers who rented videos

//function that adds rented videos of a customer to the stack
void push(int x, RentedVideo* &ptr){
    RentedVideo* temp = new RentedVideo();
    temp -> RentedVideoId = x;
    temp -> next = ptr;
    ptr = temp;
}

//function that deletes rented videos of a customer
void pop(RentedVideo* &ptr){
    RentedVideo* temp;
    if(ptr == NULL)
        return;
    temp = ptr;//points to first node in the list
    ptr = ptr->next;
    delete temp;
}

//function that deletes the id of customer who rented video
void removeRentId(int p){
	CustomerChild* temp1 = ChildHead;
	if(p == 1){
		ChildHead = temp1 -> next;
		delete(temp1);
		return;
	}
	for (int i = 0; i < p-2; i++){
		temp1->RentId;
		temp1 = temp1->next; }
	
	CustomerChild* temp2 = temp1 -> next;
	temp1 -> next = temp2 -> next;
	delete(temp2);
	
}

//function that allows customer to rent a video
void rentVideo(){
    int video_id;
    char answer;
    bool b = false, b2 = false;
    Customer* tempCustomer = front;
    CustomerChild* tempChild = new CustomerChild();
    tempChild -> next == NULL;
    tempChild -> RentVideoPtr == NULL;
    system("cls");
    cout << "Enter customer ID: ";
    cin >> tempChild -> RentId; cin.ignore();
    
    while(tempCustomer != NULL){ //iteration for customer queue
        if((tempChild -> RentId) == (tempCustomer -> CustomerId)){ //check if customer id is equal to rent id
        	b = true;
            cout << "Name: " << tempCustomer -> CustomerName << endl;
            cout << "Address: " << tempCustomer -> Address << endl;
            do{
                cout <<"\nEnter video to rent: ";
                cin >> video_id;
                Video* tempVideo = VideoHead; //declares new video pointer
                while(tempVideo != NULL){ //iteration for movies
                    if(video_id == tempVideo -> VideoId){ //check if equal to video id in linked list
                    	b2 = true;
                        cout << "Movie Title: " << tempVideo -> MovieTitle << endl;
                        cout << "Number of copies: " << tempVideo -> Copies << endl;
                        if(tempVideo -> Copies == 0) break;
                        else tempVideo -> Copies -= 1;
                        push(video_id, tempChild -> RentVideoPtr);
                    }
                    tempVideo = tempVideo -> next;
                }
                if (b2 == false) cout << "\nInvalid video ID." << endl;
                cout << "\nRent another video? (Y/N) >> ";
                cin >> answer;
            }while(answer == 'y' || answer == 'Y');
            
        }
        tempCustomer = tempCustomer-> next;
    }
    
    if (b == false) {
		cout << "\nInvalid customer ID.\n" << endl; 
	}
    

    if(ChildHead ==  NULL){
        ChildHead = tempChild;
        return;
    }
    CustomerChild* last = ChildHead;
    while(last->next != NULL){
        last = last->next;
    }
    last->next = tempChild;
    
    cout << endl;
    system("pause");
}

//function that returns the video rented by the customer
void returnVideos(){
	RentedVideo obj;
	CustomerChild obj2;
	Customer* tempCustomer = front;
    CustomerChild* tempChild = ChildHead;
    bool b = false, b2 = false;
    int cid, position=0;
    system("cls");
    cout << "Enter customer ID: ";
    cin >> cid; cin.ignore();
    while(tempCustomer != NULL){ //iterate through customer queue
        if(cid == (tempCustomer -> CustomerId)){ 
            b = true;
			cout << "Name: " << tempCustomer -> CustomerName << endl;
            cout << "Address: " << tempCustomer -> Address << endl << endl;
            
			while(tempChild != NULL){ //iterate through customerchild
				++position;
				if (cid == (tempChild -> RentId)){
					b2 = true;
				    cout << "\nYou have rented...\n\n";
					RentedVideo* tempRent = tempChild -> RentVideoPtr;
					while(tempRent != NULL){//iterate through rented videos
					    cout << "Video ID: " << tempRent -> RentedVideoId << endl;
					    Video* tempVideo = VideoHead; 
						while(tempVideo != NULL){
							if ((tempRent -> RentedVideoId) == tempVideo -> VideoId){
							    tempVideo -> Copies += 1;
							    break;
							}
							tempVideo = tempVideo -> next;
						}
					    pop(tempRent);
					}
					removeRentId(position);	        
				}
				tempChild = tempChild -> next;
			}
		}
	    tempCustomer = tempCustomer-> next;
	}
	if (b == false) cout << "\nInvalid customer ID." << endl;
	
	if (b2 == false) cout << "\nNo rented videos." << endl;
	else cout << "\nVideos returned successfully." << endl;
	
	cout << endl;
	system("pause");
}

//function that displays the videos rented by a customer
void displayRentedVideos(){
	Customer* tempCustomer = front;
	CustomerChild* tempChild = ChildHead;
    bool b = false, b2 = false;
    int cid;
    system("cls");
    cout << "Enter customer ID: ";
    cin >> cid; cin.ignore();
    while(tempCustomer != NULL){ //iterate through customer queue
        if(cid == (tempCustomer -> CustomerId)){ 
        	b = true;
            cout << "Name: " << tempCustomer -> CustomerName << endl;
            cout << "Address: " << tempCustomer -> Address << endl;
			while(tempChild != NULL){ //iterate through customerchild
				if (cid == (tempChild -> RentId)){
					b2 = true;
				    cout << "\nLIST OF RENTED VIDEOS\n\n";
				    cout << left << setw(35) << "Video ID"  
         				 << left << setw(35) << "Movie Title\n" << endl;
         				 RentedVideo* tempRent = tempChild -> RentVideoPtr;
					     while(tempRent != NULL){//iterate through rented videos
					         cout << left << setw(35) << tempRent -> RentedVideoId;
					    	 Video* tempVideo = VideoHead;
					         while(tempVideo != NULL){
						         if ((tempRent -> RentedVideoId) == tempVideo -> VideoId){
						        	 cout << left << setw(35) << tempVideo -> MovieTitle << endl;
						        	 break;
								 }
								 tempVideo = tempVideo -> next; 
							 }
							 tempRent = tempRent -> next;
						 }
				 }
				 	 
				 tempChild = tempChild -> next;       
				}
				
			}
		tempCustomer = tempCustomer-> next;
	}
	if (b == false) cout << "\nInvalid customer ID." << endl;
	if (b == true && b2 == false) cout << "\nNo rented videos." << endl;
	cout << endl;
	system("pause");
}

//function that updates the text file of customers
void updateCustomerFile(){
	fstream write;
	write.open("Customer.txt", ios :: out);
	Customer* temp = front;
    while(temp != NULL){
        write << "Customer ID: " << temp -> CustomerId << endl
             << "Name: " << temp -> CustomerName << endl
             << "Address: " << temp -> Address << endl << endl;
        temp = temp -> next;
    }
    write.close();
}

//function that updates the text file of videos
void updateVideoFile(){
	fstream write;
	write.open("Video.txt", ios::out);
	Video* temp = VideoHead;
    while(temp != NULL){
        write << "Video ID: " << temp -> VideoId << endl
             << "Movie: " << temp -> MovieTitle << endl 
             << "Genre: " << temp -> Genre << endl
             << "Production: " << temp -> Production << endl 
			 << "Copies: "<< temp -> Copies << endl << endl;
        temp = temp -> next;
    }
    write.close();
}

//function that updates the text file of customers who rented videos
void updateRentFile(){
	fstream write;
	write.open("Customer-Rent.txt", ios::out);
    CustomerChild* tempChild = ChildHead;
    
    while(tempChild != NULL){
    	Customer* tempCustomer = front;
    	while(tempCustomer != NULL){
	        if(tempCustomer -> CustomerId == tempChild -> RentId){ 
	        	write << "Customer ID: " << tempChild -> RentId << endl
					  << "Name: " << tempCustomer -> CustomerName << endl
	            	  << "Address: " << tempCustomer -> Address << endl;
	            
	            break;
			}
			tempCustomer = tempCustomer-> next;
		}
		RentedVideo* tempRent = tempChild -> RentVideoPtr;
		while(tempRent != NULL){ //iterate through rented videos
			write << "Video ID: " << tempRent -> RentedVideoId << endl;
			tempRent = tempRent -> next;
	    }
	    write << endl;
		tempChild = tempChild -> next;	
	}
	write.close();
}

//function that deletes the captions in the text file
string Video::eraseMovieAndGenre(string str){
    // Deletes 7 characters from index number 0
    str.erase(0, 7);
    return str;
}

//function that deletes the captions in the text file
string Video::eraseProduction(string str){
    // Deletes 12 characters from index number 0
    str.erase(0, 12);
    return str;
}

//function that deletes the captions in the text file
int Video::extractIntegerWords(string str){
    stringstream ss;    
  
    /* Storing the whole string into string stream */
    ss << str;
  
    /* Running loop till the end of the stream */
    string temp;
    int found;
    while (!ss.eof()) {
  
        /* extracting word by word from stream */
        ss >> temp;
  
        /* Checking the given word is integer or not */
        if (stringstream(temp) >> found)
            //cout << found << " ";
  
        /* To save from space at the end of string */
        temp = "";
    }
    return found;
}

//function that reads from the video text file
void Video::readVideoFile(){
    fstream file;
    int numchecker;
    string str, garbage;
    file.open("Video.txt", ios::in);
    while(true){
        if(file.eof()){
            break;
        }
        Video* temp = new Video();
        getline(file, str);
        numchecker = extractIntegerWords(str);
        if (numchecker == 0){break;	}
        temp -> VideoId = numchecker;
        getline(file, temp -> MovieTitle); 
        temp -> MovieTitle = eraseMovieAndGenre(temp -> MovieTitle);
        getline(file, temp -> Genre);
        temp -> Genre = eraseMovieAndGenre(temp -> Genre);
        getline(file, temp -> Production);
        temp -> Production = eraseProduction(temp -> Production);
        getline(file, str);
        temp -> Copies = extractIntegerWords(str);
        getline(file, garbage);
        temp -> next = NULL;
        
        //organizing nodes of linked list
        if(VideoHead ==  NULL){
            VideoHead = temp;
            ++size;
        }
        else{
            Video* last = VideoHead;
            while(last->next != NULL){
                last = last->next;
            }
            last->next = temp;
            ++size;
        }
    }
    file.close(); 
}

//function that adds a new video to the linked list
void Video::insertVideo(){
    Video* temp = new Video();
    char ans;
    system("cls");
    do{
	    temp -> VideoId = ++size;
	    cout << "Video ID: " << temp -> VideoId << endl;
	    cout << "Movie Title: ";
	    getline(cin, temp -> MovieTitle);
	    cout << "Genre: ";
	    getline(cin, temp -> Genre);
	    cout << "Production: ";
	    getline(cin, temp -> Production);
	    cout << "Number of copies: ";
	    cin >> temp -> Copies;
	    temp -> next = NULL;
	
	    if(VideoHead ==  NULL){
	        VideoHead = temp;
	        return;
	    }
	    Video* last = VideoHead;
	    while(last->next != NULL){
	        last = last->next;
	    }
	    last->next = temp;
	    
	    cout << "\nAdd another one? (Y/N) >> ";
	    cin >> ans;
        cin.ignore();
	    
	}while(ans == 'y' || ans == 'Y');
}

//function that displays all the videos available
void Video::displayAllVideos(){
	system("cls");
    Video* temp = VideoHead;
    cout << left << setw(45) << "Video ID"  
         << left << setw(45) << "Movie Title" 
         << left << setw(45) << "Genre" 
         << left << setw(45) << "Production" << endl << endl;
    while(temp != NULL){
        cout << left << setw(45) << temp -> VideoId
             << left << setw(45) << temp -> MovieTitle 
             << left << setw(45) << temp -> Genre 
             << left << setw(45) << temp -> Production << endl << endl;
        temp = temp -> next;
    }
    cout << endl;
    system("pause");
}

//function that shows the details of a specific video
void Video::showVideoDetails(){
	Video* temp = VideoHead;
	bool found = false; 
	int id;
    system("cls");
	cout << "Enter Video ID: ";
	cin >> id; cin.ignore();
	while(temp !=NULL){
    if(id == (temp -> VideoId)){
    	found = true;
    	cout << "\nMovie Title: " << temp -> MovieTitle 
    	     << "\nGenre: " << temp -> Genre
    	     << "\nProduction: " << temp -> Production 
    	     << "\nNumber of Copies: " << temp -> Copies << endl;
    }
    temp = temp -> next;
}
   if(found==false)cout << "\nInvalid video ID." << endl;
    cout << endl;
    system("pause");  
}

//function that checks if a video is available
void Video::checkVideoAvailability(){
   	Video* temp = VideoHead;
	bool found = false; 
	int id;
    system("cls");
	cout << "Enter Video ID: ";
	cin >> id; cin.ignore();
	while(temp !=NULL){
	    if(id == (temp -> VideoId)){
	    	found = true;
	    	cout << "\nMovie Title: " << temp -> MovieTitle 
	    	     << "\nGenre: " << temp -> Genre
	    	     << "\nProduction: " << temp -> Production 
	    	     << "\nNumber of Copies: " << temp -> Copies << endl;
	    	     
	    	if(temp -> Copies > 0) cout << "Availabity: Available" << endl;
			else cout << "Availabity: Not Available" << endl;
			
	    }	
    	temp = temp -> next;
	}
  
    if(found==false)cout << "\nInvalid video ID." << endl;
    cout << endl;
    system("pause");  
}

//function that deletes the captions in the text file
string Customer::eraseName(string str){
    // Deletes 6 characters from index number 0
    str.erase(0, 6);
    return str;
}

//function that deletes the captions in the text file
string Customer::eraseAddress(string str){
    // Deletes 9 characters from index number 0
    str.erase(0, 9);
    return str;
}

//function that deletes the captions in the text file
int Customer::extractIntegerWords(string str){
    stringstream ss;    
  
    /* Storing the whole string into string stream */
    ss << str;
  
    /* Running loop till the end of the stream */
    string temp;
    int found;
    while (!ss.eof()) {
  
        /* extracting word by word from stream */
        ss >> temp;
  
        /* Checking the given word is integer or not */
        if (stringstream(temp) >> found)
            //cout << found << " ";
  
        /* To save from space at the end of string */
        temp = "";
    }
    return found;
}

//function that reads from the customer text file
int Customer::readCustomer(){
    fstream file;
    string str, garbage;
    int numchecker;
    file.open("Customer.txt", ios::in);
    while(true){
        if(file.eof()){
            break;
        }
        Customer* temp = new Customer();
        getline(file, str);
        numchecker = extractIntegerWords(str);
        if (numchecker == 0) {break;	}
        temp -> CustomerId = numchecker;
        getline(file, temp -> CustomerName);
        temp -> CustomerName = eraseName(temp -> CustomerName);
        getline(file, temp -> Address);
        temp -> Address = eraseAddress(temp -> Address);
        getline(file, garbage);
        temp -> next = NULL;

        if(front == NULL && rear == NULL){
            front = rear = temp;
        }
        else{
            rear -> next = temp;
            rear = temp;
        }
        ++sizeC;
    }
    
    file.close();
    return sizeC;
}

//function that adds a new customer to the queue
void Customer::enqueueCustomer(int size, int add){
    Customer* temp = new Customer();
    size += add;
    temp -> CustomerId = size;
    cout << "Customer ID: " << temp -> CustomerId << endl;
    cout << "Name: ";
    getline(cin, temp -> CustomerName);
    cout << "Address: ";
    getline(cin, temp -> Address);
    temp -> next = NULL;

    if(front == NULL && rear == NULL){
        front = rear = temp;
        return;
    }
    rear -> next = temp;
    rear = temp;
}

//function that displays all the customer in a queue
void Customer::displayAllCustomer(){
    Customer* temp = front;
    system("cls");
    cout << left << setw(45) << "Customer ID"  
         << left << setw(45) << "Name" 
         << left << setw(45) << "Address" << endl << endl;
    while(temp != NULL){
        cout << left << setw(45) << temp -> CustomerId
             << left << setw(45) << temp -> CustomerName 
             << left << setw(45) << temp -> Address << endl << endl;
        temp = temp -> next;
    }
    system("pause");
}

//function that reads from the text file of customer who rented videos
void CustomerChild::readCustomerRent(){
	int numchecker;
	string str, garbage;
	fstream read;
	read.open("Customer-Rent.txt", ios :: in);
	//CustomerChild* temp = new CustomerChild();
    //temp -> RentVideoPtr = NULL;
	while (true){ 
		if(read.eof()){
            break;
        }
        CustomerChild* temp = new CustomerChild();
        temp -> RentVideoPtr = NULL;
		getline(read, str);
		numchecker = extractIntegerWords(str);
		if (numchecker == 0) {break; }
		temp -> RentId = numchecker;
		getline(read, garbage);
		getline(read, garbage);
		while (true){
			getline(read, str);
			numchecker = extractIntegerWords(str);
			if (numchecker == 0) {break;}
			push(numchecker, temp -> RentVideoPtr);
		}
		
		temp -> next = NULL;
		
	if(ChildHead ==  NULL){
        ChildHead = temp;

    }
    else{
        CustomerChild* last = ChildHead;
        while(last->next != NULL){
            last = last->next;
        }
        last->next = temp;
    }
	}		
	read.close();
}

int customer_menu(int s, int ac){
	int ch;
    Customer customer;
    Video video;
    do{
    	system("cls");
        cout << "\n[1]Add New Customer\n";
        cout << "[2]Show Customer Details\n";
        cout << "[3]List of Videos Rented by a Customer\n";
        cout << "[4]Return to Main Menu\n\n";
        cout << "Enter choice: "; cin >> ch; cin.ignore();
        switch(ch){
            case 1:
            	++ac;
                customer.enqueueCustomer(s, ac);
                break;
            case 2:
                customer.displayAllCustomer();
                break;
            case 3:
                displayRentedVideos();
                break;
			case 4:
				return ac;   
        }
    }while(true);
}

int main(){
    int choice, customersize, addc, addc2 = 0;
    Customer customer;
    CustomerChild rent;
    Video video;
    video.readVideoFile();
    customersize = customer.readCustomer();
    rent.readCustomerRent();
    do{
    	cout << "=============================================" << endl;
	 	cout << "||               VIDEO STORE               ||" << endl;    
		cout << "=============================================" << endl;
        cout << "\n[1] New Video" << endl;
        cout << "[2] Rent a Video"<< endl;
        cout << "[3] Return a Video"<< endl;
        cout << "[4] Show Video Details"<< endl;
        cout << "[5] Display All Videos" << endl;
        cout << "[6] Check Video Availability"<< endl;
        cout << "[7] Customer Maintenance"<< endl;
        cout << "[8] Save and exit"<< endl;
        cout << "\nEnter choice: "; cin >> choice; cin.ignore();
        switch(choice){
            case 1: //adding a new video to the store
                video.insertVideo();
                break;
            case 2: //for renting a video, decreases the number of copies
            	rentVideo();
                break;
            case 3: //returns rented videos, increases the number of copies
            	returnVideos();
                break;
            case 4: //shows the details of a specific video
            	video.showVideoDetails();
                break;
            case 5: //displays all videos in the store whether it's available or not
                video.displayAllVideos();
                break;
            case 6: //check if a video is available
            	video.checkVideoAvailability();
                break;
            case 7: // addc and addc2 is for organizing the number of new customers
            	addc = addc2;
            	addc2 = customer_menu(customersize, addc);
                break;
            case 8: //updates and saves files
            	updateCustomerFile();
            	updateVideoFile();
            	updateRentFile();
            	cout << "\nData successfully saved!" << endl;
            	exit(0);
                break;
        }
        
        system("cls");
        
    }while(true);
}

