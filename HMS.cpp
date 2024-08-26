#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <string>
using namespace std;
#define N 10

struct Precord
{
	char pname[50], gender[10], dincharge[50], phonenum[20], medicalhistory[300];
	double ppayment;
};

struct Appointment
{
    string patientName;
    string date;
    string time;
    bool isAvailable;
};

Appointment appointments[N];  // Use an array of Appointments

void BillingandPayment();
void PatientManagement();
void AppointmentScheduling();
void saveAppointmentsToFile();
void loadAppointmentsFromFile();
void scheduleAppointment();
void rescheduleAppointment();
void cancelAppointment();


main() {
	string username = "Admin";
	string password = "admin123";
	string APusername;
	string APpassword;
	
	cout << "Welcome to Healthcare Patient Management System\n";
	cout << "---------------------------------------------------------\n";
	
	// Username loop
	while (true) {
	    cout << "Enter username: ";
	    cin >> APusername;
	
	    if (APusername != username) {
	        cout << "Invalid username. Please try again." << endl;
	    } else {
	        cout << "Welcome, " << username << "!" << endl;
	        break;
	    }
	}
	
	// Password loop
	for (int tries = 1; tries <= 3; tries++) {
	    cout << "Enter password: ";
	    cin >> APpassword;
	
	    if (APpassword == password) {
	        cout << "Login successful!" << endl;
	        break;
	    } else {
	        cout << "Invalid password. Attempt " << tries << " of 3." << endl;
	
	        if (tries == 3) {
	            cout << "Maximum login attempts reached. Reset your password." << endl;
	            cout << "Enter a new password: ";
	            cin >> password;
	            cout << "Password reset successfully!" << endl;
	            tries = 0;
	        }
	    }
	}

	// Display the Dashboard
	int choice;
	while (true) {
		cout << "---------------------------------------------------------";
	    cout << "\nDashboard:\n";
	    cout << "1. Doctor and staff management\n";
	    cout << "2. Billing and Payments\n";
	    cout << "3. Patient management\n";
	    cout << "4. Appointment scheduling\n";
	    cout << "5. Exit\n"; 
	    cout << "Enter your choice: ";
	    cin >> choice;
	    cin.ignore();
	    
	    switch(choice)
	    {
	    	case 2: BillingandPayment(); break;
	    	case 3: PatientManagement(); break;
	    	case 4: AppointmentScheduling(); break;
		 	case 5: cout<<"------------------------------------------------------------\nThanks for using the system."; return 0; break;
		}
	 }  
}

void AppointmentScheduling()
{	
	loadAppointmentsFromFile();  // Load existing appointments from file

    int choice;

    while (true)
    {
        cout << "\nAppointment Scheduling System" << endl;
        cout << "---------------------------------------------------" << endl;
        cout << "1. Schedule Appointment" << endl;
        cout << "2. Reschedule Appointment" << endl;
        cout << "3. Cancel Appointment" << endl;
        cout << "0. Exit" << endl;
        cout << "---------------------------------------------------" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore();  // Consume the newline character left by cin

        switch (choice)
        {
        case 1:
            scheduleAppointment();
            break;
        case 2:
            rescheduleAppointment();
            break;
        case 3:
            cancelAppointment();
            break;
        case 0:
            saveAppointmentsToFile();  // Save the appointments before exiting
            return ;
        default:
            cout << "\nInvalid choice. Please enter a valid option." << endl;
        }
    }

    return ;
}

void saveAppointmentsToFile()
{
	ofstream saveFile;
	saveFile.open("appointment.txt");
	
    if (!saveFile.is_open())                  
    {
        cout << "Error opening file for writing." << endl;
        return;
    }

    for (int i = 0; i < N; ++i)
    {
        saveFile << appointments[i].patientName << " " << appointments[i].date << " " << appointments[i].time << " " << appointments[i].isAvailable << endl;
    }   
                    
    saveFile.close();
}

