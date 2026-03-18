#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    if(sortCriteria > 4 || sortCriteria <= 0)
    {
        printf("Invalid");
        return;
    }
    for(int i=0;i<addressBook->contactCount-1;i++)
    {
        for(int j=i+1;j<addressBook->contactCount;j++)
        {
            Contact temp;
            if(sortCriteria == 1) //sort the contacts by name
            {
                if(strcmp(addressBook->contacts[i].name,addressBook->contacts[j].name) > 0)
                {
                    temp = addressBook->contacts[i];
                    addressBook->contacts[i] = addressBook->contacts[j];
                    addressBook->contacts[j] = temp;
                }
            }
            else if(sortCriteria == 2) //sort the contacts by phone
            {
                if(strcmp(addressBook->contacts[i].phone,addressBook->contacts[j].phone) > 0)
                {
                    temp = addressBook->contacts[i];
                    addressBook->contacts[i] = addressBook->contacts[j];
                    addressBook->contacts[j] = temp;
                }
            }
            else if(sortCriteria == 3) //sort the contacts by email
            {
                if(strcmp(addressBook->contacts[i].email,addressBook->contacts[j].email) > 0)
                {
                    temp = addressBook->contacts[i];
                    addressBook->contacts[i] = addressBook->contacts[j];
                    addressBook->contacts[j] = temp;
                }
            }

        }
    }
    printf("-------------------------------------------------------------------------\n");
    printf("%-10s %-20s %-20s %-20s\n","S.No","Name","Phone","Email");
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-10d %-20s %-20s %-20s\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        printf("-------------------------------------------------------------------------\n");
    }
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */

    Contact newone;
    printf("Enter Name: "); //new name
    scanf(" %[^\n]", newone.name);
    int ret = valid_name(newone.name,addressBook);
    if(ret == 0)
    {
        printf("Invalid or Duplicate Data:");
        return;
    }
    printf("Enter Phone: "); //add phone number
    scanf(" %s", newone.phone);
    int retp = valid_phone(newone.phone,addressBook);
    if(retp == 0)
    {
        printf("invalid or Duplicate Data");
        return;
    }
    printf("Enter Email: "); //add email
    scanf(" %s", newone.email);
    int rete = valid_email(newone.email,addressBook);
    if(rete == 0)
    {
        printf("invalid or Duplicate Data");
        return;
    }
    
    addressBook->contacts[addressBook->contactCount] = newone;
    addressBook->contactCount++;
    printf("Contact created successfully!\n");

}
int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */

    char name[20];
    char phone[20];
    char email[50];
    printf("1.Search by name\n2.Search by number\n3.Search by email\n");
    int choice;
    printf("Enter your choice:");
    scanf("%d",&choice);
    switch(choice)    //select the choice to search by name,phone,email.
    {
        case 1:
        printf("Enter the name to be searched:");
        scanf(" %[^\n]",name);
        for(int i=0;i<addressBook->contactCount;i++)
        {

            if(strcmp(name,addressBook->contacts[i].name)==0)
            {
                printf("-------------------------------------------------------------------------\n");
                printf("%-10s %-20s %-20s %-20s\n","S.No","Name","Phone","Email");
                printf("-------------------------------------------------------------------------\n");
                printf("%-10d %-20s %-20s %-20s\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("-------------------------------------------------------------------------\n");
                return i ;
            }
            
        }
        break;
        case 2:
        printf("Enter the number to be search: ");
        scanf(" %[^\n]",phone);
        for(int i=0;i<addressBook->contactCount;i++)
        {
            
            if(strcmp(phone,addressBook->contacts[i].phone)==0)
            {
                printf("-------------------------------------------------------------------------\n");
                printf("%-10s %-20s %-20s %-20s\n","S.No","Name","Phone","Email");
                printf("-------------------------------------------------------------------------\n");
                printf("%-10d %-20s %-20s %-20s\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("-------------------------------------------------------------------------\n");
                return i;
            }
            
        }
        break;
        case 3:
        printf("Enter the email to be searched:");
        scanf(" %[^\n]",email);
        for(int i=0;i<addressBook->contactCount;i++)
        {
           
            if(strcmp(email,addressBook->contacts[i].email)==0)
           {
                printf("-------------------------------------------------------------------------\n");
                printf("%-10s %-20s %-20s %-20s\n","S.No","Name","Phone","Email");
                printf("-------------------------------------------------------------------------\n"); 
                printf("%-10d %-20s %-20s %-20s\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                printf("-------------------------------------------------------------------------\n");
               return i;
            }
        
        }
        break;
        default:
        printf("INVALID CHOICE");
        return -1;
    }
    printf("Contact not found");
    return -1;
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int index = searchContact(addressBook); // search and get index
    if(index == -1)
    {
        return;
    }
    printf("Which data do you want to edit:\n");
    printf("1. Name\n2. Number\n3. Email\n");
    int choice;
    char word[50]; // input buffer
    printf("Enter your choice: "); 
    scanf("%d", &choice);
    getchar(); // clear newline left in buffer

    int valid;
    switch(choice)
    {
        case 1:
            printf("Enter the new name: ");
            scanf(" %[^\n]", word);
            valid = valid_name(word, addressBook);
            if(valid == 0)
            {
                printf("Invalid or duplicate data\n");
                return;
            }
            strcpy(addressBook->contacts[index].name, word);
            break;

        case 2:
            printf("Enter the new number: ");
            scanf(" %[^\n]", word);
            valid = valid_phone(word, addressBook);
            if(valid == 0)
            {
                printf("Invalid or duplicate data\n");
                return;
            }
            strcpy(addressBook->contacts[index].phone, word);
            break;

        case 3:
            printf("Enter the new email: ");
            scanf(" %[^\n]", word);
            valid = valid_email(word, addressBook);
            if(valid == 0)
            {
                printf("Invalid or duplicate data\n");
                return;
            }
            strcpy(addressBook->contacts[index].email, word);
            break;

        default:
            printf("Invalid input\n");
            return;
    }

    printf("Contact modified successfully\n");
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int index = searchContact(addressBook);
    if(index == -1)//search and get index
    {
        return;
    }
    for (int i = index; i < addressBook->contactCount - 1; i++)//loop runs and remove the contact
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;
    printf("Contact deleted successfully\n");
} 


int valid_name(char *name,AddressBook *addressBook)
{
    // check invalid and duplicate values
    int i = 0;
    while(name[i] != '\0')
    {
        char ch = name[i];
        if(!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == ' ')))  //check character is present or not
        {
            return 0;
        }
        i++;
    }
    for(int i = 0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].name,name) == 0)  //check the duplicate names using strcmp
        {
            return 0;
        }
    
    }
    return 1;
}

