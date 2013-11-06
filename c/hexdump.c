// --------------------------------------------------------------------------
int hexdump(const char* buf, int size)
{
	int k = 0;
	for (int i=0; i<size; ++i) {
		if (0 == i%16) {
			if (0 < i) {
				printf("| ");
				for (int j=k; j<i; ++j) {
					if(isprint(buf[j]))
						printf("%c", buf[j]);
					else
						printf(".");
				}
				k = i;
			}
			printf("\n%04x | ", i);
		}
		printf("%02x ", buf[i]);
	} // for

	// need to insert spaces when size%16 != 0
	for (int i=size%16; i%16; ++i) {
		printf("   ");
	}

	// now, finish up the line by prining the ascii for the tail
	printf("| ");
	for (int j=k; j<size; ++j) {
		if(isprint(buf[j]))
			printf("%c", buf[j]);
		else
			printf(".");
	}

	return 0;
}


#if 0
int hexdump(const char* buf, int size)
{
	int k = 0;
	for (int i=0; i<size; ++i) {
		if (0 == i%16) {
			if (0 < i) {
				printf("| ");
				for (int j=k; j<i; ++j) {
					if(isprint(buf[j]))
						printf("%c", buf[j]);
					else
						printf(".");
				}
				k = i;
			}
			printf("\n%04x | ", i);
		}
		printf("%02x ", buf[i]);
	} // for

	// need to insert spaces when size%16 != 0
	for (int i=size%16; i%16; ++i) {
		printf("   ");
	}

	// now, finish up the line by prining the ascii for the tail
	printf("| ");
	for (int j=k; j<size; ++j) {
		if(isprint(buf[j]))
			printf("%c", buf[j]);
		else
			printf(".");
	}

	return 0;
}
#endif

int listDirectory(const char* path)
{
	DIR* dir = 0;
	struct dirent* dirent = 0;
	char* dirname = 0;

	if (path) {
		dirname = (char*)path;
	} else {
		dirname = getcwd(dirname, 0);
	}

	if (!dirname) {
		perror("dirname()");
		goto exit;
	}

	dir = opendir(dirname);
	if (!dir) {
		perror("opendir()");
		goto exit;
	}

	//printf("\n%s\n", dirname);
	while (0 != (dirent=readdir(dir))) {
		if (dirent->d_name[0] != '.') {
			int len = strlen(dirname) + strlen(dirent->d_name);
			char* fullpath = new char[len +1];
			memset(fullpath, 0, len+1);
			strcpy(fullpath, dirname);
			strcat(fullpath, "/");
			strcat(fullpath, dirent->d_name);

			printf("%s", fullpath);

			// now, open each file,
			// read up to 256 bytes from the file into a buffer
			// and do a hex dump of the data.
			// this goes well beyond just a simple directory list.
			// in reality, this is where we would feed the content
			// of the file to the servo box(es). 
			FILE* file = fopen(fullpath, "r");
			if (file) {
				int bufsize = 256;
				char* buf = new char[bufsize];
				int count = fread(buf, 1, bufsize, file);
				hexdump(buf, count); // send buffer instead of hex dump.
				delete[] buf;
				fclose(file);
			}

			printf("\n");

			if (fullpath) delete[] fullpath;
		}
	}

exit:
	if (dir) closedir(dir);
	if (dirname && dirname != path) free(dirname);

	return 0;
}