void loadAppointmentsFromFile()
{
	ifstream readFile;
	readFile.open("appointment.txt");
	
	if(!readFile.is_open())
    {
        cout << "No existing appointments file found." << endl;
        return;
    }

    for (int i = 0; i < N; ++i)
    {
        readFile >> appointments[i].patientName >> appointments[i].date >> appointments[i].time >> appointments[i].isAvailable;
    }
    
    readFile.close();
}

void scheduleAppointment()
{
	for(int i = 0; i < N; i++)
	{
		if(!appointments[i].isAvailable)
        {
            cout << "Enter patient name: ";
            getline(cin, appointments[i].patientName);

            cout << "Enter appointment date (YYYY-MM-DD): ";
            cin >> appointments[i].date;

            cout << "Enter appointment time (HH:MM): ";
            cin >> appointments[i].time;

            appointments[i].isAvailable = true;

            saveAppointmentsToFile();  // Save the updated appointments to file

            cout << "\nAppointment scheduled successfully." << endl;
            return;  // Exit the function after scheduling an appointment
        }
    }

    cout << "All appointment slots are full. Cannot schedule a new appointment." << endl;
}

void rescheduleAppointment()
{
	int i;
    cout << "Enter patient index to reschedule (0 to " << N - 1 << "): ";
    cin >> i;
    
    if(i >= 0 && i < N)
    {                                                                        	
        cout << "Enter new appointment date: ";
        cin >> appointments[i].date;

        cout << "Enter new appointment time: ";
        cin >> appointments[i].time;

        saveAppointmentsToFile();  // Save the updated appointments to file

        cout << "\nAppointment rescheduled successfully." << endl;
    }
    else
    {
        cout << "Invalid index. Please enter a valid index for rescheduling." << endl;
    }
}

void cancelAppointment()
{
	int i;
	cout << "Enter patient index to cancel (0 to " << N - 1 << "): ";
	cin >> i;
		
	if(i >= 0 && i < N)
	{
		appointments[i].isAvailable = false;
			
		saveAppointmentsToFile(); //Save the updated appointment to file
		
		cout << "\tAppointment cancelled successfully." << endl;
	}
	else
	{
		cout << "Invalid index. Please enter a valid index for cancellation." << endl;
	}
}