int valid_phone(char phone[],AddressBook *addressBook)
{
    int i = 0;
    while(phone[i] != '\0') //find lenght of the phone
    {
        i++;
    }
    if(i != 10)
    {
        return 0;
    }
    for(int i=0;i<10;i++) //check it only contains number 
    {
        char ch = phone[i];
        if(!(ch >= '0' && ch <= '9'))
        {
            return 0;
        }
    }
    for(i=0;i<addressBook->contactCount;i++) //check the duplicate
    {
        if(strcmp(addressBook->contacts[i].phone,phone) == 0)
        {
            return 0;
        }
    }
    return 1;
}
int valid_email(char *email, AddressBook *addressBook) 
{
    int len = strlen(email);
    char *at = strchr(email, '@');     
    char *dot = strrchr(email, '.');   
    for(int i=0;i<len;i++)
    {
        if(!((email[i] >= 'a' && email[i] <= 'z') ||(email[i] == '@' || email[i] == '.') || (email[i] >= '0' && email[i] <= '9')))
        {
            printf("Invalid Not characters present\n");//check for alphanumaeric if not return 0;
            return 0;
        }
    }     
    if (at == NULL || strchr(at + 1, '@') != NULL || dot == NULL) 
    {
        printf("Invalid input must contain only one '@' and '.'\n"); //check @ and . is present or not
        return 0;
    }
    if(at > dot || dot - at < 2)
    {
        printf("Invalid input character must present between '@' and '.'\n"); //check character present inbetween @ and .
        return 0;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0) //check for duplicte values
        {
            return 0; 
        }
    }

    return 1;
}
