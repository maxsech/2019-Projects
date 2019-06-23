#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>   
#include <stdlib.h>

using namespace std;

void readDevice(void* data, int length);
void writeDevice(void* writeVal, int length);
void seekDevice(int offset, int whence);

int file;

int main()
{
	bool loop = true;

	file = open("/dev/simple_character_device", O_RDWR);

	while(loop)
	{
		cout << "===============================" << endl;
		cout << "Press r to read from the device" << endl;
		cout << "Press w to write to the device" << endl;
		cout << "Press s to seek into the device" << endl;
		cout << "Press e to exit from the device" << endl;
		cout << "===============================" << endl;

		char userChoice;

		cin >> userChoice;

		switch(userChoice)
		{
			case 'r':
			{
				size_t readSize;

				cout << "Enter the number of bytes you want to read:"<<endl;
				cin >> readSize;

				void* readData = malloc(readSize);
				readDevice(readData, readSize);

				char* convert = (char*)(readData);

				cout << "Data read from the device:" << endl;
				cout << convert << endl;
				break;
			}
			case 'w':
			{
				size_t writeSize;

				std::string input;
				cout << "Enter data you want to write to the device:"<<endl;
				getline(cin, input);
				getline(cin, input);

				char* input_c = (char*)input.c_str();
				void* writeData = input_c;

				writeDevice(writeData, input.size());
				break;
			}
			case 's':
			{
				off_t input;
				int whence;
				cout << "Enter an offset value:" << endl;
				cin >> input;
				cout << "Enter a whence value:" << endl;
				cin >> whence;

				switch(whence)
				{
					case 0:
						seekDevice(input, SEEK_SET);
						break;
					case 1:
						seekDevice(input, 1);
						break;
					case 2:
						seekDevice(input, SEEK_END);
						break;
					default:
						cout << "Invalid whence value." << endl;
						break;
				}

				break;
			}
			case 'e':
				loop = false;
				break;
			default:
				loop = true;
				break;
		}
	}

	close(file);

	return 0;
}

void readDevice(void* data, int length)
{
	cout << "Reading from device."<< endl;

	if(file < 0)
	{
		cout << "Error opening File" << endl;
	}

	ssize_t count = read(file, data, length);
	cout << "Read " << count << " bytes of data." << endl;
}

void writeDevice(void* writeVal, int length)
{
	cout << "Writing to device."<< endl;

	if(file < 0)
	{
		cout << "Error opening File" << endl;
	}

	ssize_t count = write(file, writeVal, length);
}

void seekDevice(int offset, int whence)
{
	cout << "Seeking into device."<< endl;

	if(file < 0)
	{
		cout << "Error opening File" << endl;
	}

	off_t output = lseek(file, offset, whence);
	cout << "offset now at: " << output << endl;

}