void BillingandPayment()
{
	struct Precord Patient[N];
	char targetName[50];
	int i=0, j, targetIndex=-1;
	
    ifstream getpatientinfo;
    getpatientinfo.open("newpatientinfo.txt");
    
	if (!getpatientinfo.is_open())
        cout<<"File not found."<<endl;
    else
	{
		while(getpatientinfo>>Patient[i].pname>>Patient[i].gender>>Patient[i].dincharge>>Patient[i].phonenum>>Patient[i].ppayment)
			i++;
				    
		getpatientinfo.close();
	}
	
	cout<<"---------------------------------------------------------\n";
	
	//find the patient name from txt file until its found
	do
	{
		cout<<"Enter the name of the patient : ";
		cin.getline(targetName, 50);
		
		for(j=0; j<i; j++)
		{
			if(strcmp(targetName, Patient[j].pname) == 0)
			{
				targetIndex = j;
				break;
			}
		}
		
		if(targetIndex > -1)
			break;
		else
			cout<<"Patient not found.";
	}while(targetIndex = -1);
	
	int paymethod;
	char paysuccessful[2], chgorccl[10], cashcancel[2];
	double cash, balance;
	bool changeEntered = false;
	bool endAction = false;
	
	cout<<"Paying Methods :"<<endl;
	cout<<"1 -> Cash"<<endl;
	cout<<"2 -> Debit/Credit Card"<<endl;
	cout<<"3 -> QR Pay"<<endl;
	cout<<"---------------------------------------------\n";
	
	cout<<Patient[targetIndex].pname<<"'s pay amount = RM "<<fixed<<setprecision(2)<<Patient[targetIndex].ppayment * 1.06<<endl;
	
	/* Payment methods loop. Only can choose 1, 2, 3. Other than that and when 'change' for changing payment method entered,
		the loop keeps continue.*/
	do 
	{
		cout<<"Enter your paying method : ";
		cin>>paymethod;
		cin.ignore();
		
		if(paymethod<1 || paymethod >3) // Loop for incorrect input of payment methods
			cout<<"This method is not available. Re-";
		else
		{
			
			if(paymethod == 1) // pay by cash
			{
				do //do-while loop for cash amount less than the total amount the patient need to pay
				{
					cout<<"Amount of cash : RM ";
					cin>>cash;
					cin.ignore();			
				
					if(cash < Patient[targetIndex].ppayment * 1.06)
					{
						cout<<"Insufficient amount of cash. Please change to other methods or Cancel payment.\n";
						cout<<"Enter 'change' or 'cancel' : "; // change other payment methods or cancel payment
						cin.getline(chgorccl, 10);
						 
						if(strcmp(chgorccl, "cancel") == 0){
							endAction = true;
							break;
						}
						else if(strcmp(chgorccl, "change") == 0){
							changeEntered = true;
							break;
						}
						else;						
					}
					else break;
				}while(cash < Patient[targetIndex].ppayment * 1.06);
			}			
			
			else if(paymethod == 2 || paymethod == 3) // debit/credit card or QR pay
			{
				cout<<"Payment Successful?(Y/N) : "; // a way to verify the payment is successful or not
				cin.getline(paysuccessful, 2);
				
				paysuccessful[0] = toupper(paysuccessful[0]);
				
				if(strcmp(paysuccessful, "Y") == 0) //if payment successful, print invoice
					break;
					
				do // Change payment methods or cancel payment. The do-while loop is for input is other than 'change' or cancel'.
				{
					if(strcmp(paysuccessful, "N") == 0) //if payment is not successful
					{
						cout<<"Change other methods or Cancel payment?(change/cancel) : ";
						cin.getline(chgorccl, 10);
						if(strcmp(chgorccl, "cancel") == 0)
						{
							endAction = true;
							break;
						}
						else if(strcmp(chgorccl, "change") == 0)
							changeEntered = true;
						else;
					}
					else break;
				}while(strcmp(chgorccl, "change") != 0 && strcmp(chgorccl, "cancel") != 0);
					
				//if the input of 'Payment Successful?(Y/N)' is other than Y or N
				while(strcmp(paysuccessful, "Y") != 0 && strcmp(paysuccessful, "N") != 0)
				{
						cout<<"Successful or Not Successful?(Y/N) : ";
						cin.getline(paysuccessful, 2);
						paysuccessful[0] = toupper(paysuccessful[0]);
				}
			}
			else;
			
			if(endAction)
					break;
		}
	}while(paymethod<1 || paymethod>3 || changeEntered);
	
	if(endAction) // When 'cancel' entered, activity end.
		cout<<"Please pay next time.";
	else // else generate invoice
	{
		double balance;
	
		balance = cash - (Patient[targetIndex].ppayment * 1.06);
		
		ofstream paymentreceived;
		paymentreceived.open("payemnt report.txt", ios::app);
		
		paymentreceived<<"Patient Name\tReceived Amount(RM)\tPhone Number\n";
		paymentreceived<<"------------------------------------------------------\n";
		paymentreceived<<Patient[targetIndex].pname<<"\t\t"<<Patient[targetIndex].ppayment*1.06<<"\t\t\t"<<Patient[targetIndex].phonenum<<endl<<endl;
		
		paymentreceived.close();
		
		ofstream invoice;
		invoice.open("Invoice.txt", ios::app);
		
		invoice<<"------------------------------------------------------------\n";
		invoice<<"\n\t\t\t Invoice\n";
		invoice<<"------------------------------------------------------------\n";
		invoice<<"Patient Name\t\t\t: "<<Patient[targetIndex].pname<<endl;
		invoice<<"Total Amount\t\t\t: RM "<<Patient[targetIndex].ppayment<<endl;
		invoice<<"Total 6% service tax\t\t: RM "<<fixed<<setprecision(2)<<Patient[targetIndex].ppayment * 0.06<<endl;
		invoice<<"Grand Total Amount\t\t: RM "<<fixed<<setprecision(2)<<Patient[targetIndex].ppayment * 1.06<<endl;
		invoice<<"============================================================\n";
		switch (paymethod)
		{
			case 1: 
				invoice<<"Paid amount\t\t\t: RM "<<cash<<endl;
				invoice<<"Balance\t\t\t\t: RM "<<balance<<endl;
				invoice<<"Paying Method\t\t\t: Cash"<<endl;
				break;
			case 2:
				invoice<<"Paying Method\t\t\t: Debit/Credit Card"<<endl; break;
			case 3:
				invoice<<"Paying Method\t\t\t: QR Pay"<<endl; break;
		}
		invoice<<"============================================================\n";
		invoice<<"\t\t\t*APPROVED*\n";
		invoice<<"------------------------------------------------------------\n";
		
		invoice.close();
		
		cout<<"------------------------------------------------------------\n";
		cout<<"\n\t\t\t Invoice\n";
		cout<<"------------------------------------------------------------\n";
		cout<<"Patient Name\t\t\t: "<<Patient[targetIndex].pname<<endl;
		cout<<"Total Amount\t\t\t: RM "<<Patient[targetIndex].ppayment<<endl;
		cout<<"Total 6% service tax\t\t: RM "<<fixed<<setprecision(2)<<Patient[targetIndex].ppayment * 0.06<<endl;
		cout<<"Grand Total Amount\t\t: RM "<<fixed<<setprecision(2)<<Patient[targetIndex].ppayment * 1.06<<endl;
		cout<<"============================================================\n";
		switch (paymethod)
		{
			case 1: 
				cout<<"Paid amount\t\t\t: RM "<<cash<<endl;
				cout<<"Balance\t\t\t\t: RM "<<balance<<endl;
				cout<<"Paying Method\t\t\t: Cash"<<endl;
				break;
			case 2:
				cout<<"Paying Method\t\t\t: Debit/Credit Card"<<endl; break;
			case 3:
				cout<<"Paying Method\t\t\t: QR Pay"<<endl; break;
		}
		cout<<"============================================================\n";
		cout<<"\t\t\t*APPROVED*\n";
		cout<<"------------------------------------------------------------\n";
	}
}

