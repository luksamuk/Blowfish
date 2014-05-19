//
// Blowfish C++ implementation
//
// CC0 - PUBLIC DOMAIN
// This work is free of known copyright restrictions.
// http://creativecommons.org/publicdomain/zero/1.0/
//

#include "blowfish.h"
#include <cstdio>
#include <cstring>

void usage() {
	printf("Usage:\n\tblowfish file flag\n"
		   "file: full path of the file to be changed\n"
		   "flag: command to be executed\n"
		   "\t-e: Encrypts a file\n"
		   "\t-d: Decrypts a file\n");
}

int main(int argc, char** argv) {
	bool encrypt = true;
	bool collected = false;
	if(argc <= 2) {
		printf("Error: Unspecified file or procedure.\n");
		usage();
		return 1;
	}
	else {
		for(int i = 0; i < argc; i++) {
			if(!strcmp(argv[i], "-d")) {
				encrypt = false;
				collected = true;
				break;
			}
			else if(!strcmp(argv[i], "-e")) {
				encrypt = true;
				collected = true;
				break;
			}
		}
		if(!collected) {
			printf("Error: Unknown procedure.\n");
			usage();
			return 1;
		}
	}

	Blowfish blowfish;
	blowfish.SetKey("Ygj8*9P91#@l-");

	FILE* fp;
	fp = fopen(argv[1], "rb");
	if(!fp) {
		printf("Error: Can't open file.\n");
		usage();
		return 1;
	}

	fseek(fp, 0L, SEEK_END);
	long int filesize = ftell(fp);
	rewind(fp);

	printf("%s file %s with size %ld bytes:\n",
		(encrypt ? "Encrypting" : "Decrypting"),
		argv[1],
		filesize);
	printf("Copying data to memory...\n");
	char* buffer = new char[filesize];
	fread(buffer, filesize, 1, fp);
	fclose(fp);

	printf("Executing procedure...\n");
	if(encrypt)
		blowfish.Encrypt(buffer, buffer, filesize);
	else
		blowfish.Decrypt(buffer, buffer, filesize);

	printf("Saving file...\n");
	fp = fopen(argv[1], "wb");
	fwrite(buffer, filesize, 1, fp);
	printf("All done.\n");
	delete [] buffer;
	return 0;
}