void PatientManagement()
{
	struct Precord Patient[N];
	
	int choice;
	
	cout<<"1 -> Add new patient information\n";
	cout<<"2 -> Edit patient information\n";
	cout<<"--------------------------------------------------\n";
	cout<<"Enter you choice : ";
	cin>>choice;
	
	switch(choice)
	{
		//Add new patient information
		case 1:
		{
			int i, P;
			
			do
			{
				cout<<"Number of patient : ";
				cin>>P;
				cin.ignore();
				
				if(P<1)
					cout<<"Invalid number.\nPlease enter the correct ";
				else
					break;
			}while(P<1);
			
			//get patients information
			for(i=0; i<P; i++)
			{
				cout<<"Patient "<<i+1<<" Name\t\t\t: ";
				cin.getline(Patient[i].pname, 50);
				cout<<"Gender\t\t\t\t: ";
				cin.getline(Patient[i].gender, 10);
				cout<<"Doctor in charge\t\t: ";
				cin.getline(Patient[i].dincharge, 50);
				cout<<"Phone number\t\t\t: ";
				cin>>Patient[i].phonenum;
				cout<<"Patient payment(RM)\t\t: ";
				cin>>Patient[i].ppayment;
				cin.ignore();
				cout<<"Medical History\t\t\t: ";
				cin.getline(Patient[i].medicalhistory, 300);
				cout<<"-------------------------------------------------\n";
			}
			
			//file for recording patient information
			ofstream addpatient;
			addpatient.open("new patient information.txt", ios::app);
			
			for(i=0; i<P; i++)
			{
				addpatient<<"Patient Name\t\tGender\t\tDoctorInCharge\t\tPhoneNum\t\tAmount"<<endl;
				addpatient<<"---------------------------------------------------------------------------------------------------------\n";
				addpatient<<Patient[i].pname<<"\t\t";
				addpatient<<Patient[i].gender<<"\t\t";
				addpatient<<Patient[i].dincharge<<"\t\t";
				addpatient<<Patient[i].phonenum<<"\t\t";
				addpatient<<fixed<<setprecision(2)<<Patient[i].ppayment<<endl;
				addpatient<<"Medical History : "<<Patient[i].medicalhistory<<endl<<endl;
			}
			addpatient.close();
			
			//file for reading purpose
			ofstream patientinfo;
			patientinfo.open("newpatientinfo.txt", ios::app);
			for(i=0; i<P; i++)
			{
				patientinfo<<Patient[i].pname<<endl;
				patientinfo<<Patient[i].gender<<endl;
				patientinfo<<Patient[i].dincharge<<endl;
				patientinfo<<Patient[i].phonenum<<endl;
				patientinfo<<fixed<<setprecision(2)<<Patient[i].ppayment<<endl;
			}
			patientinfo.close();
			
			break;
		}
			
		//Edit existed patient information
		case 2:
		{
			char targetName[50];
			int j, i=0, targetIndex=-1;
			
		    ifstream patientFile;
			patientFile.open("newpatientinfo.txt");
		
		    if (!patientFile.is_open())
		    {
		        cout << "File not found. Exiting edit mode." << endl;
		        break;
		    }

		
		    // Read existing patient records from the file
		    while (patientFile >> Patient[i].pname >> Patient[i].gender >> Patient[i].dincharge >> Patient[i].phonenum >> Patient[i].ppayment)
		        i++;
		
		    patientFile.close();
		
		    // Allow the user to input the patient's name for editing
		    cout << "Enter the name of the patient you want to edit: ";
		    cin.ignore();
		    cin.getline(targetName, 50);
		
		    // Search for the specified patient
		    for (j = 0; j < i; j++)
		    {
		        if (strcmp(targetName, Patient[j].pname) == 0)
		        {
		            targetIndex = j;
		            break;
		        }
		    }
		
		    // If the patient is found, allow the user to edit information
		    if (targetIndex != -1)
		    {
		        cout << "Patient found. Enter new information:" << endl;
		        cout << "Gender\t\t\t\t: ";
		        cin.getline(Patient[targetIndex].gender, 10);
		        cout << "Doctor in charge\t\t: ";
		        cin.getline(Patient[targetIndex].dincharge, 50);
		        cout << "Phone number\t\t\t: ";
		        cin >> Patient[targetIndex].phonenum;
		        cout << "Patient payment(RM)\t\t: ";
		        cin >> Patient[targetIndex].ppayment;
		        cin.ignore();
		        cout << "Medical History\t\t\t: ";
		        cin.getline(Patient[targetIndex].medicalhistory, 300);
		
		        // Write all patient records back to the file
		        ofstream addpatient;
				addpatient.open("new patient information.txt", ios::trunc);
		
		        if (addpatient.is_open())
		        {
		            for (int j = 0; j < i; j++)
		            {
		            	addpatient << "Patient Name\t\tGender\t\tDoctorInCharge\t\tPhoneNum\t\tAmount" << endl;
		                addpatient << "---------------------------------------------------------------------------------------------------------\n";
		                addpatient << Patient[j].pname << "\t\t";
		                addpatient << Patient[j].gender << "\t\t";
		                addpatient << Patient[j].dincharge << "\t\t";
		                addpatient << Patient[j].phonenum << "\t\t";
		                addpatient << fixed << setprecision(2) << Patient[j].ppayment << endl;
		                addpatient << "Medical history : " << Patient[j].medicalhistory <<endl<<endl;
		            }
		            addpatient.close();
		            
		            ofstream addpat;
			        addpat.open("newpatientinfo.txt", ios::trunc);
		            for (j = 0; j < i; j++)
		            {
		                addpat<<Patient[j].pname<<endl;
		                addpat<<Patient[j].gender<<endl;
		                addpat<<Patient[j].dincharge<<endl;
		                addpat<<Patient[j].phonenum<<endl;
		                addpat<<fixed<<setprecision(2)<<Patient[j].ppayment<<endl;
		        	}
		        	addpat.close();
		        }
		        else
		            cout << "Error writing to file." << endl;
		    }
		    else
		        cout << "Patient not found." << endl;
		}
	}
}

 
